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

#include <linux/module.h>
#include <linux/if_vlan.h>
#include <linux/poll.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/skb_hook.h>

#include "sx.h"
#include "alloc.h"
#include "cq.h"
#include "dq.h"
#include "sx_proc.h"
#include "sgmii.h"
#include "ptp.h"
#include "sx_clock.h"
#include "ber_monitor.h"
#include "sx_dbg_dump_proc.h"
#include "dev_init.h"
#include "dev_db.h"
#include "emad.h"
#include "health_check.h"
#include "synce.h"
#include "qos_emad.h"

#ifdef CONFIG_44x
#include <asm/dcr.h>
#include <asm/dcr-regs.h>
#include <asm/reg.h>
#endif

/************************************************
 *  Global
 ***********************************************/
#ifdef CONFIG_SX_DEBUG
int sx_debug_level;
#endif
/************************************************
 *  Define
 ***********************************************/

#ifndef BUILD_VERSION
#define BUILD_VERSION ""
#endif

#define SX_CORE_CHAR_DEVICE_NAME "sxcdev"
#define SX_CORE_DRV_VERSION      "2.00 " BUILD_VERSION
static const char sx_version[] =
    DRV_NAME ": NVIDIA Switch Core Driver "
    SX_CORE_DRV_VERSION " (" DRV_RELDATE ")\n";

#define MCION_MODULE_STATUS_BITS_PRESENT_MASK         0x1
#define MCION_MODULE_STATUS_BITS_LOW_POWER_MASK       (1 << 8)
#define MLXSW_REG_PMMP_EEPROM_OVERRIDE_LOW_POWER_MASK (1 << 8)
#define MODULE_SENSOR_BASE                            (64)
#define SX_CORE_TX_SKB_CB(skb) (*((struct sx_rsc **)(skb)->cb))

/************************************************
 *  Enum
 ***********************************************/
enum SX_CHAR_DEVICE {
    SX_MAJOR      = 230, /* New OFED drivers consume major:231/minor:192 (range of 64 devices) */
    SX_BASE_MINOR = 0,
};
dev_t             char_dev;
struct sx_globals sx_glb;

/************************************************
 *  MODULE settings
 ***********************************************/
MODULE_AUTHOR("Amos Hersch, Anatoly Lisenko");
MODULE_DESCRIPTION("NVIDIA Switch driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(SX_CORE_DRV_VERSION);

int i2c_mode = 0;
module_param_named(i2c_mode, i2c_mode, int, 0644);
MODULE_PARM_DESC(i2c_mode, "Driver is using I2C as its main bus");

int mst_mode = 0;
module_param_named(mst_mode, mst_mode, int, 0644);
MODULE_PARM_DESC(mst_mode, "Driver is using MST protocol");

int cq_thread_sched_priority = 0;
module_param_named(cq_thread_sched_priority, cq_thread_sched_priority, int, 0644);
MODULE_PARM_DESC(cq_thread_sched_priority, "CQ credit thread real time priority");

int rx_debug;
module_param_named(rx_debug,
                   rx_debug, int, 0644);
MODULE_PARM_DESC(rx_debug, "en/dis dump of pkts");

int rx_debug_pkt_type = SX_DBG_PACKET_TYPE_ANY;
module_param_named(rx_debug_pkt_type,
                   rx_debug_pkt_type, int, 0644);
MODULE_PARM_DESC(rx_debug_pkt_type, "trap/synd number to dump, 0xff dump all pkts");

int rx_cqev2_dbg;
module_param_named(rx_cqev2_dbg,
                   rx_cqev2_dbg, int, 0644);
MODULE_PARM_DESC(rx_cqev2_dbg, "en/dis RX CQEv2 debug");

int rx_debug_emad_type = SX_DBG_EMAD_TYPE_ANY;
module_param_named(rx_debug_emad_type,
                   rx_debug_emad_type, int, 0644);
MODULE_PARM_DESC(rx_debug_emad_type, "emad number to dump, 0xffff dump all pkts");

int tx_debug;
module_param_named(tx_debug,
                   tx_debug, int, 0644);
MODULE_PARM_DESC(tx_debug, "en/dis dump of pkts");

int tx_debug_pkt_type = SX_DBG_PACKET_TYPE_ANY;
module_param_named(tx_debug_pkt_type,
                   tx_debug_pkt_type, int, 0644);
MODULE_PARM_DESC(tx_debug_pkt_type, "trap/synd number to dump, 0xff dump all pkts");

int tx_debug_emad_type = SX_DBG_EMAD_TYPE_ANY;
module_param_named(tx_debug_emad_type,
                   tx_debug_emad_type, int, 0644);
MODULE_PARM_DESC(tx_debug_emad_type, "emad type to dump, 0xff dump all emads");

int rx_dump;
module_param_named(rx_dump,
                   rx_dump, int, 0644);
MODULE_PARM_DESC(rx_dump, " 0- don't dump, 1-dump the RX packet data");

int rx_dump_cnt = SX_DBG_COUNT_UNLIMITED;
module_param_named(rx_dump_cnt,
                   rx_dump_cnt, int, 0644);
MODULE_PARM_DESC(rx_dump_cnt, " 0xFFFF - unlimited, dump CNT packets  only");

int tx_dump;
module_param_named(tx_dump,
                   tx_dump, int, 0644);
MODULE_PARM_DESC(tx_dump, " 0- don't dump, 1-dump the TX packet data");

int tx_dump_cnt = SX_DBG_COUNT_UNLIMITED;
module_param_named(tx_dump_cnt,
                   tx_dump_cnt, int, 0644);
MODULE_PARM_DESC(tx_dump_cnt, " 0xFFFF - unlimited, dump CNT packets  only");

int i2c_cmd_dump;
module_param_named(i2c_cmd_dump,
                   i2c_cmd_dump, int, 0644);
MODULE_PARM_DESC(i2c_cmd_dump, " 0- don't dump, 1-dump i2c data");

int i2c_cmd_op = SX_DBG_CMD_OP_TYPE_ANY;
module_param_named(i2c_cmd_op,
                   i2c_cmd_op, int, 0644);
MODULE_PARM_DESC(i2c_cmd_op, " cmd op to dump, 0xFFFF - dump all cmds");

int i2c_cmd_reg_id = SX_DBG_REG_TYPE_ANY;
module_param_named(i2c_cmd_reg_id,
                   i2c_cmd_reg_id, int, 0644);
MODULE_PARM_DESC(i2c_cmd_reg_id, " cmd reg_id to dump, 0xFFFF - dump all cmds");

int i2c_cmd_dump_cnt = SX_DBG_COUNT_UNLIMITED;
module_param_named(i2c_cmd_dump_cnt,
                   i2c_cmd_dump_cnt, int, 0644);
MODULE_PARM_DESC(i2c_cmd_dump_cnt, " print CNT commands and stop, 0xFFFF - don't stop");

int dis_vid2ip = 0;
module_param_named(dis_vid2ip,
                   dis_vid2ip, int, 0644);
MODULE_PARM_DESC(dis_vid2ip, " disable ip override");

int loopback_packets_counter = 0;
module_param_named(loopback_packets_counter,
                   loopback_packets_counter, int, 0644);
MODULE_PARM_DESC(loopback_packets_counter, "Loopback packets counter");

int fast_boot = 0;
module_param_named(fast_boot, fast_boot, int, 0444);
MODULE_PARM_DESC(fast_boot, "fast_boot enable/disable");

int skip_reset = 0;
module_param_named(skip_reset, skip_reset, int, 0644);
MODULE_PARM_DESC(skip_reset, "Skip reset on PCI probe");

int cpu_traffic_priority_active = 1;
module_param_named(cpu_traffic_priority_active, cpu_traffic_priority_active, int, 0644);
MODULE_PARM_DESC(cpu_traffic_priority_active, "enabled/disable built-in CPU CQ traffic priority");

int handle_monitor_rdq_in_timer = 1;
module_param_named(handle_monitor_rdq_in_timer, handle_monitor_rdq_in_timer, int, 0644);
MODULE_PARM_DESC(handle_monitor_rdq_in_timer, "enabled/disable handling Monitor CQs by timer thread");

int cpu_traffic_priority_disrupt_low_prio_upon_stress = 0;
module_param_named(cpu_traffic_priority_disrupt_low_prio_upon_stress,
                   cpu_traffic_priority_disrupt_low_prio_upon_stress,
                   int, 0644);
MODULE_PARM_DESC(cpu_traffic_priority_disrupt_low_prio_upon_stress,
                 "enabled/disable disrupt low priority traffic when high priority traffic is in load");

int cpu_traffic_priority_disrupt_low_prio_upon_stress_delay = 10;
module_param_named(cpu_traffic_priority_disrupt_low_prio_upon_stress_delay,
                   cpu_traffic_priority_disrupt_low_prio_upon_stress_delay,
                   int, 0644);
MODULE_PARM_DESC(cpu_traffic_priority_disrupt_low_prio_upon_stress_delay,
                 "msec to delay low priority thread when high priority traffic in load");

int cpu_traffic_tasklet_reschedule_enable = 1;
module_param_named(cpu_traffic_tasklet_reschedule_enable,
                   cpu_traffic_tasklet_reschedule_enable,
                   int, 0644);
MODULE_PARM_DESC(cpu_traffic_tasklet_reschedule_enable,
                 "enabled/disable reschedule of intr_tasklet_handler");

int enable_cpu_port_loopback = 0; /* ONLY FOR DEBUG */
module_param_named(enable_cpu_port_loopback, enable_cpu_port_loopback, int, 0644);
MODULE_PARM_DESC(enable_cpu_port_loopback, " Enable / Disable loopback on cpu port");

int enable_keep_packet_crc = 0; /* ONLY FOR DEBUG */
module_param_named(enable_keep_packet_crc, enable_keep_packet_crc, int, 0644);
MODULE_PARM_DESC(enable_keep_packet_crc, "Enable/Disable receiving RX packet including the CRC field");

int mon_cq_thread_cpu_util_percent = MON_CQ_HANDLER_THREAD_CPU_UTIL_PERCENT_DEFAULT;
module_param_named(mon_cq_thread_cpu_util_percent, mon_cq_thread_cpu_util_percent, uint, 0644);
MODULE_PARM_DESC(mon_cq_thread_cpu_util_percent, "mon_cq_thread_cpu_util_percent");

int enable_monitor_rdq_trace_points = 0;
module_param_named(enable_monitor_rdq_trace_points, enable_monitor_rdq_trace_points, int, 0644);
MODULE_PARM_DESC(enable_monitor_rdq_trace_points, "enabled/disable monitor RDQs trace points");

int sx_af_counters_dbg_info_gathering = 1;
module_param_named(sx_af_counters_dbg_info_gathering,
                   sx_af_counters_dbg_info_gathering, int, 0644);
MODULE_PARM_DESC(sx_af_counters_dbg_info_gathering,
                 " 0/1 - disable/enable gathering of Accumulated counters' debug info");

int sx_af_counters_dbg_info_print_in_hex = 0;
module_param_named(sx_af_counters_dbg_info_print_in_hex,
                   sx_af_counters_dbg_info_print_in_hex, int, 0644);
MODULE_PARM_DESC(sx_af_counters_dbg_info_print_in_hex,
                 " 0/1 - disable/enable printing of Accumulated counters' debug info in hex");

int eventlist_drops_global_counter = 0;
module_param_named(eventlist_drops_counter, eventlist_drops_global_counter, int, 0644);
MODULE_PARM_DESC(eventlist_drops_counter, "Event list drops counter");

static void sx_core_listeners_cleanup(void);

static void inc_eventlist_drops_global_counter(void);

/************************************************
 *  Functions
 ***********************************************/

bool sx_i2c_mode(void)
{
    return i2c_mode != 0;
}

bool sx_mst_mode(void)
{
    return mst_mode != 0;
}

bool sx_cr_mode(void)
{
    return (sx_i2c_mode() || sx_mst_mode());
}

int sx_core_skb_add_vlan(struct sk_buff **untagged_skb, uint16_t vid, uint16_t pcp)
{
    u32             vlan_hdr = cpu_to_be32((ETH_P_8021Q << 16) | ((pcp & 0x7) << 13) | (vid & 0xfff));
    struct sk_buff *skb = *untagged_skb, *new_skb = NULL;
    u8             *p_skb_data;

    if (skb_headroom(skb) < ISX_HDR_SIZE + VLAN_HLEN) {
        new_skb = alloc_skb(skb->len + ISX_HDR_SIZE + VLAN_HLEN, GFP_ATOMIC);
        if (!new_skb) {
            printk(KERN_ERR PFX "adding vlan to skb failed because of allocation\n");
            return -ENOMEM;
        }

        p_skb_data = skb_put(new_skb, skb->len + VLAN_HLEN);
        if (!p_skb_data) {
            kfree_skb(new_skb); /* drop packet flow, use kfree_skb */
            return -ENOMEM;
        }

        memcpy(p_skb_data, skb->data, 12); /* DMAC, SMAC */
        memcpy(p_skb_data + 12 + VLAN_HLEN, skb->data + 12, skb->len - 12); /* rest of the frame */

        consume_skb(skb);   /* free unused skb, use consume_skb */
        *untagged_skb = new_skb;
    } else {
        p_skb_data = skb_push(skb, VLAN_HLEN);
        memmove(p_skb_data, p_skb_data + VLAN_HLEN, 12); /* DMAC, SMAC */
    }

    memcpy(p_skb_data + 12, &vlan_hdr, VLAN_HLEN);
    return 0;
}
EXPORT_SYMBOL(sx_core_skb_add_vlan);


static inline void SX_CORE_REGISTER_FILTER_BITMASK_SET(u64 *arr, u32 num, int set)
{
    int idx = (num) / 64;
    u64 bit = (1ULL << ((num) % 64));

    if (set) {
        (arr)[idx] |= (bit);
    } else {
        (arr)[idx] &= ~(bit);
    }
}

static inline int SX_CORE_REGISTER_FILTER_BIT_IS_SET(u64 *arr, u32 num)
{
    int idx = (num) / 64;
    u64 bit = (1ULL << ((num) % 64));

    return ((arr)[idx] & (bit)) ? 1 : 0;
}

static inline void SX_CORE_REGISTER_FILTER_BITMASK_SET_ALL_ZERO(
    struct listener_register_filter_entry *register_filter_listener,
    u8                                     is_register)
{
    if (is_register) {
        register_filter_listener->is_global_register = 0;
        memset(register_filter_listener->ports_registers, 0, FROM_BITS_TO_U64((MAX_PHYPORT_NUM + 1)) * sizeof(u64));
        memset(register_filter_listener->vlans_registers, 0, FROM_BITS_TO_U64((SXD_MAX_VLAN_NUM + 1)) * sizeof(u64));
        memset(register_filter_listener->lags_registers, 0, FROM_BITS_TO_U64((MAX_LAG_NUM + 1)) * sizeof(u64));
    } else {
        register_filter_listener->is_global_filter = 0;
        memset(register_filter_listener->ports_filters, 0, FROM_BITS_TO_U64((MAX_PHYPORT_NUM + 1)) * sizeof(u64));
        memset(register_filter_listener->vlans_filters, 0, FROM_BITS_TO_U64((SXD_MAX_VLAN_NUM + 1)) * sizeof(u64));
        memset(register_filter_listener->lags_filters, 0, FROM_BITS_TO_U64((MAX_LAG_NUM + 1)) * sizeof(u64));
    }
}

static void __listeners_gc_init(struct list_head *listeners_list)
{
    INIT_LIST_HEAD(listeners_list);
}

static void __listeners_gc_add(struct list_head *listeners_list, struct listener_entry *listener)
{
    list_del_rcu(&listener->list);
    list_add(&listener->gc_list, listeners_list);
}

static void __listeners_gc_finish(struct list_head *listeners_list)
{
    struct listener_entry *entry, *tmp;

    /* we could delete the listener asynchronously with call_rcu() but the listener may hold
     * a sx_src/sx_netdev pointers that can be potentially removed in this flow synchronously.
     * So, we'll use synchronize_rcu() to wait until listeners are no longer in use and only
     * then continue with the "remove listener" flow.
     */
    synchronize_rcu();

    list_for_each_entry_safe(entry, tmp, listeners_list, gc_list) {
        kfree(entry);
    }
}

u16 translate_user_port_to_sysport(struct sx_dev *dev, u32 log_port, int* is_lag)
{
    unsigned int port_type = SX_PORT_TYPE_ID_GET(log_port);
    u16          ret = 0;

    *is_lag = 0;
    if (port_type == SX_PORT_TYPE_LAG) {
        *is_lag = 1;
        return SX_PORT_LAG_ID_GET(log_port);
    } else {
        if (SX_PORT_PHY_ID_GET(log_port) == CPU_PORT_PHY_ID) {
            /* Build CPU port route*/
            ret = UCROUTE_CPU_PORT_PREFIX;
            ret |= SX_PORT_DEV_ID_GET(log_port) << UCROUTE_CPU_DEV_BIT_OFFSET;
        } else {
            ret = sx_priv(dev)->local_to_system_db[SX_PORT_PHY_ID_GET(log_port)];
            /* For Switchx-2 it's equals to the following translation:
             *  ret = SX_PORT_DEV_ID_GET(log_port) << UCROUTE_DEV_ID_BIT_OFFSET;
             *  ret |= (SX_PORT_PHY_ID_GET(log_port) - 1) << UCROUTE_PHY_PORT_BITS_OFFSET;
             */
        }
    }
    return ret;
}
EXPORT_SYMBOL(translate_user_port_to_sysport);

u32 translate_sysport_to_user_port(struct sx_dev *dev, u16 port, u8 is_lag)
{
    u32 lag_id = 0;

    if (is_lag) {
        lag_id = port << SX_PORT_LAG_ID_OFFS;
        lag_id |= SX_PORT_TYPE_LAG << SX_PORT_TYPE_ID_OFFS;
        return lag_id;
    } else {
        if ((port & UCROUTE_CPU_PORT_PREFIX) == UCROUTE_CPU_PORT_PREFIX) {
            return ((port & ~UCROUTE_CPU_PORT_PREFIX) >> UCROUTE_CPU_DEV_BIT_OFFSET)
                   << SX_PORT_DEV_ID_OFFS;
        } else {
            return ((port >> UCROUTE_DEV_ID_BIT_OFFSET) << SX_PORT_DEV_ID_OFFS) |
                   (sx_priv(dev)->system_to_local_db[port]) << SX_PORT_PHY_ID_OFFS;
            /* For Switchx-2 it's equals to the following translation:
             *  return ((port >> UCROUTE_DEV_ID_BIT_OFFSET) << SX_PORT_DEV_ID_OFFS) |
             *   (((port >> UCROUTE_PHY_PORT_BITS_OFFSET) & 0xFF) + 1) << SX_PORT_PHY_ID_OFFS;
             */
        }
    }
}
EXPORT_SYMBOL(translate_sysport_to_user_port);

#define SNOOP_MISS_WA
#if defined(CONFIG_MLNX460EX) && defined(SNOOP_MISS_WA)
int config_l2_force_snoop(void)
{
    struct device_node *np;
    u32                 r;
    const u32          *dcrreg;
    int                 len;
    const u32          *prop;
    u32                 l2_size;
    static u32          dcrbase_l2c = 0;

    if (0 == dcrbase_l2c) {
        np = of_find_compatible_node(NULL, NULL, "ibm,l2-cache");
        if (!np) {
            return 0;
        }

        /* Get l2 cache size */
        prop = of_get_property(np, "cache-size", NULL);
        if (prop == NULL) {
            printk(KERN_ERR "%s: Can't get cache-size!\n", np->full_name);
            of_node_put(np);
            return -ENODEV;
        }
        l2_size = prop[0];

        /* Map DCRs */
        dcrreg = of_get_property(np, "dcr-reg", &len);
        if (!dcrreg || (len != 4 * sizeof(u32))) {
            printk(KERN_ERR "%s: Can't get DCR register base !",
                   np->full_name);
            of_node_put(np);
            return -ENODEV;
        }
        dcrbase_l2c = dcrreg[2];
    }

    /* Force snoop */
    r = mfdcr(dcrbase_l2c + DCRN_L2C0_CFG);
    r |= 0x0000010;
    mtdcr(dcrbase_l2c + DCRN_L2C0_CFG, r);

    return 0;
}
#endif /* SNOOP_MISS_WA */


int sx_core_get_local(struct sx_dev *dev, uint16_t lag_id, uint16_t lag_subport, uint16_t *local_p)
{
    uint16_t local = 0, phy_port_max = 0;
    uint16_t lag_max = 0, lag_member_max = 0;

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs.\n");
        return -EINVAL;
    }

    if (lag_id > lag_max) {
        net_err_ratelimited(PFX "lag_id %d is invalid. (MAX %d).\n",
                            lag_id, lag_max);
        return -EINVAL;
    }

    if (lag_subport > lag_member_max) {
        net_err_ratelimited(PFX "lag_subport %d is invalid. (MAX %d).\n",
                            lag_subport, lag_member_max);
        return -EINVAL;
    }

    local = sx_priv(dev)->lag_member_to_local_db[lag_id][lag_subport];

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        return -EINVAL;
    }

    if (local > phy_port_max) {
        net_err_ratelimited(PFX "Local %d is invalid. (MAX %d).\n",
                            local, phy_port_max);
        return -EINVAL;
    }

    *local_p = local;

    return 0;
}
EXPORT_SYMBOL(sx_core_get_local);

int sx_core_get_lag_oper_state(struct sx_dev *dev, u16 lag_id, u8 *oper_state_p)
{
    uint16_t lag_max = 0, lag_member_max = 0;

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs.\n");
        return -EINVAL;
    }

    if (lag_id >= lag_max) {
        net_err_ratelimited(PFX "lag_id %d is invalid. (MAX %d).\n",
                            lag_id, lag_max);
        return -EINVAL;
    }

    *oper_state_p = sx_priv(dev)->lag_oper_state[lag_id];

    return 0;
}
EXPORT_SYMBOL(sx_core_get_lag_oper_state);

int sx_core_get_prio2tc(struct sx_dev *dev, uint16_t port_lag_id, uint8_t is_lag, uint8_t pcp, uint8_t *tc)
{
    struct sx_priv *dev_priv = sx_priv(dev);
    uint16_t        local = 0, phy_port_max = 0;
    unsigned long   flags;

    if (pcp > MAX_PRIO_NUM) {
        printk(KERN_ERR PFX "PCP %d is invalid. (MAX %d).\n",
               pcp, MAX_PRIO_NUM);
        return -EINVAL;
    }

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (is_lag) {
        *tc = dev_priv->lag_prio2tc[port_lag_id][pcp];
    } else {
        local = dev_priv->system_to_local_db[port_lag_id];

        if (local > phy_port_max) {
            printk(KERN_ERR PFX "Local %d is invalid. (MAX %d).\n",
                   local, phy_port_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
        *tc = dev_priv->port_prio2tc[local][pcp];
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_get_prio2tc);

int sx_core_get_pvid(struct sx_dev *dev, uint16_t sysport_lag_id, uint8_t is_lag, uint16_t       *pvid)
{
    struct sx_priv *dev_priv = sx_priv(dev);
    unsigned long   flags;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (is_lag) {
        *pvid = dev_priv->pvid_lag_db[sysport_lag_id];
    } else {
        *pvid = dev_priv->pvid_sysport_db[sysport_lag_id];
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_get_pvid);

int sx_core_get_vlan_tagging(struct sx_dev *dev,
                             uint16_t       port_lag_id,
                             uint8_t        is_lag,
                             uint16_t       vlan,
                             uint8_t       *is_vlan_tagged)
{
    struct sx_priv *dev_priv = sx_priv(dev);
    uint16_t        local = 0, phy_port_max = 0;
    unsigned long   flags;

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (is_lag) {
        *is_vlan_tagged = dev_priv->lag_vtag_mode[port_lag_id][vlan];
    } else {
        local = dev_priv->system_to_local_db[port_lag_id];

        if (local > phy_port_max) {
            printk(KERN_ERR PFX "Local %d is invalid. (MAX %d).\n",
                   local, phy_port_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
        *is_vlan_tagged = dev_priv->port_vtag_mode[local][vlan];
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_get_vlan_tagging);

int sx_core_get_prio_tagging(struct sx_dev *dev, uint16_t port_lag_id, uint8_t is_lag, uint8_t *is_port_prio_tagged)
{
    struct sx_priv *dev_priv = sx_priv(dev);
    uint16_t        local = 0, phy_port_max = 0;
    unsigned long   flags;

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy port.\n");
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (is_lag) {
        *is_port_prio_tagged = dev_priv->lag_prio_tagging_mode[port_lag_id];
    } else {
        local = dev_priv->system_to_local_db[port_lag_id];

        if (local > phy_port_max) {
            printk(KERN_ERR PFX "Local %d is invalid. (MAX %d).\n",
                   local, phy_port_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
        *is_port_prio_tagged = dev_priv->port_prio_tagging_mode[local];
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_get_prio_tagging);

int sx_core_get_swid(struct sx_dev *dev, struct completion_info *comp_info, uint8_t *swid)
{
    int rc = 0;

    *swid = 0;

    if (!dev) {
        printk(KERN_ERR PFX "get_swid: dev is NULL\n");
        return -EINVAL;
    }

    rc = __sx_core_dev_specific_cb_get_reference(dev);
    if (rc) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return rc;
    }

    if (sx_priv(dev)->dev_specific_cb.get_swid_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.get_swid_cb(dev, comp_info, swid);
    } else {
        printk(KERN_ERR PFX "Error retrieving get_swid_cb callback\n");
        __sx_core_dev_specific_cb_release_reference(dev);
        return -EINVAL;
    }

    __sx_core_dev_specific_cb_release_reference(dev);
    return 0;
}

int sx_core_get_phy_port_max(struct sx_dev *dev, uint16_t *port)
{
    int rc = 0;

    if (dev == NULL) {
        printk(KERN_ERR PFX "get phy port max: dev is NULL.\n");
        return -EINVAL;
    }

    if (port == NULL) {
        printk(KERN_ERR PFX "port is NULL.\n");
        return -EINVAL;
    }

    *port = 0;

    rc = __sx_core_dev_specific_cb_get_reference(dev);
    if (rc) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return rc;
    }

    /* We don't use lock because the following function will return hard-coded
     *  value and nothing will be changed after we will init switch with
     *  appropriate callback, hence lock will be redundant here. */

    if (sx_priv(dev)->dev_specific_cb.sx_get_phy_port_max_cb != NULL) {
        if (sx_priv(dev)->dev_specific_cb.sx_get_phy_port_max_cb(port)) {
            printk(KERN_ERR PFX "Error retrieving max phy port number from sx_get_phy_port_max_cb callback\n");
            rc = -EINVAL;
        }
    } else {
        printk(KERN_ERR PFX "Error retrieving sx_get_phy_port_max_cb callback\n");
        rc = -EINVAL;
    }


    __sx_core_dev_specific_cb_release_reference(dev);
    return rc;
}
EXPORT_SYMBOL(sx_core_get_phy_port_max);

int sx_core_get_lag_max(struct sx_dev *dev, uint16_t *lags, uint16_t *pors_per_lag)
{
    int rc = 0;

    if (dev == NULL) {
        printk(KERN_ERR PFX "lag_max: dev is NULL.\n");
        return -EINVAL;
    }

    if (lags == NULL) {
        printk(KERN_ERR PFX "lags is NULL.\n");
        return -EINVAL;
    }

    if (pors_per_lag == NULL) {
        printk(KERN_ERR PFX "lags_per_port is NULL.\n");
        return -EINVAL;
    }

    rc = __sx_core_dev_specific_cb_get_reference(dev);
    if (rc) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return rc;
    }

    /* We don't use lock because the following function will return hard-coded
     *  value and nothing will be changed after we will init switch with
     *  appropriate callback, hence lock will be redundant here. */

    if (sx_priv(dev)->dev_specific_cb.sx_get_lag_max_cb != NULL) {
        if (sx_priv(dev)->dev_specific_cb.sx_get_lag_max_cb(lags, pors_per_lag)) {
            printk(KERN_ERR PFX "Error retrieving max values for LAG from sx_get_lag_max_cb callback\n");
            rc = -EINVAL;
        }
    } else {
        printk(KERN_ERR PFX "Error retrieving sx_get_lag_max_cb callback\n");
        rc = -EINVAL;
    }

    __sx_core_dev_specific_cb_release_reference(dev);
    return rc;
}
EXPORT_SYMBOL(sx_core_get_lag_max);

int sx_core_get_lag_mid(struct sx_dev *dev, u16 lag_id, u16 *mid)
{
    int rc;

    if (!dev) {
        printk(KERN_ERR PFX "get_lad_mid: dev is NULL\n");
        return -EINVAL;
    }

    rc = __sx_core_dev_specific_cb_get_reference(dev);
    if (rc) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return rc;
    }

    if (dev && (sx_priv(dev)->dev_specific_cb.get_lag_mid_cb != NULL)) {
        sx_priv(dev)->dev_specific_cb.get_lag_mid_cb(dev, lag_id, mid);
    } else {
        printk(KERN_ERR PFX "Error retrieving get_lag_mid_cb callback\n");
        __sx_core_dev_specific_cb_release_reference(dev);
        return -EINVAL;
    }

    __sx_core_dev_specific_cb_release_reference(dev);

    return 0;
}
EXPORT_SYMBOL(sx_core_get_lag_mid);

int sx_core_is_eqn_cmd_ifc_only(struct sx_dev *dev, int eqn, u8 *is_cmd_ifc_only)
{
    int rc = 0;

    if (!dev) {
        printk(KERN_ERR PFX "Error in sx_core_is_eqn_cmd_ifc_only: *dev is NULL.\n");
        return -EINVAL;
    }

    rc = __sx_core_dev_specific_cb_get_reference(dev);
    if (rc) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return rc;
    }

    if (sx_priv(dev)->dev_specific_cb.is_eqn_cmd_ifc_only_cb != NULL) {
        rc = sx_priv(dev)->dev_specific_cb.is_eqn_cmd_ifc_only_cb(eqn, is_cmd_ifc_only);
    } else {
        *is_cmd_ifc_only = 0;
    }

    __sx_core_dev_specific_cb_release_reference(dev);

    return rc;
}

int sx_core_get_rp_rfid(struct sx_dev *dev, uint16_t port_lag_id, uint8_t is_lag, uint16_t vlan_id, uint16_t *rfid)
{
    struct sx_priv *dev_priv = sx_priv(dev);
    uint16_t        local = 0, phy_port_max = 0, rif_id = 0;
    unsigned long   flags;
    uint16_t        lag_max = 0, lag_member_max = 0;

    if (vlan_id >= SXD_MAX_VLAN_NUM) {
        printk(KERN_ERR PFX "vlan_id %d is invalid. (MAX %d).\n",
               vlan_id, SXD_MAX_VLAN_NUM);
        return -EINVAL;
    }

    *rfid = 0;

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        return -EINVAL;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs.\n");
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (is_lag) {
        if (port_lag_id > lag_max) {
            net_err_ratelimited(PFX "port_lag_id %d is invalid. (MAX %d).\n",
                                port_lag_id, lag_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
        if (!dev_priv->lag_rp_rif_valid[port_lag_id][vlan_id]) {
            printk(KERN_ERR PFX "No RP on LAG ID %d and vlan %d.\n",
                   port_lag_id, vlan_id);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }

        rif_id = dev_priv->lag_rp_rif[port_lag_id][vlan_id];
        *rfid = dev_priv->rif_id_to_hwfid[rif_id];
    } else {
        local = dev_priv->system_to_local_db[port_lag_id];

        if (local > phy_port_max) {
            net_err_ratelimited(PFX "Local %d is invalid. (MAX %d).\n",
                                local, phy_port_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
        if (!dev_priv->port_rp_rif_valid[local][vlan_id]) {
            printk(KERN_ERR PFX "No RP on port %d and vlan %d.\n",
                   local, vlan_id);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }

        rif_id = dev_priv->port_rp_rif[local][vlan_id];
        *rfid = dev_priv->rif_id_to_hwfid[rif_id];
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_get_rp_rfid);

int sx_core_get_rp_vlan(struct sx_dev *dev, struct completion_info *comp_info, uint16_t *vlan_id)
{
    int rc;

    if (!dev) {
        printk(KERN_ERR PFX "get_rp_vlan: dev is NULL\n");
        return -EINVAL;
    }

    *vlan_id = 0;

    rc = __sx_core_dev_specific_cb_get_reference(dev);
    if (rc) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return rc;
    }

    if (sx_priv(dev)->dev_specific_cb.get_rp_vid_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.get_rp_vid_cb(dev, comp_info, vlan_id);
    } else {
        printk(KERN_ERR PFX "Error retrieving get_rp_vid_cb callback\n");
        __sx_core_dev_specific_cb_release_reference(dev);
        return -EINVAL;
    }

    __sx_core_dev_specific_cb_release_reference(dev);
    return 0;
}
EXPORT_SYMBOL(sx_core_get_rp_vlan);

int sx_core_get_rp_mode(struct sx_dev *dev, u8 is_lag, u16 sysport_lag_id, u16 vlan_id, u8 *is_rp)
{
    unsigned long flags;
    u16           lag_id = 0;
    uint16_t      local = 0, phy_port_max = 0;
    uint16_t      lag_max = 0, lag_member_max = 0;

    if (vlan_id >= SXD_MAX_VLAN_NUM) {
        printk(KERN_ERR PFX "vlan_id %d is invalid. (MAX %d).\n",
               vlan_id, SXD_MAX_VLAN_NUM);
        return -EINVAL;
    }

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        return -EINVAL;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs.\n");
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (is_lag) {
        if (sysport_lag_id > lag_max) {
            printk(KERN_ERR PFX "LAG ID %d is invalid. (MAX %d).\n",
                   lag_id, lag_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
        *is_rp = sx_priv(dev)->lag_rp_rif_valid[sysport_lag_id][vlan_id];
    } else {
        local = sx_priv(dev)->system_to_local_db[sysport_lag_id];

        if (local > phy_port_max) {
            printk(KERN_ERR PFX "Local %d is invalid. (MAX %d).\n",
                   local, phy_port_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
        *is_rp = sx_priv(dev)->port_rp_rif_valid[local][vlan_id];
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_get_rp_mode);


int sx_core_get_vlan2ip(struct sx_dev *dev, uint16_t vid, uint32_t *ip_addr)
{
    struct sx_priv *dev_priv = sx_priv(dev);
    unsigned long   flags;

    if (dis_vid2ip) {
        return 0;
    }

    if (vid >= SXD_MAX_VLAN_NUM) {
        printk(KERN_ERR PFX "vid %d is invalid. (MAX %d).\n",
               vid, SXD_MAX_VLAN_NUM);
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    *ip_addr = dev_priv->icmp_vlan2ip_db[vid];

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_get_vlan2ip);

int sx_core_get_fid_by_port_vid(struct sx_dev *dev, struct completion_info *comp_info, uint16_t *fid)
{
    struct sx_priv *dev_priv = sx_priv(dev);
    uint16_t        local = 0, phy_port_max = 0;
    unsigned long   flags;
    uint8_t         is_lag = comp_info->is_lag;
    uint16_t        sysport_lag_id = comp_info->sysport;
    uint16_t        lag_port_id = comp_info->lag_subport;
    uint16_t        vid = comp_info->vid;

    if (vid >= SXD_MAX_VLAN_NUM) {
        printk(KERN_ERR PFX "vid %d is invalid. (MAX %d).\n",
               vid, SXD_MAX_VLAN_NUM);
        return -EINVAL;
    }

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    if (is_lag) {
        local = sx_priv(dev)->lag_member_to_local_db[sysport_lag_id][lag_port_id];
    } else {
        local = dev_priv->system_to_local_db[sysport_lag_id];
        if (local > phy_port_max) {
            printk(KERN_ERR PFX "Local %d is invalid. (MAX %d).\n",
                   local, phy_port_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
    }
    *fid = dev_priv->port_vid_to_fid[local][vid];
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}

int sx_core_get_ib_system_port_mid(struct sx_dev *dev, u16 ib_port, u16* sys_port_mid)
{
    u16 ret = 0;

    /* this function is called from the sx_ib/IPoIB drivers that work only with PCI devices.
     * When OOB is enabled, these drivers work with the SX dev and its specific callbacks.
     * This is the point when we change the sx_dev we work with in order to work with the
     * right callbacks!
     */
    if (is_sgmii_supported()) {
        dev = sx_glb.fake_dev; /* the SGMII device with the right callbacks */
    }

    ret = __sx_core_dev_specific_cb_get_reference(dev);
    if (ret) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return ret;
    }

    if (sx_priv(dev)->dev_specific_cb.get_ib_system_port_mid != NULL) {
        ret = sx_priv(dev)->dev_specific_cb.get_ib_system_port_mid(dev, ib_port, sys_port_mid);
    } else {
        printk(KERN_ERR PFX "Error retrieving get_ib_system_port_mid callback structure!\n");
        printk(KERN_ERR PFX "Hint: Check call to IB code from ETH flow!\n");
        __sx_core_dev_specific_cb_release_reference(dev);
        return -EINVAL;
    }

    __sx_core_dev_specific_cb_release_reference(dev);

    return ret;
}
EXPORT_SYMBOL(sx_core_get_ib_system_port_mid);

int sx_core_get_send_to_port_as_data(struct sx_dev *dev, u8* send_to_port_as_data, u8 send_default)
{
    int ret = 0;

    ret = __sx_core_dev_specific_cb_get_reference(dev);
    if (ret) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return ret;
    }

    if (sx_priv(dev)->dev_specific_cb.get_send_to_port_as_data_supported_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.get_send_to_port_as_data_supported_cb(send_to_port_as_data);
    } else {
        *send_to_port_as_data = send_default;
    }
    __sx_core_dev_specific_cb_release_reference(dev);

    return ret;
}
EXPORT_SYMBOL(sx_core_get_send_to_port_as_data);

int sx_core_get_module_by_port(struct sx_dev *dev, uint16_t local_port, uint8_t *slot, uint8_t *module)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;

    if (local_port > MAX_PHYPORT_NUM) {
        net_err_ratelimited(PFX "Local port %d is invalid. (MAX %d).\n",
                            local_port, MAX_PHYPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    *slot = priv->local_to_slot_map[local_port];
    *module = priv->local_to_module_map[local_port];

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_module_by_port);

int sx_core_get_ports_by_module(struct sx_dev *dev,
                                uint8_t        slot,
                                uint8_t        module,
                                uint16_t      *local_ports,
                                uint16_t      *sys_ports,
                                uint8_t       *count)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    int             i = 0;

    if ((!dev) || (!count)) {
        err = -EINVAL;
        goto out;
    }

    *count = priv->modules_to_port_map_count[slot][module];
    for (i = 0; i < *count; i++) {
        if (local_ports) {
            local_ports[i] = priv->module_to_ports_map[slot][module][i];
        }
        if (sys_ports) {
            sys_ports[i] = priv->local_to_system_db[priv->module_to_ports_map[slot][module][i]];
        }
    }

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_ports_by_module);

bool sx_core_is_profile_set(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    return priv->profile.dev_profile_set;
}
EXPORT_SYMBOL(sx_core_is_profile_set);

static int __sx_core_set_low_power_mode(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool low_power)
{
    struct sx_priv           *priv = sx_priv(dev);
    int                       err = 0, err1 = 0;
    struct ku_access_pmmp_reg reg_data;

    mutex_lock(&priv->module_access_mutex);

    err = sx_core_set_module(dev, slot_id, module_id, 0, 0);
    if (err) {
        printk(KERN_ERR PFX "Failed to disable module %d.\n", module_id);
        goto out;
    }

    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_PMMP_ID, EMAD_METHOD_WRITE);

    reg_data.pmmp_reg.slot_index = slot_id;
    reg_data.pmmp_reg.module = module_id;
    reg_data.pmmp_reg.eeprom_override_mask = 0xFFFF;
    reg_data.pmmp_reg.eeprom_override_mask &= ~MLXSW_REG_PMMP_EEPROM_OVERRIDE_LOW_POWER_MASK;
    reg_data.pmmp_reg.eeprom_override |= low_power ? MLXSW_REG_PMMP_EEPROM_OVERRIDE_LOW_POWER_MASK : 0;

    err = sx_ACCESS_REG_PMMP(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMMP, err=%d\n", err);
        goto bring_module_up;
    }
    if (reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMMP, status=%d\n", reg_data.op_tlv.status);
        goto bring_module_up;
    }

bring_module_up:
    err1 = sx_core_set_module(dev, slot_id, module_id, 1, 0);
    if (err1) {
        printk(KERN_ERR PFX "Failed to enable module %d.\n", module_id);
        err = err1;
        goto out;
    }

out:
    mutex_unlock(&priv->module_access_mutex);
    return err;
}

int sx_core_update_module_power_mode(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool port_up)
{
    int             err = 0;
    struct sx_priv *priv = sx_priv(dev);
    int             i = 0;
    uint16_t        local_port = 0;
    bool            any_port_up = false;
    unsigned long   flags;

    if ((slot_id >= MAX_SLOT_NUM) || (module_id >= MAX_MODULE_NUM)) {
        err = -EINVAL;
        printk(KERN_ERR PFX "slot id %d or module id %d is out of range.\n", slot_id, module_id);
        goto out;
    }

    spin_lock_irqsave(&priv->db_lock, flags);
    if (priv->module_data[slot_id][module_id].power_mode_policy != SX_MODULE_POWER_MODE_POLICY_AUTO) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }

    for (i = 0; i < priv->modules_to_port_map_count[slot_id][module_id]; i++) {
        local_port = priv->module_to_ports_map[slot_id][module_id][i];
        if ((priv->local_port_state[local_port] == SXD_PAOS_ADMIN_STATUS_UP_E) ||
            (priv->local_port_state[local_port] == SXD_PAOS_ADMIN_STATUS_UP_ONCE_E)) {
            any_port_up = true;
            break;
        }
    }

    if (any_port_up) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    err = __sx_core_set_low_power_mode(dev, slot_id, module_id, !port_up);
    if (err) {
        printk(KERN_ERR PFX "slot id %d or module id %d is out of range.\n", slot_id, module_id);
        goto out;
    }

out:
    return err;
}

int sx_core_set_module(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, uint8_t enable, uint8_t reset)
{
    struct ku_access_pmaos_reg reg_data;
    int                        err = 0;
    bool                       is_system_ind = false;
    unsigned long              flags;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    is_system_ind = sx_priv(dev)->independent_module_params.is_independent;
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);


    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, PMAOS_REG_ID, EMAD_METHOD_WRITE);

    reg_data.pmaos_reg.slot_index = slot_id;
    reg_data.pmaos_reg.module = module_id;
    reg_data.pmaos_reg.rst = reset;
    reg_data.pmaos_reg.ase = 1;
    if (enable) {
        reg_data.pmaos_reg.admin_status = SXD_PMAOS_ADMIN_STATUS_ENABLED_E;
    } else {
        reg_data.pmaos_reg.admin_status = SXD_PMAOS_ADMIN_STATUS_DISABLED_BY_CONFIGURATION_E;
    }

    if (is_system_ind) {
        reg_data.pmaos_reg.ee = 1;
        reg_data.pmaos_reg.e = SXD_PMAOS_E_GENERATE_EVENT_E;
    }

    err = sx_ACCESS_REG_PMAOS(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMAOS, err=%d\n", err);
        goto out;
    }
    if (reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMAOS, status=%d\n", reg_data.op_tlv.status);
        goto out;
    }
out:
    return err;
}

int sx_core_rearm_module_event(struct sx_dev                    *dev,
                               uint8_t                           slot_id,
                               uint8_t                           module_id,
                               sxd_pmaos_e_t                     gen_mode,
                               struct ku_rearm_module_event_ret *ret_vals)
{
    struct ku_rearm_module_event_ret saved_vals;
    struct ku_access_pmaos_reg       reg_data;
    struct ku_access_pmaos_reg       reg_data_saved;
    sxd_pmaos_admin_status_t         admin_status;
    int                              err = 0;
    struct sx_priv                  *priv = sx_priv(dev);

    mutex_lock(&priv->module_access_mutex);
    memset(&reg_data_saved, 0, sizeof(reg_data_saved));

    /* 1. set pmaos rearm event */
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, PMAOS_REG_ID, EMAD_METHOD_WRITE);
    reg_data.pmaos_reg.slot_index = slot_id;
    reg_data.pmaos_reg.module = module_id;
    reg_data.pmaos_reg.admin_status = 1;
    reg_data.pmaos_reg.ase = 0;
    reg_data.pmaos_reg.ee = 1;
    reg_data.pmaos_reg.e = gen_mode;
    reg_data_saved = reg_data;

    err = sx_ACCESS_REG_PMAOS(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMAOS, err=%d\n", err);
        goto out;
    }

    /* 2. get current pmaos status */
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, PMAOS_REG_ID, EMAD_METHOD_QUERY);
    reg_data.pmaos_reg.slot_index = slot_id;
    reg_data.pmaos_reg.module = module_id;

    err = sx_ACCESS_REG_PMAOS(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMAOS, err=%d\n", err);
        goto out;
    }
    if (reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMAOS, status=%d\n", reg_data.op_tlv.status);
        goto out;
    }
    admin_status = reg_data.pmaos_reg.admin_status;
    saved_vals.oper_status = reg_data.pmaos_reg.oper_status;
    saved_vals.error_type = reg_data.pmaos_reg.error_type;

    /* 3. set pmaos admin + rearm event */
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, PMAOS_REG_ID, EMAD_METHOD_WRITE);
    reg_data.pmaos_reg.slot_index = slot_id;
    reg_data.pmaos_reg.module = module_id;
    reg_data.pmaos_reg.admin_status = admin_status;
    reg_data.pmaos_reg.ase = 1;
    reg_data.pmaos_reg.ee = 1;
    reg_data.pmaos_reg.e = gen_mode;

    err = sx_ACCESS_REG_PMAOS(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMAOS, err=%d\n", err);
        goto out;
    }
    if (reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMAOS, status=%d\n", reg_data.op_tlv.status);
        goto out;
    }

    *ret_vals = saved_vals;
out:
    mutex_unlock(&priv->module_access_mutex);
    return err;
}
EXPORT_SYMBOL(sx_core_rearm_module_event);

int sx_core_set_module_power_mode_policy(struct sx_dev                   *dev,
                                         uint8_t                          slot_id,
                                         uint8_t                          module_id,
                                         enum sx_module_power_mode_policy power_mode_policy)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    unsigned long   flags;
    int             i = 0;
    bool            any_port_up = false;
    bool            low_power = false;
    uint16_t        local_port = 0;
    bool            is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        printk(KERN_ERR PFX "%s: Failed: module is independent (SW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if ((slot_id >= MAX_SLOT_NUM) || (module_id >= MAX_MODULE_NUM)) {
        err = -EINVAL;
        net_err_ratelimited(PFX "slot id %d or module id %d is out of range.\n", slot_id, module_id);
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    if (power_mode_policy == priv->module_data[slot_id][module_id].power_mode_policy) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }

    for (i = 0; i < priv->modules_to_port_map_count[slot_id][module_id]; i++) {
        local_port = priv->module_to_ports_map[slot_id][module_id][i];
        if ((priv->local_port_state[local_port] == SXD_PAOS_ADMIN_STATUS_UP_E) ||
            (priv->local_port_state[local_port] == SXD_PAOS_ADMIN_STATUS_UP_ONCE_E)) {
            any_port_up = true;
            break;
        }
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    if (any_port_up == true) {
        goto out_set_policy;
    }

    low_power = (power_mode_policy == SX_MODULE_POWER_MODE_POLICY_AUTO);

    err = __sx_core_set_low_power_mode(dev, slot_id, module_id, low_power);
    if (err) {
        goto out;
    }

out_set_policy:
    priv->module_data[slot_id][module_id].power_mode_policy = power_mode_policy;
out:
    return err;
}
EXPORT_SYMBOL(sx_core_set_module_power_mode_policy);

int sx_core_set_port_module_power_mode_policy(struct sx_dev                   *dev,
                                              uint16_t                         local_port,
                                              enum sx_module_power_mode_policy power_mode_policy)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    unsigned long   flags;
    uint8_t         slot_id = 0;
    uint8_t         module_id = 0;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    err = sx_core_set_module_power_mode_policy(dev, slot_id, module_id, power_mode_policy);
out:
    return err;
}
EXPORT_SYMBOL(sx_core_set_port_module_power_mode_policy);

int sx_core_get_module_power_mode(struct sx_dev                      *dev,
                                  uint8_t                             slot_id,
                                  uint8_t                             module_id,
                                  struct sx_module_power_mode_params *params)
{
    struct sx_priv            *priv = sx_priv(dev);
    int                        err = 0;
    unsigned long              flags;
    struct ku_access_mcion_reg reg_data;
    bool                       is_independent = false;

    if ((slot_id >= MAX_SLOT_NUM) || (module_id >= MAX_MODULE_NUM)) {
        err = -EINVAL;
        net_err_ratelimited(PFX "slot id %d or module id %d is out of range.\n", slot_id, module_id);
        goto out;
    }

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        printk(KERN_ERR PFX "%s: Failed: module is independent (SW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    spin_lock_irqsave(&priv->db_lock, flags);
    params->policy = priv->module_data[slot_id][module_id].power_mode_policy;
    spin_unlock_irqrestore(&priv->db_lock, flags);

    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_QUERY);

    reg_data.mcion_reg.slot_index = slot_id;
    reg_data.mcion_reg.module = module_id;

    err = sx_ACCESS_REG_MCION(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access MCION, err=%d\n", err);
        goto out;
    }
    if (reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access MCION, status=%d\n", reg_data.op_tlv.status);
        goto out;
    }

    if (!(reg_data.mcion_reg.module_status_bits & MCION_MODULE_STATUS_BITS_PRESENT_MASK)) {
        err = -ENODEV;
        printk(KERN_INFO PFX "Module %d is not presented\n", module_id);
        goto out;
    }

    if (reg_data.mcion_reg.module_status_bits & MCION_MODULE_STATUS_BITS_LOW_POWER_MASK) {
        params->mode = SX_MODULE_POWER_MODE_LOW;
    } else {
        params->mode = SX_MODULE_POWER_MODE_HIGH;
    }

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_module_power_mode);

int sx_core_get_port_module_power_mode(struct sx_dev                      *dev,
                                       uint16_t                            local_port,
                                       struct sx_module_power_mode_params *params)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    unsigned long   flags;
    uint8_t         slot_id = 0;
    uint8_t         module_id = 0;

    spin_lock_irqsave(&priv->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    err = sx_core_get_module_power_mode(dev, slot_id, module_id, params);
out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_power_mode);

int sx_core_reset_module(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    bool            is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        printk(KERN_ERR PFX "%s: Failed reset: module is independent (SW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    mutex_lock(&priv->module_access_mutex);
    err = sx_core_set_module(dev, slot_id, module_id, 1, 1);
    if (err) {
        mutex_unlock(&priv->module_access_mutex);
        goto out;
    }
    mutex_unlock(&priv->module_access_mutex);

out:
    return err;
}
EXPORT_SYMBOL(sx_core_reset_module);

int sx_core_reset_port_module(struct sx_dev *dev, uint16_t local_port)
{
    int           err = 0;
    unsigned long flags;
    uint8_t       slot_id = 0;
    uint8_t       module_id = 0;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    err = sx_core_reset_module(dev, slot_id, module_id);

out:
    return err;
}
EXPORT_SYMBOL(sx_core_reset_port_module);

int sx_core_get_module_temperature(struct sx_dev                *dev,
                                   uint8_t                       slot_id,
                                   uint8_t                       module_id,
                                   struct sx_temperature_params *params)
{
    int                        err = 0;
    uint16_t                   temperature = 0;
    uint64_t                   sensor_name = 0;
    struct ku_access_pmaos_reg pmaos_reg_data;
    struct ku_access_mtmp_reg  mtmp_reg_data;
    struct ku_access_mtbr_reg  mtbr_reg_data;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        printk(KERN_ERR PFX "%s: Failed: module is independent (SW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&pmaos_reg_data, 0, sizeof(pmaos_reg_data));
    pmaos_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&pmaos_reg_data.op_tlv, PMAOS_REG_ID, EMAD_METHOD_QUERY);

    pmaos_reg_data.pmaos_reg.slot_index = slot_id;
    pmaos_reg_data.pmaos_reg.module = module_id;

    err = sx_ACCESS_REG_PMAOS(dev, &pmaos_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMAOS, err=%d\n", err);
        goto out;
    }

    if (pmaos_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMAOS, status=%d\n", pmaos_reg_data.op_tlv.status);
        goto out;
    }

    if (pmaos_reg_data.pmaos_reg.oper_status != SXD_PMAOS_OPER_STATUS_PLUGGED_ENABLED_E) {
        err = -ENODEV;
        pr_debug(PFX "Module %d oper status (%d) is not plugged enabled.\n", module_id,
                 pmaos_reg_data.pmaos_reg.oper_status);
        goto out;
    }

    memset(params, 0, sizeof(struct sx_temperature_params));

    memset(&mtbr_reg_data, 0, sizeof(mtbr_reg_data));
    mtbr_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtbr_reg_data.op_tlv, MTBR_REG_ID, EMAD_METHOD_QUERY);

    mtbr_reg_data.mtbr_reg.base_sensor_index = MODULE_SENSOR_BASE + module_id;
    mtbr_reg_data.mtbr_reg.slot_index = slot_id;
    mtbr_reg_data.mtbr_reg.num_rec = 1;

    err = sx_ACCESS_REG_MTBR(dev, &mtbr_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access MTBR, err=%d\n", err);
        goto out;
    }
    if (mtbr_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access MTBR, status=%d\n", mtbr_reg_data.op_tlv.status);
        goto out;
    }

    temperature = mtbr_reg_data.mtbr_reg.temperature_record[0].temperature;
    if ((temperature == 0) || (temperature == SXD_MTBR_NO_CABLE) || (temperature == SXD_MTBR_NO_READ) ||
        (temperature == SXD_MTBR_INVALID_INDEX) || (temperature == SXD_MTBR_READ_FAILED) ||
        (temperature == SXD_MTBR_NO_SENSOR)) {
        err = -ENODEV;
        pr_debug(PFX "Temperature sensing is not supported on module %d, status=0x%x\n", module_id,
                 temperature);
        goto out;
    }

    params->highest = mtbr_reg_data.mtbr_reg.temperature_record[0].max_temperature;
    params->input = mtbr_reg_data.mtbr_reg.temperature_record[0].temperature;

    memset(&mtmp_reg_data, 0, sizeof(mtmp_reg_data));
    mtmp_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtmp_reg_data.op_tlv, MLXSW_MTMP_ID, EMAD_METHOD_QUERY);

    mtmp_reg_data.mtmp_reg.sensor_index = MODULE_SENSOR_BASE + module_id;
    mtmp_reg_data.mtmp_reg.slot_index = slot_id;

    err = sx_ACCESS_REG_MTMP(dev, &mtmp_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access MTMP, err=%d\n", err);
        goto out;
    }
    if (mtmp_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access MTMP, status=%d\n", mtmp_reg_data.op_tlv.status);
        goto out;
    }

    sensor_name =
        ((uint64_t)mtmp_reg_data.mtmp_reg.sensor_name_hi << 32) | (uint64_t)mtmp_reg_data.mtmp_reg.sensor_name_lo;
    be64_to_cpus(&sensor_name);
    memcpy(params->label, &sensor_name, sizeof(uint64_t));

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_module_temperature);

int sx_core_get_port_module_temperature(struct sx_dev *dev, uint16_t local_port, struct sx_temperature_params *params)
{
    int           err = 0;
    unsigned long flags;
    uint8_t       slot_id = 0;
    uint8_t       module_id = 0;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    err = sx_core_get_module_temperature(dev, slot_id, module_id, params);

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_temperature);

/************************************************
 *  Helper Functions
 ***********************************************/
void inc_unconsumed_packets_counter(struct sx_priv *priv, u16 hw_synd, enum sx_packet_type pkt_type)
{
    if (priv) {
        priv->stats.rx_unconsumed_by_synd[hw_synd][pkt_type]++;
        priv->stats.unconsumed_packets_counter++;
    }
#ifdef SX_DEBUG
    printk(KERN_ERR PFX "A packet with trap ID 0x%x and type %s "
           "was not consumed\n", hw_synd, sx_cqe_packet_type_str[pkt_type]);
#endif
}

void inc_eventlist_drops_counter(struct sx_priv* priv, u16 hw_synd)
{
    inc_eventlist_drops_global_counter();
    if (priv != NULL) {
        priv->stats.eventlist_drops_counter++;
        priv->stats.rx_eventlist_drops_by_synd[hw_synd]++;
    }

#ifdef SX_DEBUG
    printk(KERN_ERR PFX "A packet with trap ID 0x%x "
           "was dropped from the event list\n", hw_synd);
#endif
}

void inc_filtered_lag_packets_counter(struct sx_priv *priv)
{
    if (priv) {
        priv->stats.filtered_lag_packets_counter++;
    }
}

void inc_filtered_port_packets_counter(struct sx_priv *priv)
{
    if (priv) {
        priv->stats.filtered_port_packets_counter++;
    }
}

void inc_eventlist_drops_global_counter(void)
{
    eventlist_drops_global_counter++;
}

static int check_valid_meta(struct sx_dev *dev, struct isx_meta *meta)
{
    uint8_t rdq_num = 0;
    int     rc = 0;

    if (meta->etclass >= NUMBER_OF_ETCLASSES) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "Error: etclass (%u) "
                   "is invalid\n",
                   meta->etclass);
        }
        return -ERANGE;
    }

    rc = sx_core_get_rdq_param_max(dev, &rdq_num, NULL);
    if (rc) {
        printk(KERN_ERR PFX "Error: failed to get max RDQ num\n");
        return rc;
    }

    if ((meta->rdq >= rdq_num) &&
        (meta->rdq != 0x1F)) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "Error: rdq (%u) is invalid\n",
                   meta->rdq);
        }
        return -ERANGE;
    }

    if ((meta->swid >= NUMBER_OF_SWIDS) &&
        (meta->swid != SWID_NUM_DONT_CARE)) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "Error: swid (%u) is invalid\n",
                   meta->swid);
        }
        return -ERANGE;
    }

    /* Validate the swid really exists */
    if (dev != NULL) {
        if ((meta->swid != SWID_NUM_DONT_CARE) &&
            (0 == sx_bitmap_test(&sx_priv(dev)->swid_bitmap, meta->swid))) {
            printk(KERN_WARNING PFX "Error: swid (%u) does not exists\n", meta->swid);
            return -EINVAL;
        }
    }

    if ((meta->to_cpu != false) && (meta->to_cpu != true)) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "Error: to_cpu (%u) "
                   "is invalid\n",
                   meta->to_cpu);
        }
        return -ERANGE;
    }

    if ((meta->type < SX_PKT_TYPE_MIN) ||
        (meta->type > SX_PKT_TYPE_MAX)) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "Error: type (%d) is invalid\n",
                   meta->type);
        }
        return -ERANGE;
    }

    return 0;
}

/**
 * Get a packet encapsulated in ku struct
 * (scattered to small buffers pointed by internal io vector)
 * and gather them together to one buffer encapsulated in the given skb data.
 * (NOTE: allocate skb)
 *
 * @param ku[in]   -  The given ku that encapsulated the scattered packet
 * @param reserve_hdrs[in]   -  Should the function reserve place for headers
 * @param skb[out] -  A pointer to the pointer of allocated skb
 *                    to be updated by the function with the gathered packet
 *
 * returns: 0 success
 *	    !0 error
 */
static int copy_buff_to_skb(struct sk_buff **skb,
                            struct ku_write *write_data,
                            u8               reserve_hdrs,
                            u8               is_from_user,
                            gfp_t            gfp_mask)
{
    int              err = 0;
    int              index = 0;
    int              packet_size = 0;
    unsigned char   *p_skb_data = NULL;
    struct ku_iovec *iov;
    int              max_headers_size = 0;

    if ((!skb) || (!write_data)) {
        err = -EINVAL;
        goto out_err;
    }

    if (is_from_user) {
        iov = kmalloc(sizeof(*iov) * (write_data->vec_entries), GFP_KERNEL);
        if (!iov) {
            err = -ENOMEM;
            goto out_err;
        }

        /*1. copy io vector */
        err = copy_from_user((void*)iov, (void*)(write_data->iov),
                             sizeof(*iov) * (write_data->vec_entries));
        if (err) {
            printk(KERN_WARNING PFX "failed to copy buffer from user\n");
            goto out_free;
        }
    } else {
        iov = write_data->iov;
    }

    /* 2. calc the packet size */
    for (index = 0; index < write_data->vec_entries; index++) {
        /*valid param check*/
        if ((iov[index].iov_len == 0) || (iov[index].iov_base == NULL)) {
            err = -EINVAL;
            goto out_free;
        }

        packet_size += iov[index].iov_len;
    }

    packet_size += 2; /* ETH FCS when using SGMII */
    if (reserve_hdrs == true) {
        max_headers_size = ISX_HDR_SIZE +
                           sizeof(struct sx_sgmii_ctrl_segment) +
                           sizeof(struct sx_ethernet_header);
    }

    /* 3. allocate skb according to packet size */
    *skb = alloc_skb(packet_size + max_headers_size, gfp_mask);
    if (!*skb) {
        err = -ENOMEM;
        goto out_free;
    }

    if (max_headers_size) {
        skb_reserve(*skb, max_headers_size);
    }

    /*4. copy the scattered buffers of the           */
    /*   packet to be gathered inside the skb buffer */
    for (index = 0; index < write_data->vec_entries; index++) {
        p_skb_data = skb_put(*skb, iov[index].iov_len);
        if (p_skb_data == NULL) {
            printk(KERN_WARNING PFX "copy_ku_to_skb: "
                   "skb_put failed\n");
            err = -EFAULT;
            goto out_free_skb;
        }

        memset(p_skb_data, 0, iov[index].iov_len);

        if (is_from_user) {
            err = copy_from_user(p_skb_data, iov[index].iov_base,
                                 iov[index].iov_len);
            if (err) {
                printk(KERN_WARNING PFX "failed to copy buffer from user index:[%d]\n", index);
                goto out_free_skb;
            }
        } else {
            memcpy(p_skb_data, iov[index].iov_base, iov[index].iov_len);
        }
    }

    goto out_free;

out_free_skb:
    kfree_skb(*skb);    /* drop packet flow, use kfree_skb */
out_free:
    if (is_from_user) {
        kfree(iov);
    }
out_err:
    return err;
}

static int sx_send_loopback(struct sx_dev         *dev,
                            struct ku_write       *write_data,
                            void                  *context,
                            u8                     is_from_user,
                            pid_t                  target_pid,
                            gfp_t                  gfp_mask,
                            struct listener_entry *listener)
{
    struct sx_priv        *priv = sx_priv(dev);
    int                    err = 0;
    struct completion_info ci;
    struct ethhdr         *eth_h = NULL;
    u8                     is_from_rp = IS_RP_DONT_CARE_E;
    u16                    fid = 0;

    memset(&ci, 0, sizeof(ci));
    err = copy_buff_to_skb(&ci.skb, write_data, false, is_from_user, gfp_mask);
    if (err) {
        printk(KERN_WARNING "sx_send_loopback: failed copying buffer to SKB err:[%d]\n", err);
        goto out;
    }

#ifdef SX_DEBUG
    pr_debug(PFX "sx_send_loopback: got from user:\n");
    pr_debug(PFX "sx_send_loopback: trap_id = %u\n",
             write_data->meta.loopback_data.trap_id);
    pr_debug(PFX "sx_send_loopback: buffer_size = %u\n",
             ci.skb->len);
    SX_CORE_HEXDUMP16(ci.skb->data, ci.skb->len);
#endif

    ci.swid = write_data->meta.swid;
    ci.sysport = write_data->meta.system_port_mid;
    ci.hw_synd = write_data->meta.loopback_data.trap_id;
    ci.is_send = 0;
    ci.pkt_type = PKT_TYPE_ETH;
    ci.info.eth.dmac = DMAC_DONT_CARE_VALUE;
    ci.info.eth.ethtype = ETHTYPE_DONT_CARE_VALUE;
    ci.info.eth.emad_tid = TID_DONT_CARE_VALUE;
    ci.is_lag = write_data->meta.loopback_data.is_lag;
    ci.lag_subport = write_data->meta.loopback_data.lag_subport;
    eth_h = (struct ethhdr *)(ci.skb->data);
    if (be16_to_cpu(eth_h->h_proto) == ETH_P_8021Q) {
        ci.is_tagged = VLAN_TAGGED_E;
        ci.vid = be16_to_cpu(((struct vlan_ethhdr*)ci.skb->data)->h_vlan_TCI) & 0xfff;
        if (ci.vid == 0) {
            ci.is_tagged = VLAN_PRIO_TAGGED_E;
        }
    } else {
        ci.is_tagged = VLAN_UNTAGGED_E;
    }
    if (ci.vid == 0) {
        spin_lock_bh(&priv->db_lock);
        if (ci.is_lag) {
            ci.vid = priv->pvid_lag_db[ci.sysport];
        } else {
            ci.vid = priv->pvid_sysport_db[ci.sysport];
        }
        spin_unlock_bh(&priv->db_lock);
    }

    if ((ci.sysport != 0) || (ci.is_lag != 0)) {
        err = sx_core_get_rp_mode(dev, ci.is_lag, ci.sysport, ci.vid, &is_from_rp);
        if (err) {
            printk(KERN_ERR PFX "Failed sx_core_get_rp_mode(). err: %d \n", err);
        }
        ci.info.eth.from_rp = (is_from_rp) ? IS_RP_FROM_RP_E : IS_RP_NOT_FROM_RP_E;

        err = sx_core_get_fid_by_port_vid(dev, &ci, &fid);
        if (err) {
            printk(KERN_ERR PFX "Failed sx_core_get_bridge(). err: %d \n", err);
        }
        ci.bridge_id = fid;
        ci.info.eth.from_bridge = (fid) ? IS_BRIDGE_FROM_BRIDGE_E : IS_BRIDGE_NOT_FROM_BRIDGE_E;
    }

    ci.context = context;
    ci.dest_is_lag = 0;
    ci.dest_lag_subport = 0;
    ci.dest_sysport = 0xFFFF;
    ci.user_def_val = 0;
    ci.mirror_reason = 0;
    ci.mirror_cong = 0xFFFF;
    ci.mirror_lantency = 0xFFFFFF;
    ci.mirror_tclass = 0x1F;
    ci.mirror_elephant = 0;
    ci.device_id = dev->device_id;
    ci.target_pid = target_pid;
    SX_RX_TIMESTAMP_INIT(&ci.rx_timestamp, 0, 0, SXD_TS_TYPE_NONE);

    if (listener) {
        listener->handler(&ci, listener->context);
        listener->rx_pkts++;
        priv->stats.rx_eventlist_by_synd[write_data->meta.loopback_data.trap_id]++;
    } else if (dispatch_pkt(dev, &ci, ci.hw_synd, 0) > 0) {
        priv->stats.rx_eventlist_by_synd[write_data->meta.loopback_data.trap_id]++;
    }

out:
    consume_skb(ci.skb);    /* free unused skb, use consume_skb */
    return err;
}

static int send_trap_ex(const void            *buf,
                        uint32_t               buf_size,
                        uint16_t               trap_id,
                        u8                     is_from_user,
                        u8                     device_id,
                        pid_t                  target_pid,
                        gfp_t                  gfp_mask,
                        struct listener_entry *listener)
{
    struct sx_dev  *dev;
    struct ku_write write_data;
    struct ku_iovec iov;
    int             err = 0;

    if (is_sgmii_device(device_id)) {
        dev = sx_glb.fake_dev;
    } else {
        dev = sx_dev_db_get_dev_by_id(device_id);
        if (!dev) {
            printk(KERN_WARNING "device is NULL\n");
            err = 1;
            goto out;
        }
    }

    memset(&iov, 0, sizeof(iov));
    iov.iov_base = (void*)buf;
    iov.iov_len = buf_size;

    memset(&write_data, 0, sizeof(write_data));
    write_data.vec_entries = 1;
    write_data.iov = &iov;
    write_data.meta.type = SX_PKT_TYPE_LOOPBACK_CTL;
    write_data.meta.dev_id = device_id;
    write_data.meta.etclass = 6;
    write_data.meta.loopback_data.trap_id = trap_id;

    err = sx_send_loopback(dev, &write_data, NULL, is_from_user, target_pid, gfp_mask, listener);

out:
    return err;
}

int send_trap(const void *buf,
              uint32_t    buf_size,
              uint16_t    trap_id,
              u8          is_from_user,
              u8          device_id,
              pid_t       target_pid,
              gfp_t       gfp_mask)
{
    return send_trap_ex(buf, buf_size, trap_id, is_from_user, device_id, target_pid, gfp_mask, NULL);
}
EXPORT_SYMBOL(send_trap);


int sx_send_health_event(uint8_t                  dev_id,
                         sxd_health_cause_t       cause,
                         sxd_health_severity_t    severity,
                         uint8_t                  irisc_id,
                         sxd_event_health_data_t *event_extra_data,
                         struct listener_entry   *listener)
{
    sxd_event_health_notification_t sdk_health;

    memset(&sdk_health, 0, sizeof(sdk_health));

    sdk_health.device_id = dev_id;
    sdk_health.cause = cause;
    sdk_health.severity = severity;
    sdk_health.irisc_id = irisc_id;

    sdk_health.was_debug_started = false;
    if (event_extra_data) {
        memcpy(&sdk_health.data, event_extra_data, sizeof(sxd_event_health_data_t));
    }

    /* Send SDK health event */
    printk(KERN_NOTICE "Sending SDK health event [dev=%u, cause=%d, severity=%d, irisc=%u, sync_new_listener=%s]\n",
           sdk_health.device_id,
           sdk_health.cause,
           sdk_health.severity,
           sdk_health.irisc_id,
           ((listener) ? "true" : "false"));

    return send_trap_ex(&sdk_health,
                        sizeof(sdk_health),
                        SXD_TRAP_ID_SDK_HEALTH_EVENT,
                        0,
                        dev_id,
                        TARGET_PID_DONT_CARE,
                        GFP_KERNEL,
                        listener);
}


/**
 * Prepare a meta-data struct from the edata
 *
 * param[in] metadata_p   - The place the meta-data + packet should be copied to
 * param[in] edata - The packet and meta-data parameters
 *
 * returns: void
 */
void sx_copy_pkt_metadata_prepare(struct ku_read *metadata_p, struct event_data *edata_p)
{
    metadata_p->length = edata_p->skb->len;
    metadata_p->system_port = edata_p->system_port;
    metadata_p->trap_id = edata_p->trap_id;
    metadata_p->is_lag = edata_p->is_lag;
    metadata_p->swid = edata_p->swid;
    metadata_p->original_packet_size = edata_p->original_packet_size;
    if (edata_p->is_lag) {
        metadata_p->lag_subport = edata_p->lag_sub_port;
    }

    metadata_p->has_timestamp = (edata_p->rx_timestamp.ts_type != SXD_TS_TYPE_NONE);
    if (metadata_p->has_timestamp) {
        metadata_p->timestamp_type = edata_p->rx_timestamp.ts_type;
        metadata_p->timestamp.tv_sec = edata_p->rx_timestamp.timestamp.tv_sec;
        metadata_p->timestamp.tv_nsec = edata_p->rx_timestamp.timestamp.tv_nsec;
    }

    metadata_p->dest_is_lag = edata_p->dest_is_lag;
    metadata_p->dest_lag_subport = edata_p->dest_lag_subport;
    metadata_p->dest_sysport = edata_p->dest_sysport;
    metadata_p->user_def_val = edata_p->user_def_val;

    metadata_p->mirror_reason = edata_p->mirror_reason;
    metadata_p->mirror_cong = edata_p->mirror_cong;
    metadata_p->mirror_lantency = edata_p->mirror_lantency;
    metadata_p->mirror_tclass = edata_p->mirror_tclass;
    metadata_p->mirror_elephant = edata_p->mirror_elephant;
    if (!sx_core_has_predefined_devices()) {
        metadata_p->dev_id = edata_p->dev_id;
    } else {
        /* In multi-asic systems, SDK processes are oblivious to other asics.
         * Each SDK is only aware of one device - with device_id 1.
         */
        metadata_p->dev_id = 1;
    }
    metadata_p->channel_experienced_drop = edata_p->channel_experienced_drop;
}


/**
 * Get edata which is the packet parameters and a place to copy it (buf).
 *
 * Create a meta-data struct from the edata and copy it to the user
 * After it in sequential way copy the packet
 * (NOTE: the function assuming there is enough place in the given buf )
 *
 * param[in] buf   - The place the meta-data + packet should be copied to
 * param[in] edata - The packet and meta-data parameters
 *
 * returns: positive number on success (the copied size of meta-data + packet)
 *	    !0 error
 */
static int copy_pkt_to_user(char __user *buf, struct event_data *edata)
{
    struct ku_read metadata;
    int            copied_size = 0;

    memset(&metadata, 0, sizeof(metadata));

#ifdef SX_DEBUG
    pr_debug(PFX "copy_pkt_to_user()\n");
#endif

    sx_copy_pkt_metadata_prepare(&metadata, edata);

    if (copy_to_user(buf, &metadata, sizeof(metadata))) {
        return -EFAULT;
    }

    copied_size += sizeof(metadata);
    if (copy_to_user(buf + copied_size, edata->skb->data, edata->skb->len)) {
        return -EFAULT;
    }

    copied_size += edata->skb->len;
#ifdef SX_DEBUG
    pr_debug(PFX " copy_pkt_to_user() metadata.length=[%llu] " \
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
 * NOTE: The function assumes that there is enough free space in
 * the buffer (which was already checked before calling here)
 *
 * param[in] edata - The packet and meta-data parameters
 * param[in] buf   - the data buffer, ku_read struct
 *
 * returns: The size of data which copied to the user buffer
 *	   !0 error
 */
static int copy_edata_to_user(struct event_data *edata, char __user *buf)
{
    struct event_data *tmp = NULL;
    int                so_far_copied = 0;
    int                copied_size = 0;
    int                err = 0;
    struct list_head  *pos, *q;
    struct sx_dev    * sx_dev = NULL;
    struct sx_priv    *priv = NULL;

#ifdef SX_DEBUG
    pr_debug(PFX " copy_edata_to_user()\n");
#endif
    list_for_each_safe(pos, q, &edata->list) {
        tmp = list_entry(pos, struct event_data, list);
        copied_size = copy_pkt_to_user(buf + so_far_copied, tmp);
        if (copied_size < 0) {
            err = copied_size;
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
        priv = sx_priv(sx_dev);

        if (sx_dev && !priv->stats.eventlist_drops_counter) {
            printk(KERN_WARNING PFX
                   "copy_pkt_to_user failed, " \
                   "dropping RX packet\n");
        }

        inc_eventlist_drops_counter(priv, tmp->trap_id);
        list_del(pos);
        kfree_skb(tmp->skb);
        kfree(tmp);
    }

    return so_far_copied ? so_far_copied : err;
}


/**
 *
 * Create edata linked-list and return it
 *
 * while the event list is not empty, pop event-data ,
 * if the packet size in the event-data is not to big then add it to
 * the buffer counter and continue while the buffer counter is
 * less then the user buffer
 *
 * param[in] evlist - The given event list
 * param[in] user_counter  - The number of bites to send(the user buffer size)
 *
 *
 * returns:
 *	edata list on - success
 *      NULL          - error
 * retval:
 *      0 on success, otherwise the size of the buffer needed for the
 *      first packet if there is enough space in the buffer for
 *      metadata, -ENOMEM if not
 */
int get_edata_from_elist(int               *evlist_size,
                         struct event_data *edata_list,
                         struct list_head  *evlist,
                         size_t             user_counter,
                         int                multi_packet_read_enable)
{
    struct  list_head  *pos, *q;
    struct  event_data *edata = NULL;
    size_t              buf_counter = 0;
    int                 pkt_size = 0;

    list_for_each_safe(pos, q, evlist) {
        edata = list_entry(pos, struct event_data, list);
        pkt_size = sizeof(struct ku_read) + edata->skb->len;
        if (buf_counter + pkt_size > user_counter) {
            break;
        }

        buf_counter += pkt_size;
        list_del(pos);
        list_add_tail(&edata->list, &edata_list->list);
        (*evlist_size)--;
        if (multi_packet_read_enable == false) {
            break;
        }
    }

    /* Not enough place for even a single packet */
    if (0 == buf_counter) {
        if (sizeof(struct ku_read) > user_counter) {
            return -ENOMEM;
        }
        return pkt_size;
    }
    return 0;
}

static int is_same_listener(u8                               swid,
                            enum l2_type                     type,
                            u8                               is_default,
                            const union ku_filter_critireas *critireas,
                            void                            *context,
                            struct listener_entry           *listener,
                            cq_handler                       handler)
{
    if (listener->is_default != is_default) {
        return false;
    }

    if (is_default) {
        return true;
    }

    if (listener->context != context) {
        return false;
    }

    if (listener->swid != swid) {
        return false;
    }

    if (listener->listener_type != type) {
        return false;
    }

    switch (type) {
    case L2_TYPE_DONT_CARE:
        break;

    case L2_TYPE_ETH:
        if (listener->critireas.eth.ethtype != critireas->eth.ethtype) {
            return false;
        }

        if (listener->critireas.eth.dmac != critireas->eth.dmac) {
            return false;
        }

        if (listener->critireas.eth.emad_tid != critireas->eth.emad_tid) {
            return false;
        }

        if (listener->critireas.eth.from_rp != critireas->eth.from_rp) {
            return false;
        }

        if (listener->critireas.eth.from_bridge != critireas->eth.from_bridge) {
            return false;
        }

        break;

    case L2_TYPE_IB:
        if (listener->critireas.ib.qpn != critireas->ib.qpn) {
            return false;
        }

        break;

    default:
        break;
    }

    if ((handler != NULL) && (listener->handler != handler)) {
        return false;
    }

    return true;
}

static int listener_register_filter_is_empty(struct listener_register_filter_entry *register_filter_listener)
{
    int i = 0;

    if ((register_filter_listener->is_global_register == 1) || (register_filter_listener->is_global_filter == 1)) {
        return 0;
    }
    for (i = 0; i < FROM_BITS_TO_U64((MAX_PHYPORT_NUM + 1)); i++) {
        if (register_filter_listener->ports_registers[i] != 0) {
            return 0;
        }
    }
    for (i = 0; i < FROM_BITS_TO_U64((SXD_MAX_VLAN_NUM + 1));
         i++) {
        if (register_filter_listener->vlans_registers[i] != 0) {
            return 0;
        }
    }
    for (i = 0; i < FROM_BITS_TO_U64((MAX_LAG_NUM + 1)); i++) {
        if (register_filter_listener->lags_registers[i] != 0) {
            return 0;
        }
    }
    for (i = 0; i < FROM_BITS_TO_U64((MAX_PHYPORT_NUM + 1)); i++) {
        if (register_filter_listener->ports_filters[i] != 0) {
            return 0;
        }
    }
    for (i = 0; i < FROM_BITS_TO_U64((SXD_MAX_VLAN_NUM + 1)); i++) {
        if (register_filter_listener->vlans_filters[i] != 0) {
            return 0;
        }
    }
    for (i = 0; i < FROM_BITS_TO_U64((MAX_LAG_NUM + 1)); i++) {
        if (register_filter_listener->lags_filters[i] != 0) {
            return 0;
        }
    }

    return 1;
}

static void listener_register_filter_entry_update(u8                                     is_register,
                                                  const struct ku_port_vlan_params      *port_vlan,
                                                  struct listener_register_filter_entry *register_filter_listener,
                                                  int                                    set)
{
    if (is_register) {
        register_filter_listener->is_global_register = 0;
        switch (port_vlan->port_vlan_type) {
        case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
            if (set) {
                register_filter_listener->is_global_register = 1;
            }
            break;

        case KU_PORT_VLAN_PARAMS_TYPE_PORT:
            SX_CORE_REGISTER_FILTER_BITMASK_SET(register_filter_listener->ports_registers, port_vlan->sysport, set);
            break;

        case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
            SX_CORE_REGISTER_FILTER_BITMASK_SET(register_filter_listener->vlans_registers, port_vlan->vlan, set);
            break;

        case KU_PORT_VLAN_PARAMS_TYPE_LAG:
            SX_CORE_REGISTER_FILTER_BITMASK_SET(register_filter_listener->lags_registers, port_vlan->lag_id, set);
            break;

        case KU_PORT_VLAN_PARAMS_TYPE_NONE:
            SX_CORE_REGISTER_FILTER_BITMASK_SET_ALL_ZERO(register_filter_listener, is_register);
            break;
        }
    } else {
        register_filter_listener->is_global_filter = 0;
        switch (port_vlan->port_vlan_type) {
        case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
            if (set) {
                register_filter_listener->is_global_filter = 1;
            }
            break;

        case KU_PORT_VLAN_PARAMS_TYPE_PORT:
            SX_CORE_REGISTER_FILTER_BITMASK_SET(register_filter_listener->ports_filters, port_vlan->sysport, set);
            break;

        case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
            SX_CORE_REGISTER_FILTER_BITMASK_SET(register_filter_listener->vlans_filters, port_vlan->vlan, set);
            break;

        case KU_PORT_VLAN_PARAMS_TYPE_LAG:
            SX_CORE_REGISTER_FILTER_BITMASK_SET(register_filter_listener->lags_filters, port_vlan->lag_id, set);
            break;

        case KU_PORT_VLAN_PARAMS_TYPE_NONE:
            SX_CORE_REGISTER_FILTER_BITMASK_SET_ALL_ZERO(register_filter_listener, is_register);
            break;
        }
    }
}

static int __sx_core_port_vlan_listener_exist(const struct ku_port_vlan_params *port_vlan,
                                              struct listener_entry            *listener,
                                              u8                                is_register)
{
    if (is_register) {
        switch (port_vlan->port_vlan_type) {
        case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
            return listener->listener_register_filter.is_global_register;

        case KU_PORT_VLAN_PARAMS_TYPE_PORT:
            return SX_CORE_REGISTER_FILTER_BIT_IS_SET(listener->listener_register_filter.ports_registers,
                                                      port_vlan->sysport);

        case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
            return SX_CORE_REGISTER_FILTER_BIT_IS_SET(listener->listener_register_filter.vlans_registers,
                                                      port_vlan->vlan);

        case KU_PORT_VLAN_PARAMS_TYPE_LAG:
            return SX_CORE_REGISTER_FILTER_BIT_IS_SET(listener->listener_register_filter.lags_registers,
                                                      port_vlan->lag_id);

        default:
            break;
        }
    } else { /* filter */
        switch (port_vlan->port_vlan_type) {
        case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
            return listener->listener_register_filter.is_global_filter;

        case KU_PORT_VLAN_PARAMS_TYPE_PORT:
            return SX_CORE_REGISTER_FILTER_BIT_IS_SET(listener->listener_register_filter.ports_filters,
                                                      port_vlan->sysport);

        case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
            return SX_CORE_REGISTER_FILTER_BIT_IS_SET(listener->listener_register_filter.vlans_filters,
                                                      port_vlan->vlan);

        case KU_PORT_VLAN_PARAMS_TYPE_LAG:
            return SX_CORE_REGISTER_FILTER_BIT_IS_SET(listener->listener_register_filter.lags_filters,
                                                      port_vlan->lag_id);

        default:
            break;
        }
    }

    return 0;
}

/**
 * Create new listener with the given swid,type,critireas and add it to an entry
 * in sx device listeners data-base when the entry is according to the hw_synd
 *
 * Note: A default listener is a listener which receives all the packets
 *       that haven't been consumed by another non-default listener.
 *
 * param swid            [in] - The listener swid
 * param hw_synd         [in] - The listener syndrome number
 * param type            [in] - The listener type - ETH,IB or FC, or Don't care
 * param called_pid      [in] - Process ID of the caller
 * param is_default      [in] - If the listener is a default listener
 * param is_register     [in] - If the requested action is register or filter
 * param filter_critireas[in] - The listener additional filter critireas
 * param handler         [in] -
 * param context         [in] -
 * param check_dup       [in] - block the listener from registering twice to same trap.
 *
 * returns: 0 success
 *	   !0 error
 *
 */
int sx_core_add_synd(u8                                swid,
                     u16                               hw_synd,
                     enum l2_type                      type,
                     pid_t                             caller_pid,
                     const char                       *caller_name,
                     u8                                is_default,
                     const union ku_filter_critireas  *crit,
                     cq_handler                        handler,
                     void                             *context,
                     check_dup_e                       check_dup,
                     struct sx_dev                   * sx_dev,
                     const struct ku_port_vlan_params *port_vlan,
                     u8                                is_register)
{
    struct sx_priv                   *priv;
    struct listeners_and_rf_info     *info = NULL;
    struct listener_entry            *listener = NULL;
    struct listener_entry            *listener_filter = NULL;
    struct listener_entry            *new_listener = NULL;
    unsigned int                      found_same_listener = 0, found_same_port_vlan_listener = 0;
    struct ku_port_vlan_params        tmp_port_vlan = {0};
    const struct ku_port_vlan_params *port_vlan_p;

    /* if NULL use default sx_dev */
    if (sx_dev == NULL) {
        sx_dev = sx_dev_db_get_default_device();
        if (sx_dev == NULL) {
            printk(KERN_ERR PFX "sx_dev_db_get_default_device return sx_dev == NULL\n");
            return -EINVAL;
        }
    }

    priv = sx_priv(sx_dev);

    if (!handler) {
        printk(KERN_WARNING PFX "sx_core_add_synd: Cannot add listener, handler is NULL\n");
        return -EINVAL;
    }

    new_listener = kmalloc(sizeof(*new_listener), GFP_ATOMIC);
    if (!new_listener) {
        printk(KERN_WARNING PFX "sx_core_add_synd: Failed allocating memory for the new listener\n");
        return -ENOMEM;
    }
    memset(new_listener, 0, sizeof(*new_listener));
    new_listener->swid = swid;
    new_listener->pid = caller_pid;
    if (caller_name) {
        strncpy(new_listener->pname, caller_name, sizeof(listener->pname) - 1);
    }
    new_listener->critireas = *crit;
    new_listener->handler = handler;
    new_listener->context = context;
    new_listener->listener_type = type;
    new_listener->is_default = is_default;
    new_listener->rx_pkts = 0;
    INIT_LIST_HEAD(&new_listener->gc_list);

    port_vlan_p = port_vlan;
    if (!port_vlan_p) {
        tmp_port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        port_vlan_p = &tmp_port_vlan;
    }

    mutex_lock(&priv->listeners_and_rf_db.lock);
    info = priv->listeners_and_rf_db.info;
    if (!info) {
        printk(KERN_ERR "listeners database does not exist!\n");
        kfree(new_listener);
        goto out;
    }

    listener_filter = new_listener;

    list_for_each_entry(listener, &info->per_synd_list[hw_synd], list) {
        if (is_same_listener(swid, type, is_default, crit, context, listener, handler)) {
            found_same_port_vlan_listener = __sx_core_port_vlan_listener_exist(port_vlan,
                                                                               listener,
                                                                               is_register);
            if ((check_dup == CHECK_DUP_ENABLED_E) &&
                found_same_port_vlan_listener) {
                kfree(new_listener);
                goto out;
            }
            found_same_listener = 1;
            listener_filter = listener;

            kfree(new_listener);
            break;
        }
    }

    listener_register_filter_entry_update(is_register, port_vlan_p, &(listener_filter->listener_register_filter), 1);

    if (found_same_listener == 0) {
        if (is_default) {
            list_add_tail_rcu(&(new_listener->list), &(info->per_synd_list[hw_synd]));
        } else {
            list_add_rcu(&(new_listener->list), &(info->per_synd_list[hw_synd]));
        }

        if (hw_synd == SXD_TRAP_ID_SDK_HEALTH_EVENT) {
            sx_health_handle_new_listener(sx_dev, new_listener);
        }
    }

out:
    mutex_unlock(&priv->listeners_and_rf_db.lock);
    return 0;
}
EXPORT_SYMBOL(sx_core_add_synd);

int sx_core_remove_synd(u8                                swid,
                        u16                               hw_synd,
                        enum l2_type                      type,
                        u8                                is_default,
                        const union ku_filter_critireas  *critireas,
                        void                             *context,
                        struct sx_dev                    *sx_dev,
                        cq_handler                        handler,
                        const struct ku_port_vlan_params *port_vlan,
                        u8                                is_register,
                        u8                               *synd_was_removed)
{
    struct sx_priv                   *priv;
    struct listeners_and_rf_info     *info = NULL;
    struct listener_entry            *listener = NULL, *q = NULL;
    int                               entry = 0;
    struct ku_port_vlan_params        tmp_port_vlan;
    const struct ku_port_vlan_params *port_vlan_p;
    struct list_head                  listeners_gc;

    memset(&tmp_port_vlan, 0, sizeof(tmp_port_vlan));
    if (synd_was_removed != NULL) {
        *synd_was_removed = 0;
    }

    if (sx_dev == NULL) {
        sx_dev = sx_dev_db_get_default_device();
        if (!sx_dev) {
            printk(KERN_ERR "default device wasn't found\n");
            return -ENODEV;
        }
    }

    priv = sx_priv(sx_dev);

    port_vlan_p = port_vlan;
    if (!port_vlan_p) {
        tmp_port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        port_vlan_p = &tmp_port_vlan;
    }

    __listeners_gc_init(&listeners_gc);

    mutex_lock(&priv->listeners_and_rf_db.lock);
    info = priv->listeners_and_rf_db.info;
    if (!info) {
        printk(KERN_ERR "listeners database does not exist!\n");
        goto out;
    }

    entry = hw_synd;

    list_for_each_entry_safe(listener, q, &info->per_synd_list[entry], list) {
        if (is_same_listener(swid, type, is_default, critireas, context, listener, handler)) {
            listener_register_filter_entry_update(is_register,
                                                  port_vlan_p,
                                                  &(listener->listener_register_filter),
                                                  0);
            if (listener_register_filter_is_empty(&(listener->listener_register_filter))) {
                __listeners_gc_add(&listeners_gc, listener);
                if (synd_was_removed != NULL) {
                    *synd_was_removed = 1;
                }
            }
        }
    }

out:
    mutex_unlock(&priv->listeners_and_rf_db.lock);
    __listeners_gc_finish(&listeners_gc);
    return 0;
}
EXPORT_SYMBOL(sx_core_remove_synd);

void sx_cq_handle_event_data_prepare(struct event_data      *edata_p,
                                     struct sk_buff         *skb_p,
                                     struct completion_info *comp_info_p)
{
    INIT_LIST_HEAD(&edata_p->list);

    edata_p->skb = skb_p;
    edata_p->system_port = comp_info_p->sysport;
    edata_p->trap_id = comp_info_p->hw_synd;
    edata_p->dev_id = comp_info_p->device_id;
    edata_p->dev = comp_info_p->dev;
    edata_p->is_lag = comp_info_p->is_lag;
    edata_p->lag_sub_port = comp_info_p->lag_subport;
    edata_p->swid = comp_info_p->swid;
    edata_p->original_packet_size = comp_info_p->original_packet_size;
    SX_RX_TIMESTAMP_COPY(&edata_p->rx_timestamp, &comp_info_p->rx_timestamp);
    edata_p->dest_is_lag = comp_info_p->dest_is_lag;

    edata_p->dest_lag_subport = comp_info_p->dest_lag_subport;
    edata_p->dest_sysport = comp_info_p->dest_sysport;
    edata_p->user_def_val = comp_info_p->user_def_val;

    edata_p->mirror_reason = comp_info_p->mirror_reason;
    edata_p->mirror_cong = comp_info_p->mirror_cong;
    edata_p->mirror_lantency = comp_info_p->mirror_lantency;
    edata_p->mirror_tclass = comp_info_p->mirror_tclass;
    edata_p->mirror_elephant = comp_info_p->mirror_elephant;

#ifdef SX_DEBUG
    pr_debug(PFX " %s(): skb->len=[%d]  sysport=[%d]"
             " hw_synd(trap_id)=[%d]\n", __func__,
             skb_p->len, edata_p->system_port, edata_p->trap_id);
#endif
}


static int check_valid_profile(struct sx_dev *dev, struct sx_pci_profile *profile)
{
    struct sx_priv *priv = sx_priv(dev);
    int             i, j;
    uint8_t         rdq_num = 0;
    uint16_t        entry_size = 0;
    int             rc = 0;

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        for (j = 0; j < NUMBER_OF_ETCLASSES; j++) {
            if (profile->tx_prof[i][j].sdq >=
                priv->dev_cap.max_num_sdqs) {
                printk(KERN_WARNING PFX "sdq num is > max\n");
                return -EINVAL;
            }
            if (profile->tx_prof[i][j].stclass >= 8) {
                printk(KERN_WARNING PFX "stclass num is > "
                       "max\n");
                return -EINVAL;
            }
        }
    }
    if (profile->emad_tx_prof.sdq >= priv->dev_cap.max_num_sdqs) {
        printk(KERN_WARNING PFX "emad sdq num is > max\n");
        return -EINVAL;
    }
    if (profile->emad_tx_prof.stclass >= 8) {
        printk(KERN_WARNING PFX "emad stclass num is > max\n");
        return -EINVAL;
    }

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        /* Normalize the RDQ number according chip capability */
        if (profile->rdq_count[i] > (priv->dev_cap.max_num_rdqs - 1)) {
            printk(KERN_WARNING PFX "Normalize rdq num %d to dev_cap_max_num_rdq %d\n",
                   profile->rdq_count[i], priv->dev_cap.max_num_rdqs);
            profile->rdq_count[i] = priv->dev_cap.max_num_rdqs - 1;
        }

        for (j = 0; j < profile->rdq_count[i]; j++) {
            if (profile->rdq[i][j] >= priv->dev_cap.max_num_rdqs) {
                printk(KERN_WARNING PFX "rdq[%d][%d] = %d "
                       "> max\n", i, j, profile->rdq[i][j]);
                return -EINVAL;
            }
        }
    }
    if ((profile->pci_profile >= PCI_PROFILE_EN_SINGLE_SWID) &&
        (profile->emad_rdq >= priv->dev_cap.max_num_rdqs)) {
        printk(KERN_WARNING PFX "emad_rdq = %d > max\n",
               profile->emad_rdq);
        return -EINVAL;
    }

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if ((profile->swid_type[i] != SX_KU_L2_TYPE_IB) &&
            (profile->swid_type[i] != SX_KU_L2_TYPE_ETH) &&
            (profile->swid_type[i] != SX_KU_L2_TYPE_ROUTER_PORT) &&
            (profile->swid_type[i] != SX_KU_L2_TYPE_DONT_CARE)) {
            printk(KERN_WARNING PFX "for swid %d type = "
                   "%d is wrong!\n",
                   i, profile->swid_type[i]);
            return -EINVAL;
        }
    }

    rc = sx_core_get_rdq_param_max(dev, &rdq_num, &entry_size);
    if (rc) {
        printk(KERN_ERR PFX "Error: failed to get max RDQ params\n");
        return rc;
    }

    for (i = 0; i < rdq_num; i++) {
        if ((profile->rdq_properties[i].number_of_entries >
             1 << priv->dev_cap.log_max_rdq_sz) ||
            (profile->rdq_properties[i].entry_size >
             entry_size)) {
            printk(KERN_WARNING PFX "%s:%d\n", __FILE__, __LINE__);
            printk(KERN_WARNING PFX "%d: n_enties %d , max_rdq_sz:"
                   " %d , entry_sz:%d, SX_MAX_MSG_SZ:%d\n",
                   i,
                   profile->rdq_properties[i].number_of_entries,
                   1 << priv->dev_cap.log_max_rdq_sz,
                   profile->rdq_properties[i].entry_size,
                   entry_size);
            return -EINVAL;
        }
    }

    for (i = 0; i < NUMBER_OF_SDQS; i++) {
        if (profile->cpu_egress_tclass[i] >= 64) {
            printk(KERN_WARNING PFX "cpu_egress_tclass[%d] = "
                   "%d > max\n",
                   i, profile->cpu_egress_tclass[i]);
            return -EINVAL;
        }
    }

    return 0;
}

int sx_send_enable_ib_swid_events(struct sx_dev *dev, u8 swid)
{
    struct sx_priv      *priv = sx_priv(dev);
    int                  i;
    int                  err = 0;
    union sx_event_data *event_data = NULL;
    union sx_event_data *rpa_init_event_data = NULL;
    bool                 first_ib_swid;

    if (priv->profile.pci_profile.swid_type[swid] == SX_KU_L2_TYPE_IB) {
        event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
        if (!event_data) {
            printk(KERN_ERR "%s: failed to allocate event data\n", __FUNCTION__);
            err = -ENOMEM;
            goto out;
        }

        event_data->ib_swid_change.swid = swid;
        event_data->ib_swid_change.dev_id = dev->device_id;
        sx_core_dispatch_event(dev, SX_DEV_EVENT_IB_SWID_UP, event_data);

        spin_lock(&priv->profile.profile_lock);
        first_ib_swid = priv->profile.first_ib_swid;
        priv->profile.first_ib_swid = false;
        spin_unlock(&priv->profile.profile_lock);
        if (first_ib_swid) {
            rpa_init_event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
            if (!rpa_init_event_data) {
                printk(KERN_ERR "%s: failed to allocate rpa_event_data\n", __FUNCTION__);
                err = -ENOMEM;
                goto out;
            }

            for (i = 0; i < NUMBER_OF_SWIDS; i++) {
                if (priv->profile.pci_profile.ipoib_router_port_enable[i]) {
                    rpa_init_event_data->rpa_init.swid[rpa_init_event_data->rpa_init.num_of_ib_swids++] = i;
                }
            }

            if (rpa_init_event_data->rpa_init.num_of_ib_swids != 0) {
                rpa_init_event_data->rpa_init.max_pkey = priv->profile.pci_profile.max_pkey;
                sx_core_dispatch_event(dev, SX_DEV_EVENT_TYPE_RPA_INIT, rpa_init_event_data);
            }
        }
    } else {
        printk(KERN_ERR PFX "Error: try to send IB_SWID_UP event on swid %d from non-IB type %d, ",
               swid, priv->profile.pci_profile.swid_type[swid]);
        err = -EINVAL;
        goto out;
    }

out:
    if (event_data) {
        kfree(event_data);
    }

    if (rpa_init_event_data) {
        kfree(rpa_init_event_data);
    }

    return err;
}


int sx_enable_swid(struct sx_dev *dev, int sx_dev_id, u8 swid, int synd, u64 mac)
{
    struct sx_priv      *priv = sx_priv(dev);
    int                  i;
    int                  err = 0;
    u8                   dqn;
    u64                  dq_bitmap = 0;
    struct sx_dq        *dq;
    union sx_event_data *event_data = NULL;
    unsigned long        flags;
    bool                 dev_profile_set;

    /* IF PCI-E path is not valid, no need to open DQs */
    if (!sx_dpt_is_path_valid(sx_dev_id, DPT_PATH_PCI_E)) {
        printk(KERN_INFO PFX "PCIe path is not valid for device %u, "
               "will not open DQs\n",
               sx_dev_id);
        goto send_events;
    }

    for (i = 0; i < NUMBER_OF_ETCLASSES; i++) {
        err = sx_get_sqd_num(dev, swid, i, &dqn);
        if (err) {
            printk(KERN_ERR PFX "Error retrieving sx_get_sdq_cb callback structure! err=[%d]\n", err);
            goto out;
        }

        spin_lock_irqsave(&priv->sdq_table.lock, flags);
        dq = priv->sdq_table.dq[dqn];
        spin_unlock_irqrestore(&priv->sdq_table.lock, flags);
        if (!dq) {
            err = sx_core_create_sdq(dev,
                                     1 << priv->dev_cap.log_max_sdq_sz, dqn, &dq);
            if (err) {
                goto out;
            }

            dq_bitmap |= (1ULL << dqn);
            /* We only want to increase the refcount if the dq is in use in another swid */
        } else if (!(dq_bitmap & (1ULL << dqn))) {
            atomic_inc(&dq->refcount);
        }
    }

    dq_bitmap = 0;
    for (i = 0; i < priv->profile.pci_profile.rdq_count[swid]; i++) {
        dqn = priv->profile.pci_profile.rdq[swid][i];
        spin_lock_irqsave(&priv->rdq_table.lock, flags);
        dq = priv->rdq_table.dq[dqn];
        spin_unlock_irqrestore(&priv->rdq_table.lock, flags);
        if (!dq) {
            err = sx_core_create_rdq(dev, priv->profile.pci_profile.rdq_properties[dqn].number_of_entries,
                                     dqn, &dq);
            if (err) {
                printk(KERN_ERR PFX "Failed to create RDQ %d \n", dqn);
                goto out;
            }

            dq_bitmap |= (1ULL << dqn);
        } else if (!(dq_bitmap & (1ULL << dqn))) {
            atomic_inc(&dq->refcount);
        }
    }

send_events:
    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        printk(KERN_ERR "%s: failed to allocate event data\n", __FUNCTION__);
        err = -ENOMEM;
        goto out;
    }

    spin_lock(&priv->profile.profile_lock);
    if (is_sgmii_supported()) {
        priv->profile.dev_profile_set = true;
    }
    dev_profile_set = priv->profile.dev_profile_set;
    spin_unlock(&priv->profile.profile_lock);
    if ((priv->profile.pci_profile.swid_type[swid] == SX_KU_L2_TYPE_IB) &&
        dev_profile_set) {
        err = sx_send_enable_ib_swid_events(dev, swid);
        if (err) {
            spin_lock(&priv->profile.profile_lock);
            priv->profile.dev_profile_set = false;
            spin_unlock(&priv->profile.profile_lock);
            goto out;
        }
    } else if (priv->profile.pci_profile.swid_type[swid] == SX_KU_L2_TYPE_ETH) {
        priv->swid_data[swid].eth_swid_data.synd = synd;
        priv->swid_data[swid].eth_swid_data.mac = mac;
        event_data->eth_swid_up.swid = swid;
        event_data->eth_swid_up.synd = synd;
        event_data->eth_swid_up.mac = mac;
        sx_core_dispatch_event(dev, SX_DEV_EVENT_ETH_SWID_UP, event_data);
    }

    sx_bitmap_set(&priv->swid_bitmap, swid);

out:
    if (event_data) {
        kfree(event_data);
    }

    return err;
}

void sx_disable_swid(struct sx_dev *dev, u8 swid)
{
    struct sx_priv      *priv = sx_priv(dev);
    int                  i;
    u8                   dqn;
    struct sx_dq        *dq;
    union sx_event_data *event_data = NULL;
    bool                 dev_profile_set;
    int                  err = 0;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        printk(KERN_WARNING PFX "Failed to allocate memory for event data\n");
        goto out;
    }

    if (!sx_bitmap_test(&priv->swid_bitmap, swid)) {
        printk(KERN_WARNING PFX "SWID %u is not set\n", swid);
        goto out;
    }

    for (i = 0; i < NUMBER_OF_ETCLASSES; i++) {
        err = sx_get_sqd_num(dev, swid, i, &dqn);
        if (err) {
            printk(KERN_ERR PFX "Error retrieving sx_get_sdq_cb callback structure! err=[%d]\n", err);
            break;
        }

        dq = priv->sdq_table.dq[dqn];
        if (dq && (atomic_read(&dq->refcount) == 1)) {
            sx_core_destroy_sdq(dev, dq);
            priv->sdq_table.dq[dqn] = NULL;
        } else if (dq) {
            atomic_dec(&dq->refcount);
        }
    }

    for (i = 0; i < priv->profile.pci_profile.rdq_count[swid]; i++) {
        dqn = priv->profile.pci_profile.rdq[swid][i];
        dq = priv->rdq_table.dq[dqn];
        if (dq && (atomic_read(&dq->refcount) == 1)) {
            disable_monitor_rdq(dev, dqn, 1);
            sx_core_destroy_rdq(dev, dq);
            priv->rdq_table.dq[dqn] = NULL;
        } else if (dq) {
            atomic_dec(&dq->refcount);
        }
    }

    spin_lock(&priv->profile.profile_lock);
    dev_profile_set = priv->profile.dev_profile_set;
    spin_unlock(&priv->profile.profile_lock);
    event_data->ib_swid_change.swid = swid;
    event_data->ib_swid_change.dev_id = priv->profile.pci_profile.dev_id;
    if ((priv->profile.pci_profile.swid_type[swid] == SX_KU_L2_TYPE_IB) && dev_profile_set) {
        sx_core_dispatch_event(dev, SX_DEV_EVENT_IB_SWID_DOWN, event_data);
    } else if (priv->profile.pci_profile.swid_type[swid] == SX_KU_L2_TYPE_ETH) {
        sx_core_dispatch_event(dev, SX_DEV_EVENT_ETH_SWID_DOWN, event_data);
    }

    sx_bitmap_free(&priv->swid_bitmap, swid);

out:
    if (event_data) {
        kfree(event_data);
    }
}

/*
 *  Workaround for rdq stuck because of wqe_too_short error.
 *  Force rdq size to be maximum allowed on SX
 */
static void __sx_adjust_rdq_size(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             i;
    int             rc = 0;
    uint8_t         rdq_num = 0;
    uint16_t        entry_size = 0;

    rc = sx_core_get_rdq_param_max(dev, &rdq_num, &entry_size);
    if (rc) {
        printk(KERN_ERR PFX "Error: failed to get max RDQ num\n");
    }

    for (i = 0; i < rdq_num; i++) {
        if (priv->profile.pci_profile.rdq_properties[i].entry_size != 0) {
            priv->profile.pci_profile.rdq_properties[i].entry_size = entry_size;
        }
    }
}

int sx_handle_set_profile(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    struct sx_dq   *sdq, *rdq;
    u8              dqn;

    __sx_adjust_rdq_size(dev);

    err = check_valid_profile(dev, &priv->profile.pci_profile);
    if (err) {
        printk(KERN_ERR PFX "input profile is not valid\n");
        goto out;
    }

    if (!sx_dpt_is_path_valid(priv->profile.pci_profile.dev_id, DPT_PATH_PCI_E)) {
        printk(KERN_INFO PFX "PCIe path is not valid for device %u, "
               "will not open EMAD DQs\n", priv->profile.pci_profile.dev_id);
        goto out;
    }

    /* no need to open EMAD RDQ on IB only systems */
    if ((priv->profile.pci_profile.pci_profile >= PCI_PROFILE_EN_SINGLE_SWID) &&
        (sx_dpt_get_emad_path(dev->device_id) == DPT_PATH_PCI_E)) {
        dqn = priv->profile.pci_profile.emad_tx_prof.sdq;
        err = sx_core_create_sdq(dev, 1 << priv->dev_cap.log_max_sdq_sz, dqn, &sdq);
        if (err) {
            printk(KERN_ERR PFX "create EMAD sdq %d failed. err: %d\n",
                   dqn, err);
            goto out;
        }

        dqn = priv->profile.pci_profile.emad_rdq;
        err = sx_core_create_rdq(dev, priv->profile.pci_profile.rdq_properties[dqn].number_of_entries,
                                 dqn, &rdq);
        if (err) {
            printk(KERN_ERR PFX "create EMAD rdq %d failed. err: %d\n",
                   dqn, err);
            goto out;
        }
    }

out: return err;
}

int sx_core_get_rdq_param_max(struct sx_dev *dev, uint8_t *rdq_num_max_p, uint16_t *rdq_max_entry_size_p)
{
    int rc = 0;

    /* each one of the parameters (rdq_num_max_p / rdq_max_entry_size_p) may be NULL,
     *  the function will get only the desired parameters */

    /* We don't use lock because the following function will return hard-coded
     *  value and nothing will be changed after we will init switch with
     *  appropriate callback, hence lock will be redundant here. */

    if (dev && (sx_priv(dev)->dev_specific_cb.sx_get_rdq_max_cb != NULL)) {
        sx_priv(dev)->dev_specific_cb.sx_get_rdq_max_cb(rdq_num_max_p, rdq_max_entry_size_p);
    } else {
        printk(KERN_ERR PFX "Error retrieving sx_get_rdq_max_cb callback\n");
        rc = -EINVAL;
    }

    return rc;
}

int __sx_core_dev_specific_cb_get_reference(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    unsigned long   flags;
    u8              err = 0;

    spin_lock_irqsave(&priv->db_lock, flags);

    if (!priv->dev_specific_cb_init_done) {
        err = -EFAULT;
        spin_unlock_irqrestore(&priv->db_lock, flags);
        printk(KERN_INFO PFX "dev_specific_cb is not init\n");
        goto out;
    }

    atomic_inc(&priv->dev_specific_cb_refcnt);
    spin_unlock_irqrestore(&priv->db_lock, flags);

out:
    return err;
}

void __sx_core_dev_specific_cb_release_reference(struct sx_dev *dev)
{
    if (atomic_dec_and_test(&sx_priv(dev)->dev_specific_cb_refcnt)) {
        wake_up(&sx_priv(dev)->dev_specific_cb_not_in_use);
    }
}

static void sx_skb_destructor(struct sk_buff *skb)
{
    struct sx_rsc *rsc = SX_CORE_TX_SKB_CB(skb);

    up(&rsc->write_sem);
}

static void sx_flush_dqs(struct sx_dev *dev, u8 send)
{
    struct sx_priv     *priv = sx_priv(dev);
    int                 err;
    int                 i;
    int                 max = send ? priv->dev_cap.max_num_sdqs : priv->dev_cap.max_num_rdqs;
    struct sx_dq_table *dq_table = send ?
                                   &priv->sdq_table : &priv->rdq_table;

    for (i = 0; i < max; i++) {
        if (dq_table->dq[i]) {
            dq_table->dq[i]->is_flushing = 1;
            err = sx_flush_dq(dev, dq_table->dq[i], false);
            if (err && dq_table->dq[i]->is_send) {
                sx_warn(dev, "failed to flush dq %d. err %d\n", i, err);
            }

            dq_table->dq[i]->is_flushing = 0;
        }
    }
}

int sx_change_configuration(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             i;

    spin_lock(&priv->profile.profile_lock);
    if (priv->profile.pci_profile_set) {
        priv->profile.pci_profile_set = false;
        spin_unlock(&priv->profile.profile_lock);
        /* we unregister the device first, so sx_ib resources will be
         * cleaned (if there are such) because they might try to send
         * packets during the unregister process */
        sx_core_unregister_device(dev);
        if (dev->pdev) {
            sx_flush_dqs(dev, true);
            sx_core_destroy_sdq_table(dev, false);
            sx_flush_dqs(dev, false);
            sx_core_destroy_rdq_table(dev, false);
        }

        for (i = 0; i < NUMBER_OF_SWIDS; i++) {
            sx_bitmap_free(&priv->swid_bitmap, i);
        }

        sx_core_register_device(dev);
        goto out;
    }

    spin_unlock(&priv->profile.profile_lock);
out:
    return 0;
}

/************************************************
 *  Char device Functions
 ***********************************************/

/**
 * This function opens the device for file operations.
 * We support multiple file opens for the same device.
 * Initialize an event list per file and keep it in the file context.
 * The maximum size of the event list is constant.
 * When the file is opened, we can't read or write to it until the
 * profile is set with ioctl
 *
 * param[in] inode - the associated inode.
 * param[in] filp - a pointer to the associated file.
 *
 * returns: 0 success
 *        !0 error
 */
static int sx_core_open(struct inode *inode, struct file *filp)
{
    struct sx_rsc *file = NULL;

#ifdef SX_DEBUG
    pr_debug(PFX " sx_core_open() \n");
#endif
    SX_CORE_UNUSED_PARAM(inode);
    file = kzalloc(sizeof(*file), GFP_KERNEL);
    if (!file) {
#ifdef SX_DEBUG
        pr_debug(PFX " sx_core_open() \n");
#endif
        return -ENOMEM;
    }

    INIT_LIST_HEAD(&file->evlist.list);
    file->evlist_size = 0;
    spin_lock_init(&file->lock);
    init_waitqueue_head(&file->poll_wait);
    atomic_set(&file->multi_packet_read_enable, false);
    atomic_set(&file->read_blocking_state, true);
    file->queue_type = KU_QUEUE_TYPE_TAIL_DROP;
    file->channel_experienced_drop = false;
    sema_init(&file->write_sem, SX_WRITE_LIMIT);
    file->owner = filp;
    filp->private_data = file; /* connect the fd with its resources */
    atomic_set(&file->refcnt, 1);

    return 0;
}

void sx_core_file_add_ref(struct sx_rsc *file)
{
    WARN_ON(atomic_read(&file->refcnt) <= 0);
    atomic_inc(&file->refcnt);
}

void sx_core_file_dec_ref(struct sx_rsc *file)
{
    WARN_ON(atomic_read(&file->refcnt) <= 0);
    if (atomic_dec_and_test(&file->refcnt)) {
        kfree(file);
    }
}

/**
 * Send packets - EMADs, Ethernet packets. We copy the packets
 * from user space, as is, and post them to the HW SDQ. The
 * header is built by user space. SDQ number is calculated
 * according to the profile. Buf is formatted according to
 * ku_write struct. Count is the size of ku_write buffer
 * (without the packets data). We support sending multiple
 * packets in a single operation.
 *
 * param[in] filp  - a pointer to the associated file
 * param[in] buf   - ku_write struct/s
 * param[in] count - the number of bytes to send
 * param[in] pos   - not in use
 *
 *
 * returns: 0<=res - The size of the given buffer that was written
 *          res<0  - Error
 */
static ssize_t sx_core_write(struct file *filp, const char __user *buf, size_t count, loff_t *pos)
{
    struct ku_write write_data;
    int             err = 0;
    int             user_buffer_copied_size = 0;
    struct sk_buff *skb = NULL;
    struct sx_dev  *dev = NULL;
    struct sx_priv *priv = NULL;
    struct sx_rsc  *rsc = filp->private_data;
    int             i;

    if ((count == 0) || (buf == NULL)) {
        err = -EINVAL;
        goto out;
    }

    while (user_buffer_copied_size + sizeof(write_data) <= count) {
        err = copy_from_user((void*)&write_data,
                             ((void*)buf) + user_buffer_copied_size,
                             sizeof(write_data));

        if (sx_core_has_predefined_devices()) {
            write_data.meta.dev_id = get_device_id_from_fd(filp);
        }

        if (err) {
            goto out;
        }

        if (((write_data.vec_entries != 0) && (write_data.iov == NULL)) ||
            ((write_data.vec_entries == 0) && (write_data.iov != NULL))) {
            err = -EINVAL;
            goto out;
        }

        if (write_data.vec_entries == 0) {
            break;
        }

        if (is_sgmii_device(write_data.meta.dev_id)) {
            dev = sx_glb.fake_dev;
        } else {
            dev = sx_dev_db_get_dev_by_id(write_data.meta.dev_id);
            if (!dev) {
                printk(KERN_WARNING PFX "sx_core_write: "
                       "Device doesn't exist. Aborting\n");
                goto out;
            }

            err = check_valid_meta(dev, &write_data.meta);
            if (err) {
                printk(KERN_WARNING PFX "Cannot execute because meta "
                       "is invalid\n");
                goto out;
            }
        }

        priv = sx_priv(dev);

        if (write_data.meta.type == SX_PKT_TYPE_LOOPBACK_CTL) {
            err = sx_send_loopback(dev, &write_data, filp, 1, TARGET_PID_DONT_CARE, GFP_KERNEL, NULL);
            if (err) {
                printk(KERN_WARNING PFX "sx_core_write: "
                       "Failed sending loopback packet\n");
                goto out;
            }

            if (priv) {
                loopback_packets_counter++;
                priv->stats.loopback_packets_counter++;
            }
            user_buffer_copied_size += sizeof(write_data);
            continue;
        }

        /* according to the PRM, emads should get "any ethernet swid" */
        if ((write_data.meta.type == SX_PKT_TYPE_DROUTE_EMAD_CTL) ||
            (write_data.meta.type == SX_PKT_TYPE_EMAD_CTL)) {
            if (!dev || !priv->profile.pci_profile_set || is_sgmii_device(write_data.meta.dev_id)) {
                write_data.meta.swid = 0;
            } else {
                for (i = 0; i < NUMBER_OF_SWIDS; i++) {
                    if ((priv->profile.pci_profile.swid_type[i] ==
                         SX_KU_L2_TYPE_ETH) || (priv->profile.pci_profile.swid_type[i] == SX_KU_L2_TYPE_IB)) {
                        write_data.meta.swid = i;
                        break;
                    }
                }

                if (i == NUMBER_OF_SWIDS) { /* no ETH or IB swids found */
                    printk(KERN_WARNING PFX "sx_core_write: Err: "
                           "trying to send an emad from "
                           "an IB only system\n");
                    err = -EFAULT;
                    write_data.meta.swid = 0;
                    goto out;
                }
            }
        }

        user_buffer_copied_size += sizeof(write_data);
        err = copy_buff_to_skb(&skb, &write_data, true, 1, GFP_KERNEL);
        if (err) {
            goto out;
        }

        if (down_timeout(&rsc->write_sem, msecs_to_jiffies(10000)) == -ETIME) {
            printk(KERN_ERR "packet is waiting too long on TX queue, discarding.\n");
            err = -ETIMEDOUT;
            kfree_skb(skb);
            goto out;
        }

        SX_CORE_TX_SKB_CB(skb) = rsc;
        skb->destructor = sx_skb_destructor;
        err = sx_core_post_send(dev, skb, &write_data.meta);
        if (err) {
            printk(KERN_WARNING PFX "sx_core_write: got error"
                   " from sx_core_post_send\n");
            /* we don't free the packet because sx_core_post_send free
             * the packet in case of an error */
            goto out;
        }
    }

    SX_CORE_UNUSED_PARAM(pos);
    return user_buffer_copied_size;

out:
#ifdef SX_DEBUG
    pr_debug(PFX "sx_core_write: return "
             "value is %d (error)\n", err);
#endif
    return err;
}

void sx_monitor_flush(struct sx_rsc *file, struct sx_dq *bound_monitor_rdq)
{
    unsigned long      flags;
    struct list_head  *pos = NULL, *q = NULL;
    struct event_data *entry = NULL;

    bound_monitor_rdq->mon_rx_start = bound_monitor_rdq->mon_rx_count;

    /* update start point for total counter */
    bound_monitor_rdq->mon_rx_start_total = bound_monitor_rdq->mon_rx_count;

    spin_lock_irqsave(&file->lock, flags);

    /* flush SW buffer and relevant counters */
    bound_monitor_rdq->sw_dup_evlist_cnt = 0;
    bound_monitor_rdq->sw_dup_evlist_total_cnt = 0;

    list_for_each_safe(pos, q, &bound_monitor_rdq->sw_dup_evlist_p->list) {
        entry = list_entry(pos, struct event_data, list);
        list_del(pos);

        consume_skb(entry->skb);    /* free unused skb, use consume_skb */
        kfree(entry);
    }

    spin_unlock_irqrestore(&file->lock, flags);
}


/**
 * Read a bulk of packets up to count size (count includes packet and metadata)
 * Format to buf according to ku_en_read struct.
 * Read packets from the file event list.
 * The event list holds pointers to cloned skbs.
 * On each read, we free the skb.
 * If multi-packets mode (see ioctl) is enabled,
 * we read multiple packets up to count.
 * If multi-packets mode is disabled, we read a single packet up to count.
 *
 * param[in] filp  - a pointer to the associated file
 * param[in] buf   - the data buffer, ku_read struct
 * param[in] count - the number of bites to send (the size of the buffer)
 * param[in] pos   - not in use
 *
 *
 * returns: The size of data which copied to the user buffer
 *	   !0 error
 */
static ssize_t sx_core_read(struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
    unsigned long     flags;
    struct event_data edata_list;
    struct sx_rsc    *file = filp->private_data;
    int               multi_packet_read_enable = false;
    int               read_blocking_state = true;
    int               err;

    SX_CORE_UNUSED_PARAM(pos);
#ifdef SX_DEBUG
    pr_debug(PFX " sx_core_read()\n");
#endif
    if ((count == 0) || (buf == NULL)) {
        return -EINVAL;
    }

    spin_lock_irqsave(&file->lock, flags);
    while (list_empty(&file->evlist.list)) {
        spin_unlock_irqrestore(&file->lock, flags);
        read_blocking_state = atomic_read(&file->read_blocking_state);
        if (read_blocking_state == false) { /* non-blocking */
            return -EAGAIN;
        }

        if (wait_event_interruptible(file->poll_wait,
                                     !list_empty(&file->evlist.list))) {
            return -ERESTARTSYS;
        }

        spin_lock_irqsave(&file->lock, flags);
    }

    multi_packet_read_enable = atomic_read(&file->multi_packet_read_enable);
    INIT_LIST_HEAD(&edata_list.list);
    err = get_edata_from_elist(&file->evlist_size, &edata_list,
                               &file->evlist.list, count, multi_packet_read_enable);
    spin_unlock_irqrestore(&file->lock, flags);

    /*
     *   not enough room for single packet (meta + packet)
     *  but enough room for meta
     */
    if (err > 0) {
        struct ku_read metadata;

        memset(&metadata, 0, sizeof(metadata));
        metadata.length = err;
        if (copy_to_user(buf, &metadata, sizeof(metadata))) {
            return -EFAULT;
        }
        return 0;
    }
    /* not enough room for meta */
    else if (err < 0) {
        return err;
    }

    return copy_edata_to_user(&edata_list, buf);
}

void unset_monitor_rdq(struct sx_dq *dq)
{
    dq->is_monitor = 0;
    if ((dq->file_priv_p != NULL) && (dq->file_priv_p->bound_monitor_rdq != NULL)) {
        sx_monitor_flush(dq->file_priv_p, dq->file_priv_p->bound_monitor_rdq);
        kfree(dq->file_priv_p->bound_monitor_rdq->sw_dup_evlist_p);
        dq->file_priv_p->bound_monitor_rdq = NULL;
        sx_core_file_dec_ref(dq->file_priv_p); /* release reference from the file */
        dq->file_priv_p = NULL;
    }
    dq->cpu_tclass = 0;
}

static unsigned int sx_core_poll(struct file *filp, poll_table *wait)
{
    unsigned int   mask = 0;
    struct sx_rsc *file = NULL;
    unsigned long  flags;

    file = filp->private_data;
    poll_wait(filp, &file->poll_wait, wait);
    spin_lock_irqsave(&file->lock, flags);
    if (!list_empty(&file->evlist.list)) {
        mask |= POLLIN | POLLRDNORM;  /* readable */
    }
    if (file->evlist_size < SX_EVENT_LIST_SIZE) {
        mask |= POLLOUT | POLLWRNORM; /* writable */
    }
    spin_unlock_irqrestore(&file->lock, flags);

    return mask;
}

static void __zero_tx_skb_destructor_pointers(struct sx_dev *dev, struct file *filp)
{
    int               sdqn = 0;
    struct sx_dq     *sdq = NULL;
    struct sx_priv   *priv = sx_priv(dev);
    struct sx_rsc    *rsc = filp->private_data;
    struct sx_pkt    *curr_pkt;
    struct list_head *pos;

    if (!priv->sdq_table.dq) {
        return;
    }

    for (sdqn = 0; sdqn < priv->dev_cap.max_num_sdqs; sdqn++) {
        sdq = priv->sdq_table.dq[sdqn];
        if (!sdq) {
            continue;
        }

        spin_lock_bh(&sdq->lock);
        list_for_each(pos, &sdq->pkts_comp_list.list_wait_for_completion) {
            curr_pkt = list_entry(pos, struct sx_pkt, list_wait_for_completion);
            if (curr_pkt->skb->destructor && (rsc == SX_CORE_TX_SKB_CB(curr_pkt->skb))) {
                curr_pkt->skb->destructor = NULL;
            }
        }
        spin_unlock_bh(&sdq->lock);
    }
}

static bool __listener_context_filter(struct listener_entry *listener, void *context)
{
    return (listener->context == context);
}

typedef bool (*flush_listeners_filter_cb)(struct listener_entry *listener, void *context);
static void __flush_listeners(struct sx_dev *dev, flush_listeners_filter_cb filter_cb, void *context)
{
    struct sx_priv               *priv = sx_priv(dev);
    struct listeners_and_rf_info *info = NULL;
    struct listener_entry        *listener, *q;
    struct list_head              listeners_gc;
    int                           synd;

    __listeners_gc_init(&listeners_gc);

    mutex_lock(&priv->listeners_and_rf_db.lock);
    info = priv->listeners_and_rf_db.info;

    if (!info) {
        goto out;
    }

    for (synd = 0; synd < NUM_HW_SYNDROMES + 1; synd++) {
        list_for_each_entry_safe(listener, q, &info->per_synd_list[synd], list) {
            if (filter_cb(listener, context)) {
                __listeners_gc_add(&listeners_gc, listener);
            }
        }
    }

out:
    mutex_unlock(&priv->listeners_and_rf_db.lock);
    __listeners_gc_finish(&listeners_gc);
}

static int sx_core_close(struct inode *inode, struct file *filp)
{
    struct event_data *edata;
    unsigned long      flags;
    struct list_head  *pos, *q;
    struct sx_rsc     *file = filp->private_data;
    struct sx_dev     *dev;
    struct sx_dq      *dq = NULL;
    int                dqn = -1;
    int                ret = 0;

    spin_lock_irqsave(&file->lock, flags);
    list_for_each_safe(pos, q, &file->evlist.list) {
        edata = list_entry(pos, struct event_data, list);
        list_del(pos);
        consume_skb(edata->skb);    /* free unused skb, use consume_skb */
        kfree(edata);
    }

    spin_unlock_irqrestore(&file->lock, flags);

    down_write(&sx_glb.pci_restart_lock);

    dev = sx_dev_db_get_dev_by_id(get_device_id_from_fd(filp));
    if (dev != NULL) {
        __zero_tx_skb_destructor_pointers(dev, filp);
        __flush_listeners(dev, __listener_context_filter, filp);
    }

    if (sx_glb.pci_drivers_in_use & PCI_DRIVER_F_SX_DRIVER) {
        if (file->bound_monitor_rdq) {
            dq = file->bound_monitor_rdq;
            dev = dq->dev;

            spin_lock_irqsave(&sx_priv(dev)->rdq_table.lock, flags);
            BUG_ON(!dq->is_monitor);
            BUG_ON(dq->file_priv_p != file);
            dqn = dq->dqn;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
            if (sx_priv(dev)->filter_ebpf_progs[dqn] != NULL) {
                bpf_prog_put(sx_priv(dev)->filter_ebpf_progs[dqn]);
                sx_priv(dev)->filter_ebpf_progs[dqn] = NULL;
            }
#endif
            spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);
        }

        /* this code MUST be out of the rdq_table lock! */
        if (dqn >= 0) {
            ret = disable_monitor_rdq(dev, dqn, 0);
            if (ret) {
                printk(KERN_ERR "failed to disable monitoring RDQ on file close (err=%d)\n", ret);
            }
        }
    }
    up_write(&sx_glb.pci_restart_lock);

    file->owner = NULL;

    /* releasing file reference, probably the last one. There is a case that the file was bound
     * to a WJH RDQ and we failed to unbound it [in disable_monitor_rdq() a few lines above]. in this
     * case we want the file pointer to be valid until the user will bind a new file descriptor to
     * the RDQ. this is why we don't call kfree() directly.
     */
    sx_core_file_dec_ref(file);
    SX_CORE_UNUSED_PARAM(inode);

    return 0;
}


static bool __dev_iterator_flush_by_context(struct sx_dev *dev, void *context)
{
    __flush_listeners(dev, __listener_context_filter, context);
    return true;
}

int sx_core_flush_synd_by_context(void * context)
{
    sx_dev_db_iterate(__dev_iterator_flush_by_context, context);
    return 0;
}
EXPORT_SYMBOL(sx_core_flush_synd_by_context);

static bool __listener_handler_filter(struct listener_entry *listener, void *context)
{
    return (listener->handler == (cq_handler)context);
}

static bool __dev_iterator_flush_by_handler(struct sx_dev *dev, void *context)
{
    __flush_listeners(dev, __listener_handler_filter, context);
    return true;
}

int sx_core_flush_synd_by_handler(cq_handler handler)
{
    sx_dev_db_iterate(__dev_iterator_flush_by_handler, handler);
    return 0;
}
EXPORT_SYMBOL(sx_core_flush_synd_by_handler);


struct sx_handler_and_context_info {
    cq_handler handler;
    void      *context;
};

static bool __listener_handler_and_context_filter(struct listener_entry *listener, void *context)
{
    struct sx_handler_and_context_info *info = (struct sx_handler_and_context_info*)context;

    return (listener->handler == info->handler && listener->context == info->context);
}

static bool __dev_iterator_flush_by_handler_and_context(struct sx_dev *dev, void *context)
{
    __flush_listeners(dev, __listener_handler_and_context_filter, context);
    return true;
}

int sx_core_flush_synd_by_handler_and_context(cq_handler handler, void *context)
{
    struct sx_handler_and_context_info info = {
        .handler = handler,
        .context = context
    };

    sx_dev_db_iterate(__dev_iterator_flush_by_handler_and_context, &info);
    return 0;
}

/************************************************
 *  Data-Structures
 ***********************************************/

long sx_core_ioctl(struct file *filp, unsigned int cmd, unsigned long data);
int sx_core_mmap(struct file *filp, struct vm_area_struct *vma);

static const struct file_operations sx_core_fops = {
    .owner = THIS_MODULE,
    .open = sx_core_open,
    .read = sx_core_read,
    .mmap = sx_core_mmap,
    .write = sx_core_write,
    .unlocked_ioctl = sx_core_ioctl,
    .compat_ioctl = sx_core_ioctl,
    .poll = sx_core_poll,
    .release = sx_core_close
};

/************************************************
 *  Module Functions
 ***********************************************/

void sx_core_clear_internal_data(void)
{
    int dev_id;

    /* dpt clean up except local devices LOCAL_DEVICE_ID_MIN..LOCAL_DEVICE_ID_MAX */
    for (dev_id = 0; dev_id < LOCAL_DEVICE_ID_MIN; dev_id++) {
        memset(&sx_glb.sx_dpt.dpt_info[dev_id], 0, sizeof(sx_glb.sx_dpt.dpt_info[0]));
    }

    /* kernel db is cleared in sx_core_remove_one_pci */
}

void sx_core_cleanup_dynamic_data(void)
{
    sx_core_listeners_cleanup();
    sx_core_clear_internal_data();
}
EXPORT_SYMBOL(sx_core_cleanup_dynamic_data);

int sx_core_send_mad_sync(struct sx_dev *dev,
                          int            dev_id,
                          u32            in_modifier,
                          u8             op_modifier,
                          void          *in_mad,
                          int            in_size,
                          void          *out_mad,
                          int            out_size)
{
    int err = 0;

    if (is_sgmii_supported()) {
        err = sgmii_simulate_sync_mad_ifc(dev, dev_id, in_modifier, op_modifier, in_mad, in_size, out_mad, out_size);
    } else {
        err = sx_cmd_send_mad_sync(dev, dev_id, in_modifier, op_modifier, in_mad, in_size, out_mad, out_size);
    }

    return err;
}
EXPORT_SYMBOL(sx_core_send_mad_sync);

static void __sx_init_char_dev(struct cdev *cdev_p)
{
    cdev_init(cdev_p, &sx_core_fops);
    cdev_p->owner = THIS_MODULE;
}

int sx_add_char_dev(struct cdev *cdev_p, int dev_id)
{
    int ret = 0;
    int devno, major, minor;

    major = MAJOR(char_dev);
    minor = MINOR(char_dev) + dev_id;
    devno = MKDEV(major, minor);

    ret = cdev_add(cdev_p, devno, 1);
    printk(KERN_NOTICE "Create char dev with major:%d minor:%d \n", major, minor);
    if (ret) {
        printk(KERN_ERR PFX "Couldn't add char device for device %d. Aborting... err: %d\n",
               dev_id, ret);
        goto out;
    }

out:
    return ret;
}

static void __sx_deinit_char_dev(struct cdev *cdev_p)
{
    printk(KERN_NOTICE "Deinit char dev: %p , usage:%d\n",
           cdev_p, cdev_p->count);
    cdev_del(cdev_p);
}

static int __init sx_core_init(void)
{
    struct sx_priv *priv = NULL;
    int             ret = 0;
    u32             probes_total = 0, probes_ok = 0, total_removes = 0;

    printk(KERN_INFO "%s", sx_version);

    memset(&sx_glb, 0, sizeof(sx_glb));

    sx_glb.generic_wq = sx_health_check_create_monitored_workqueue("sx_generic");
    if (!sx_glb.generic_wq) {
        printk(KERN_ERR "failed to create generic work-queue\n");
        ret = -ENOMEM;
        goto out;
    }

    sx_core_skb_hook_init();

#if defined(CONFIG_MLNX460EX) && defined(SNOOP_MISS_WA)
    config_l2_force_snoop();
#endif

    dev_db_init();
    sx_core_init_proc_fs();
    if (!sx_core_has_predefined_devices()) {
        sx_dbg_dump_proc_fs_init(NULL, NULL);
        sx_dbg_init(NULL, NULL);
    }
    ret = sx_core_clock_init();
    if (ret) {
        goto out_close_proc;
    }
    ret = sx_core_ber_monitor_init();
    if (ret) {
        goto out_deinit_clock;
    }

    sx_dpt_init();

    ret = sx_emad_init();
    if (ret) {
        printk(KERN_ERR "failed to initialize EMAD (err=%d)\n", ret);
        goto emad_init_failed;
    }

    ret = sx_qos_emad_init();
    if (ret) {
        printk(KERN_ERR "failed to initialize EMAD QOS (err=%d)\n", ret);
        goto emad_qos_init_failed;
    }

    ret = sx_health_check_init();
    if (ret) {
        printk(KERN_ERR "failed to initialize health-check (err=%d)\n", ret);
        goto health_check_init_failed;
    }

    init_rwsem(&sx_glb.pci_restart_lock);

    char_dev = MKDEV(SX_MAJOR, SX_BASE_MINOR);
    ret = register_chrdev_region(char_dev, SX_MAX_DEVICES,
                                 SX_CORE_CHAR_DEVICE_NAME);
    if (ret) {
        printk(KERN_INFO PFX "Couldn't register the default device number. "
               "Trying to allocate one dynamically\n");
        ret = alloc_chrdev_region(&char_dev, SX_BASE_MINOR, SX_MAX_DEVICES,
                                  SX_CORE_CHAR_DEVICE_NAME);
        if (ret) {
            printk(KERN_ERR PFX "Couldn't register device number. "
                   "Aborting...\n");
            goto out_deinit_health_check;
        }
    }

    __sx_init_char_dev(&sx_glb.cdev);

    if (sx_cr_mode()) {
        ret = sx_dev_init_cr_device(!fast_boot);
        if (ret) {
            goto out_cdev;
        }
    } else { /* PCI flow */
        ret = sx_dev_init_core_pci(!fast_boot && !skip_reset, &probes_total, &probes_ok);
        if (ret) {
            printk(KERN_ERR "PCI probe failed, aborting (err=%d)\n", ret);
            goto out_cdev;
        }

        if (probes_total == 0) { /* no PCI device found, create a temporary device */
            ret = sx_core_create_fake_device(&priv);
            if (ret) {
                goto out_cdev;
            }
            ret = sx_add_char_dev(&sx_glb.cdev, 1 /* Use minor 1 for char device */);
            if (ret) {
                printk(KERN_ERR "sx_init_char_dev() failed (err=%d)\n", ret);
                goto out_unreg_dev;
            }
        } else if ((probes_total > 1) && !sx_core_has_predefined_devices()) {
            printk(
                KERN_ERR "Detected more than one PCI device, driver must have predefined mapping of PCI bus to device ID\n");
            ret = -EINVAL;
            goto out_unreg_dev;
        }
    }

    if (sx_core_has_predefined_devices()) {
        sx_dev_db_iterate(sx_dbg_dump_proc_fs_init, NULL);
        sx_dev_db_iterate(sx_dbg_init, NULL);
        sx_dev_db_iterate(sx_dpt_dump_hanlders_per_device_init, NULL);
        sx_dev_db_iterate(sx_emad_dump_hanlders_per_device_init, NULL);
    } else {
        sx_emad_dump_hanlders_per_device_init(NULL, NULL);
        sx_dpt_dump_hanlders_per_device_init(NULL, NULL);
    }

    ret = sx_core_synce_init();
    if (ret < 0) {
        printk(KERN_ERR "sx_core_synce_init() failed (err=%d)\n", ret);
        goto out_deinit_char_dev;
    }

    return 0;

out_deinit_char_dev:
    __sx_deinit_char_dev(&sx_glb.cdev);

out_unreg_dev:
    if (probes_total > 0) {
        sx_dev_deinit_core_pci(&total_removes);
    } else {
        sx_core_remove_one(priv, false);
    }

out_cdev:
    unregister_chrdev_region(char_dev, SX_MAX_DEVICES);

out_deinit_health_check:
    sx_health_check_deinit();

health_check_init_failed:
    sx_qos_emad_deinit();

emad_qos_init_failed:
    sx_emad_deinit();
    sx_dpt_dereg_i2c_ifc();
    sx_dpt_dereg_mst_ifc();

emad_init_failed:
    sx_core_ber_monitor_deinit();

out_deinit_clock:
    sx_core_clock_deinit();

out_close_proc:
    if (sx_core_has_predefined_devices()) {
        sx_dev_db_iterate(sx_dbg_deinit, NULL);
        sx_dev_db_iterate(sx_dpt_dump_hanlders_per_device_deinit, NULL);
        sx_dev_db_iterate(sx_emad_dump_hanlders_per_device_deinit, NULL);
        sx_dev_db_iterate(sx_dbg_dump_proc_fs_deinit, NULL);
        sx_dbg_dump_proc_fs_remove_parent_proc_folder();
    } else {
        sx_dbg_deinit(NULL, NULL);
        sx_dpt_dump_hanlders_per_device_deinit(NULL, NULL);
        sx_emad_dump_hanlders_per_device_deinit(NULL, NULL);
        sx_dbg_dump_proc_fs_deinit(NULL, NULL);
    }
    sx_core_close_proc_fs();
    dev_db_deinit();
    sx_health_check_destroy_monitored_workqueue(sx_glb.generic_wq);

out:
    return ret;
}

static bool __dev_iterate_listeners_cleanup(struct sx_dev *dev, void *context)
{
    struct sx_priv               *priv = sx_priv(dev);
    struct listeners_and_rf_info *info = NULL;
    struct listener_entry        *listener, *q;
    int                           entry;
    struct list_head              listeners_gc;

    printk(KERN_INFO PFX "sx_core_listeners_cleanup (device %d)\n", dev->device_id);

    __listeners_gc_init(&listeners_gc);

    /* delete all remaining listener entries */
    mutex_lock(&priv->listeners_and_rf_db.lock);
    info = priv->listeners_and_rf_db.info;
    if (!info) {
        goto out;
    }

    for (entry = 0; entry < NUM_HW_SYNDROMES + 1; entry++) {
        list_for_each_entry_safe(listener, q, &info->per_synd_list[entry], list){
            __listeners_gc_add(&listeners_gc, listener);
        }
    }

out:
    mutex_unlock(&priv->listeners_and_rf_db.lock);
    __listeners_gc_finish(&listeners_gc);
    return true;
}

static void sx_core_listeners_cleanup(void)
{
    sx_dev_db_iterate(__dev_iterate_listeners_cleanup, NULL);
}

static void __exit sx_core_cleanup(void)
{
    u32 total_removes = 0;

    printk(KERN_INFO PFX "sx_core_cleanup_module \n");

    sx_core_synce_deinit();

    if (is_sgmii_supported()) {
        sgmii_deinit();
        sx_dev_deinit_oob_pci();
    }


    if (sx_core_has_predefined_devices()) {
        sx_dev_db_iterate(sx_dbg_deinit, NULL);
        sx_dev_db_iterate(sx_dpt_dump_hanlders_per_device_deinit, NULL);
        sx_dev_db_iterate(sx_emad_dump_hanlders_per_device_deinit, NULL);
        sx_dev_db_iterate(sx_dbg_dump_proc_fs_deinit, NULL);
        sx_dbg_dump_proc_fs_remove_parent_proc_folder();
    }

    if (sx_cr_mode()) {
        sx_dev_deinit_cr_device();
    } else if (sx_glb.fake_dev) { /* we're running on a VM or OOB system */
        sx_core_remove_fake_device(sx_priv(sx_glb.fake_dev));
    } else { /* we deal with real PCI devices */
        sx_dev_deinit_core_pci(&total_removes);
    }

    __sx_deinit_char_dev(&sx_glb.cdev);

    unregister_chrdev_region(char_dev, SX_MAX_DEVICES);
    sx_dpt_dereg_i2c_ifc();
    sx_dpt_dereg_mst_ifc();

    sx_core_listeners_cleanup();
    sx_core_ber_monitor_deinit();
    sx_core_clock_deinit();
    sx_health_check_deinit();
    sx_qos_emad_deinit();
    sx_emad_deinit();
    if (!sx_core_has_predefined_devices()) {
        sx_dbg_deinit(NULL, NULL);
        sx_dpt_dump_hanlders_per_device_deinit(NULL, NULL);
        sx_emad_dump_hanlders_per_device_deinit(NULL, NULL);
        sx_dbg_dump_proc_fs_deinit(NULL, NULL);
    }
    sx_core_close_proc_fs();
    dev_db_deinit();
    sx_health_check_destroy_monitored_workqueue(sx_glb.generic_wq);
}

/************************************************
 *  MODULE init/exit
 ***********************************************/
module_init(sx_core_init);
module_exit(sx_core_cleanup);


/************************************************
 *                  EOF                         *
 ***********************************************/
