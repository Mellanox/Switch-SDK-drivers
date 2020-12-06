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
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/types.h>
#include <linux/uio.h>
#include <linux/skbuff.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/pci.h>
#include <linux/if_vlan.h>
#include <linux/kthread.h>
#include <linux/vmalloc.h>
#include <linux/ptp_clock_kernel.h>
#include <linux/file.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>
#include <net/sock.h>
#include <linux/mlx_sx/skb_hook.h>
#include "sx.h"
#include "cq.h"
#include "dq.h"
#include "eq.h"
#include "alloc.h"
#include "icm.h"
#include "fw.h"
#include "sx_dbg_dump_proc.h"
#include "sx_dpt.h"
#include "sx_proc.h"
#include "sx_clock.h"
#include "ptp.h"
#include "sgmii.h"
#include "counter.h"

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
    DRV_NAME ": Mellanox SwitchX Core Driver "
    SX_CORE_DRV_VERSION " (" DRV_RELDATE ")\n";

#define MAX_ROUTER_MID_TABLE_SIZE 0xffff
#define MAX_IB_PORT               65

#define SX_CORE_PHY_PORT_NUM_MAX                64
#define SX_CORE_PHY_PORT_NUM_QUANTUM_MAX        80
#define SX_CORE_PHY_PORT_NUM_QUANTUM2_MAX       128
#define SX_CORE_PHY_PORT_NUM_SPECTRUM2_MAX      128
#define SX_CORE_LAG_NUM_MAX                     64
#define SX_CORE_LAG_NUM_SPECTRUM2_MAX           128
#define SX_CORE_PORTS_PER_LAG_NUM_MAX           32
#define SX_CORE_PORTS_PER_LAG_NUM_SPECTRUM2_MAX 64
#define SX_CORE_DEV_CB_FINISH_WAIT_TIMEOUT      (30 * HZ)

/* The following defines are used in the chip specific
 * callback functions to get the correct number of RDQ
 * (Receive descriptor queues) for the relevant chip
 * in respect with the PRM.
 * Please refer cap_max_num_rdq.
 */
#define RDQ_NUM_MAX      37
#define RDQ_NUM_MAX_SPC2 56


/************************************************
 *  Enum
 ***********************************************/

enum SX_CHAR_DEVICE {
    SX_MAJOR = 231,
    SX_BASE_MINOR = 193,
};
dev_t             char_dev;
struct sx_globals sx_glb;

/************************************************
 *  MODULE settings
 ***********************************************/
MODULE_AUTHOR("Amos Hersch, Anatoly Lisenko");
MODULE_DESCRIPTION("Mellanox SwitchX driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(SX_CORE_DRV_VERSION);

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

int g_chip_type = 0;
module_param_named(g_chip_type,
                   g_chip_type, int, 0644);
MODULE_PARM_DESC(g_chip_type, " set chip type for NO PCI and SGMII");

int eventlist_drops_counter = 0;
module_param_named(eventlist_drops_counter, eventlist_drops_counter, int, 0644);
MODULE_PARM_DESC(eventlist_drops_counter, "Event list drops counter");

int unconsumed_packets_counter = 0;
module_param_named(unconsumed_packets_counter,
                   unconsumed_packets_counter, int, 0644);
MODULE_PARM_DESC(unconsumed_packets_counter, "Unconsumed packets counter");

int filtered_lag_packets_counter = 0;
module_param_named(filtered_lag_packets_counter,
                   filtered_lag_packets_counter, int, 0644);
MODULE_PARM_DESC(filtered_lag_packets_counter, "Filtered LAG packets counter");

int filtered_port_packets_counter = 0;
module_param_named(filtered_port_packets_counter,
                   filtered_port_packets_counter, int, 0644);
MODULE_PARM_DESC(filtered_port_packets_counter, "Filtered port packets counter");

int loopback_packets_counter = 0;
module_param_named(loopback_packets_counter,
                   loopback_packets_counter, int, 0644);
MODULE_PARM_DESC(loopback_packets_counter, "Loopback packets counter");

int fast_boot = 0;
module_param_named(fast_boot, fast_boot, int, 0444);
MODULE_PARM_DESC(fast_boot, "fast_boot enable/disable");

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

int chip_info_type = -1;
module_param_named(chip_info_type, chip_info_type, int, 0444);
MODULE_PARM_DESC(chip_info_type, "chip_info: type");

int chip_info_revision = -1;
module_param_named(chip_info_revision, chip_info_revision, int, 0444);
MODULE_PARM_DESC(chip_info_revision, "chip_info: revision");

char chip_info_psid[16] = "";
module_param_string(chip_info_psid, chip_info_psid, 16, 0444);
MODULE_PARM_DESC(chip_info_psid, "chip_info: psid");

int enable_cpu_port_loopback = 0; /* ONLY FOR DEBUG */
module_param_named(enable_cpu_port_loopback, enable_cpu_port_loopback, int, 0644);
MODULE_PARM_DESC(enable_cpu_port_loopback, " Enable / Disable loopback on cpu port");

int enable_keep_packet_crc = 0; /* ONLY FOR DEBUG */
module_param_named(enable_keep_packet_crc, enable_keep_packet_crc, int, 0644);
MODULE_PARM_DESC(enable_keep_packet_crc, "Enable/Disable receiving RX packet including the CRC field");

int mon_cq_thread_delay_time_usec = 20;
module_param_named(mon_cq_thread_delay_time_usec, mon_cq_thread_delay_time_usec, int, 0644);
MODULE_PARM_DESC(mon_cq_thread_delay_time_usec, "mon_cq_thread_delay_time_usec");

int enable_monitor_rdq_trace_points = 0;
module_param_named(enable_monitor_rdq_trace_points, enable_monitor_rdq_trace_points, int, 0644);
MODULE_PARM_DESC(enable_monitor_rdq_trace_points, "enabled/disable monitor RDQs trace points");

#ifdef CONFIG_PCI_MSI

static int msi_x = 1;
module_param(msi_x, int, 0444);
MODULE_PARM_DESC(msi_x, "attempt to use MSI-X if nonzero");

#else /* CONFIG_PCI_MSI */

static int msi_x = 0;

#endif /* CONFIG_PCI_MSI */

int sx_core_dev_init_switchx_cb(struct sx_dev *dev, enum sxd_chip_types chip_type, bool force);
int sx_core_init_one(struct sx_priv **sx_priv);
void sx_core_remove_one(struct sx_priv *priv);
static void inc_eventlist_drops_global_counter(u16 hw_synd);
#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
static void sx_core_shutdown(struct pci_dev *pdev);
#endif
static void sx_disconnect_all_trap_groups_spectrum(struct sx_dev *dev);
static void sx_core_listeners_cleanup(void);

int sx_init_char_dev(struct cdev *cdev_p);
void sx_deinit_char_dev(struct cdev *cdev_p);

enum {
    PCI_PROBE_STATE_NONE_E,
    PCI_PROBE_STATE_STARTED_E,
    PCI_PROBE_STATE_SUCCESS_E
};

static u8 __pci_probe_state = PCI_PROBE_STATE_NONE_E;
static u8 __perform_chip_reset = 0;
static u8 __oob_pci = 0;
u8        __warm_boot_mode = 0;

/************************************************
 *  Functions
 ***********************************************/

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
            kfree_skb(new_skb);
            return -ENOMEM;
        }

        memcpy(p_skb_data, skb->data, 12); /* DMAC, SMAC */
        memcpy(p_skb_data + 12 + VLAN_HLEN, skb->data + 12, skb->len - 12); /* rest of the frame */

        kfree_skb(skb);
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

    return ((arr)[idx] & (bit));
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


int sx_core_get_local(struct sx_dev *dev, uint16_t lag_id, uint8_t lag_subport, uint16_t *local_p)
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

void get_lag_id_from_local_port(struct sx_dev *dev, u8 sysport, u16 *lag_id, u8 *is_lag_member)
{
    int      i = 0, j = 0;
    uint16_t lag_max = 0, lag_member_max = 0;

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs.\n");
        return;
    }

    for (i = 0; i < lag_max; i++) { /* lag */
        for (j = 0; j < lag_member_max; j++) { /* lag member id */
            if (sx_priv(dev)->lag_member_to_local_db[i][j] == sysport) {
                if (lag_id != NULL) {
                    *lag_id = i;
                }
                if (is_lag_member != NULL) {
                    *is_lag_member = 1;
                }
                return;
            }
        }
        if (is_lag_member != NULL) {
            *is_lag_member = 0;
        }
    }
}
EXPORT_SYMBOL(get_lag_id_from_local_port);


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
EXPORT_SYMBOL(sx_core_get_swid);

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
        sx_priv(dev)->dev_specific_cb.get_lag_mid_cb(lag_id, mid);
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
EXPORT_SYMBOL(sx_core_is_eqn_cmd_ifc_only);

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
EXPORT_SYMBOL(sx_core_get_fid_by_port_vid);

int sx_core_get_ib_system_port_mid(struct sx_dev *dev, u16 ib_port, u16* sys_port_mid)
{
    u16 ret = 0;

    /* this function is called from the sx_ib/IPoIB drivers that work only with PCI devices.
     * When OOB is enabled, these drivers work with the SX dev and its specific callbacks.
     * This is the point when we change the sx_dev we work with in order to work with the
     * right callbacks!
     */
    if (is_sgmii_supported()) {
        dev = sx_glb.tmp_dev_ptr; /* the SGMII device with the right callbacks */
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


/**
 * Update the device's cap struct with the default capabilities of the HW
 * (number of RDQs, SDQs, CQs Etc.)
 */
static void set_default_capabilities(struct sx_dev *dev)
{
    dev->dev_cap.log_max_rdq_sz = SX_MAX_LOG_DQ_SIZE;
    dev->dev_cap.log_max_sdq_sz = SX_MAX_LOG_DQ_SIZE;
    dev->dev_cap.log_max_cq_sz = 10;

    dev->dev_cap.max_num_rdqs = NUMBER_OF_RDQS;
    dev->dev_cap.max_num_sdqs = NUMBER_OF_SDQS;
    dev->dev_cap.max_num_cqs = NUMBER_OF_RDQS + NUMBER_OF_SDQS;

    dev->dev_cap.max_num_cpu_egress_tcs = 12;
    dev->dev_cap.max_num_cpu_ingress_tcs = 16;
}

int ver_set_capabilities(struct sx_dev_cap *cap)
{
    struct sx_dev *dev = sx_glb.tmp_dev_ptr;

    printk(KERN_DEBUG PFX "ver_set_capabilities: Entered function\n");
    printk(KERN_DEBUG PFX "ver_set_capabilities: "
           "cap->log_max_rdq_sz = %d\n", cap->log_max_rdq_sz);

    dev->dev_cap.log_max_rdq_sz = cap->log_max_rdq_sz;
    dev->dev_cap.log_max_sdq_sz = cap->log_max_sdq_sz;
    dev->dev_cap.log_max_cq_sz = cap->log_max_cq_sz;

    dev->dev_cap.max_num_rdqs = cap->max_num_rdqs;
    dev->dev_cap.max_num_sdqs = cap->max_num_sdqs;
    dev->dev_cap.max_num_cqs = cap->max_num_cqs;

    dev->dev_cap.max_num_cpu_egress_tcs = cap->max_num_cpu_egress_tcs;
    dev->dev_cap.max_num_cpu_ingress_tcs = cap->max_num_cpu_ingress_tcs;

    return 0;
}
EXPORT_SYMBOL(ver_set_capabilities);

/**
 * Return a pointer to the sx device
 *
 * returns: Pointer to the sx device - success
 *	    NULL                     - error
 */
void * sx_get_dev_context(void)
{
    return sx_glb.sx_dpt.dpt_info[DEFAULT_DEVICE_ID].
           sx_pcie_info.sx_dev;
}
EXPORT_SYMBOL(sx_get_dev_context);

/************************************************
 *  Helper Functions
 ***********************************************/
void inc_unconsumed_packets_counter(struct sx_dev *dev, u16 hw_synd, enum sx_packet_type pkt_type)
{
    inc_unconsumed_packets_global_counter(hw_synd, pkt_type);
    if (dev) {
        dev->stats.rx_unconsumed_by_synd[hw_synd][pkt_type]++;
        dev->unconsumed_packets_counter++;
    }
#ifdef SX_DEBUG
    printk(KERN_ERR PFX "A packet with trap ID 0x%x and type %s "
           "was not consumed\n", hw_synd, sx_cqe_packet_type_str[pkt_type]);
#endif
}

void inc_eventlist_drops_counter(struct sx_dev* sx_dev, u16 hw_synd)
{
    inc_eventlist_drops_global_counter(hw_synd);

    if (sx_dev != NULL) {
        sx_dev->eventlist_drops_counter++;
        sx_dev->stats.rx_eventlist_drops_by_synd[hw_synd]++;
    }

#ifdef SX_DEBUG
    printk(KERN_ERR PFX "A packet with trap ID 0x%x "
           "was dropped from the event list\n", hw_synd);
#endif
}

void inc_filtered_lag_packets_counter(struct sx_dev *dev)
{
    inc_filtered_lag_packets_global_counter();
    if (dev != NULL) {
        dev->filtered_lag_packets_counter++;
    }
}

void inc_filtered_port_packets_counter(struct sx_dev *dev)
{
    inc_filtered_port_packets_global_counter();
    if (dev != NULL) {
        dev->filtered_port_packets_counter++;
    }
}

void inc_unconsumed_packets_global_counter(u16 hw_synd, enum sx_packet_type pkt_type)
{
    unconsumed_packets_counter++;
    sx_glb.stats.rx_unconsumed_by_synd[hw_synd][pkt_type]++;
 #ifdef SX_DEBUG
    printk(KERN_ERR PFX "A packet with trap ID 0x%x and type %s "
           "was not consumed\n", hw_synd, sx_cqe_packet_type_str[pkt_type]);
 #endif
}

static void inc_eventlist_drops_global_counter(u16 hw_synd)
{
    eventlist_drops_counter++;
    sx_glb.stats.rx_eventlist_drops_by_synd[hw_synd]++;
 #ifdef SX_DEBUG
    printk(KERN_ERR PFX "A packet with trap ID 0x%x "
           "was dropped from the event list\n", hw_synd);
 #endif
}

void inc_filtered_lag_packets_global_counter(void)
{
    filtered_lag_packets_counter++;
}

void inc_filtered_port_packets_global_counter(void)
{
    filtered_port_packets_counter++;
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

    rc = sx_core_get_rdq_num_max(dev, &rdq_num);
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
static int copy_buff_to_skb(struct sk_buff **skb, struct ku_write *write_data, u8 reserve_hdrs, u8 is_from_user)
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
    *skb = alloc_skb(packet_size + max_headers_size, GFP_KERNEL);
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
    kfree_skb(*skb);
out_free:
    if (is_from_user) {
        kfree(iov);
    }
out_err:
    return err;
}

static int sx_send_loopback(struct sx_dev   *dev,
                            struct ku_write *write_data,
                            void            *context,
                            u8               is_from_user,
                            pid_t            target_pid)
{
    int                    err = 0;
    struct completion_info ci;
    struct ethhdr         *eth_h = NULL;
    u8                     is_from_rp = IS_RP_DONT_CARE_E;
    u16                    fid = 0;

    memset(&ci, 0, sizeof(ci));
    err = copy_buff_to_skb(&ci.skb, write_data, false, is_from_user);
    if (err) {
        printk(KERN_WARNING "sx_send_loopback: failed copying buffer to SKB err:[%d]\n", err);
        goto out;
    }

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "sx_send_loopback: got from user:\n");
    printk(KERN_DEBUG PFX "sx_send_loopback: trap_id = %u\n",
           write_data->meta.loopback_data.trap_id);
    printk(KERN_DEBUG PFX "sx_send_loopback: buffer_size = %u\n",
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
        spin_lock_bh(&sx_priv(dev)->db_lock);
        if (ci.is_lag) {
            ci.vid = sx_priv(dev)->pvid_lag_db[ci.sysport];
        } else {
            ci.vid = sx_priv(dev)->pvid_sysport_db[ci.sysport];
        }
        spin_unlock_bh(&sx_priv(dev)->db_lock);
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
    ci.device_id = dev->device_id;
    ci.target_pid = target_pid;
    SX_RX_TIMESTAMP_INIT(&ci.rx_timestamp, 0, 0, SXD_TS_TYPE_NONE);

    if (dispatch_pkt(dev, &ci, ci.hw_synd, 0) > 0) {
        dev->stats.rx_eventlist_by_synd[write_data->meta.loopback_data.trap_id]++;
        sx_glb.stats.rx_eventlist_by_synd[write_data->meta.loopback_data.trap_id]++;
    }

out:
    kfree_skb(ci.skb);
    return err;
}

int send_trap(const void    *buf,
              const uint32_t buf_size,
              uint16_t       trap_id,
              u8             is_from_user,
              u8             device_id,
              pid_t          target_pid)
{
    struct ku_write write_data;
    struct ku_iovec iov;
    int             err = 0;

    if (!sx_glb.tmp_dev_ptr) {
        printk(KERN_WARNING "device is NULL\n");
        err = 1;
        goto out;
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

    err = sx_send_loopback(sx_glb.tmp_dev_ptr, &write_data, NULL, is_from_user, target_pid);

out:
    return err;
}
EXPORT_SYMBOL(send_trap);


int sx_send_health_event(uint8_t dev_id, sxd_health_cause_t cause)
{
    sxd_event_health_notification_t sdk_health;

    memset(&sdk_health, 0, sizeof(sdk_health));

    sdk_health.device_id = dev_id;
    sdk_health.cause = cause;
    sdk_health.severity = SXD_HEALTH_SEVERITY_ERR;
    sdk_health.irisc_id = DBG_ALL_IRICS;
    sdk_health.was_debug_started = false;

    /* Send SDK health event */
    printk(KERN_ERR PFX "SDK health event, device:[%d] \n", sdk_health.device_id);

    return send_trap(&sdk_health, sizeof(sdk_health), SXD_TRAP_ID_SDK_HEALTH_EVENT, 0, dev_id, TARGET_PID_DONT_CARE);
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
    metadata_p->dev_id = edata_p->dev_id;
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
    printk(KERN_DEBUG PFX "copy_pkt_to_user()\n");
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
    printk(KERN_DEBUG PFX " copy_pkt_to_user() metadata.length=[%llu] " \
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

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX " copy_edata_to_user()\n");
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

int __sx_core_match_port_vlan_listener(struct listener_port_vlan_entry *entry_one,
                                       struct listener_port_vlan_entry *entry_two)
{
    switch (entry_one->match_crit) {
    case PORT_VLAN_MATCH_PORT_VALID:
        if ((entry_two->match_crit == PORT_VLAN_MATCH_PORT_VALID) &&
            (entry_one->sysport == entry_two->sysport)) {
            return 1;
        }
        break;

    case PORT_VLAN_MATCH_LAG_VALID:
        if ((entry_two->match_crit == PORT_VLAN_MATCH_LAG_VALID) &&
            (entry_one->lag_id == entry_two->lag_id)) {
            return 1;
        }
        break;

    case PORT_VLAN_MATCH_VLAN_VALID:
        if ((entry_two->match_crit == PORT_VLAN_MATCH_VLAN_VALID) &&
            (entry_one->vlan == entry_two->vlan)) {
            return 1;
        }
        break;

    case PORT_VLAN_MATCH_GLOBAL:
        if (entry_two->match_crit == PORT_VLAN_MATCH_GLOBAL) {
            return 1;
        }
        break;
    }
    return 0;
}


static int is_same_listener(u8                        swid,
                            enum l2_type              type,
                            u8                        is_default,
                            union ku_filter_critireas critireas,
                            void                     *context,
                            struct listener_entry    *listener,
                            cq_handler                handler)
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
        if (listener->critireas.eth.ethtype != critireas.eth.ethtype) {
            return false;
        }

        if (listener->critireas.eth.dmac != critireas.eth.dmac) {
            return false;
        }

        if (listener->critireas.eth.emad_tid != critireas.eth.emad_tid) {
            return false;
        }

        if (listener->critireas.eth.from_rp != critireas.eth.from_rp) {
            return false;
        }

        if (listener->critireas.eth.from_bridge != critireas.eth.from_bridge) {
            return false;
        }

        break;

    case L2_TYPE_IB:
        if (listener->critireas.ib.qpn != critireas.ib.qpn) {
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
                                                  struct ku_port_vlan_params            *port_vlan,
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

static int __sx_core_port_vlan_listener_exist(struct ku_port_vlan_params *port_vlan,
                                              struct listener_entry      *listener,
                                              u8                          is_register)
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
int sx_core_add_synd(u8                          swid,
                     u16                         hw_synd,
                     enum l2_type                type,
                     pid_t                       caller_pid,
                     u8                          is_default,
                     union ku_filter_critireas   crit,
                     cq_handler                  handler,
                     void                       *context,
                     check_dup_e                 check_dup,
                     struct sx_dev             * sx_dev,
                     struct ku_port_vlan_params *port_vlan,
                     u8                          is_register)
{
    unsigned long               flags;
    struct listener_entry      *listener = NULL;
    struct listener_entry      *new_listener = NULL;
    unsigned int                found_same_listener = 0, found_same_port_vlan_listener = 0;
    struct list_head           *pos;
    struct ku_port_vlan_params  tmp_port_vlan;
    struct ku_port_vlan_params *port_vlan_p;


    /* if NULL use default sx_dev */
    if (sx_dev == NULL) {
        sx_dev = sx_glb.tmp_dev_ptr;
    }


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
    new_listener->critireas = crit;
    new_listener->handler = handler;
    new_listener->context = context;
    new_listener->listener_type = type;
    new_listener->is_default = is_default;
    new_listener->rx_pkts = 0;

    port_vlan_p = port_vlan;
    if (!port_vlan_p) {
        tmp_port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        port_vlan_p = &tmp_port_vlan;
    }

    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    if (!list_empty(&sx_glb.listeners_rf_db[hw_synd].list)) {
        list_for_each(pos, &sx_glb.listeners_rf_db[hw_synd].list) {
            listener = list_entry(pos, struct listener_entry, list);
            if (is_same_listener(swid, type, is_default, crit, context, listener,
                                 handler)) {
                found_same_port_vlan_listener = __sx_core_port_vlan_listener_exist(port_vlan,
                                                                                   listener,
                                                                                   is_register);
                if ((check_dup == CHECK_DUP_ENABLED_E) &&
                    found_same_port_vlan_listener) {
                    kfree(new_listener);
                    goto out;
                }
                found_same_listener = 1;
                kfree(new_listener);
                break;
            }
        }
    }
    if (found_same_listener == 0) {
        if (is_default) {
            list_add_tail(&(new_listener->list),
                          &(sx_glb.listeners_rf_db[hw_synd].list));
        } else {
            list_add(&(new_listener->list),
                     &(sx_glb.listeners_rf_db[hw_synd].list));
        }
        listener = new_listener;
    }
    /* TODO : if found same listener and same port vlan listener register twice */
    listener_register_filter_entry_update(is_register, port_vlan_p, &(listener->listener_register_filter), 1);
out:
    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_add_synd);

int sx_core_remove_synd(u8                          swid,
                        u16                         hw_synd,
                        enum l2_type                type,
                        u8                          is_default,
                        union ku_filter_critireas   critireas,
                        void                       *context,
                        struct sx_dev              *sx_dev,
                        cq_handler                  handler,
                        struct ku_port_vlan_params *port_vlan,
                        u8                          is_register)
{
    unsigned long               flags;
    struct listener_entry      *listener = NULL;
    struct list_head           *pos;
    struct list_head           *q;
    int                         entry = 0;
    struct ku_port_vlan_params  tmp_port_vlan;
    struct ku_port_vlan_params *port_vlan_p;

    /*
     * if NULL use default sx_dev
     * TODO: add instead logic for all_devs
     */
    if (sx_dev == NULL) {
        sx_dev = sx_glb.tmp_dev_ptr;
    }
    port_vlan_p = port_vlan;
    if (!port_vlan_p) {
        tmp_port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        port_vlan_p = &tmp_port_vlan;
    }
    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    entry = hw_synd;
    if (!list_empty(&(sx_glb.listeners_rf_db[entry].list))) {
        list_for_each_safe(pos, q, &sx_glb.listeners_rf_db[entry].list) {
            listener = list_entry(pos, struct listener_entry, list);
            if (is_same_listener(swid, type, is_default, critireas, context, listener, handler)) {
                listener_register_filter_entry_update(is_register,
                                                      port_vlan_p,
                                                      &(listener->listener_register_filter),
                                                      0);
                if (listener_register_filter_is_empty(&(listener->listener_register_filter))) {
                    list_del(pos);
                    kfree(listener);
                }
            }
        }
    }
    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);
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

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX " %s(): skb->len=[%d]  sysport=[%d]"
           " hw_synd(trap_id)=[%d]\n", __func__,
           skb_p->len, edata_p->system_port, edata_p->trap_id);
#endif
}


static int check_valid_profile(struct sx_dev *dev, struct sx_pci_profile *profile)
{
    int     i, j;
    uint8_t rdq_num = 0;
    int     rc = 0;

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        for (j = 0; j < NUMBER_OF_ETCLASSES; j++) {
            if (profile->tx_prof[i][j].sdq >=
                dev->dev_cap.max_num_sdqs) {
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
    if (profile->emad_tx_prof.sdq >= dev->dev_cap.max_num_sdqs) {
        printk(KERN_WARNING PFX "emad sdq num is > max\n");
        return -EINVAL;
    }
    if (profile->emad_tx_prof.stclass >= 8) {
        printk(KERN_WARNING PFX "emad stclass num is > max\n");
        return -EINVAL;
    }

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        /* Normalize the RDQ number according chip capability */
        if (profile->rdq_count[i] > (dev->dev_cap.max_num_rdqs - 1)) {
            printk(KERN_WARNING PFX "Normalize rdq num %d to dev_cap_max_num_rdq %d\n",
                   profile->rdq_count[i], dev->dev_cap.max_num_rdqs);
            profile->rdq_count[i] = dev->dev_cap.max_num_rdqs - 1;
        }

        for (j = 0; j < profile->rdq_count[i]; j++) {
            if (profile->rdq[i][j] >= dev->dev_cap.max_num_rdqs) {
                printk(KERN_WARNING PFX "rdq[%d][%d] = %d "
                       "> max\n", i, j, profile->rdq[i][j]);
                return -EINVAL;
            }
        }
    }
    if ((profile->pci_profile >= PCI_PROFILE_EN_SINGLE_SWID) &&
        (profile->emad_rdq >= dev->dev_cap.max_num_rdqs)) {
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

    rc = sx_core_get_rdq_num_max(dev, &rdq_num);
    if (rc) {
        printk(KERN_ERR PFX "Error: failed to get max RDQ num\n");
        return rc;
    }

    for (i = 0; i < rdq_num; i++) {
        if ((profile->rdq_properties[i].number_of_entries >
             1 << dev->dev_cap.log_max_rdq_sz) ||
            (profile->rdq_properties[i].entry_size >
             SX_MAX_MSG_SIZE)) {
            printk(KERN_WARNING PFX "%s:%d\n", __FILE__, __LINE__);
            printk(KERN_WARNING PFX "%d: n_enties %d , max_rdq_sz:"
                   " %d , entry_sz:%d, SX_MAX_MSG_SZ:%d\n",
                   i,
                   profile->rdq_properties[i].number_of_entries,
                   1 << dev->dev_cap.log_max_rdq_sz,
                   profile->rdq_properties[i].entry_size,
                   SX_MAX_MSG_SIZE);
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
    int                  i;
    int                  err = 0;
    union sx_event_data *event_data = NULL;
    union sx_event_data *tca_init_event_data = NULL;
    u8                   first_ib_swid;

    if (dev->profile.swid_type[swid] == SX_KU_L2_TYPE_IB) {
        event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
        if (!event_data) {
            printk(KERN_ERR "%s: failed to allocate event data\n", __FUNCTION__);
            err = -ENOMEM;
            goto out;
        }

        event_data->ib_swid_change.swid = swid;
        event_data->ib_swid_change.dev_id = dev->device_id;
        sx_core_dispatch_event(dev, SX_DEV_EVENT_IB_SWID_UP, event_data);

        spin_lock(&dev->profile_lock);
        first_ib_swid = dev->first_ib_swid;
        dev->first_ib_swid = 0;
        spin_unlock(&dev->profile_lock);
        if (first_ib_swid) {
            tca_init_event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
            if (!tca_init_event_data) {
                printk(KERN_ERR "%s: failed to allocate tca_event_data\n", __FUNCTION__);
                err = -ENOMEM;
                goto out;
            }

            for (i = 0; i < NUMBER_OF_SWIDS; i++) {
                if (dev->profile.ipoib_router_port_enable[i]) {
                    tca_init_event_data->tca_init.swid[tca_init_event_data->tca_init.num_of_ib_swids++] = i;
                }
            }

            if (tca_init_event_data->tca_init.num_of_ib_swids != 0) {
                tca_init_event_data->tca_init.max_pkey = dev->profile.max_pkey;
                if (dev->profile.pci_profile == PCI_PROFILE_VPI_SINGLE_SWID) {
                    sx_core_dispatch_event(dev, SX_DEV_EVENT_TYPE_TCA_INIT, tca_init_event_data);
                } else {
                    sx_core_dispatch_event(dev, SX_DEV_EVENT_TYPE_RPA_INIT, tca_init_event_data);
                }
            }
        }
    } else {
        printk(KERN_ERR PFX "Error: try to send IB_SWID_UP event on swid %d from non-IB type %d, ",
               swid, dev->profile.swid_type[swid]);
        err = -EINVAL;
        goto out;
    }

out:
    if (event_data) {
        kfree(event_data);
    }

    if (tca_init_event_data) {
        kfree(tca_init_event_data);
    }

    return err;
}


int sx_enable_swid(struct sx_dev *dev, int sx_dev_id, u8 swid, int synd, u64 mac)
{
    int                  i;
    int                  err = 0;
    u8                   dqn;
    u64                  dq_bitmap = 0;
    struct sx_dq        *dq;
    union sx_event_data *event_data = NULL;
    unsigned long        flags;
    u8                   dev_profile_set;

    /* IF PCI-E path is not valid, no need to open DQs */
    if (!sx_dpt_is_path_valid(sx_dev_id, DPT_PATH_PCI_E)) {
        printk(KERN_INFO PFX "PCIe path is not valid for device %u, "
               "will not open DQs\n",
               sx_dev_id);
        goto send_events;
    }

    /* TODO: handle errors */
    for (i = 0; i < NUMBER_OF_ETCLASSES; i++) {
        err = sx_get_sqd_num(dev, swid, i, &dqn);
        if (err) {
            printk(KERN_ERR PFX "Error retrieving sx_get_sdq_cb callback structure! err=[%d]\n", err);
            goto out;
        }

        spin_lock_irqsave(&sx_priv(dev)->sdq_table.lock, flags);
        dq = sx_priv(dev)->sdq_table.dq[dqn];
        spin_unlock_irqrestore(&sx_priv(dev)->sdq_table.lock, flags);
        if (!dq) {
            err = sx_core_create_sdq(dev,
                                     1 << dev->dev_cap.log_max_sdq_sz, dqn, &dq);
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
    for (i = 0; i < dev->profile.rdq_count[swid]; i++) {
        dqn = dev->profile.rdq[swid][i];
        spin_lock_irqsave(&sx_priv(dev)->rdq_table.lock, flags);
        dq = sx_priv(dev)->rdq_table.dq[dqn];
        spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);
        if (!dq) {
            err = sx_core_create_rdq(dev, dev->profile.rdq_properties[dqn].number_of_entries,
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

    spin_lock(&dev->profile_lock);
    if (is_sgmii_supported()) {
        dev->dev_profile_set = 1;
    }
    dev_profile_set = dev->dev_profile_set;
    spin_unlock(&dev->profile_lock);
    if ((dev->profile.swid_type[swid] == SX_KU_L2_TYPE_IB) &&
        dev_profile_set) {
        err = sx_send_enable_ib_swid_events(dev, swid);
        if (err) {
            spin_lock(&dev->profile_lock);
            dev->dev_profile_set = 0;
            spin_unlock(&dev->profile_lock);
            goto out;
        }
    } else if (dev->profile.swid_type[swid] == SX_KU_L2_TYPE_ETH) {
        sx_priv(dev)->swid_data[swid].eth_swid_data.synd = synd;
        sx_priv(dev)->swid_data[swid].eth_swid_data.mac = mac;
        event_data->eth_swid_up.swid = swid;
        event_data->eth_swid_up.synd = synd;
        event_data->eth_swid_up.mac = mac;
        sx_core_dispatch_event(dev, SX_DEV_EVENT_ETH_SWID_UP, event_data);
    }

    sx_bitmap_set(&sx_priv(dev)->swid_bitmap, swid);

out:
    if (event_data) {
        kfree(event_data);
    }

    return err;
}

void sx_disable_swid(struct sx_dev *dev, u8 swid)
{
    int                  i;
    u8                   dqn;
    struct sx_dq        *dq;
    union sx_event_data *event_data = NULL;
    u8                   dev_profile_set;
    int                  err = 0;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        printk(KERN_WARNING PFX "Failed to allocate memory for event data\n");
        goto out;
    }

    if (!sx_bitmap_test(&sx_priv(dev)->swid_bitmap, swid)) {
        printk(KERN_WARNING PFX "SWID %u is not set\n", swid);
        goto out;
    }

    for (i = 0; i < NUMBER_OF_ETCLASSES; i++) {
        err = sx_get_sqd_num(dev, swid, i, &dqn);
        if (err) {
            printk(KERN_ERR PFX "Error retrieving sx_get_sdq_cb callback structure! err=[%d]\n", err);
            break;
        }

        dq = sx_priv(dev)->sdq_table.dq[dqn];
        if (dq && (atomic_read(&dq->refcount) == 1)) {
            sx_core_destroy_sdq(dev, dq);
            sx_priv(dev)->sdq_table.dq[dqn] = NULL;
        } else if (dq) {
            atomic_dec(&dq->refcount);
        }
    }

    for (i = 0; i < dev->profile.rdq_count[swid]; i++) {
        dqn = dev->profile.rdq[swid][i];
        dq = sx_priv(dev)->rdq_table.dq[dqn];
        if (dq && (atomic_read(&dq->refcount) == 1)) {
            sx_core_del_rdq_from_monitor_rdq_list(dq);
            sx_core_destroy_rdq(dev, dq);
            sx_priv(dev)->rdq_table.dq[dqn] = NULL;
        } else if (dq) {
            atomic_dec(&dq->refcount);
        }
    }

    spin_lock(&dev->profile_lock);
    dev_profile_set = dev->dev_profile_set;
    spin_unlock(&dev->profile_lock);
    event_data->ib_swid_change.swid = swid;
    event_data->ib_swid_change.dev_id = dev->profile.dev_id;
    if ((dev->profile.swid_type[swid] == SX_KU_L2_TYPE_IB) && dev_profile_set) {
        sx_core_dispatch_event(dev, SX_DEV_EVENT_IB_SWID_DOWN, event_data);
    } else if (dev->profile.swid_type[swid] == SX_KU_L2_TYPE_ETH) {
        sx_core_dispatch_event(dev, SX_DEV_EVENT_ETH_SWID_DOWN, event_data);
    }

    sx_bitmap_free(&sx_priv(dev)->swid_bitmap, swid);

out:
    if (event_data) {
        kfree(event_data);
    }
}

/*
 *  Workaround for rdq stuck because of wqe_too_short error.
 *  Force rdq size to be SX_MAX_MSG_SIZE on SX
 */
void __sx_adjust_rdq_size(struct sx_dev *dev)
{
    int     i;
    int     rc = 0;
    uint8_t rdq_num = 0;

    rc = sx_core_get_rdq_num_max(dev, &rdq_num);
    if (rc) {
        printk(KERN_ERR PFX "Error: failed to get max RDQ num\n");
    }

    for (i = 0; i < rdq_num; i++) {
        if (dev->profile.rdq_properties[i].entry_size != 0) {
            dev->profile.rdq_properties[i].entry_size = SX_MAX_MSG_SIZE;
        }
    }
}

int sx_handle_set_profile(struct sx_dev *dev)
{
    int           err = 0;
    struct sx_dq *sdq, *rdq;
    u8            dqn;

    __sx_adjust_rdq_size(dev);

    err = check_valid_profile(dev, &dev->profile);
    if (err) {
        printk(KERN_ERR PFX "input profile is not valid\n");
        goto out;
    }

    if (!sx_dpt_is_path_valid(dev->profile.dev_id, DPT_PATH_PCI_E)) {
        printk(KERN_INFO PFX "PCIe path is not valid for device %u, "
               "will not open EMAD DQs\n", dev->profile.dev_id);
        goto out;
    }

    /* no need to open EMAD RDQ on IB only systems */
    if ((dev->profile.pci_profile >= PCI_PROFILE_EN_SINGLE_SWID) &&
        (sx_dpt_get_emad_path(dev->device_id) == DPT_PATH_PCI_E)) {
        dqn = dev->profile.emad_tx_prof.sdq;
        err = sx_core_create_sdq(dev, 1 << dev->dev_cap.log_max_sdq_sz, dqn, &sdq);
        if (err) {
            printk(KERN_ERR PFX "create EMAD sdq %d failed. err: %d\n",
                   dqn, err);
            goto out;
        }

        dqn = dev->profile.emad_rdq;
        err = sx_core_create_rdq(dev, dev->profile.rdq_properties[dqn].number_of_entries,
                                 dqn, &rdq);
        if (err) {
            printk(KERN_ERR PFX "create EMAD rdq %d failed. err: %d\n",
                   dqn, err);
            goto out;
        }
    }

out: return err;
}

static int sx_core_get_hw_etclass_impl(struct isx_meta *meta, u8* hw_etclass)
{
    /* According to the SX PRM
     * etclass should be set to the following value: (7 - Egress Tclass) */

    *hw_etclass = 7 - meta->etclass;

    return 0;
}

static int get_ib_system_port_mid(struct sx_dev *dev, u16 ib_port, u16* system_port_mid)
{
    *system_port_mid = ib_port;

    return 0;
}

static int get_ib_system_port_mid_with_fix_up(struct sx_dev *dev, u16 ib_port, u16* system_port_mid)
{
    *system_port_mid =
        MAX_ROUTER_MID_TABLE_SIZE - MAX_IB_PORT + ib_port;

    return 0;
}


static int sx_core_get_hw_etclass_impl_spectrum(struct isx_meta *meta, u8* hw_etclass)
{
    /* According to the SX PRM
     * etclass should be set to the following value: (7 - Egress Tclass) */

    *hw_etclass = meta->etclass;

    return 0;
}

static int sx_core_get_send_to_port_as_data_supported(u8* send_to_port_as_data_supported)
{
    *send_to_port_as_data_supported = false;

    return 0;
}

static int sx_core_get_send_to_port_as_data_supported_spectrum(u8* send_to_port_as_data_supported)
{
    *send_to_port_as_data_supported = true;

    return 0;
}

static int get_rp_vid_from_db(struct sx_dev *dev, struct completion_info *comp_info, u16 *vlan_id)
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

static int get_rp_vid_from_ci(struct sx_dev *dev, struct completion_info *comp_info, u16 *vlan_id)
{
    *vlan_id = comp_info->vid;
    return 0;
}

static int get_swid_from_db(struct sx_dev *dev, struct completion_info *comp_info, u8 *swid)
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

    case PKT_TYPE_IB_Raw: /* TODO: Extract qpn from IB Raw pkts */
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

static int get_swid_from_ci(struct sx_dev *dev, struct completion_info *comp_info, u8 *swid)
{
    *swid = comp_info->swid;

    return 0;
}

/* Used for SX */
static int sx_get_lag_mid(u16 lag_id, u16 *mid)
{
    if (mid) {
        *mid = lag_id + 0xC000 + sx_glb.profile.max_mid;
    }
    return 0;
}

/* Used for Spectrum */
static int sdk_get_lag_mid(u16 lag_id, u16 *mid)
{
    if (mid) {
        *mid = lag_id + 0x100;
    }
    return 0;
}


static u8 max_cpu_etclass_for_unlimited_mtu_switchx(void)
{
    return 1; /* PRM 2.8.1 "Egress Traffic Class Allocation" */
}


static u8 max_cpu_etclass_for_unlimited_mtu_spectrum(void)
{
    return 3; /* PRM 2.8.1 "Egress Traffic Class Allocation" */
}

static u16 cap_max_mtu_get_sib(void)
{
    return KU_CAP_MAX_MTU_SWITCH_IB;
}

static u16 cap_max_mtu_get_spectrum(void)
{
    return KU_CAP_MAX_MTU_SPECTRUM;
}

static void sx_set_device_profile_update_cqe_v0(struct ku_profile           * profile,
                                                struct profile_driver_params *driver_params)
{
    profile->set_mask_0_63 = profile->set_mask_0_63 | 0x100000000;
    driver_params->cqe_version = 0;
}

static void sx_set_device_profile_update_cqe_v2(struct ku_profile           * profile,
                                                struct profile_driver_params *driver_params)
{
    profile->set_mask_0_63 = profile->set_mask_0_63 | 0x100000000;
    driver_params->cqe_version = 1;
}

static void sx_set_device_profile_update_spc2(struct ku_profile *profile, struct profile_driver_params *driver_params)
{
    profile->set_mask_0_63 = profile->set_mask_0_63 | 0x500000000;
    driver_params->cqe_version = 1;
    driver_params->cqe_time_stamp_type = 2; /* 2: UTC */
}

static u8 sw_rate_limiter_supported(void)
{
    return 1;
}

static int sx_get_phy_port_max(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_MAX;  /* maximum number of physical ports per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static int sx_get_phy_port_max_quantum(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_QUANTUM_MAX;  /* maximum number of physical ports for Quantum per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static int sx_get_phy_port_max_quantum2(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_QUANTUM2_MAX;  /* maximum number of physical ports for Quantum2 per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}
static int sx_get_phy_port_max_spectrum2(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_SPECTRUM2_MAX;  /* maximum number of physical ports for Spectrum2 per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static int sx_get_lag_max(uint16_t *lags, uint16_t *ports_per_lag)
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

static int sx_get_lag_max_spectrum2(uint16_t *lags, uint16_t *ports_per_lag)
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

static uint8_t sx_get_rdq_max(void)
{
    return RDQ_NUM_MAX;
}

/* static - un-comment when ifdef on line 3455 will be removed */
uint8_t sx_get_rdq_max_spectrum2(void)
{
    return RDQ_NUM_MAX_SPC2;
}

int sx_core_get_rdq_num_max(struct sx_dev *dev, uint8_t *rdq_num_max_p)
{
    int rc = 0;

    if (rdq_num_max_p == NULL) {
        printk(KERN_ERR PFX "lags is NULL\n");
        rc = -EINVAL;
        return rc;
    }

    /* We don't use lock because the following function will return hard-coded
     *  value and nothing will be changed after we will init switch with
     *  appropriate callback, hence lock will be redundant here. */

    if (dev && (sx_priv(dev)->dev_specific_cb.sx_get_rdq_max_cb != NULL)) {
        *rdq_num_max_p = sx_priv(dev)->dev_specific_cb.sx_get_rdq_max_cb();
    } else {
        printk(KERN_ERR PFX "Error retrieving sx_get_rdq_max_cb callback\n");
        rc = -EINVAL;
    }

    return rc;
}
EXPORT_SYMBOL(sx_core_get_rdq_num_max);
static int is_eqn_cmd_ifc_only(int eqn, u8 *is_cmd_ifc_only)
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

struct dev_specific_cb spec_cb_sx_a1 = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl,
    .sx_build_isx_header_cb = sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = max_cpu_etclass_for_unlimited_mtu_switchx,
    .sx_get_sdq_cb = sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = get_rp_vid_from_db,
    .get_swid_cb = get_swid_from_db,
    .get_lag_mid_cb = sx_get_lag_mid,
    .get_ib_system_port_mid = get_ib_system_port_mid_with_fix_up,
    .sx_ptp_init = NULL,
    .sx_ptp_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max,
    .sx_get_lag_max_cb = sx_get_lag_max,
    .sx_get_rdq_max_cb = sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_init = NULL,
    .sx_clock_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = cap_max_mtu_get_spectrum,
};
struct dev_specific_cb spec_cb_sx_a2 = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl,
    .sx_build_isx_header_cb = sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = max_cpu_etclass_for_unlimited_mtu_switchx,
    .sx_get_sdq_cb = sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = get_rp_vid_from_ci,
    .get_swid_cb = get_swid_from_db,
    .get_lag_mid_cb = sx_get_lag_mid,
    .get_ib_system_port_mid = get_ib_system_port_mid_with_fix_up,
    .sx_ptp_init = NULL,
    .sx_ptp_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max,
    .sx_get_lag_max_cb = sx_get_lag_max,
    .sx_get_rdq_max_cb = sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_init = NULL,
    .sx_clock_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = cap_max_mtu_get_spectrum,
};
struct dev_specific_cb spec_cb_pelican = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = NULL,
    .sx_get_sdq_cb = sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = get_rp_vid_from_db,
    .get_swid_cb = get_swid_from_db,
    .get_lag_mid_cb = NULL,
    .get_ib_system_port_mid = get_ib_system_port_mid_with_fix_up,
    .sx_ptp_init = NULL,
    .sx_ptp_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max,
    .sx_get_lag_max_cb = sx_get_lag_max,
    .sx_get_rdq_max_cb = sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_init = NULL,
    .sx_clock_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = cap_max_mtu_get_sib,
};
struct dev_specific_cb spec_cb_quantum = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = NULL,
    .sx_get_sdq_cb = sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = get_rp_vid_from_db,
    .get_swid_cb = get_swid_from_db,
    .get_lag_mid_cb = NULL,
    .get_ib_system_port_mid = get_ib_system_port_mid,
    .sx_ptp_init = NULL,
    .sx_ptp_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max_quantum,
    .sx_get_lag_max_cb = sx_get_lag_max,
    .sx_get_rdq_max_cb = sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = is_eqn_cmd_ifc_only,
    .sx_clock_init = NULL,
    .sx_clock_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = cap_max_mtu_get_sib,
};
struct dev_specific_cb spec_cb_quantum2 = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = NULL,
    .sx_get_sdq_cb = sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = get_rp_vid_from_db,
    .get_swid_cb = get_swid_from_db,
    .get_lag_mid_cb = NULL,
    .get_ib_system_port_mid = get_ib_system_port_mid,
    .sx_ptp_init = NULL,
    .sx_ptp_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max_quantum2,
    .sx_get_lag_max_cb = sx_get_lag_max,
    .sx_get_rdq_max_cb = sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = is_eqn_cmd_ifc_only,
    .sx_clock_init = NULL,
    .sx_clock_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = cap_max_mtu_get_sib,
};
struct dev_specific_cb spec_cb_spectrum = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = sx_build_isx_header_v1,
    .max_cpu_etclass_for_unlimited_mtu = max_cpu_etclass_for_unlimited_mtu_spectrum,
    .sx_get_sdq_cb = sx_get_sdq_per_traffic_type,
    .sx_get_sdq_num_cb = sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported_spectrum,
    .get_rp_vid_cb = get_rp_vid_from_ci,
    .get_swid_cb = get_swid_from_ci,
    .get_lag_mid_cb = sdk_get_lag_mid,
    .get_ib_system_port_mid = NULL,
    .sx_ptp_init = sx_ptp_init_spc1,
    .sx_ptp_cleanup = sx_ptp_cleanup_spc1,
    .sx_ptp_dump = sx_ptp_dump_spc1,
    .sx_ptp_rx_handler = sx_ptp_rx_handler_spc1,
    .sx_ptp_tx_handler = sx_ptp_tx_handler_spc1,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_cqe_v2,
    .sx_init_cq_db_cb = sx_init_cq_db_spc,
    .sx_printk_cqe_cb = sx_printk_cqe_v2,
    .is_sw_rate_limiter_supported = NULL,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v2,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v2,
    .sx_disconnect_all_trap_groups_cb = sx_disconnect_all_trap_groups_spectrum,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max,
    .sx_get_lag_max_cb = sx_get_lag_max,
    .sx_get_rdq_max_cb = sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_init = sx_clock_init_spc1,
    .sx_clock_cleanup = sx_clock_cleanup_spc1,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = sx_clock_dump_spc1,
    .cap_max_mtu_get_cb = cap_max_mtu_get_spectrum,
};
struct dev_specific_cb spec_cb_spectrum2 = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = sx_build_isx_header_v1,
    .max_cpu_etclass_for_unlimited_mtu = max_cpu_etclass_for_unlimited_mtu_spectrum,
    .sx_get_sdq_cb = sx_get_sdq_per_traffic_type,
    .sx_get_sdq_num_cb = sx_get_sdq_num_per_etclasss,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported_spectrum,
    .get_rp_vid_cb = get_rp_vid_from_ci,
    .get_swid_cb = get_swid_from_ci,
    .get_lag_mid_cb = sdk_get_lag_mid,
    .get_ib_system_port_mid = NULL,
    .sx_ptp_init = sx_ptp_init_spc2,
    .sx_ptp_cleanup = sx_ptp_cleanup_spc2,
    .sx_ptp_dump = sx_ptp_dump_spc2,
    .sx_ptp_rx_handler = sx_ptp_rx_handler_spc2,
    .sx_ptp_tx_handler = sx_ptp_tx_handler_spc2,
    .sx_ptp_tx_ts_handler = sx_ptp_tx_ts_handler_spc2,
    .sx_ptp_tx_control_to_data = sx_ptp_tx_control_to_data_spc2,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_spc2,
    .sx_init_cq_db_cb = sx_init_cq_db_v2,
    .sx_printk_cqe_cb = sx_printk_cqe_v2,
    .is_sw_rate_limiter_supported = NULL,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v2,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v2,
    .sx_disconnect_all_trap_groups_cb = sx_disconnect_all_trap_groups_spectrum,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max_spectrum2,
    .sx_get_lag_max_cb = sx_get_lag_max_spectrum2,
    .sx_get_rdq_max_cb = sx_get_rdq_max_spectrum2,
    .is_eqn_cmd_ifc_only_cb = is_eqn_cmd_ifc_only,
    .sx_clock_init = sx_clock_init_spc2,
    .sx_clock_cleanup = sx_clock_cleanup_spc2,
    .sx_clock_cqe_ts_to_utc = sx_clock_cqe_ts_to_utc_spc2,
    .sx_clock_dump = sx_clock_dump_spc2,
    .cap_max_mtu_get_cb = cap_max_mtu_get_spectrum,
};
struct dev_specific_cb spec_cb_spectrum3 = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = sx_build_isx_header_v1,
    .max_cpu_etclass_for_unlimited_mtu = max_cpu_etclass_for_unlimited_mtu_spectrum,
    .sx_get_sdq_cb = sx_get_sdq_per_traffic_type,
    .sx_get_sdq_num_cb = sx_get_sdq_num_per_etclasss,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported_spectrum,
    .get_rp_vid_cb = get_rp_vid_from_ci,
    .get_swid_cb = get_swid_from_ci,
    .get_lag_mid_cb = sdk_get_lag_mid,
    .get_ib_system_port_mid = NULL,
    .sx_ptp_init = sx_ptp_init_spc2,
    .sx_ptp_cleanup = sx_ptp_cleanup_spc2,
    .sx_ptp_dump = sx_ptp_dump_spc2,
    .sx_ptp_rx_handler = sx_ptp_rx_handler_spc2,
    .sx_ptp_tx_handler = sx_ptp_tx_handler_spc2,
    .sx_ptp_tx_ts_handler = sx_ptp_tx_ts_handler_spc2,
    .sx_ptp_tx_control_to_data = sx_ptp_tx_control_to_data_spc2,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_spc2,
    .sx_init_cq_db_cb = sx_init_cq_db_v2,
    .sx_printk_cqe_cb = sx_printk_cqe_v2,
    .is_sw_rate_limiter_supported = NULL,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v2,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v2,
    .sx_disconnect_all_trap_groups_cb = sx_disconnect_all_trap_groups_spectrum,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max_spectrum2,
    .sx_get_lag_max_cb = sx_get_lag_max_spectrum2,
    .sx_get_rdq_max_cb = sx_get_rdq_max_spectrum2,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_init = sx_clock_init_spc2,
    .sx_clock_cleanup = sx_clock_cleanup_spc2,
    .sx_clock_cqe_ts_to_utc = sx_clock_cqe_ts_to_utc_spc2,
    .sx_clock_dump = sx_clock_dump_spc2,
    .cap_max_mtu_get_cb = cap_max_mtu_get_spectrum,
};
struct dev_specific_cb spec_cb_spectrum4 = {
    .get_hw_etclass_cb = sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = sx_build_isx_header_v1,
    .max_cpu_etclass_for_unlimited_mtu = max_cpu_etclass_for_unlimited_mtu_spectrum,
    .sx_get_sdq_cb = sx_get_sdq_per_traffic_type,
    .sx_get_sdq_num_cb = sx_get_sdq_num_per_etclasss,
    .get_send_to_port_as_data_supported_cb = sx_core_get_send_to_port_as_data_supported_spectrum,
    .get_rp_vid_cb = get_rp_vid_from_ci,
    .get_swid_cb = get_swid_from_ci,
    .get_lag_mid_cb = sdk_get_lag_mid,
    .get_ib_system_port_mid = NULL,
    .sx_ptp_init = sx_ptp_init_spc2,
    .sx_ptp_cleanup = sx_ptp_cleanup_spc2,
    .sx_ptp_dump = sx_ptp_dump_spc2,
    .sx_ptp_rx_handler = sx_ptp_rx_handler_spc2,
    .sx_ptp_tx_handler = sx_ptp_tx_handler_spc2,
    .sx_ptp_tx_ts_handler = sx_ptp_tx_ts_handler_spc2,
    .sx_set_device_profile_update_cb = sx_set_device_profile_update_spc2,
    .sx_init_cq_db_cb = sx_init_cq_db_v2,
    .sx_printk_cqe_cb = sx_printk_cqe_v2,
    .is_sw_rate_limiter_supported = NULL,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v2,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v2,
    .sx_disconnect_all_trap_groups_cb = sx_disconnect_all_trap_groups_spectrum,
    .sx_get_phy_port_max_cb = sx_get_phy_port_max_spectrum2,
    .sx_get_lag_max_cb = sx_get_lag_max_spectrum2,
    .sx_get_rdq_max_cb = sx_get_rdq_max_spectrum2,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_init = sx_clock_init_spc2,
    .sx_clock_cleanup = sx_clock_cleanup_spc2,
    .sx_clock_cqe_ts_to_utc = sx_clock_cqe_ts_to_utc_spc2,
    .sx_clock_dump = sx_clock_dump_spc2,
    .cap_max_mtu_get_cb = cap_max_mtu_get_spectrum,
};

int sx_core_dev_init_switchx_cb(struct sx_dev *dev, enum sxd_chip_types chip_type, bool force)
{
    int           err = 0;
    unsigned long flags;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    if (!force && (dev->dev_specific_cb_init_done == 1)) {
        printk(KERN_ERR PFX "init callbacks called but just was initialized, chip_type [%d].\n",
               chip_type);
        goto out;
    }

    memset(&(sx_priv(dev)->dev_specific_cb), 0, sizeof(sx_priv(dev)->dev_specific_cb));

    /* init specific and common callbacks per device revision */
    switch (chip_type) {
    case SXD_CHIP_TYPE_SWITCHX_A0:
        sx_err(dev, "Cannot add device , the SDK does not support "
               "SwitchX with revision A0\n");
        err = -EINVAL;
        break;

    case SXD_CHIP_TYPE_SWITCHX_A1:
        /* for A1 revision add specific cb */
        sx_priv(dev)->dev_specific_cb = spec_cb_sx_a1;
        break;

    case SXD_CHIP_TYPE_SWITCHX_A2:
        sx_priv(dev)->dev_specific_cb = spec_cb_sx_a2;
        break;

    case SXD_CHIP_TYPE_SWITCH_IB:
    case SXD_CHIP_TYPE_SWITCH_IB2:
        /* for pelican/eagle add specific cb */
        sx_priv(dev)->dev_specific_cb = spec_cb_pelican;
        break;

    case SXD_CHIP_TYPE_QUANTUM:
        /* for quantum add specific cb */
        sx_priv(dev)->dev_specific_cb = spec_cb_quantum;
        break;

    case SXD_CHIP_TYPE_QUANTUM2:
        /* for quantum2 add specific cb */
        sx_priv(dev)->dev_specific_cb = spec_cb_quantum2;
        break;

    case SXD_CHIP_TYPE_SPECTRUM:
    case SXD_CHIP_TYPE_SPECTRUM_A1:
        /* for condor add specific cb */
        sx_priv(dev)->dev_specific_cb = spec_cb_spectrum;
        break;

    case SXD_CHIP_TYPE_SPECTRUM2:
        /* for spectrum2 add specific cb */
        sx_priv(dev)->dev_specific_cb = spec_cb_spectrum2;
        break;

    case SXD_CHIP_TYPE_SPECTRUM3:
        /* for spectrum3 add specific cb */
        sx_priv(dev)->dev_specific_cb = spec_cb_spectrum3;
        break;

    case SXD_CHIP_TYPE_SPECTRUM4:
        /* for spectrum4 add specific cb */
        sx_priv(dev)->dev_specific_cb = spec_cb_spectrum4;
        break;

    default:
        err = -EINVAL;
        sx_err(dev, "ERROR:hw_ver: 0x%x unsupported. \n",
               chip_type);
        goto out;
    }

    dev->dev_specific_cb_init_done = 1;
    printk(KERN_DEBUG PFX "sx_core_dev_init_switchx_cb chip_type [%d]\n", chip_type);

out:
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

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

static int sx_core_dev_deinit_switchx_cb(struct sx_dev *dev)
{
    int           err = 0;
    unsigned long flags;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    if (dev->dev_specific_cb_init_done == 0) {
        printk(KERN_ERR PFX "deinit callbacks called before was initialized. \n");
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }

    dev->dev_specific_cb_init_done = 0;

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    __sx_core_dev_specific_cb_release_reference(dev);

    /*
     * wait for refcnt == 0
     * In case of timeout , wait_event_timeout return with a value of 0
     * regardless of how condition evaluates.
     */
    if (!wait_event_timeout(sx_priv(dev)->dev_specific_cb_not_in_use,
                            !atomic_read(&sx_priv(dev)->dev_specific_cb_refcnt),
                            SX_CORE_DEV_CB_FINISH_WAIT_TIMEOUT)) {
        printk(KERN_ERR PFX "sx_core_dev_specific_cb_deinit_timeout.\n");
        err = -EBUSY;
        goto out;
    }

    memset(&(sx_priv(dev)->dev_specific_cb), 0, sizeof(sx_priv(dev)->dev_specific_cb));

    printk(KERN_DEBUG PFX "sx_core_dev_deinit_cb done successfully.\n");

out:

    return err;
}

int __sx_core_dev_specific_cb_get_reference(struct sx_dev *dev)
{
    unsigned long flags;
    u8            err = 0;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    if (!dev->dev_specific_cb_init_done) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        printk(KERN_INFO PFX "dev_specific_cb is not init\n");
        goto out;
    }

    atomic_inc(&sx_priv(dev)->dev_specific_cb_refcnt);
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

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
#ifndef NO_PCI
    struct sx_rsc *rsc;

    memcpy(&rsc, skb->cb, sizeof(rsc));
    up(&rsc->write_sem);

    fput(rsc->owner);
#endif
}

static void sx_flush_dqs(struct sx_dev *dev, u8 send)
{
    struct sx_priv     *priv = sx_priv(dev);
    int                 err;
    int                 i;
    int                 max = send ? dev->dev_cap.max_num_sdqs : dev->dev_cap.max_num_rdqs;
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
    int i;

    spin_lock(&dev->profile_lock);
    if (dev->profile_set == 1) {
        dev->profile_set = 0;
        spin_unlock(&dev->profile_lock);
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
            sx_bitmap_free(&sx_priv(dev)->swid_bitmap, i);
        }

        sx_core_register_device(dev);
        goto out;
    }

    spin_unlock(&dev->profile_lock);
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
    printk(KERN_DEBUG PFX " sx_core_open() \n");
#endif
    SX_CORE_UNUSED_PARAM(inode);
    file = kzalloc(sizeof(*file), GFP_KERNEL);
    if (!file) {
#ifdef SX_DEBUG
        printk(KERN_DEBUG PFX " sx_core_open() \n");
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

    return 0;
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

        err = sx_dpt_get_sx_dev_by_id(write_data.meta.dev_id, &dev);
        if (err) {
            printk(KERN_WARNING PFX "sx_core_write: "
                   "Device doesn't exist. Aborting\n");
            goto out;
        }
#if 0
        if (dev && !dev->profile_set) {
            printk(KERN_WARNING PFX "sx_core_write() cannot "
                   "execute because the profile is not "
                   "set\n");
            err = -ENOEXEC;
            goto out;
        }
#endif

        if (!is_sgmii_device(write_data.meta.dev_id)) {
            err = check_valid_meta(dev, &write_data.meta);
            if (err) {
                printk(KERN_WARNING PFX "Cannot execute because meta "
                       "is invalid\n");
                goto out;
            }
        }

        if (write_data.meta.type == SX_PKT_TYPE_LOOPBACK_CTL) {
            err = sx_send_loopback(dev, &write_data, filp, 1, TARGET_PID_DONT_CARE);
            if (err) {
                printk(KERN_WARNING PFX "sx_core_write: "
                       "Failed sending loopback packet\n");
                goto out;
            }

            if (dev) {
                loopback_packets_counter++;
                dev->loopback_packets_counter++;
            } else if (sx_glb.tmp_dev_ptr) {
                sx_glb.tmp_dev_ptr->loopback_packets_counter++;
            }
            user_buffer_copied_size += sizeof(write_data);
            continue;
        }

        /* according to the PRM, emads should get "any ethernet swid" */
        if ((write_data.meta.type == SX_PKT_TYPE_DROUTE_EMAD_CTL) ||
            (write_data.meta.type == SX_PKT_TYPE_EMAD_CTL)) {
            if (!dev || !dev->profile_set || is_sgmii_device(write_data.meta.dev_id)) {
                write_data.meta.swid = 0;
            } else {
                for (i = 0; i < NUMBER_OF_SWIDS; i++) {
                    if (dev->profile.swid_type[i] ==
                        SX_KU_L2_TYPE_ETH) {
                        write_data.meta.swid = i;
                        break;
                    }
                }

                if (i == NUMBER_OF_SWIDS) { /* no ETH swids found */
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
        err = copy_buff_to_skb(&skb, &write_data, true, 1);
        if (err) {
            goto out;
        }

        memcpy(skb->cb, &rsc, sizeof(rsc));
        skb->destructor = sx_skb_destructor;
#ifndef NO_PCI
        get_file(rsc->owner);
        down(&rsc->write_sem);
#endif
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
    printk(KERN_DEBUG PFX "sx_core_write: return "
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

        kfree_skb(entry->skb);
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
    printk(KERN_DEBUG PFX " sx_core_read()\n");
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
int sx_core_ioctl_monitor_rdq_stat_get(struct file *filp, struct sx_dev *dev, unsigned long data)
{
    int                                     err = 0;
    struct ku_monitor_trap_group_stat_ioctl ku;
    struct sx_dq                           *monitor_dq;

    SX_CORE_UNUSED_PARAM(filp);

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


void unset_monitor_rdq(struct sx_dq *dq)
{
    dq->is_monitor = 0;
    if (dq->file_priv_p != NULL) {
        sx_monitor_flush(dq->file_priv_p, dq->file_priv_p->bound_monitor_rdq);
        kfree(dq->file_priv_p->bound_monitor_rdq->sw_dup_evlist_p);
        dq->file_priv_p->bound_monitor_rdq = NULL;
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

static int sx_core_close(struct inode *inode, struct file *filp)
{
    struct event_data     *edata;
    unsigned long          flags;
    struct listener_entry *listener;
    struct list_head      *pos, *q;
    int                    entry;
    struct sx_rsc         *file = filp->private_data;
    struct sx_dev         *dev = sx_glb.tmp_dev_ptr;
    struct sx_dq          *dq;
    uint8_t                i;

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX " sx_core_close() \n");
#endif

    /* delete all listener entries belong to this fd */
    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    for (entry = 0; entry < NUM_HW_SYNDROMES + 1; entry++) {
        if (!list_empty(&sx_glb.listeners_rf_db[entry].list)) {
            list_for_each_safe(pos, q, &sx_glb.listeners_rf_db[entry].list) {
                listener = list_entry(pos,
                                      struct listener_entry, list);
                if ((struct file *)listener->context == filp) {
                    list_del(pos);
                    kfree(listener);
                }
            }
        }
    }
    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);
    spin_lock_irqsave(&file->lock, flags);
    list_for_each_safe(pos, q, &file->evlist.list) {
        edata = list_entry(pos, struct event_data, list);
        list_del(pos);
        kfree_skb(edata->skb);
        kfree(edata);
    }

    spin_unlock_irqrestore(&file->lock, flags);

    if (sx_glb.pci_drivers_in_use & PCI_DRIVER_F_SX_DRIVER) {
        down_write(&sx_glb.pci_restart_lock);
        spin_lock_irqsave(&sx_priv(dev)->rdq_table.lock, flags);
        for (i = 0; i < dev->dev_cap.max_num_rdqs; ++i) {
            dq = sx_priv(dev)->rdq_table.dq[i];
            if (dq && dq->is_monitor && (dq->file_priv_p == file)) {
                sx_core_del_rdq_from_monitor_rdq_list(dq);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
                if (sx_priv(dev)->filter_ebpf_progs[i] != NULL) {
                    bpf_prog_put(sx_priv(dev)->filter_ebpf_progs[i]);
                    sx_priv(dev)->filter_ebpf_progs[i] = NULL;
                }
#endif
            }
        }
        spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);
        up_write(&sx_glb.pci_restart_lock);
    }

    file->owner = NULL;
    kfree(file);
    SX_CORE_UNUSED_PARAM(inode);

    return 0;
}

int sx_core_flush_synd_by_context(void * context)
{
    unsigned long          flags;
    struct listener_entry *listener;
    struct list_head      *pos, *q;
    int                    entry;

    /* delete all listener entries belong to this context */
    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    for (entry = 0; entry < NUM_HW_SYNDROMES + 1; entry++) {
        if (!list_empty(&sx_glb.listeners_rf_db[entry].list)) {
            list_for_each_safe(pos, q,
                               &sx_glb.listeners_rf_db[entry].list){
                listener = list_entry(pos,
                                      struct listener_entry, list);
                if (listener->context == context) {
                    list_del(pos);
                    kfree(listener);
                }
            }
        }
    }
    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_flush_synd_by_context);

int sx_core_flush_synd_by_handler(cq_handler handler)
{
    unsigned long          flags;
    struct listener_entry *listener;
    struct list_head      *pos, *q;
    int                    entry;

    /* delete all listener entries belong to this context */
    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    for (entry = 0; entry < NUM_HW_SYNDROMES + 1; entry++) {
        if (!list_empty(&sx_glb.listeners_rf_db[entry].list)) {
            list_for_each_safe(pos, q,
                               &sx_glb.listeners_rf_db[entry].list){
                listener = list_entry(pos,
                                      struct listener_entry, list);
                if (listener->handler == handler) {
                    list_del(pos);
                    kfree(listener);
                }
            }
        }
    }

    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);

    return 0;
}
EXPORT_SYMBOL(sx_core_flush_synd_by_handler);

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
static int sx_load_fw(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err;

    priv->fw.fw_icm = sx_alloc_icm(dev, priv->fw.fw_pages,
                                   GFP_HIGHUSER | __GFP_NOWARN, 0);
    if (!priv->fw.fw_icm) {
        sx_err(dev, "Couldn't allocate FW area, aborting.\n");
        return -ENOMEM;
    }

    err = sx_MAP_FA(dev, priv->fw.fw_icm);
    if (err) {
        sx_err(dev, "MAP_FA command failed, aborting.\n");
        goto err_free;
    }

    return 0;

err_free:
    sx_free_icm(dev, priv->fw.fw_icm, 0);
    return err;
}

static int sx_core_init_cb(struct sx_dev *dev, uint16_t device_id, uint16_t device_hw_revision)
{
    int                 err = 0;
    enum sxd_chip_types chip_type;

    switch (device_id) {
    case SXD_MGIR_HW_DEV_ID_SX:
        if (device_hw_revision == 0xA1) {
            chip_type = SXD_CHIP_TYPE_SWITCHX_A1;
        } else if (device_hw_revision == 0xA2) {
            chip_type = SXD_CHIP_TYPE_SWITCHX_A2;
        } else if (device_hw_revision == 0xA0) {
            printk(KERN_ERR PFX "The SwitchX device revision is A0, "
                   "and therefore it is not supported by SX driver\n");
            return -EFAULT;
        } else {
            printk(KERN_ERR PFX "The SwitchX device revision (0x%x) "
                   "is not supported by SX driver\n", device_hw_revision);
            return -EFAULT;
        }
        break;

    case SXD_MGIR_HW_DEV_ID_SWITCH_IB:
        chip_type = SXD_CHIP_TYPE_SWITCH_IB;
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM:
        if (device_hw_revision == 0xA1) {
            chip_type = SXD_CHIP_TYPE_SPECTRUM_A1;
        } else if (device_hw_revision == 0xA0) {
            chip_type = SXD_CHIP_TYPE_SPECTRUM;
        } else {
            printk(KERN_ERR PFX "The Spectrum device revision (0x%x) "
                   "is not supported by SX driver\n", device_hw_revision);
            return -EFAULT;
        }
        break;

    case SXD_MGIR_HW_DEV_ID_SWITCH_IB2:
        chip_type = SXD_CHIP_TYPE_SWITCH_IB2;
        break;

    case SXD_MGIR_HW_DEV_ID_QUANTUM:
        chip_type = SXD_CHIP_TYPE_QUANTUM;
        break;

    case SXD_MGIR_HW_DEV_ID_QUANTUM2:
        chip_type = SXD_CHIP_TYPE_QUANTUM2;
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM2:
        chip_type = SXD_CHIP_TYPE_SPECTRUM2;
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM3:
        chip_type = SXD_CHIP_TYPE_SPECTRUM3;
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM4:
        chip_type = SXD_CHIP_TYPE_SPECTRUM4;
        break;

    default:
        printk(KERN_ERR PFX "ERROR: Unresolved chip type. device_id (%u)\n", device_id);
        return -EFAULT;
    }

    err = sx_core_dev_init_switchx_cb(dev, chip_type, 0);
    if (err) {
        printk(KERN_ERR PFX "callback device init failed for device (%u)\n",
               dev->profile.dev_id);
        return err;
    }

    return err;
}

static int sx_init_board(struct sx_dev *dev)
{
    int                        err;
    struct ku_query_board_info board;
    struct ku_access_mgir_reg  reg_data;
    int                        retry_num = 0;

    /*
     *   This is a workaround to race condition happens when FW
     *   boot isn't finished and we start to read MGIR.
     *   We post the in_mailbox but FW zero GO bit. So we think
     *   that command is done.
     *   After this race we get 0 in all MGIR fields.
     *   The temporary solution is to reread again.
     *   The real solution should provide interface to read HEALTH
     *   bits which will indicate that FW boot is finished.
     */
    while (retry_num < 3) {
        memset(&reg_data, 0, sizeof(reg_data));
        reg_data.dev_id = dev->device_id;
        reg_data.op_tlv.type = 1;
        reg_data.op_tlv.length = 4;
        reg_data.op_tlv.dr = 0;
        reg_data.op_tlv.status = 0;
        reg_data.op_tlv.register_id = 0x9020; /* MGIR register ID */
        reg_data.op_tlv.r = 0;
        reg_data.op_tlv.method = 1; /* Query */
        reg_data.op_tlv.op_class = 1;
        reg_data.op_tlv.tid = 0;

        err = sx_ACCESS_REG_MGIR(dev, &reg_data);
        /* Only if we managed to read MGIR successfully we check the HW revision
         * to see it's not A0 */
        if (!err && !reg_data.op_tlv.status &&
            (reg_data.mgir_reg.hw_info.device_id == SXD_MGIR_HW_DEV_ID_SX) &&
            (reg_data.mgir_reg.hw_info.device_hw_revision == SXD_MGIR_HW_REV_ID_A0)) {
            printk(KERN_ERR PFX "The SwitchX device revision is A0, "
                   "and therefore it is not supported by SX driver\n");
            return -EFAULT;
        }

        if (reg_data.mgir_reg.hw_info.device_id != 0) {
            break;
        }

        msleep(500 * retry_num);
        retry_num++;
    }

    chip_info_type = reg_data.mgir_reg.hw_info.device_id;
    chip_info_revision = reg_data.mgir_reg.hw_info.device_hw_revision;
    strncpy(chip_info_psid, (const char*)reg_data.mgir_reg.fw_info.psid, sizeof(chip_info_psid) - 1);

    err = sx_core_init_cb(dev, reg_data.mgir_reg.hw_info.device_id,
                          reg_data.mgir_reg.hw_info.device_hw_revision);
    if (err) {
        printk(KERN_ERR PFX "callback dev init failed for device (%u)\n",
               dev->profile.dev_id);
        return err;
    }

    err = sx_QUERY_FW(dev, NULL);
    if (err) {
        sx_err(dev, "QUERY_FW command failed, aborting.\n");
        return err;
    }

    /* init local mailboxes */
    err = sx_QUERY_FW_2(dev, dev->device_id);
    if (err) {
        sx_err(dev, "QUERY_FW_2 command failed, aborting.\n");
        return err;
    }

    dev->bar0_dbregs_offset = sx_priv(dev)->fw.doorbell_page_offset;
    dev->bar0_dbregs_bar = sx_priv(dev)->fw.doorbell_page_bar;

    err = sx_load_fw(dev);
    if (err) {
        sx_err(dev, "Failed to start FW, aborting.\n");
        return err;
    }

    err = sx_QUERY_AQ_CAP(dev);
    if (err) {
        sx_err(dev, "QUERY_AQ_CAP command failed, aborting.\n");
        goto err_stop_fw;
    }
    dev->dev_cap.max_num_cpu_egress_tcs = 12;
    dev->dev_cap.max_num_cpu_ingress_tcs = 16;

    err = sx_QUERY_BOARDINFO(dev, &board);
    if (err) {
        sx_err(dev, "QUERY_BOARDINFO command failed, aborting.\n");
        goto err_stop_fw;
    }

    dev->xm_exists = board.xm_exists;
    dev->xm_num_local_ports = board.xm_num_local_ports;
    memcpy(dev->xm_local_ports, board.xm_local_ports, sizeof(dev->xm_local_ports));
    sx_priv(dev)->eq_table.inta_pin = board.inta_pin;
    memcpy(dev->board_id, board.board_id, sizeof(dev->board_id));
    dev->vsd_vendor_id = board.vsd_vendor_id;
    return 0;

err_stop_fw:
    sx_UNMAP_FA(dev);
    sx_free_icm(dev, sx_priv(dev)->fw.fw_icm, 0);

    return err;
}

static void sx_enable_msi_x(struct sx_dev *dev)
{
    struct sx_priv   *priv = sx_priv(dev);
    struct msix_entry entry;
    int               err;
    int               i;

    if (msi_x) {
        entry.entry = 0;
        err = pci_enable_msix(dev->pdev, &entry, 1);
        if (err) {
            if (err > 0) {
                printk(KERN_INFO PFX "Only %d MSI-X vectors available, "
                       "not using MSI-X\n", err);
            } else {
                printk(KERN_DEBUG PFX "Failed enabling MSI-X interrupts. "
                       "Going to use standard interrupts instead\n");
            }

            goto no_msi;
        }

        sx_info(dev, "MSI-X interrupts were enabled successfully\n");
        for (i = 0; i < SX_NUM_EQ; ++i) {
            priv->eq_table.eq[i].irq = entry.vector;
        }

        dev->flags |= SX_FLAG_MSI_X;
        return;
    }

no_msi:
    msi_x = 0;
    for (i = 0; i < SX_NUM_EQ; ++i) {
        priv->eq_table.eq[i].irq = dev->pdev->irq;
    }
}

static int sx_map_doorbell_area(struct sx_dev *dev)
{
    dev->db_base =
        ioremap(pci_resource_start(dev->pdev, dev->bar0_dbregs_bar)
                + dev->bar0_dbregs_offset,
                SX_DBELL_REGION_SIZE);
    if (!dev->db_base) {
        printk(KERN_ERR "%s(): bar: %d doorbell base: is NULL \n",
               __func__, dev->bar0_dbregs_bar);

        return -EINVAL;
    }

    printk(KERN_DEBUG "%s(): bar: %d dev->db_base phys: 0x%llx , doorbell base: %p \n",
           __func__,
           dev->bar0_dbregs_bar,
           pci_resource_start(dev->pdev, dev->bar0_dbregs_bar)
           + dev->bar0_dbregs_offset,
           dev->db_base);

    return 0;
}

static void sx_doorbell_cleanup(struct sx_dev *dev)
{
    iounmap(dev->db_base);
}

static int sx_map_cr_space_area(struct sx_dev *dev)
{
    dev->cr_space_size = pci_resource_end(dev->pdev, 0) -
                         pci_resource_start(dev->pdev, 0);
    dev->cr_space_start = ioremap(pci_resource_start(dev->pdev, 0),
                                  dev->cr_space_size);
    if (!dev->cr_space_start) {
        printk(KERN_ERR "%s(): cr_space ioremap failed \n", __func__);
        return -EINVAL;
    }

    printk(KERN_DEBUG "%s(): map cr_space area p:0x%llx, size:%d, cr_space start:%p \n",
           __func__,  pci_resource_start(dev->pdev, 0), dev->cr_space_size, dev->cr_space_start);

    return 0;
}

static void sx_cr_space_cleanup(struct sx_dev *dev)
{
    iounmap(dev->cr_space_start);
    dev->cr_space_size = 0;
}


static void sx_close_board(struct sx_dev *dev)
{
    sx_UNMAP_FA(dev);
    sx_free_icm(dev, sx_priv(dev)->fw.fw_icm, 0);
}

#ifdef NO_PCI
static void sx_destroy_sx(struct sx_dev *dev)
{
    /**Clearing the rdq tables**/
    sx_core_destroy_rdq_table(dev, true);

    /**Clearing the sdq tables**/
    sx_core_destroy_sdq_table(dev, true);

    /**Clearing the cq tables**/
    sx_core_destroy_cq_table(dev);

    /**Returning to polling (not command)**/
    sx_cmd_use_polling(dev);

    /**Clearing the eq tables**/
    sx_cleanup_eq_table(dev);

    return;
}
#endif

static int sx_setup_sx(struct sx_dev *dev)
{
    int err = 0;

    err = sx_init_eq_table(dev);
    if (err) {
        sx_err(dev, "Failed to initialize "
               "event queue table, aborting.\n");
        goto out_ret;
    }

    err = sx_cmd_use_events(dev);
    if (err) {
        sx_err(dev, "Failed to switch to event-driven "
               "firmware commands, aborting.\n");
        goto err_eq_table_free;
    }

    err = sx_core_init_cq_table(dev);
    if (err) {
        sx_err(dev, "Failed to initialize CQ table, aborting.\n");
        goto err_cmd_poll;
    }

    err = sx_core_init_sdq_table(dev);
    if (err) {
        sx_err(dev, "Failed to initialize SDQ table, aborting.\n");
        goto err_cq_table_free;
    }

    err = sx_core_init_rdq_table(dev);
    if (err) {
        sx_err(dev, "Failed to initialize RDQ table, aborting.\n");
        goto err_sdq_table_free;
    }

    return 0;

err_sdq_table_free:
    sx_core_destroy_sdq_table(dev, true);

err_cq_table_free:
    sx_core_destroy_cq_table(dev);

err_cmd_poll:
    sx_cmd_use_polling(dev);

err_eq_table_free:
    sx_cleanup_eq_table(dev);

out_ret:
    return err;
}


static int sx_core_init_one_pci(struct pci_dev *pdev, const struct pci_device_id *id)
{
    struct sx_priv *priv = NULL;
    struct sx_dev  *dev = NULL;
    int             err = 0;

    __pci_probe_state = PCI_PROBE_STATE_STARTED_E;

#ifdef NO_PCI
    printk(KERN_ERR "Running VM version on a real chassis. Aborting.\n");
    return -1;
#endif

    sx_glb.pci_devs_cnt++;

    printk(KERN_INFO PFX "Probe %s(%d) device %u\n", __FUNCTION__, __LINE__, \
           pdev->device);
    err = sx_core_init_one(&priv);
    if (err) {
        dev_err(&pdev->dev, "sx_core_init_one failed with err: %d , aborting.\n",
                err);
        goto out;
    }

    dev = &priv->dev;

    err = pci_enable_device(pdev);
    if (err) {
        dev_err(&pdev->dev, "Cannot enable PCI device, aborting.\n");
        goto err_enable_pdev;
    }

    /* Check for BARs. Length of PCI space: LOG2_CR_BAR_SIZE
     * We expect BAR0:
     * - 1MB in Baz;
     * - 4MB in Pelican;
     * - 16MB in Quantum, Phoenix;
     * - 64MB in Firebird;
     */
    if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
        ((pci_resource_len(pdev, 0) != 1 << 20) &&
         (pci_resource_len(pdev, 0) != 1 << 22) &&
         (pci_resource_len(pdev, 0) != 1 << 24) &&
         (pci_resource_len(pdev, 0) != 1 << 26))) {
        dev_err(&pdev->dev, "Missing BAR0, aborting. Flags: %#lx Len: %#llx \n",
                pci_resource_flags(pdev, 0), pci_resource_len(pdev, 0));
        err = -ENODEV;
        goto err_disable_pdev;
    }

    err = pci_request_region(pdev, 0, DRV_NAME);
    if (err) {
        dev_err(&pdev->dev, "Cannot request control region, "
                "aborting.\n");
        goto err_disable_pdev;
    }

    pci_set_master(pdev);
    err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
    if (err) {
        dev_warn(&pdev->dev, "Warning: couldn't set 64-bit PCI "
                 "DMA mask.\n");
        err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
        if (err) {
            dev_err(&pdev->dev, "Can't set PCI DMA mask, aborting.\n");
            goto err_release_bar0;
        }
    }

    err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
    if (err) {
        dev_warn(&pdev->dev, "Warning: couldn't set 64-bit "
                 "consistent PCI DMA mask.\n");
        err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
        if (err) {
            dev_err(&pdev->dev, "Can't set consistent PCI DMA "
                    "mask, aborting.\n");
            goto err_release_bar0;
        }
    }

    dev->pdev = pdev;

    if (sx_cmd_pool_create(dev)) {
        sx_err(dev, "Failed to create command buffer pool, aborting.\n");
        goto err_release_bar0;
    }

    if (sx_cmd_init_pci(dev)) {
        sx_err(dev, "Failed to initialize command interface, aborting.\n");
        goto err_free_pool;
    }

    pci_set_drvdata(pdev, dev);
    spin_lock(&sx_glb.pci_devs_lock);
    list_add(&dev->list, &sx_glb.pci_devs_list);
    spin_unlock(&sx_glb.pci_devs_lock);
    err = sx_dpt_init_dev_pci(dev);
    if (err) {
        sx_err(dev, "Failed initializing default PCI device "
               "attributes in the DPT, aborting.\n");
        goto err_free_pool;
    }

#if defined(PD_BU)
    printk(KERN_INFO PFX "Performing SW reset is SKIPPED in PD mode.\n");
#else
    err = sx_reset(dev, __perform_chip_reset);
    if (err) {
        sx_err(dev, "Failed to reset HW, aborting.\n");
        goto err_free_pool;
    }
#endif

    err = sx_init_board(dev);
    if (err) {
        goto err_cmd;
    }

    sx_enable_msi_x(dev);
    err = sx_map_doorbell_area(dev);
    if (err) {
        goto err_dbell;
    }

    err = sx_map_cr_space_area(dev);
    if (err) {
        goto err_cr_space;
    }

    /* Only if the device is not registered */
    if (priv->unregistered) {
        err = sx_core_register_device(dev);
        if (err) {
            sx_err(dev, "Failed to register the device, aborting.\n");
            goto err_cr_space_clean;
        }

        priv->unregistered = 0;
    }

    err = sx_setup_sx(dev);
    if ((err == -EBUSY) && (dev->flags & SX_FLAG_MSI_X)) {
        dev->flags &= ~SX_FLAG_MSI_X;
        pci_disable_msix(dev->pdev);
        err = sx_setup_sx(dev);
    }

    if (err) {
        goto out_unregister;
    }

    dev->global_flushing = 0;
    dev->dev_stuck = 0;
    dev->dev_stuck_time = 0;
    sx_core_start_catas_poll(dev);

    if (__oob_pci) {
        sx_glb.oob_backbone_dev = dev;
    }

    err = sx_core_clock_init(priv);
    if (err) {
        sx_err(dev, "Failed to initialize clock. aborting.\n");
        goto out_clock_failed;
    }

    __pci_probe_state = PCI_PROBE_STATE_SUCCESS_E;

    if (__perform_chip_reset) {
        /* udev event for system management purpose (only if chip was reset or warm_boot) */
        kobject_uevent(&pdev->dev.kobj, KOBJ_ADD);
    }

    return 0;

out_clock_failed:
    sx_core_stop_catas_poll(dev);

out_unregister:
    if (!priv->unregistered) {
        sx_core_unregister_device(dev);
        priv->unregistered = 1;
    }

err_cr_space_clean:
    sx_cr_space_cleanup(dev);

err_cr_space:
    sx_doorbell_cleanup(dev);

err_dbell:
    if (dev->flags & SX_FLAG_MSI_X) {
        pci_disable_msix(pdev);
    }

    sx_close_board(dev);

err_free_pool:
    sx_cmd_pool_destroy(dev);
    list_del(&dev->list);

err_cmd:
    sx_cmd_unmap(dev);

err_release_bar0:
    pci_release_region(pdev, 0);

err_disable_pdev:
    pci_disable_device(pdev);
    pci_set_drvdata(pdev, NULL);

err_enable_pdev:
    sx_core_remove_one(priv);

out:
    return err;
}

int sx_core_init_one(struct sx_priv **sx_priv)
{
    struct sx_priv *priv;
    struct sx_dev  *dev;
    int             i, j, err;

#ifdef NO_PCI
    printk(KERN_INFO PFX "Initializing in NO_PCI mode\n");
#endif

    if (!sx_priv) {
        printk(KERN_ERR PFX "Invalid param %s\n", __func__);
        return -EINVAL;
    }

    priv = vmalloc(sizeof(struct sx_priv));
    if (!priv) {
        printk(KERN_ERR PFX "Device struct alloc failed, aborting.\n");
        err = -ENOMEM;
        goto out;
    }
    memset(priv, 0, sizeof *priv);
    dev = &priv->dev;

    /* default pvid for all ports is 1 */
    for (i = 0; i < MAX_SYSPORT_NUM; i++) {
        if (i < MAX_LAG_NUM) {
            priv->pvid_lag_db[i] = 1;
        }

        priv->pvid_sysport_db[i] = 1;
    }

    /* initialize lag_filter_db with invalid value */
    for (i = 0; i < NUM_HW_SYNDROMES; i++) {
        for (j = 0; j < MAX_LAG_PORTS_IN_FILTER; j++) {
            priv->lag_filter_db[i][j] = LAG_ID_INVALID;
        }
    }

    /* initialize fid to hw_fid mapping with invalid value */
    for (i = 0; i < MAX_FIDS_NUM; i++) {
        priv->fid_to_hwfid[i] = INVALID_HW_FID_ID;
    }

    /* initialize rif to hw_fid mapping with invalid value */
    for (i = 0; i < MAX_RIFS_NUM; i++) {
        priv->rif_id_to_hwfid[i] = INVALID_HW_FID_ID;
    }

    err = sx_dpt_init_default_dev(dev);
    if (err) {
        sx_err(dev, "Failed initializing default device "
               "attributes in the DPT, aborting.\n");
        goto out_free_priv;
    }

    err = sx_cmd_init(dev);
    if (err) {
        sx_err(dev, "Failed initializing command interface, aborting.\n");
        goto out_free_priv;
    }

    spin_lock_init(&dev->profile_lock);
    dev->profile_set = 0;
    dev->dev_profile_set = 0;
    dev->first_ib_swid = 1;
    dev->dev_sw_rst_flow = 0;
    spin_lock_init(&priv->ctx_lock);
    spin_lock_init(&priv->db_lock);
    INIT_LIST_HEAD(&priv->ctx_list);
    INIT_LIST_HEAD(&priv->dev_list);
    atomic_set(&priv->cq_backup_polling_refcnt, 0);
    atomic_set(&priv->dev_specific_cb_refcnt, 0);
    init_waitqueue_head(&priv->dev_specific_cb_not_in_use);
    priv->pause_cqn = -1;

    err = sx_core_catas_init(dev);
    if (err) {
        printk(KERN_ERR PFX "Couldn't start catas. Aborting...\n");
        goto out_free_priv;
    }

    err = sx_bitmap_init(&priv->swid_bitmap, NUMBER_OF_SWIDS);
    if (err) {
        sx_err(dev, "Failed to initialize SWIDs bitmap, aborting.\n");
        goto catas_stop;
    }

    set_default_capabilities(dev);
    err = sx_core_register_device(dev);
    if (err) {
        sx_err(dev, "Failed to register the device, aborting.\n");
        goto catas_stop;
    }
    memset(&dev->stats, 0, sizeof(dev->stats));

#ifdef NO_PCI
    err = sx_setup_sx(dev);
    if (err) {
        sx_err(dev, "Failed to in sx_setup_sx, aborting.\n");
        goto out_unregister;
    }

    spin_lock(&sx_glb.pci_devs_lock);
    list_add(&dev->list, &sx_glb.pci_devs_list);
    spin_unlock(&sx_glb.pci_devs_lock);
#endif

    if (sx_priv != NULL) {
        *sx_priv = priv;
    }

    return 0;

#ifdef NO_PCI
out_unregister:
    sx_core_unregister_device(dev);
    priv->unregistered = 1;
#endif

catas_stop:
    sx_core_catas_cleanup(dev);

out_free_priv:
    vfree(priv);

out:
    return err;
}

void sx_core_remove_one(struct sx_priv *priv)
{
    struct sx_dev *dev;

    if (priv == NULL) {
        dev = sx_glb.tmp_dev_ptr;
        sx_glb.tmp_dev_ptr = NULL;
        priv = sx_priv(dev);
    } else {
        dev = &priv->dev;
    }

    if (!dev) {
        return;
    }

    if (!priv->unregistered) {
        sx_core_unregister_device(dev);
        priv->unregistered = 1;
    }

    sx_core_catas_cleanup(dev);

#ifdef NO_PCI
    spin_lock(&sx_glb.pci_devs_lock);
    list_del(&dev->list);
    spin_unlock(&sx_glb.pci_devs_lock);

    /*Freeing the memory for the device tables*/
    sx_destroy_sx(dev);
#endif

    sx_dpt_remove_dev(dev->device_id, 1);

    sx_core_dev_deinit_switchx_cb(dev);
    vfree(priv);
}

static void sx_disconnect_all_trap_groups_spectrum(struct sx_dev *dev)
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
    printk(KERN_DEBUG PFX "sx_disconnect_all_trap_groups: succeeded \n");
}

void sx_core_disconnect_all_trap_groups(struct sx_dev *dev)
{
    int err;

    if (dev == NULL) {
        printk(KERN_ERR PFX "sx_core_disconnect_all_trap_groups: dev is NULL \n");
        return;
    }

    err = __sx_core_dev_specific_cb_get_reference(dev);
    if (err) {
        printk(KERN_ERR PFX " dev_specific_cb_get_ref failed. Failed disconnect trap groups.\n");
        return;
    }

    if (sx_priv(dev)->dev_specific_cb.sx_disconnect_all_trap_groups_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.sx_disconnect_all_trap_groups_cb(dev);
    }
    __sx_core_dev_specific_cb_release_reference(dev);
}


static void sx_core_remove_one_pci(struct pci_dev *pdev)
{
    struct sx_priv *priv;
    struct sx_dev  *dev;
    int             i;

    if (__perform_chip_reset || __warm_boot_mode) {
        /* udev event for system management purpose (only if chip was reset enable or warm boot) */
        kobject_uevent(&pdev->dev.kobj, KOBJ_REMOVE);
    }

    spin_lock(&sx_glb.pci_devs_lock);
    dev = pci_get_drvdata(pdev);
    if (!dev) {
        spin_unlock(&sx_glb.pci_devs_lock);
        return;
    }
    pci_set_drvdata(pdev, NULL);
    list_del(&dev->list);
    spin_unlock(&sx_glb.pci_devs_lock);
    sx_glb.pci_devs_cnt--;

    priv = sx_priv(dev);

    if (!priv->unregistered) {
        sx_core_unregister_device(dev);
        priv->unregistered = 1;
    }

    /*
     * Disconnect all trap groups before flush and destroy
     */
    sx_core_disconnect_all_trap_groups(dev);

    dev->global_flushing = 1;

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if (sx_bitmap_test(&sx_priv(dev)->swid_bitmap, i)) {
            sx_disable_swid(dev, i);
        }
    }

    sx_core_destroy_rdq_table(dev, true);
    sx_core_destroy_sdq_table(dev, true);
    sx_cmd_use_polling(dev);
    sx_cleanup_eq_table(dev);
    sx_core_destroy_cq_table(dev);
    sx_cr_space_cleanup(dev);
    sx_doorbell_cleanup(dev);

    sx_core_ptp_cleanup(priv);
    sx_core_clock_deinit(priv);

    if (dev->flags & SX_FLAG_MSI_X) {
        pci_disable_msix(dev->pdev);
    }

    sx_UNMAP_FA(dev);
    sx_free_icm(dev, sx_priv(dev)->fw.fw_icm, 0);
    sx_cmd_pool_destroy(dev);
    sx_cmd_unmap(dev);

    pci_release_region(pdev, 0);
    pci_disable_device(pdev);

    sx_core_remove_one(priv);
}

void sx_core_clear_internal_data(void)
{
    int dev_id;

    /* dpt clean up except local devices LOCAL_DEVICE_ID_MIN..LOCAL_DEVICE_ID_MAX */
    for (dev_id = 0; dev_id < LOCAL_DEVICE_ID_MIN; dev_id++) {
        memset(&sx_glb.sx_dpt.dpt_info[dev_id], 0, sizeof(sx_glb.sx_dpt.dpt_info[0]));
    }

    /* clear global stats */
    memset(&sx_glb.stats, 0, sizeof(sx_glb.stats));

    /* kernel db is cleared in sx_core_remove_one_pci */
}

int sx_restart_one_pci(struct pci_dev *pdev)
{
    int err = 0;

    if (pdev == NULL) {
        printk(KERN_ERR PFX "sx_restart_one_pci error: pdev == NULL, exit \n");
        return -ENODEV;
    }

    /* enable chip reset from sx_restart_one_pci even
     * if driver was loaded with __perform_chip_reset = 0
     * for example in case of WARM boot*/
    __perform_chip_reset = 1;

    down_write(&sx_glb.pci_restart_lock);
    sx_core_remove_one_pci(pdev);
    err = sx_core_init_one_pci(pdev, NULL);
    up_write(&sx_glb.pci_restart_lock);

    return err;
}

void sx_core_cleanup_dynamic_data(void)
{
    sx_core_listeners_cleanup();
    sx_core_clear_internal_data();
}
EXPORT_SYMBOL(sx_core_cleanup_dynamic_data);
struct pci_device_id sx_pci_table[] = {
    /* Spectrum PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM_PCI_DEV_ID) },

    /* Spectrum2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM2_PCI_DEV_ID) },

    /* Spectrum3 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM3_PCI_DEV_ID) },

    /* Spectrum4 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM4_PCI_DEV_ID) },

    /* SwitchIB PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCH_IB_PCI_DEV_ID) },

    /* SwitchIB2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCH_IB2_PCI_DEV_ID) },

    /* Quantum PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM_PCI_DEV_ID) },

    /* Quantum2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM2_PCI_DEV_ID) },

    { 0, }
};

MODULE_DEVICE_TABLE(pci, sx_pci_table);

static struct pci_driver sx_driver = {
    .name = DRV_NAME,
    .id_table = sx_pci_table,
    .probe = sx_core_init_one_pci,
    .remove = sx_core_remove_one_pci,
#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
    .shutdown = sx_core_shutdown
#endif
};
struct pci_device_id     sx_oob_pci_table[] = {
    /* SwitchX PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCHX_PCI_DEV_ID) },
    { 0, }
};

MODULE_DEVICE_TABLE(pci, sx_oob_pci_table);

static struct pci_driver sx_oob_driver = {
    .name = DRV_NAME "_oob",
    .id_table = sx_oob_pci_table,
    .probe = sx_core_init_one_pci,
    .remove = sx_core_remove_one_pci,
#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
    .shutdown = sx_core_shutdown
#endif
};


int sx_oob_pci_init(void)
{
    int err = 0;

    printk(KERN_INFO "OOB: initializing SwitchX device on PCI\n");

    __pci_probe_state = PCI_PROBE_STATE_NONE_E;
    __perform_chip_reset = 1;
    __oob_pci = 1; /* marking for probe function that we're looking for the OOB pci device */
    err = pci_register_driver(&sx_oob_driver);
    __oob_pci = 0;

    if (err) {
        printk(KERN_ERR "OOB: pci_register_driver() failed (err=%d)\n", err);
        goto out;
    }

#ifndef NO_PCI
    if (__pci_probe_state == PCI_PROBE_STATE_NONE_E) {
        printk(KERN_ERR "OOB: SwitchX device was not found!\n");
        err = -ENODEV;
        goto out;
    }

    if (__pci_probe_state == PCI_PROBE_STATE_STARTED_E) {
        printk(KERN_ERR "OOB: SwitchX found but initialization failed\n");
        err = -EFAULT;
        goto out;
    }
#endif

    printk(KERN_INFO "OOB: SwitchX device was successfully initialized on PCI\n");
    sx_glb.pci_drivers_in_use |= PCI_DRIVER_F_SX_OOB_DRIVER;

out:
    return err;
}


static void __sx_oob_pci_deinit(void)
{
    printk(KERN_INFO "OOB: deinitializing SwitchX device on PCI\n");
    pci_unregister_driver(&sx_oob_driver);
}


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

int sx_init_char_dev(struct cdev *cdev_p)
{
    int ret = 0;
    int devno, major, minor;

    major = MAJOR(char_dev);
    minor = MINOR(char_dev);
    devno = MKDEV(major, minor);
    printk("%s: Create char dev with major:%d minor:%d \n",
           __func__, major, minor);

    cdev_init(cdev_p, &sx_core_fops);
    cdev_p->owner = THIS_MODULE;

    ret = cdev_add(cdev_p, devno, 1);
    if (ret) {
        printk(KERN_ERR PFX "Couldn't add char device. Aborting... err: %d\n",
               ret);
        goto out;
    }

out:
    return ret;
}

void sx_deinit_char_dev(struct cdev *cdev_p)
{
    printk("Deinit char dev: %p , usage:%d\n",
           cdev_p, cdev_p->count);
    cdev_del(cdev_p);
}


int register_driver_with_pci(void)
{
    int err;

    printk(KERN_INFO "Registering with PCI on demand\n");

    printk(KERN_INFO "Unregister old PCI first\n");

    down_write(&sx_glb.pci_restart_lock);

    pci_unregister_driver(&sx_driver);

    __pci_probe_state = PCI_PROBE_STATE_NONE_E;
    __perform_chip_reset = 1;
    err = pci_register_driver(&sx_driver);

    up_write(&sx_glb.pci_restart_lock);

    if (err) {
        printk(KERN_ERR "pci_register_driver() failed (err=%d)\n", err);
        return err;
    }

#ifndef NO_PCI
    if (__pci_probe_state == PCI_PROBE_STATE_NONE_E) {
        printk(KERN_EMERG "pci_register_driver() returned successfully but probe function not called\n");
        pci_unregister_driver(&sx_driver);
    } else if (__pci_probe_state == PCI_PROBE_STATE_STARTED_E) {
        printk(KERN_EMERG "pci_register_driver() returned successfully but probe function failed\n");
        return -1;
    } else {
        sx_glb.pci_drivers_in_use |= PCI_DRIVER_F_SX_DRIVER;
    }
#endif

    printk(KERN_INFO "Successfully registered with PCI\n");

    return 0;
}

#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
static void sx_core_shutdown(struct pci_dev *pdev)
{
    printk(KERN_DEBUG PFX "Shutdown PCI driver\n");
    sx_core_remove_one_pci(pdev);
}
#endif

static int __init sx_core_init(void)
{
    struct sx_priv *priv = NULL;
    int             ret = 0;
    int             i = 0;

#if defined(NO_PCI)
    const int no_pci = 1;
#else
    const int no_pci = 0;
#endif

    printk(KERN_INFO "%s", sx_version);

    memset(&sx_glb, 0, sizeof(sx_glb));

    sx_core_skb_hook_init();

#ifndef NO_PCI
#if defined(CONFIG_MLNX460EX) && defined(SNOOP_MISS_WA)
    config_l2_force_snoop();
#endif
#endif

    sx_core_init_proc_fs();
    sx_dbg_dump_proc_fs_init();

    sx_dpt_init();

    init_rwsem(&sx_glb.pci_restart_lock);
    spin_lock_init(&sx_glb.pci_devs_lock);
    INIT_LIST_HEAD(&sx_glb.pci_devs_list);

    spin_lock_init(&sx_glb.listeners_lock);
    for (i = 0; i < NUM_HW_SYNDROMES + 1; i++) {
        INIT_LIST_HEAD(&sx_glb.listeners_rf_db[i].list);
    }

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
            goto out_close_proc;
        }
    }

    sx_glb.pci_devs_cnt = 0;

    __perform_chip_reset = !fast_boot;
    ret = pci_register_driver(&sx_driver);
    if (ret < 0) {
        printk(KERN_ERR "pci_register_driver() failed (err=%d)\n", ret);
        goto out_remove_one;
    }

    if (__pci_probe_state != PCI_PROBE_STATE_SUCCESS_E) {
        if (!no_pci) { /* PCI probe should have been successful!!! */
            if (__pci_probe_state == PCI_PROBE_STATE_NONE_E) {
                printk(KERN_ERR "pci_register_driver() returned successfully but probe function not called\n");
                pci_unregister_driver(&sx_driver);
            } else if (__pci_probe_state == PCI_PROBE_STATE_STARTED_E) {
                printk(KERN_ERR "pci_register_driver() returned successfully but probe function failed\n");
                ret = -1;
                goto out_unreg_pci;
            }

            printk(KERN_ERR "real PCI device is idle. creating a temporary SX device\n");
        } else { /* NO_PCI, create a default device to work with */
            printk(KERN_INFO "PCI is disabled. creating a SX device.\n");
        }

        ret = sx_core_init_one(&priv);
        if (ret) {
            printk(KERN_ERR PFX "Couldn't initialize the device. Aborting...\n");
            goto out_cdev;
        }

        if (g_chip_type == 0) {
            printk(KERN_ERR PFX "Chip type is not defined for device.\n");
            goto out_remove_one;
        }

        ret = sx_core_dev_init_switchx_cb(&priv->dev, g_chip_type, 0);
        if (ret) {
            printk(KERN_ERR PFX "callback dev init failed for device (%u)\n",
                   priv->dev.profile.dev_id);
            goto out_remove_one;
        }

        sx_glb.tmp_dev_ptr = &priv->dev;
    } else {
        sx_glb.pci_drivers_in_use |= PCI_DRIVER_F_SX_DRIVER;
    }

    ret = sx_init_char_dev(&sx_glb.cdev);
    if (ret < 0) {
        printk(KERN_ERR "sx_init_char_dev() failed (err=%d)\n", ret);
        goto out_unreg_pci;
    }

    return 0;

out_unreg_pci:
    pci_unregister_driver(&sx_driver);
    __pci_probe_state = PCI_PROBE_STATE_NONE_E;

out_remove_one:
    if (no_pci && priv) {
        sx_core_remove_one(priv);
    }

out_cdev:
    unregister_chrdev_region(char_dev, SX_MAX_DEVICES);

out_close_proc:
    sx_dbg_dump_proc_fs_deinit();
    sx_core_close_proc_fs();

    return ret;
}

static void sx_core_listeners_cleanup(void)
{
    unsigned long          flags;
    struct listener_entry *listener;
    struct list_head      *pos, *q;
    int                    entry;

    printk(KERN_INFO PFX "sx_core_listeners_cleanup \n");

    /* delete all remaining listener entries */
    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    for (entry = 0; entry < NUM_HW_SYNDROMES + 1; entry++) {
        if (!list_empty(&sx_glb.listeners_rf_db[entry].list)) {
            list_for_each_safe(pos, q, &sx_glb.listeners_rf_db[entry].list){
                listener = list_entry(pos, struct listener_entry, list);
                list_del(pos);
                kfree(listener);
            }
        }
    }
    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);
}

static void __exit sx_core_cleanup(void)
{
    printk(KERN_INFO PFX "sx_core_cleanup_module \n");

    if (is_sgmii_supported()) {
        sgmii_deinit();

        if (sx_glb.pci_drivers_in_use & PCI_DRIVER_F_SX_OOB_DRIVER) {
            __sx_oob_pci_deinit();
        }
    }

    if (sx_glb.pci_drivers_in_use & PCI_DRIVER_F_SX_DRIVER) {
        pci_unregister_driver(&sx_driver);
        __pci_probe_state = PCI_PROBE_STATE_NONE_E;
    }

    sx_deinit_char_dev(&sx_glb.cdev);

#if defined(NO_PCI)
    sx_core_remove_one(sx_priv(sx_glb.tmp_dev_ptr));
#endif

    unregister_chrdev_region(char_dev, SX_MAX_DEVICES);
    sx_dpt_dereg_i2c_ifc();

    sx_core_listeners_cleanup();
    sx_core_counters_deinit();
    sx_dbg_dump_proc_fs_deinit();
    sx_core_close_proc_fs();
}

/************************************************
 *  MODULE init/exit
 ***********************************************/
module_init(sx_core_init);
module_exit(sx_core_cleanup);


/************************************************
 *                  EOF                         *
 ***********************************************/
