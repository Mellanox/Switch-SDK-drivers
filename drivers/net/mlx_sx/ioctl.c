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

#include <uapi/linux/errno.h>
#include <linux/rwsem.h>

#include <linux/mlx_sx/kernel_user.h>
#include "sx.h"
#include "ioctl_internal.h"

static long __ctrl_cmd_not_implemented(struct file *file, unsigned int cmd, unsigned long data)
{
    SX_CORE_UNUSED_PARAM(cmd);
    SX_CORE_UNUSED_PARAM(data);

    printk(KERN_ERR "ioctl() command %u is not implemented\n", cmd);
    return -ENOTTY;
}

extern const ioctl_handler_cb_t ioctl_reg_handler_table[];
extern const ioctl_handler_cb_t ioctl_auto_reg_handler_table[];
static const ioctl_handler_cb_t
    __ioctl_handler_table[CTRL_CMD_MAX_VAL - CTRL_CMD_MIN_VAL + 1] = {
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_CAPABILITIES)] = ctrl_cmd_get_capabilities,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_PCI_PROFILE)] = ctrl_cmd_set_pci_profile,
    [IOCTL_CMD_INDEX(CTRL_CMD_INVALID)] = __ctrl_cmd_not_implemented, /* do not use this entry! */
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_DEVICE_PROFILE)] = ctrl_cmd_get_device_profile,
    [IOCTL_CMD_INDEX(CTRL_CMD_ADD_SYND)] = ctrl_cmd_add_synd,
    [IOCTL_CMD_INDEX(CTRL_CMD_REMOVE_SYND)] = ctrl_cmd_remove_synd,
    [IOCTL_CMD_INDEX(CTRL_CMD_MONITOR_SW_QUEUE_SYND)] = ctrl_cmd_monitor_sw_queue_synd,
    [IOCTL_CMD_INDEX(CTRL_CMD_MULTI_PACKET_ENABLE)] = ctrl_cmd_multi_packet_enable,
    [IOCTL_CMD_INDEX(CTRL_CMD_BLOCKING_ENABLE)] = ctrl_cmd_blocking_enable,
    [IOCTL_CMD_INDEX(CTRL_CMD_PCI_REGISTER_DRIVER)] = ctrl_cmd_pci_register_driver,
    [IOCTL_CMD_INDEX(CTRL_CMD_RESET)] = ctrl_cmd_reset,
    [IOCTL_CMD_INDEX(CTRL_CMD_PCI_DEVICE_RESTART)] = ctrl_cmd_pci_device_restart,
    [IOCTL_CMD_INDEX(CTRL_CMD_RAISE_EVENT)] = ctrl_cmd_raise_event,
    [IOCTL_CMD_INDEX(CTRL_CMD_ENABLE_SWID)] = ctrl_cmd_enable_swid,
    [IOCTL_CMD_INDEX(CTRL_CMD_DISABLE_SWID)] = ctrl_cmd_disable_swid,
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_SYNDROME_STATUS)] = ctrl_cmd_get_syndrome_status,
    [IOCTL_CMD_INDEX(CTRL_CMD_QUERY_FW)] = ctrl_cmd_query_fw,
    [IOCTL_CMD_INDEX(CTRL_CMD_MAD_DEMUX)] = ctrl_cmd_mad_demux,
    [IOCTL_CMD_INDEX(CTRL_CMD_QUERY_RSRC)] = ctrl_cmd_query_rsrc,
    [IOCTL_CMD_INDEX(CTRL_CMD_QUERY_BOARD_INFO)] = ctrl_cmd_query_board_info,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_SYSTEM_MKEY)] = ctrl_cmd_set_system_mkey,
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_SYSTEM_MKEY)] = ctrl_cmd_get_system_mkey,
    [IOCTL_CMD_INDEX(CTRL_CMD_ISSU_FW)] = ctrl_cmd_issu_fw,
    [IOCTL_CMD_INDEX(CTRL_CMD_ADD_DEV_PATH)] = ctrl_cmd_add_dev_path,
    [IOCTL_CMD_INDEX(CTRL_CMD_REMOVE_DEV_PATH)] = ctrl_cmd_remove_dev_path,
    [IOCTL_CMD_INDEX(CTRL_CMD_REMOVE_DEV)] = ctrl_cmd_remove_dev,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_CMD_PATH)] = ctrl_cmd_set_cmd_path,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_EMAD_PATH)] = ctrl_cmd_set_emad_path,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_MAD_PATH)] = ctrl_cmd_set_mad_path,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_CR_ACCESS_PATH)] = ctrl_cmd_set_cr_access_path,
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_PCI_PROFILE)] = ctrl_cmd_get_pci_profile,
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_SWID_2_RDQ)] = ctrl_cmd_get_swid_2_rdq,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_DEFAULT_VID)] = ctrl_cmd_set_default_vid,
#if defined(PD_BU)
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_PORT_ADMIN_STATUS)] = ctrl_cmd_set_port_admin_status,
#endif
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_VID_MEMBERSHIP)] = ctrl_cmd_set_vid_membership,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_PRIO_TAGGING)] = ctrl_cmd_set_prio_tagging,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_PRIO_TO_TC)] = ctrl_cmd_set_prio_to_tc,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_DEVICE_PROFILE)] = ctrl_cmd_set_device_profile,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_RDQ_RATE_LIMITER)] = ctrl_cmd_set_rdq_rate_limiter,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_RDQ_TIMESTAMP_STATE)] = ctrl_cmd_set_rdq_timestamp_state,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_RDQ_CPU_PRIORITY)] = ctrl_cmd_set_rdq_cpu_priority,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_TRUNCATE_PARAMS)] = ctrl_cmd_set_truncate_params,
    [IOCTL_CMD_INDEX(CTRL_CMD_CR_SPACE_READ)] = ctrl_cmd_cr_space_read,
    [IOCTL_CMD_INDEX(CTRL_CMD_CR_SPACE_WRITE)] = ctrl_cmd_cr_space_write,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_LOCAL_PORT_TO_SWID)] = ctrl_cmd_set_local_port_to_swid,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_IB_TO_LOCAL_PORT)] = ctrl_cmd_set_ib_to_local_port,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_SYSTEM_TO_LOCAL_PORT)] = ctrl_cmd_set_system_to_local_port,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_PORT_RP_MODE)] = ctrl_cmd_set_port_rp_mode,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_LOCAL_PORT_TO_LAG)] = ctrl_cmd_set_local_port_to_lag,
    [IOCTL_CMD_INDEX(CTRL_CMD_LAG_OPER_STATE_SET)] = ctrl_cmd_lag_oper_state_set,
    [IOCTL_CMD_INDEX(CTRL_CMD_PORT_BER_MONITOR_STATE_SET)] = ctrl_cmd_port_ber_monitor_state_set,
    [IOCTL_CMD_INDEX(CTRL_CMD_PORT_BER_MONITOR_BITMASK_SET)] = ctrl_cmd_port_ber_monitor_bitmask_set,
    [IOCTL_CMD_INDEX(CTRL_CMD_TELE_THRESHOLD_SET)] = ctrl_cmd_tele_threshold_set,
    [IOCTL_CMD_INDEX(CTRL_CMD_TRAP_FILTER_ADD)] = ctrl_cmd_trap_filter_add,
    [IOCTL_CMD_INDEX(CTRL_CMD_TRAP_FILTER_REMOVE)] = ctrl_cmd_trap_filter_remove,
    [IOCTL_CMD_INDEX(CTRL_CMD_TRAP_FILTER_REMOVE_ALL)] = ctrl_cmd_trap_filter_remove_all,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_VID_2_IP)] = ctrl_cmd_set_vid_2_ip,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_PORT_VID_TO_FID_MAP)] = ctrl_cmd_set_port_vid_to_fid_map,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_SGMII_SYSTEM_CFG)] = ctrl_cmd_set_sgmii_system_cfg,
    [IOCTL_CMD_INDEX(CTRL_CMD_INIT_SGMII_DEV)] = ctrl_cmd_init_sgmii_dev,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_SGMII_DEFAULT_DEV)] = ctrl_cmd_set_sgmii_default_dev,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_SGMII_MFT_INFO)] = ctrl_cmd_set_sgmii_mft_info,
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_COUNTERS)] = ctrl_cmd_get_counters,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_PTP_MODE)] = ctrl_cmd_set_ptp_mode,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_MONITOR_RDQ)] = ctrl_cmd_set_monitor_rdq,
    [IOCTL_CMD_INDEX(CTRL_CMD_READ_MULTI)] = ctrl_cmd_read_multi,
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_RDQ_STAT)] = ctrl_cmd_get_rdq_stat,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_SKB_OFFLOAD_FWD_MARK_EN)] = ctrl_cmd_set_skb_offload_fwd_mark_en,
    [IOCTL_CMD_INDEX(CTRL_CMD_SAVE_SX_CORE_DB)] = ctrl_cmd_save_sx_core_db,
    [IOCTL_CMD_INDEX(CTRL_CMD_RESTORE_SX_CORE_DB)] = ctrl_cmd_restore_sx_core_db,
    [IOCTL_CMD_INDEX(CTRL_CMD_GET_SX_CORE_DB_RESTORE_ALLOWED)] = ctrl_cmd_get_sx_core_db_restore_allowed,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_FID_TO_HWFID_MAP)] = ctrl_cmd_set_fid_to_hwfid_map,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_PCI_PROFILE_DRIVER_ONLY)] = ctrl_cmd_set_pci_profile_driver_only,
    [IOCTL_CMD_INDEX(CTRL_CMD_FLUSH_EVLIST)] = ctrl_cmd_flush_evlist,
    [IOCTL_CMD_INDEX(CTRL_CMD_SET_SW_IB_NODE_DESC)] = ctrl_cmd_set_sw_ib_node_desc,
};


/**
 * This function is used to perform some configuration commands
 * on the local device.
 *
 * param[in] inode - the associated inode
 * param[in] filp  - a pointer to the associated file
 * param[in] cmd   - the ioctl command to be performed
 * param[in] data  - a data to be passed to the invoked function
 *
 * returns: 0 success
 *	   !0 error
 */

long sx_core_ioctl(struct file *filp, unsigned int cmd, unsigned long data)
{
    ioctl_handler_cb_t handler = NULL;
    long               err = -ENOTTY;
    u8                 access_reg_cmd = 0;

    if ((cmd >= CTRL_CMD_MIN_VAL) && (cmd <= CTRL_CMD_MAX_VAL)) {
        handler = __ioctl_handler_table[IOCTL_CMD_INDEX(cmd)];
    } else if ((cmd >= CTRL_CMD_ACCESS_REG_MIN) && (cmd <= CTRL_CMD_ACCESS_REG_MAX)) {
        access_reg_cmd = 1;
        handler = ioctl_reg_handler_table[IOCTL_REG_INDEX(cmd)];

        /* maybe the handler is implemented in auto-reg */
        if (!handler) {
            handler = ioctl_auto_reg_handler_table[IOCTL_REG_INDEX(cmd)];
        }
    } else {
        err = -EINVAL;
    }

    if (!handler) { /* somehow the given command does not have a handler ... */
        goto out;
    }

    if (access_reg_cmd) {
        down_read(&sx_glb.pci_restart_lock);
        err = handler(filp, cmd, data);
        up_read(&sx_glb.pci_restart_lock);
    } else {
        err = handler(filp, cmd, data);
    }

out:
    return err;
}
