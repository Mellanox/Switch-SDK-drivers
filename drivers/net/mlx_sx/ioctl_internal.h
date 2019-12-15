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

struct file;
struct sx_dev;
extern struct sx_globals sx_glb;

#define IOCTL_CMD_INDEX(cmd) ((cmd) - CTRL_CMD_MIN_VAL)
#define IOCTL_REG_INDEX(cmd) ((cmd) - CTRL_CMD_ACCESS_REG_MIN)
#define IOCTL_REG_HANDLER(reg_name)                                                \
                             [IOCTL_REG_INDEX(CTRL_CMD_ACCESS_REG_ ## reg_name)] = \
        ctrl_cmd_access_reg_ ## reg_name

typedef long (*ioctl_handler_cb_t)(struct file *file, unsigned int cmd, unsigned long data);

#define SX_CORE_IOCTL_ACCESS_REG_HANDLER(reg_name, ku_reg_struct_name)                                     \
    long ctrl_cmd_access_reg_ ## reg_name(struct file *file, unsigned int cmd, unsigned long data)         \
    {                                                                                                      \
        struct ku_reg_struct_name reg_data;                                                                \
        struct sx_dev            *dev;                                                                     \
        int                       err;                                                                     \
                                                                                                           \
        err = copy_from_user(&reg_data, (void*)data, sizeof(reg_data));                                    \
        if (err) {                                                                                         \
            goto out;                                                                                      \
        }                                                                                                  \
                                                                                                           \
        err = sx_dpt_get_cmd_sx_dev_by_id(reg_data.dev_id, &dev);                                          \
        if (err) {                                                                                         \
            printk(KERN_WARNING PFX "sx_core_access_reg " #reg_name ": Device doesn't exist. Aborting\n"); \
            goto out;                                                                                      \
        }                                                                                                  \
                                                                                                           \
        err = sx_ACCESS_REG_ ## reg_name(dev, &reg_data);                                                  \
        if (!err) {                                                                                        \
            err = copy_to_user((void*)data, &reg_data, sizeof(reg_data));                                  \
        }                                                                                                  \
                                                                                                           \
out:                                                                                                       \
        return (long)err;                                                                                  \
    }

#define SX_CORE_IOCTL_GET_GLOBAL_DEV(dev_pp)                                               \
    do {                                                                                   \
        *(dev_pp) = sx_glb.tmp_dev_ptr;                                                    \
        if (!(*(dev_pp))) {                                                                \
            printk(KERN_WARNING PFX "%s: Device doesn't exist. Aborting\n", __FUNCTION__); \
            return -ENXIO;                                                                 \
        }                                                                                  \
    } while (0)


/* helper functions not only for ioctl() */
int register_driver_with_pci(void);
int sx_oob_pci_init(void);
void inc_eventlist_drops_counter(struct sx_dev* sx_dev, u16 hw_synd);
void sx_cq_handle_event_data_prepare(struct event_data      *edata_p,
                                     struct sk_buff         *skb_p,
                                     struct completion_info *comp_info_p);
void sx_monitor_flush(struct sx_rsc *file, struct sx_dq *bound_monitor_rdq);
int get_edata_from_elist(int               *evlist_size,
                         struct event_data *edata_list,
                         struct list_head  *evlist,
                         size_t             user_counter,
                         int                multi_packet_read_enable);
void sx_copy_pkt_metadata_prepare(struct ku_read    *metadata_p,
                                  struct event_data *edata_p);
void unset_monitor_rdq(struct sx_dq *dq);
int sx_core_ptp_cleanup(struct sx_dev *dev);
int sx_send_enable_ib_swid_events(struct sx_dev *dev, u8 swid);

/* ioctl_cmd_ifc.c */
long ctrl_cmd_query_fw(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_mad_demux(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_query_rsrc(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_query_board_info(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_device_profile(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_get_device_profile(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_system_mkey(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_get_system_mkey(struct file *file, unsigned int cmd, unsigned long data);

/* ioctl_common.c - ioctl() helper functions */
int sx_core_ioctl_enable_swid(struct sx_dev *dev, unsigned long data);
int sx_core_add_synd_l2(u8 swid, u16 hw_synd, struct sx_dev *dev, struct ku_port_vlan_params *port_vlan_params);
int sx_core_add_synd_l3(u8 swid, u16 hw_synd, struct sx_dev *dev, struct ku_port_vlan_params *port_vlan_params);
int sx_core_add_synd_phy(u8 swid, u16 hw_synd, struct sx_dev *dev, struct ku_port_vlan_params *port_vlan_params);
int sx_core_ioctl_set_pci_profile(struct sx_dev *dev, unsigned long data, uint8_t set_profile);
int sx_core_ioctl_get_pci_profile(struct sx_dev *dev, unsigned long data);

/* ioctl_db.c */
long ctrl_cmd_restore_sx_core_db(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_save_sx_core_db(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_get_sx_core_db_restore_allowed(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_vid_membership(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_prio_tagging(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_prio_to_tc(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_local_port_to_swid(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_ib_to_local_port(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_system_to_local_port(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_port_rp_mode(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_local_port_to_lag(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_lag_oper_state_set(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_port_ber_monitor_state_set(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_port_ber_monitor_bitmask_set(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_tele_threshold_set(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_vid_2_ip(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_port_vid_to_fid_map(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_fid_to_hwfid_map(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_default_vid(struct file *file, unsigned int cmd, unsigned long data);

/* ioctl_dpt.c */
long ctrl_cmd_add_dev_path(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_remove_dev_path(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_remove_dev(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_cmd_path(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_mad_path(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_emad_path(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_cr_access_path(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_cr_space_read(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_cr_space_write(struct file *file, unsigned int cmd, unsigned long data);

/* ioctl_host_ifc.c */
long ctrl_cmd_add_synd(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_remove_synd(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_monitor_sw_queue_synd(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_multi_packet_enable(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_blocking_enable(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_raise_event(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_get_syndrome_status(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_get_swid_2_rdq(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_rdq_rate_limiter(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_rdq_timestamp_state(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_rdq_cpu_priority(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_truncate_params(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_get_counters(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_monitor_rdq(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_read_multi(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_get_rdq_stat(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_skb_offload_fwd_mark_en(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_flush_evlist(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_trap_filter_add(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_trap_filter_remove(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_trap_filter_remove_all(struct file *file, unsigned int cmd, unsigned long data);

/* ioctl_misc.c */
long ctrl_cmd_get_capabilities(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_issu_fw(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_enable_swid(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_disable_swid(struct file *file, unsigned int cmd, unsigned long data);
#if defined(PD_BU)
long ctrl_cmd_set_port_admin_status(struct file *file, unsigned int cmd, unsigned long data);
#endif /* PD_BU */
long ctrl_cmd_set_ptp_mode(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_sw_ib_node_desc(struct file *file, unsigned int cmd, unsigned long data);

/* ioctl_pci.c */
long ctrl_cmd_set_pci_profile(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_pci_profile_driver_only(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_pci_register_driver(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_pci_device_restart(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_get_pci_profile(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_reset(struct file *file, unsigned int cmd, unsigned long data);

/* ioctl_sgmii.c */
long ctrl_cmd_set_sgmii_system_cfg(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_init_sgmii_dev(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_sgmii_default_dev(struct file *file, unsigned int cmd, unsigned long data);
long ctrl_cmd_set_sgmii_mft_info(struct file *file, unsigned int cmd, unsigned long data);
