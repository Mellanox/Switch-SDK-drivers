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

#include <linux/seq_file.h>
#include "sx.h"
#include "sx_dbg_dump_proc.h"
#include "dev_db.h"

static int __fid_to_hwfid_dump(struct seq_file *m, void *v, void *context)
{
    u16             i = 0;
    u16             fid = 0;
    struct sx_priv *priv = NULL;
    unsigned long   flags;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "FID to HW_FID mapping dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    sx_dbg_dump_print_table_header(m, "%-7s| %-7s| %-7s", "#", "FID", "HW_FID");

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    i = 0;
    for (fid = 0; fid < MAX_FIDS_NUM; fid++) {
        if (priv->fid_to_hwfid[fid] != INVALID_HW_FID_ID) {
            i++;
            seq_printf(m, "%-7u| %-7u| %-7u\n",
                       i,
                       fid,
                       priv->fid_to_hwfid[fid]);
        }
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __rif_to_hwfid_dump(struct seq_file *m, void *v, void *context)
{
    u16             i = 0;
    u16             rif_id = 0;
    struct sx_priv *priv = NULL;
    unsigned long   flags;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "RIF to HW_FID mapping dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    sx_dbg_dump_print_table_header(m, "%-7s| %-7s| %-7s", "#", "RIF", "HW_FID");

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    i = 0;
    for (rif_id = 0; rif_id < MAX_RIFS_NUM; rif_id++) {
        if (priv->rif_id_to_hwfid[rif_id] != INVALID_HW_FID_ID) {
            i++;
            seq_printf(m, "%-7u| %-7u| %-7u\n",
                       i,
                       rif_id,
                       priv->fid_to_hwfid[rif_id]);
        }
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __rif_data_dump(struct seq_file *m, void *v, void *context)
{
    u16             rif_id = 0;
    struct sx_priv *priv = NULL;
    unsigned long   flags;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "RIF data dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    sx_dbg_dump_print_table_header(m, "%-7s| %-7s| %-15s| %-7s|", "RIF", "IS_LAG", "LAG_ID/PORT", "VLAN_ID");

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    for (rif_id = 0; rif_id < MAX_RIFS_NUM; rif_id++) {
        if (priv->rif_data[rif_id].is_valid) {
            seq_printf(m, "%-7u| %-7u| %-15u| %-7u|\n",
                       rif_id,
                       priv->rif_data[rif_id].is_lag,
                       priv->rif_data[rif_id].is_lag ?
                       priv->rif_data[rif_id].lag_id : priv->rif_data[rif_id].local_port,
                       priv->rif_data[rif_id].vlan_id);
        }
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __sys_to_local_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "system-port to local-port dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    sx_dbg_dump_print_table_header(m, "%-7s   %-5s   %-4s",
                                   "system", "local", "PVID");

    for (i = 0; i < MAX_SYSPORT_NUM; i++) {
        if (priv->system_to_local_db[i] != 0) {
            seq_printf(m, "0x%-5x   %-5d   %-4d\n",
                       i, priv->system_to_local_db[i], priv->pvid_sysport_db[i]);
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __local_to_sys_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "local-port to system-port dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    sx_dbg_dump_print_table_header(m, "%-5s   %-7s   %-4s",
                                   "local", "system", "PVID");

    for (i = 0; i < MAX_PHYPORT_NUM + 1; i++) {
        if (priv->local_to_system_db[i] != 0) {
            seq_printf(m, "%-5d   0x%-5x   %-4d\n",
                       i, priv->local_to_system_db[i], priv->pvid_sysport_db[priv->local_to_system_db[i]]);
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __lag_to_pvid_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        lag_max = 0, lag_member_max = 0;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "LAG to PVID dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        seq_printf(m, "failed to get max number of LAGs.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-6s   %-4s",
                                   "LAG ID", "PVID");

    for (i = 0; i < lag_max; i++) {
        if (priv->pvid_lag_db[i] != 0) {
            seq_printf(m, "%-6d   %-4d\n",
                       i, priv->pvid_lag_db[i]);
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __local_to_module_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "local-port to module and slot dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    sx_dbg_dump_print_table_header(m, "%-5s   %-7s   %-4s",
                                   "local", "module", "slot");

    for (i = 0; i < MAX_PHYPORT_NUM + 1; i++) {
        seq_printf(m, "%-5d   %-7d   %-4d\n",
                   i, priv->local_to_module_map[i], priv->local_to_slot_map[i]);
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __lag_member_to_local_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        lag_max = 0, lag_member_max = 0;
    u8              is_printed;
    int             i, j;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "LAG member to local dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        seq_printf(m, "failed to get max number of LAGs.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-6s   %-10s   %-5s",
                                   "LAG ID", "LAG-member", "local");

    for (i = 0; i < lag_max; i++) { /* lag id */
        is_printed = 0;

        for (j = 0; j < lag_member_max; j++) { /* lag member id */
            if (priv->lag_member_to_local_db[i][j] != 0) {
                if (!is_printed) {
                    seq_printf(m, "%-6d   %-10d   %-5d\n",
                               i, j, priv->lag_member_to_local_db[i][j]);
                    is_printed = 1;
                } else {
                    seq_printf(m, "%-6s   %-10d   %-5d\n",
                               "", j, priv->lag_member_to_local_db[i][j]);
                }
            }
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __router_port_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        lag_max = 0, lag_member_max = 0, phy_port_max = 0;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "router port dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        seq_printf(m, "failed to get max number of PHY ports.\n");
        return 0;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        seq_printf(m, "failed to get max number of LAGs.\n");
        return 0;
    }

    for (i = 0; i < phy_port_max; i++) { /* system port */
        if (priv->local_is_rp[i] != 0) {
            seq_printf(m, "local: %d\n", i);
        }
    }

    sx_dbg_dump_print_empty_line(m);

    for (i = 0; i < lag_max; i++) { /* LAG ID */
        if (priv->lag_is_rp[i] != 0) {
            seq_printf(m, "LAG: %d\n", i);
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __local_to_swid_dump(struct seq_file *m, void *v, void *context)
{
    uint16_t        phy_port_max = 0;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_priv *priv;
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "local to swid dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        seq_printf(m, "failed to get max number of PHY ports.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-5s   %-4s",
                                   "local", "swid");

    for (i = 0; i < (phy_port_max + 1); i++) { /* system port */
        seq_printf(m, "%-5d   %-4d\n",
                   i, priv->local_to_swid_db[i]);
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __truncate_size_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "truncate size dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    sx_dbg_dump_print_table_header(m, "%-3s   %-13s",
                                   "RDQ", "truncate-size");

    for (i = 0; i < NUMBER_OF_RDQS; i++) { /* rdq */
        if (priv->truncate_size_db[i] != 0) {
            seq_printf(m, "%-3d   %-13d\n",
                       i, priv->truncate_size_db[i]);
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __prio_to_tc_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        lag_max = 0, lag_member_max = 0, phy_port_max = 0;
    int             i, j;
    u8              is_printed;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "prio to tc dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        seq_printf(m, "failed to get max number of PHY ports.\n");
        return 0;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        seq_printf(m, "failed to get max number of LAGs.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-7s   %-4s   %-2s",
                                   "sysport", "prio", "tc");

    for (i = 0; i < (phy_port_max + 1); i++) { /* system port */
        is_printed = 0;

        for (j = 0; j < (MAX_PRIO_NUM + 1); j++) { /* prio */
            if (priv->port_prio2tc[i][j]) {
                if (!is_printed) {
                    seq_printf(m, "0x%-5x   %-4d   %-2d\n",
                               i,
                               j,
                               priv->port_prio2tc[i][j]);
                    is_printed = 1;
                } else {
                    seq_printf(m, "%-7s   %-4d   %-2d\n",
                               "",
                               j,
                               priv->port_prio2tc[i][j]);
                }
            }
        }
    }

    sx_dbg_dump_print_empty_line(m);

    sx_dbg_dump_print_table_header(m, "%-6s   %-4s   %-2s",
                                   "LAG ID", "prio", "tc");

    for (i = 0; i < (lag_max + 1); i++) { /* LAG ID */
        is_printed = 0;

        for (j = 0; j < (MAX_PRIO_NUM + 1); j++) { /* prio */
            if (priv->lag_prio2tc[i][j]) {
                if (!is_printed) {
                    seq_printf(m, "%-6d   %-4d   %-2d\n",
                               i,
                               j,
                               priv->lag_prio2tc[i][j]);
                    is_printed = 1;
                } else {
                    seq_printf(m, "%-6s   %-4d   %-2d\n",
                               "",
                               j,
                               priv->lag_prio2tc[i][j]);
                }
            }
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __vtag_mode_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        lag_max = 0, lag_member_max = 0, phy_port_max = 0;
    int             i, j;
    u8              is_printed;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "vtag mode dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        seq_printf(m, "failed to get max number of PHY ports.\n");
        return 0;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        seq_printf(m, "failed to get max number of LAGs.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-7s   %-4s",
                                   "sysport", "vlan");

    for (i = 0; i < (phy_port_max + 1); i++) { /* system port */
        is_printed = 0;

        for (j = 0; j < SXD_MAX_VLAN_NUM; j++) { /* vlan */
            if (priv->port_vtag_mode[i][j]) {
                if (!is_printed) {
                    seq_printf(m, "0x%-5x   %-4d\n",
                               i,
                               j);
                    is_printed = 1;
                } else {
                    seq_printf(m, "%-7s   %-4d\n",
                               "",
                               j);
                }
            }
        }
    }

    sx_dbg_dump_print_empty_line(m);

    sx_dbg_dump_print_table_header(m, "%-6s   %-4s",
                                   "LAG ID", "vlan");

    for (i = 0; i < (lag_max + 1); i++) { /* LAG ID */
        is_printed = 0;

        for (j = 0; j < SXD_MAX_VLAN_NUM; j++) { /* vlan */
            if (priv->lag_vtag_mode[i][j]) {
                if (!is_printed) {
                    seq_printf(m, "%-6d   %-4d\n",
                               i,
                               j);
                    is_printed = 1;
                } else {
                    seq_printf(m, "%-6s   %-4d\n",
                               "",
                               j);
                }
            }
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __prio_tag_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        lag_max = 0, lag_member_max = 0, phy_port_max = 0;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "prio tag dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        seq_printf(m, "failed to get max number of PHY ports.\n");
        return 0;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        seq_printf(m, "failed to get max number of LAGs.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-7s",
                                   "sysport");

    for (i = 0; i < (phy_port_max + 1); i++) { /* system port */
        if (priv->port_prio_tagging_mode[i]) {
            seq_printf(m, "0x%-5x\n", i);
        }
    }

    sx_dbg_dump_print_empty_line(m);

    sx_dbg_dump_print_table_header(m, "%-6s",
                                   "LAG ID");

    for (i = 0; i < (lag_max + 1); i++) { /* LAG ID */
        if (priv->lag_prio_tagging_mode[i]) {
            seq_printf(m, "%-6d\n", i);
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __vid_to_ip_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "vid to ip dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    sx_dbg_dump_print_table_header(m, "%-4s   %-10s",
                                   "vlan", "ip");

    for (i = 0; i < (SXD_MAX_VLAN_NUM - 1); i++) { /* vlan */
        if (priv->icmp_vlan2ip_db[i]) {
            seq_printf(m, "%-4d   0x%08x\n",
                       i, priv->icmp_vlan2ip_db[i]);
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __vport_rif_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        lag_max = 0, lag_member_max = 0, phy_port_max = 0;
    int             i, j;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "vport rif dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        seq_printf(m, "failed to get max number of PHY ports.\n");
        return 0;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        seq_printf(m, "failed to get max number of LAGs.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-5s   %-4s   %-5s",
                                   "local", "vlan", "rif");

    for (i = 0; i < (phy_port_max + 1); i++) {
        for (j = 0; j < SXD_MAX_VLAN_NUM; j++) {
            if (priv->port_rp_rif_valid[i][j]) {
                seq_printf(m, "%-5d   %-4d   %-5u\n",
                           i, j, priv->port_rp_rif[i][j]);
            }
        }
    }

    sx_dbg_dump_print_empty_line(m);

    sx_dbg_dump_print_table_header(m, "%-6s   %-4s   %-5s",
                                   "LAG ID", "vlan", "rif");

    for (i = 0; i < lag_max; i++) {
        for (j = 0; j < SXD_MAX_VLAN_NUM; j++) {
            if (priv->lag_rp_rif_valid[i][j]) {
                seq_printf(m, "%-6d   %-4d   %-5u\n",
                           i, j, priv->lag_rp_rif[i][j]);
            }
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __vid_to_fid_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        phy_port_max = 0;
    int             i, j;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "vid to fid dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        seq_printf(m, "failed to get max number of PHY ports.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-5s   %-4s   %-5s",
                                   "local", "vlan", "fid");

    for (i = 0; i < phy_port_max; i++) {
        for (j = 0; j < SXD_MAX_VLAN_NUM; j++) {
            if (priv->port_vid_to_fid[i][j]) {
                seq_printf(m, "%-5d   %-4d    %-5u\n",
                           i, j, priv->port_vid_to_fid[i][j]);
            }
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

static int __lag_oper_state_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv;
    uint16_t        lag_max = 0, lag_member_max = 0;
    int             i;
    char            header[SX_DBG_DUMP_HEADER_MAX_LEN];
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "LAG oper state dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(m, header);

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        seq_printf(m, "failed to get max number of LAGs.\n");
        return 0;
    }

    sx_dbg_dump_print_table_header(m, "%-6s   %-10s",
                                   "LAG ID", "oper-state");

    for (i = 0; i < lag_max; i++) { /* lag id */
        if (priv->lag_oper_state[i]) {
            seq_printf(m, "%-6d   %-10s\n",
                       i, "up");
        } else {
            seq_printf(m, "%-6d   %-10s\n",
                       i, "down");
        }
    }

    sx_dbg_dump_print_empty_line(m);
    return 0;
}

int sx_dbg_db_init(struct sx_dev *dev)
{
    sx_dbg_dump_read_handler_register("fid_to_hwfid_dump", __fid_to_hwfid_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("rif_to_hwfid_dump", __rif_to_hwfid_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("rif_data_dump", __rif_data_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("sys_to_local_dump", __sys_to_local_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("local_to_sys_dump", __local_to_sys_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("lag_to_pvid_dump", __lag_to_pvid_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("lag_member_to_local_dump", __lag_member_to_local_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("local_to_module_dump", __local_to_module_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("router_port_dump", __router_port_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("local_to_swid_dump", __local_to_swid_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("truncate_size_dump", __truncate_size_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("prio_to_tc_dump", __prio_to_tc_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("vtag_mode_dump", __vtag_mode_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("prio_tag_dump", __prio_tag_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("vid_to_ip_dump", __vid_to_ip_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("vport_rif_dump", __vport_rif_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("vid_to_fid_dump", __vid_to_fid_dump, NULL, dev, NULL);
    sx_dbg_dump_read_handler_register("lag_oper_state_dump", __lag_oper_state_dump, NULL, dev, NULL);
    return 0;
}

void sx_dbg_db_deinit(struct sx_dev *dev)
{
    sx_dbg_dump_read_handler_unregister("fid_to_hwfid_dump", dev);
    sx_dbg_dump_read_handler_unregister("rif_to_hwfid_dump", dev);
    sx_dbg_dump_read_handler_unregister("rif_data_dump", dev);
    sx_dbg_dump_read_handler_unregister("sys_to_local_dump", dev);
    sx_dbg_dump_read_handler_unregister("local_to_sys_dump", dev);
    sx_dbg_dump_read_handler_unregister("lag_to_pvid_dump", dev);
    sx_dbg_dump_read_handler_unregister("lag_member_to_local_dump", dev);
    sx_dbg_dump_read_handler_unregister("local_to_module_dump", dev);
    sx_dbg_dump_read_handler_unregister("router_port_dump", dev);
    sx_dbg_dump_read_handler_unregister("local_to_swid_dump", dev);
    sx_dbg_dump_read_handler_unregister("truncate_size_dump", dev);
    sx_dbg_dump_read_handler_unregister("prio_to_tc_dump", dev);
    sx_dbg_dump_read_handler_unregister("vtag_mode_dump", dev);
    sx_dbg_dump_read_handler_unregister("prio_tag_dump", dev);
    sx_dbg_dump_read_handler_unregister("vid_to_ip_dump", dev);
    sx_dbg_dump_read_handler_unregister("vport_rif_dump", dev);
    sx_dbg_dump_read_handler_unregister("vid_to_fid_dump", dev);
    sx_dbg_dump_read_handler_unregister("lag_oper_state_dump", dev);
}
