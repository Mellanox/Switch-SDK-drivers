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

#include "sx.h"
#include "sgmii_internal.h"
#include "sx_dpt.h"
#include "map.h"
#include "sx_dbg_dump_proc.h"

#define MAC_ADDR_FMT "%02x:%02x:%02x:%02x:%02x:%02x"
#define MAC_ADDR(mac) (mac)[0], (mac)[1], (mac)[2], (mac)[3], (mac)[4], (mac)[5]

#define INVALID_DEV_ID (-1)
#define DEV_ID_IS_VALID(dev_id) ((dev_id) >= 0 && (dev_id) < MAX_NUM_OF_REMOTE_SWITCHES)

#define MAX_OOB_CPU_INGRESS_TCLASS (24)

struct sgmii_dev {
    struct sx_core_map_info   map_info;
    int                       dev_id;
    atomic_t                  refcnt;
    struct completion         delete_completion;
    struct proc_dir_entry    *proc_file;
    struct ku_dpt_sgmii_info  dpt_info;
    struct ku_sgmii_mft_info  mft_info;
    struct sgmii_dev_counters counters;
};

/* MAP: MAC/Vlan-id ==> dev_id */
static struct sx_core_map __sgmii_dev_map;
static rwlock_t           __sgmii_dev_lock;
static DEFINE_MUTEX(__sgmii_dev_lock_user);
static int __sgmii_default_dev_id;

#define FW_TOOL_PROC_DIR_NAME "mlnx-dev"
static struct proc_dir_entry *__fw_tool_proc_dir = NULL;
static struct sgmii_dev      *__sgmii_devices[MAX_NUM_OF_REMOTE_SWITCHES + 1];
struct sgmii_global_counters  __sgmii_global_counters;
struct sgmii_dev_db_dump_context {
    struct seq_file *m;
};


void __sgmii_dev_counters_init(int dev_id, struct sgmii_dev_counters *dev_counters)
{
    char category_name[MAX_COUNTER_CATEGORY_NAME_LEN];

    sprintf(category_name, "sgmii-remote-dev/%d", dev_id);
    sx_core_counter_category_init(&dev_counters->category, category_name);

    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_tx,
                         "EMAD application transmissions",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_rx,
                         "EMAD traps received",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_timeout,
                         "EMAD transaction timeout",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_terminated,
                         "EMAD transaction terminated",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_retransmission,
                         "EMAD retransmission",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_send_failed,
                         "EMAD send failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_transaction_init_failed,
                         "EMAD transaction initialization failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_transaction_completed,
                         "EMAD transaction completed successfully",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_dev_mismatch,
                         "EMAD transaction RX and TX devices mismatch",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->emad_unsolicited,
                         "EMAD unsolicited message",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_tx,
                         "MAD application transmissions",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_rx,
                         "MAD traps received",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_timeout,
                         "MAD transaction timeout",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_terminated,
                         "MAD transaction terminated",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_retransmission,
                         "MAD retransmission",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_send_failed,
                         "MAD send failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_unrecognized_packet,
                         "MAD packet is corrupted",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_transaction_init_failed,
                         "MAD transaction initialization failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_transaction_completed,
                         "MAD transaction completed successfully",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->mad_dev_mismatch,
                         "MAD transaction RX and TX devices mismatch",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_invalid_size,
                         "CR-Space invalid size",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_skb_alloc_failed,
                         "CR-Space failed to allocate skb",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_read,
                         "CR-Space read request",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_write,
                         "CR-Space write request",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_rx,
                         "CR-Space traps received",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_transaction_init_failed,
                         "CR-Space transaction initialization failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_transaction_completed,
                         "CR-Space transaction completed successfully",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_timeout,
                         "CR-Space timeout",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_retransmission,
                         "CR-Space retransmission",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_interrupted,
                         "CR-Space request interrupted by user",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_send_failed,
                         "CR-Space send failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->misc_tx,
                         "MISC packet application transmissions",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->misc_send_failed,
                         "MISC packet send failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_invalid_argument,
                         "TX invalid argument",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_invalid_metadata,
                         "TX invalid metadata",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_sgmii_not_initialized,
                         "TX SGMII not initialized",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_skb_cow_failed,
                         "TX skb_cow() failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_skb_clone_failed,
                         "TX skb_clone() failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_skb_fragmented,
                         "TX - skb is fragmented",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_dev_queue_xmit_failed,
                         "TX dev_queue_xmit() failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_netdev_carrier_down,
                         "TX net device carrier is down",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_exceeds_mtu,
                         "TX frame size exceeds net device's MTU",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->tx_ok,
                         "TX succeeded",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->rx_invalid_ethertype,
                         "RX invalid ethertype",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->rx_cqe_trimmed,
                         "RX CQE trimmed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->rx_untagged_frame,
                         "RX untagged frame",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->rx_warn_vlan_mismatch,
                         "RX VLAN mismatch",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->rx_cqev0_handler_failed,
                         "RX (CQEv0) handling failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->rx_cqev2_handler_failed,
                         "RX (CQEv2) handling failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->rx_cqev0_ok,
                         "RX (CQEv0) succeeded",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->rx_cqev2_ok,
                         "RX (CQEv2) succeeded",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_default_device_not_configured,
                         "CR-Space default device is not configured",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_dev_mismatch,
                         "CR-Space transaction RX and TX devices mismatch",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_invalid_oob_checks,
                         "CR-Space invalid OOB checks",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_invalid_trap_id,
                         "CR-Space invalid trap ID",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_misc_failed,
                         "CR-Space misc failure",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_unsolicited,
                         "CR-Space unsolicited message",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&dev_counters->category,
                         &dev_counters->cr_space_snipped_data,
                         "CR-Space snipped packet",
                         COUNTER_SEV_ERROR);
}


void __sgmii_dev_counters_deinit(int dev_id, struct sgmii_dev_counters *dev_counters)
{
    sx_core_counter_deinit(&dev_counters->emad_tx);
    sx_core_counter_deinit(&dev_counters->emad_rx);
    sx_core_counter_deinit(&dev_counters->emad_timeout);
    sx_core_counter_deinit(&dev_counters->emad_terminated);
    sx_core_counter_deinit(&dev_counters->emad_retransmission);
    sx_core_counter_deinit(&dev_counters->emad_send_failed);
    sx_core_counter_deinit(&dev_counters->emad_transaction_init_failed);
    sx_core_counter_deinit(&dev_counters->emad_transaction_completed);
    sx_core_counter_deinit(&dev_counters->mad_tx);
    sx_core_counter_deinit(&dev_counters->mad_rx);
    sx_core_counter_deinit(&dev_counters->mad_timeout);
    sx_core_counter_deinit(&dev_counters->mad_terminated);
    sx_core_counter_deinit(&dev_counters->mad_retransmission);
    sx_core_counter_deinit(&dev_counters->mad_send_failed);
    sx_core_counter_deinit(&dev_counters->mad_unrecognized_packet);
    sx_core_counter_deinit(&dev_counters->mad_transaction_init_failed);
    sx_core_counter_deinit(&dev_counters->mad_transaction_completed);
    sx_core_counter_deinit(&dev_counters->cr_space_invalid_size);
    sx_core_counter_deinit(&dev_counters->cr_space_skb_alloc_failed);
    sx_core_counter_deinit(&dev_counters->cr_space_read);
    sx_core_counter_deinit(&dev_counters->cr_space_write);
    sx_core_counter_deinit(&dev_counters->cr_space_rx);
    sx_core_counter_deinit(&dev_counters->cr_space_transaction_init_failed);
    sx_core_counter_deinit(&dev_counters->cr_space_transaction_completed);
    sx_core_counter_deinit(&dev_counters->cr_space_timeout);
    sx_core_counter_deinit(&dev_counters->cr_space_retransmission);
    sx_core_counter_deinit(&dev_counters->cr_space_interrupted);
    sx_core_counter_deinit(&dev_counters->cr_space_send_failed);
    sx_core_counter_deinit(&dev_counters->misc_tx);
    sx_core_counter_deinit(&dev_counters->misc_send_failed);
    sx_core_counter_deinit(&dev_counters->tx_invalid_argument);
    sx_core_counter_deinit(&dev_counters->tx_invalid_metadata);
    sx_core_counter_deinit(&dev_counters->tx_sgmii_not_initialized);
    sx_core_counter_deinit(&dev_counters->tx_skb_cow_failed);
    sx_core_counter_deinit(&dev_counters->tx_skb_clone_failed);
    sx_core_counter_deinit(&dev_counters->tx_skb_fragmented);
    sx_core_counter_deinit(&dev_counters->tx_dev_queue_xmit_failed);
    sx_core_counter_deinit(&dev_counters->tx_netdev_carrier_down);
    sx_core_counter_deinit(&dev_counters->tx_exceeds_mtu);
    sx_core_counter_deinit(&dev_counters->tx_ok);
    sx_core_counter_deinit(&dev_counters->rx_invalid_ethertype);
    sx_core_counter_deinit(&dev_counters->rx_cqe_trimmed);
    sx_core_counter_deinit(&dev_counters->rx_untagged_frame);
    sx_core_counter_deinit(&dev_counters->rx_warn_vlan_mismatch);
    sx_core_counter_deinit(&dev_counters->rx_cqev0_handler_failed);
    sx_core_counter_deinit(&dev_counters->rx_cqev2_handler_failed);
    sx_core_counter_deinit(&dev_counters->rx_cqev0_ok);
    sx_core_counter_deinit(&dev_counters->rx_cqev2_ok);
    sx_core_counter_deinit(&dev_counters->emad_dev_mismatch);
    sx_core_counter_deinit(&dev_counters->emad_unsolicited);
    sx_core_counter_deinit(&dev_counters->mad_dev_mismatch);
    sx_core_counter_deinit(&dev_counters->cr_space_default_device_not_configured);
    sx_core_counter_deinit(&dev_counters->cr_space_dev_mismatch);
    sx_core_counter_deinit(&dev_counters->cr_space_invalid_oob_checks);
    sx_core_counter_deinit(&dev_counters->cr_space_invalid_trap_id);
    sx_core_counter_deinit(&dev_counters->cr_space_misc_failed);
    sx_core_counter_deinit(&dev_counters->cr_space_unsolicited);
    sx_core_counter_deinit(&dev_counters->cr_space_snipped_data);
    sx_core_counter_category_deinit(&dev_counters->category);
}


static inline int __sgmii_info_compare(const void *dmac1, const void *dmac2)
{
    /* ignoring PCP & VID in comparison */
    return memcmp(dmac1, dmac2, 6);
}


static uint8_t __is_sgmii_device_LOCKED(int dev_id)
{
    return (DEV_ID_IS_VALID(dev_id) && __sgmii_devices[dev_id] != NULL);
}


uint8_t is_sgmii_device(int dev_id)
{
    unsigned long flags;
    uint8_t       ret;

    if (!is_sgmii_supported()) {
        return 0;
    }

    /* we use read_lock_irqsave/read_lock_irqrestore and not read_lock_bh/read_unlock_bh because we may
     * get here from IB flow where in its layers it uses a spinlock with spin_lock_irqsave() so we cannot
     * use '_bh' style in this context. An example for IB layer that uses spin_lock_irqsave() is ib_send_mad().
     */

    read_lock_irqsave(&__sgmii_dev_lock, flags);
    ret = __is_sgmii_device_LOCKED(dev_id);
    read_unlock_irqrestore(&__sgmii_dev_lock, flags);

    return ret;
}


static int __sgmii_dev_get_by_id_LOCKED(int dev_id, struct sgmii_dev **sgmii_dev)
{
    if (!__is_sgmii_device_LOCKED(dev_id)) {
        return -ENODEV;
    }

    *sgmii_dev = __sgmii_devices[dev_id];
    sgmii_dev_inc_ref(*sgmii_dev);
    return 0;
}


/* must be called outside of sgmii_dev_db lock ! */
static int __sgmii_dev_init_hopf(struct sgmii_dev *sgmii_dev)
{
    struct ku_hopf_reg reg_hopf;
    ku_mgmt_board_t    mgmt_brd;
    uint8_t            cqe_ver;
    int                i, err = 0, ret = 0;

    mgmt_brd = sgmii_get_management_board();
    cqe_ver = sgmii_get_cqe_ver();

    memset(&reg_hopf, 0, sizeof(reg_hopf));
    reg_hopf.cqe_ver = cqe_ver;
    err = sgmii_get_netdev_mac(reg_hopf.mac);
    if (err) {
        printk(KERN_ERR "failed to get SGMII netdev MAC address\n");
        return err;
    }

    reg_hopf.pcp = 0;
    reg_hopf.vid = sgmii_dev->dpt_info.vid;
    reg_hopf.i_f = (mgmt_brd == KU_MGMT_BOARD_1) ? 0 : 1;

    reg_hopf.sr = 1; /* send */
    reg_hopf.rcv_cpu_tclass = 0; /* reserved for SEND flows */
    for (i = 0; i < NUMBER_OF_ETCLASSES; i++) {
        reg_hopf.flow_number = i;

        err = sgmii_emad_access_hopf(sgmii_dev->dev_id, &reg_hopf);
        if (err) {
            printk(KERN_ERR "failed to init HOPF (SDQ %d) for dev id %d [err=%d]\n", i, sgmii_dev->dev_id, err);
            ret = err;
        }
    }

    reg_hopf.sr = 0; /* receive */
    for (i = 0; i < MAX_OOB_CPU_INGRESS_TCLASS; i++) {
        reg_hopf.flow_number = i;
        reg_hopf.rcv_cpu_tclass = i;

        err = sgmii_emad_access_hopf(sgmii_dev->dev_id, &reg_hopf);
        if (err) {
            printk(KERN_ERR "failed to init HOPF (RDQ %d) for dev id %d [err=%d]\n", i, sgmii_dev->dev_id, err);
            ret = err;
        }
    }

    return ret;
}


int sgmii_dev_init(int dev_id, uint8_t init_hopf)
{
    ku_mgmt_board_t    mgmt_brd;
    struct sgmii_dev  *sgmii_dev;
    struct ku_ppad_reg reg_ppad;
    int                err = 0;

    if (!is_sgmii_supported()) {
        printk(KERN_ERR "SGMII is disabled\n");
        return -EPERM;
    }

    mgmt_brd = sgmii_get_management_board();

    err = sgmii_dev_get_by_id(dev_id, &sgmii_dev);
    if (err) {
        printk(KERN_ERR "Dev %d is not SGMII device\n", dev_id);
        return err;
    }

    memset(&reg_ppad, 0, sizeof(reg_ppad));
    reg_ppad.local_port = (mgmt_brd == KU_MGMT_BOARD_1) ? 1 : 2;
    memcpy(reg_ppad.mac, sgmii_dev->dpt_info.dmac, 6);
    err = sgmii_emad_access_ppad(dev_id, &reg_ppad);
    if (err) {
        printk(KERN_ERR "failed to init PPAD for dev_id %d [err=%d]\n", dev_id, err);
        goto out;
    }

    if (init_hopf) {
        err = __sgmii_dev_init_hopf(sgmii_dev);
        if (err) {
            goto out;
        }
    }

out:
    sgmii_dev_dec_ref(sgmii_dev);
    return err;
}


int sgmii_default_dev_set(int dev_id)
{
    struct sgmii_dev *new_default;
    int               err = 0;

    if (!is_sgmii_supported()) {
        printk(KERN_ERR "SGMII is disabled\n");
        return -EPERM;
    }

    mutex_lock(&__sgmii_dev_lock_user);

    err = sgmii_dev_get_by_id(dev_id, &new_default);
    if (err) {
        printk(KERN_ERR "cannot set default device to %d - not a SGMII device\n", dev_id);
        goto out;
    }

    err = __sgmii_dev_init_hopf(new_default);
    if (!err) {
        write_lock_bh(&__sgmii_dev_lock);
        __sgmii_default_dev_id = dev_id;
        write_unlock_bh(&__sgmii_dev_lock);
    }

    sgmii_dev_dec_ref(new_default);

out:
    mutex_unlock(&__sgmii_dev_lock_user);
    return err;
}


static int __sgmii_dev_proc_show(struct seq_file *m, void *v)
{
    struct sgmii_dev *sgmii_dev;
    const char       *dev_type_name;
    int               dev_id;
    int               ret;

    dev_id = (int)(long)m->private;
    ret = sgmii_dev_get_by_id(dev_id, &sgmii_dev);
    if (ret) {
        return 0;
    }

    if (sgmii_dev->mft_info.version == 0) { /* MFT information is not initialized, ignore this device */
        goto out;
    }

    switch (sgmii_dev->mft_info.chip_type) {
    case SXD_MGIR_HW_DEV_ID_SX:
        dev_type_name = "Switch-X";
        break;

    case SXD_MGIR_HW_DEV_ID_SWITCH_IB:
        dev_type_name = "Switch-IB";
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM:
        dev_type_name = "Switch-Spectrum";
        break;

    case SXD_MGIR_HW_DEV_ID_SWITCH_IB2:
        dev_type_name = "Switch-IB-2";
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM2:
        dev_type_name = "Switch-Spectrum-2";
        break;

    case SXD_MGIR_HW_DEV_ID_QUANTUM:
        dev_type_name = "Switch-IB-3";
        break;

    default:
        dev_type_name = "N/A";
        break;
    }

    seq_printf(m, "FORMAT_VERSION=%u\n", sgmii_dev->mft_info.version);
    seq_printf(m, "DEVICE_TYPE=%s\n", dev_type_name);
    seq_printf(m, "FRU_NAME=%s\n", sgmii_dev->mft_info.fru_name);
    seq_printf(m, "FRU_MODIFIER=%u\n", sgmii_dev->mft_info.fru_modifier);
    seq_printf(m, "UID=%d\n", sgmii_dev->mft_info.dev_id);

out:
    sgmii_dev_dec_ref(sgmii_dev);
    return 0;
}


static int __sgmii_dev_proc_open(struct inode *inode, struct file *file)
{
    int dev_id;

    dev_id = (int)(long)PDE_DATA(inode);
    return single_open(file, __sgmii_dev_proc_show, (void*)(long)dev_id);
}


#define MAX_PROC_FILENAME_LEN (20)

static void __sgmii_dev_id_to_proc_file_name(int dev_id, char *proc_file_name)
{
    snprintf(proc_file_name, MAX_PROC_FILENAME_LEN, "mlnxsw-%d", dev_id);
}


static void __sgmii_dev_create_proc_file(struct sgmii_dev *sgmii_dev)
{
    static const struct file_operations __sgmii_dev_proc_handler = {
        .owner = THIS_MODULE,
        .open = __sgmii_dev_proc_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release
    };
    char                                proc_file_name[MAX_PROC_FILENAME_LEN];

    __sgmii_dev_id_to_proc_file_name(sgmii_dev->dev_id, proc_file_name);
    sgmii_dev->proc_file = proc_create_data(proc_file_name,
                                            S_IFREG | S_IRUGO,
                                            __fw_tool_proc_dir,
                                            &__sgmii_dev_proc_handler,
                                            (void*)(long)sgmii_dev->dev_id);

    if (!sgmii_dev->proc_file) {
        printk(KERN_ERR "failed to create proc file for dev_id %d. ignoring\n", sgmii_dev->dev_id);
    }
}


static void __sgmii_dev_delete_proc_file(struct sgmii_dev *sgmii_dev)
{
    char proc_file_name[MAX_PROC_FILENAME_LEN];

    __sgmii_dev_id_to_proc_file_name(sgmii_dev->dev_id, proc_file_name);

    printk(KERN_INFO "delete proc file %s\n", proc_file_name);
    remove_proc_entry(proc_file_name, __fw_tool_proc_dir);
}


int sgmii_dev_add(int dev_id, const struct ku_dpt_sgmii_info *dpt_sgmii_info)
{
    struct sgmii_dev *sgmii_dev;
    int               ret = 0;

    if (!DEV_ID_IS_VALID(dev_id) ||
        !dpt_sgmii_info ||
        ZERO_MAC(dpt_sgmii_info->dmac) ||
        (dpt_sgmii_info->vid > 0xfff)) {
        printk(KERN_ERR "sgmii information has invalid data\n");
        return -EINVAL;
    }

    sgmii_dev = kzalloc(sizeof(struct sgmii_dev), GFP_KERNEL);
    if (!sgmii_dev) {
        printk(KERN_ERR "failed to allocate sgmii device\n");
        return -ENOMEM;
    }

    sgmii_dev->dev_id = dev_id;
    memcpy(&sgmii_dev->dpt_info, dpt_sgmii_info, sizeof(sgmii_dev->dpt_info));
    atomic_set(&sgmii_dev->refcnt, 1);

    mutex_lock(&__sgmii_dev_lock_user);
    write_lock_bh(&__sgmii_dev_lock);

    if (__is_sgmii_device_LOCKED(dev_id)) {
        printk(KERN_ERR "failed to insert a new sgmii dev - already exists\n");
        ret = -EEXIST;
        goto out;
    }

    ret = sx_core_map_insert(&__sgmii_dev_map, dpt_sgmii_info->dmac, &sgmii_dev->map_info, GFP_ATOMIC);
    if (ret) {
        printk(KERN_ERR "failed to insert a new sgmii dev. ret=%d\n", ret);
        goto out;
    }

    __sgmii_devices[dev_id] = sgmii_dev;
    __sgmii_dev_counters_init(dev_id, &sgmii_dev->counters);

    sx_glb.sx_dpt.dpt_info[dev_id].is_ifc_valid[DPT_PATH_I2C] = 1;
    sx_dpt_set_cmd_path(dev_id, DPT_PATH_I2C);

out:
    write_unlock_bh(&__sgmii_dev_lock);

    /* here we're out of the spinlock but still inside mutex.
     * we can do some operations that we could not do within a spinlock
     */

    if (ret == 0) {
        __sgmii_dev_create_proc_file(sgmii_dev);
    }

    mutex_unlock(&__sgmii_dev_lock_user);

    if (ret) {
        kfree(sgmii_dev);
    }

    return ret;
}


int sgmii_dev_del(int dev_id)
{
    struct sgmii_dev        *sgmii_dev = NULL;
    struct sx_core_map_info *map_info;
    int                      ret = 0;

    mutex_lock(&__sgmii_dev_lock_user);
    write_lock_bh(&__sgmii_dev_lock);

    if (!__is_sgmii_device_LOCKED(dev_id)) {
        printk(KERN_ERR "failed to delete sgmii dev %d - not SGMII device\n", dev_id);
        ret = -ENODEV;
        goto out;
    }

    sgmii_dev = __sgmii_devices[dev_id];

    __sgmii_dev_counters_deinit(sgmii_dev->dev_id, &sgmii_dev->counters);
    sx_core_map_remove(&__sgmii_dev_map, sgmii_dev->dpt_info.dmac, &map_info);
    __sgmii_devices[dev_id] = NULL;

    if (__sgmii_default_dev_id == dev_id) {
        printk(KERN_WARNING "delete sgmii dev %d - this is currently the default device!\n", dev_id);
        __sgmii_default_dev_id = INVALID_DEV_ID;
    }

out:
    write_unlock_bh(&__sgmii_dev_lock);

    /* here we're out of the spinlock but still inside mutex.
     * we can do some operations that we could not do within a spinlock
     */

    if (ret == 0) {
        __sgmii_dev_delete_proc_file(sgmii_dev);
    }

    mutex_unlock(&__sgmii_dev_lock_user);

    if (sgmii_dev) {
        init_completion(&sgmii_dev->delete_completion);
        sgmii_dev_dec_ref(sgmii_dev);
        wait_for_completion_interruptible(&sgmii_dev->delete_completion);

        kfree(sgmii_dev);
    }

    return ret;
}


int sgmii_dev_set_mft_info(const struct ku_sgmii_mft_info *mft_info)
{
    struct sgmii_dev *sgmii_dev;
    int               ret = 0;

    if (!mft_info || !DEV_ID_IS_VALID(mft_info->dev_id)) {
        printk(KERN_ERR "set_mft_info() invalid parameters\n");
        return -EINVAL;
    }

    mutex_lock(&__sgmii_dev_lock_user);
    write_lock_bh(&__sgmii_dev_lock);

    if (!__is_sgmii_device_LOCKED(mft_info->dev_id)) {
        printk(KERN_ERR "failed to set MFT info for sgmii dev %d - not SGMII device\n", mft_info->dev_id);
        ret = -ENODEV;
        goto out;
    }

    sgmii_dev = __sgmii_devices[mft_info->dev_id];
    memcpy(&sgmii_dev->mft_info, mft_info, sizeof(sgmii_dev->mft_info));

out:
    write_unlock_bh(&__sgmii_dev_lock);
    mutex_unlock(&__sgmii_dev_lock_user);

    return ret;
}


int sgmii_dev_get_by_mac(const uint8_t *mac, struct sgmii_dev **sgmii_dev)
{
    struct sx_core_map_info *map_info;
    int                      ret;

    read_lock_bh(&__sgmii_dev_lock);

    ret = sx_core_map_lookup(&__sgmii_dev_map, mac, &map_info);
    if (ret) {
        goto out;
    }

    *sgmii_dev = container_of(map_info, struct sgmii_dev, map_info);
    sgmii_dev_inc_ref(*sgmii_dev);

out:
    read_unlock_bh(&__sgmii_dev_lock);
    return ret;
}


int sgmii_dev_get_by_id(int dev_id, struct sgmii_dev **sgmii_dev)
{
    int ret;

    read_lock_bh(&__sgmii_dev_lock);

    if (dev_id == DEFAULT_DEVICE_ID) {
        if (__sgmii_default_dev_id == INVALID_DEV_ID) {
            COUNTER_INC(&__sgmii_global_counters.tx_default_device_not_configured);
            ret = -ENODEV;
            goto out;
        }

        dev_id = __sgmii_default_dev_id;
    }

    ret = __sgmii_dev_get_by_id_LOCKED(dev_id, sgmii_dev);
    if (ret) {
        COUNTER_INC(&__sgmii_global_counters.tx_not_sgmii_dev);
    }

out:
    read_unlock_bh(&__sgmii_dev_lock);
    return ret;
}


int sgmii_default_dev_id_get(int *dev_id)
{
    struct sgmii_dev *sgmii_dev;
    int               ret;

    ret = sgmii_dev_get_by_id(DEFAULT_DEVICE_ID, &sgmii_dev);
    if (ret == 0) {
        *dev_id = sgmii_dev->dev_id;
        sgmii_dev_dec_ref(sgmii_dev);
    }

    return ret;
}


static int __sgmii_dev_db_handler(struct seq_file *m, void *v)
{
    struct sgmii_dev *sgmii_dev;
    const uint8_t    *dmac;
    char              is_default;
    int               i;

    seq_printf(m, "----------------------------------------------------------------------\n");
    seq_printf(m, "%-1s   %-6s   %-17s   %-7s   %-6s\n",
               "D", "dev-id", "DMAC", "vlan-id", "RefCnt");
    seq_printf(m, "----------------------------------------------------------------------\n");

    read_lock_bh(&__sgmii_dev_lock);

    for (i = 0; i < sizeof(__sgmii_devices) / sizeof(__sgmii_devices[0]); i++) {
        sgmii_dev = __sgmii_devices[i];

        if (!sgmii_dev) {
            continue;
        }

        dmac = sgmii_dev->dpt_info.dmac;

        if (sgmii_dev->dev_id == __sgmii_default_dev_id) {
            is_default = '*';
        } else {
            is_default = ' ';
        }

        seq_printf(m, "%c   %-6d   %02x:%02x:%02x:%02x:%02x:%02x   %-7u   %-6d\n",
                   is_default,
                   sgmii_dev->dev_id,
                   dmac[0], dmac[1], dmac[2], dmac[3], dmac[4], dmac[5],
                   sgmii_dev->dpt_info.vid,
                   atomic_read(&sgmii_dev->refcnt));
    }

    read_unlock_bh(&__sgmii_dev_lock);

    return 0;
}


void sgmii_dev_inc_ref(struct sgmii_dev *sgmii_dev)
{
    atomic_inc(&sgmii_dev->refcnt);
}


void sgmii_dev_dec_ref(struct sgmii_dev *sgmii_dev)
{
    int refs;

    refs = atomic_dec_return(&sgmii_dev->refcnt);
    if (refs < 0) {
        printk(KERN_ERR "SGMII device %d reference count is negative!\n", sgmii_dev->dev_id);
        dump_stack();
    }

    if (refs == 0) { /* only sgmii_dev_del() should get to refcnt=0 */
        complete(&sgmii_dev->delete_completion);
    }
}


struct sgmii_dev_counters * sgmii_dev_get_counters(struct sgmii_dev *sgmii_dev)
{
    return &sgmii_dev->counters;
}


const struct ku_dpt_sgmii_info * sgmii_dev_get_dpt_info(const struct sgmii_dev *sgmii_dev)
{
    return &sgmii_dev->dpt_info;
}


int sgmii_dev_get_id(const struct sgmii_dev *sgmii_dev)
{
    return sgmii_dev->dev_id;
}


int sgmii_dev_db_init(void)
{
    int ret;

    rwlock_init(&__sgmii_dev_lock);
    __sgmii_default_dev_id = INVALID_DEV_ID;

    __fw_tool_proc_dir = proc_mkdir(FW_TOOL_PROC_DIR_NAME, NULL);
    if (!__fw_tool_proc_dir) {
        printk(KERN_ERR "failed to create fw_tool proc dir\n");
        return -ENOMEM;
    }

    ret = sx_core_map_init(&__sgmii_dev_map, __sgmii_info_compare, 6, 0);
    if (ret) {
        printk(KERN_ERR "failed to create sgmii device map (err=%d)\n", ret);
        return ret;
    }

    return sx_dbg_dump_proc_fs_register("sgmii_dev_db", __sgmii_dev_db_handler, NULL);
}


void sgmii_dev_db_deinit(void)
{
    sx_dbg_dump_proc_fs_unregister("sgmii_dev_db");
    remove_proc_entry(FW_TOOL_PROC_DIR_NAME, NULL);
}
