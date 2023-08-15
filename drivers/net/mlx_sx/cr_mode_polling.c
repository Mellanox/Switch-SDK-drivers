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
#include <linux/kthread.h>
#include <linux/spinlock.h>
#include <linux/bitops.h>
#include <linux/delay.h>

#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>

#include "sx.h"
#include "cq.h"

static int cr_rx_dump;
module_param_named(cr_rx_dump, cr_rx_dump, int, 0644);
MODULE_PARM_DESC(cr_rx_dump, "en/dis dump of RX packets in CR mode");

static int cr_tx_dump;
module_param_named(cr_tx_dump, cr_tx_dump, int, 0644);
MODULE_PARM_DESC(cr_tx_dump, "en/dis dump of TX packets in CR mode");

static int cr_polling_active = 1;
module_param_named(cr_polling_active, cr_polling_active, int, 0644);
MODULE_PARM_DESC(cr_polling_active, "enable/disable CR-mode polling");

struct cr_tx_entry {
    struct list_head tx_list;
    struct sx_dev   *dev;
    struct sk_buff  *skb;
    struct isx_meta  meta;
};

static int __generate_pude(struct sx_dev *dev, u8 swid, u16 local_port, u8 admin_state, u8 oper_state)
{
    u8 pude_buff[] = {
        /* Ethernet Header */
        0x01, 0x02, 0xc9, 0x00, /* offset [0x00] */
        0x00, 0x01, 0xb8, 0x59, /* offset [0x04] */
        0x9f, 0xa7, 0x5c, 0x00, /* offset [0x08] */
        0x89, 0x32, 0x00, 0x00, /* offset [0x0c] */

        /* Operation TLV */
        0x08, 0x04, 0x00, 0x00, /* offset [0x10] */
        0x50, 0x09, 0x05, 0x01, /* offset [0x14] */
        0x00, 0x00, 0x00, 0x00, /* offset [0x18] */
        0x00, 0x00, 0x00, 0x00, /* offset [0x1c] */

        /* Register TLV (header) */
        0x18, 0x04, 0x00, 0x00, /* offset [0x20] */

        /* Register TLV (PUDE register layout) */
        0x00, 0x00, 0x00, 0x00, /* offset [0x24] */
        0x00, 0x00, 0x00, 0x00, /* offset [0x28] */
        0x00, 0x00, 0x00, 0x00, /* offset [0x2c] */

        /* End TLV */
        0x00, 0x01, 0x00, 0x00  /* offset [0x30] */
    };

    pude_buff[0x24] = swid; /* swid */
    pude_buff[0x25] = local_port & 0xff; /* local port LSB */
    pude_buff[0x26] = (((local_port >> 8) & 0x3) << 4) | /* local port MSB */
                      (admin_state & 0xf); /* admin state */
    pude_buff[0x27] = oper_state & 0xf;

    return send_trap(pude_buff, sizeof(pude_buff), SXD_TRAP_ID_PUDE, 0, dev->device_id, 0, GFP_KERNEL);
}

static bool __cr_check_for_rx_packet(struct sx_dev *dev, struct ku_access_mopr_reg *mopr_reg_data)
{
    int err = 0;

    mopr_reg_data->mopr_reg.op = 0;
    mopr_reg_data->mopr_reg.packet = NULL;
    err = sx_ACCESS_REG_MOPR(dev, mopr_reg_data);
    if (err) {
        printk(KERN_ERR "CR check for RX packet: failed to access MOPR (err=%d)\n", err);
        return false;
    }

    return (mopr_reg_data->mopr_reg.packet_length > 0);
}

static int __cr_receive_packet(struct sx_dev *dev, struct ku_access_mopr_reg *mopr_reg_data)
{
    union sx_cqe           cqe = {
        .v2 = NULL
    };
    struct sk_buff        *skb;
    struct sx_rx_timestamp rx_ts;
    int                    err = 0;

    skb = alloc_skb(2 * 1024, GFP_KERNEL);
    if (!skb) {
        printk(KERN_ERR "CR receive packet: No memory to allocate buffer\n");
        return -ENOMEM;
    }

    mopr_reg_data->mopr_reg.op = 1;
    mopr_reg_data->mopr_reg.packet = skb->data;
    err = sx_ACCESS_REG_MOPR(dev, mopr_reg_data);
    if (err) {
        printk(KERN_ERR "CR receive packet: failed to access MOPR (err=%d)\n", err);
        goto out_free_skb;
    }

    if (mopr_reg_data->mopr_reg.packet_length == 0) {
        goto out_free_skb;
    }

    SX_RX_TIMESTAMP_INIT(&rx_ts, 0, 0, SXD_TS_TYPE_NONE);
    cqe.v2 = (struct sx_cqe_v2*)mopr_reg_data->mopr_reg.cqe_v2;
    skb_put(skb, mopr_reg_data->mopr_reg.packet_length);

    if (cr_rx_dump) {
        printk(KERN_NOTICE "CR RX buffer (len=%d)\n", skb->len);
        print_hex_dump(KERN_NOTICE, "", DUMP_PREFIX_OFFSET, 16, 1, mopr_reg_data->mopr_reg.cqe_v2, 32, 0);
        print_hex_dump(KERN_NOTICE, "", DUMP_PREFIX_OFFSET, 16, 1, skb->data, skb->len, 0);
    }

    err = rx_skb(dev, skb, &cqe, &rx_ts, 0, NULL, dev->device_id);
    if (err) {
        printk(KERN_ERR "CR receive packet: failed to handle incoming packet (err=%d)\n", err);
        goto out_free_skb;
    }

    return 0;

out_free_skb:
    consume_skb(skb);
    return err;
}

static void __cr_send_packet(struct sx_dev *dev)
{
    struct sx_priv               *priv = sx_priv(dev);
    struct ku_access_mopir_v2_reg mopir_v2_reg_data;
    struct cr_tx_entry           *entry;

    spin_lock_bh(&priv->cr_mode.tx_queue_lock);
    entry = list_first_entry_or_null(&priv->cr_mode.tx_queue, struct cr_tx_entry, tx_list);
    if (entry) {
        list_del(&entry->tx_list);
    }
    spin_unlock_bh(&priv->cr_mode.tx_queue_lock);

    if (!entry) {
        return;
    }

    memset(&mopir_v2_reg_data, 0, sizeof(mopir_v2_reg_data));
    mopir_v2_reg_data.dev_id = entry->dev->device_id;
    sx_cmd_set_op_tlv(&mopir_v2_reg_data.op_tlv, MOPIR_V2_REG_ID, EMAD_METHOD_WRITE);
    mopir_v2_reg_data.mopir_v2_reg.dst_port = entry->meta.system_port_mid;
    mopir_v2_reg_data.mopir_v2_reg.is_control = (entry->meta.system_port_mid != 0);
    mopir_v2_reg_data.mopir_v2_reg.packet_length = entry->skb->len;
    mopir_v2_reg_data.mopir_v2_reg.packet = entry->skb->data;

    if (cr_tx_dump) {
        printk(KERN_NOTICE "CR TX buffer (dst_port=%u, len=%d)\n", entry->meta.system_port_mid, entry->skb->len);
        print_hex_dump(KERN_NOTICE, "", DUMP_PREFIX_OFFSET, 16, 1, entry->skb->data, entry->skb->len, 0);
    }

    sx_ACCESS_REG_MOPIR_V2(dev, &mopir_v2_reg_data);

    consume_skb(entry->skb);
    kfree(entry);
}

static int __cr_polling_thread(void *arg)
{
    struct sx_dev  *dev = (struct sx_dev*)arg;
    struct sx_priv *priv = sx_priv(dev);

    DECLARE_BITMAP(port_states, MAX_PHYPORT_NUM + 1);
    struct ku_access_paos_reg paos_reg_data;
    struct ku_access_mopr_reg mopr_reg_data;
    int                       cmd_path = 0;
    u16                       local_port;
    u16                       num_of_ports_up = 0;
    u8                        swid;
    int                       err;

    printk(KERN_INFO "CR polling thread started\n");

    bitmap_zero(port_states, MAX_PHYPORT_NUM + 1);

    memset(&paos_reg_data, 0, sizeof(paos_reg_data));
    paos_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&paos_reg_data.op_tlv, MLXSW_PAOS_ID, EMAD_METHOD_QUERY);

    memset(&mopr_reg_data, 0, sizeof(mopr_reg_data));
    mopr_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mopr_reg_data.op_tlv, MOPR_REG_ID, EMAD_METHOD_QUERY);

    while (!kthread_should_stop()) {
        msleep(1);

        cmd_path = sx_dpt_get_cmd_path(dev->device_id);
        if (!cr_polling_active || (cmd_path == DPT_PATH_INVALID)) {
            continue;
        }

        /* poll for link state changes and incoming packets */
        for (local_port = 1; local_port < MAX_PHYPORT_NUM + 1; local_port++) {
            spin_lock_bh(&priv->db_lock);
            swid = priv->local_to_swid_db[local_port];
            spin_unlock_bh(&priv->db_lock);

            if (swid == 255) { /* invalid swid, port is not mapped to any swid */
                continue;
            }

            memset(&paos_reg_data.paos_reg, 0, sizeof(paos_reg_data.paos_reg));
            SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(paos_reg_data.paos_reg.local_port,
                                                paos_reg_data.paos_reg.lp_msb,
                                                local_port);

            err = sx_ACCESS_REG_PAOS(dev, &paos_reg_data);
            if (err) {
                printk(KERN_ERR "Failed to poll local port %u state (err=%d)\n", local_port, err);
                continue;
            }

            /* Check if port was down and now it is up */
            if (!test_bit(local_port, port_states) && (paos_reg_data.paos_reg.oper_status == 1)) {
                printk(KERN_NOTICE "Local port %u is up\n", local_port);
                __generate_pude(dev,
                                swid,
                                local_port,
                                paos_reg_data.paos_reg.admin_status,
                                paos_reg_data.paos_reg.oper_status);
                set_bit(local_port, port_states);
                num_of_ports_up++;
            }
            /* Check if port was up and now it is down */
            else if (test_bit(local_port, port_states) && (paos_reg_data.paos_reg.oper_status & 0x6)) {
                printk(KERN_NOTICE "Local port %u is down\n", local_port);
                __generate_pude(dev,
                                swid,
                                local_port,
                                paos_reg_data.paos_reg.admin_status,
                                paos_reg_data.paos_reg.oper_status);
                clear_bit(local_port, port_states);
                num_of_ports_up--;
            }
        }

        if (num_of_ports_up > 0) {
            /* poll for TX packets */
            __cr_send_packet(dev);

            /* poll for RX packets */
            memset(&mopr_reg_data.mopr_reg, 0, sizeof(mopr_reg_data.mopr_reg));
            if (__cr_check_for_rx_packet(dev, &mopr_reg_data)) {
                __cr_receive_packet(dev, &mopr_reg_data);
            }
        }
    }

    return 0;
}

int sx_cr_polling_thread_init(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;

    priv->cr_mode.polling_thread = kthread_run(__cr_polling_thread, dev, "cr_polling_thread");
    if (IS_ERR(priv->cr_mode.polling_thread)) {
        err = PTR_ERR(priv->cr_mode.polling_thread);
        printk(KERN_ERR "Failed to start CR polling thread (err=%d)\n", err);
        priv->cr_mode.polling_thread = NULL;
        goto out;
    }

out:
    return err;
}

void sx_cr_polling_thread_deinit(struct sx_dev *dev)
{
    struct sx_priv     *priv = sx_priv(dev);
    struct cr_tx_entry *entry;

    if (priv->cr_mode.polling_thread) {
        kthread_stop(priv->cr_mode.polling_thread);
    }

    spin_lock_bh(&priv->cr_mode.tx_queue_lock);
    while (!list_empty(&priv->cr_mode.tx_queue)) {
        entry = list_first_entry(&priv->cr_mode.tx_queue, struct cr_tx_entry, tx_list);
        list_del(&entry->tx_list);
        consume_skb(entry->skb);
        kfree(entry);
    }
    spin_unlock_bh(&priv->cr_mode.tx_queue_lock);
}

int sx_cr_send_packet(struct sx_dev *dev, struct sk_buff *skb, struct isx_meta *meta)
{
    struct cr_tx_entry *tx_entry;
    struct sx_priv     *priv = sx_priv(dev);

    tx_entry = kmalloc(sizeof(struct cr_tx_entry), GFP_ATOMIC);
    if (!tx_entry) {
        return -ENOMEM;
    }

    INIT_LIST_HEAD(&tx_entry->tx_list);
    tx_entry->dev = dev;
    tx_entry->skb = skb;
    memcpy(&tx_entry->meta, meta, sizeof(tx_entry->meta));

    spin_lock_bh(&priv->cr_mode.tx_queue_lock);
    list_add_tail(&tx_entry->tx_list, &priv->cr_mode.tx_queue);
    spin_unlock_bh(&priv->cr_mode.tx_queue_lock);

    return 0;
}
