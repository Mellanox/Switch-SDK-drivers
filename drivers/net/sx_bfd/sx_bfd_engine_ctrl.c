/*
 * Copyright (C) 2010-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#include <linux/types.h>
#include <linux/kernel.h>

#include "sx_bfd_engine_ctrl.h"
#include "sx_bfd_cdev.h"
#include <linux/sx_bfd/sx_bfd_ctrl_cmds.h>
#include "sx_bfd_tx_session.h"
#include "sx_bfd_rx_session.h"

static int sx_bfd_parse_cmd(char* data, int cmd)
{
    int err = -ENOTTY;

    switch (cmd) {
    case SX_BFD_CMD_START_TX_OFFLOAD:
        return sx_bfd_tx_sess_add(data, NULL);

    case SX_BFD_CMD_UPDATE_TX_OFFLOAD:
        return sx_bfd_tx_sess_update(data);

    case SX_BFD_CMD_STOP_TX_OFFLOAD:
        return sx_bfd_tx_sess_del(data, NULL);

    case SX_BFD_CMD_START_RX_OFFLOAD:
        return sx_bfd_rx_sess_add(data);

    case SX_BFD_CMD_UPDATE_RX_OFFLOAD:
        return sx_bfd_rx_sess_update(data);

    case SX_BFD_CMD_STOP_RX_OFFLOAD:
        return sx_bfd_rx_sess_del(data);

    case SX_BFD_CMD_GET_RX_STATS:
        return sx_bfd_get_rx_sess_stats(data, false);

    case SX_BFD_CMD_GET_TX_STATS:
        return sx_bfd_get_tx_sess_stats(data, false);

    case SX_BFD_CMD_GET_AND_CLEAR_RX_STATS:
        return sx_bfd_get_rx_sess_stats(data, true);

    case SX_BFD_CMD_GET_AND_CLEAR_TX_STATS:
        return sx_bfd_get_tx_sess_stats(data, true);

    default:
        pr_debug("Unsupported sx bfd command %d", cmd);
    }

    return err;
}

int sx_bfd_engine_ctrl_init(void)
{
    int err;

    err = sx_bfd_cdev_init(&sx_bfd_parse_cmd);
    if (err < 0) {
        printk(KERN_ERR "Kernel BFD chardevice failed to initialize.\n");
        goto bail;
    }

    err = sx_bfd_workqueue_init();
    if (err < 0) {
        printk(KERN_ERR "Kernel BFD workqueue initialization failed.\n");
        goto bail;
    }

    err = sx_bfd_rx_session_init();
    if (err < 0) {
        printk(KERN_ERR "Kernel BFD RX session initialization failed.\n");
        goto bail;
    }

    err = sx_bfd_tx_session_init();
    if (err < 0) {
        printk(KERN_ERR "Kernel BFD TX session initialization failed.\n");
        goto bail;
    }

bail:
    if (err) {
        sx_bfd_engine_ctrl_deinit();
    }
    return err;
}

void sx_bfd_engine_ctrl_deinit(void)
{
    sx_bfd_cdev_deinit();

    sx_bfd_rx_session_deinit();

    sx_bfd_tx_session_deinit();

    sx_bfd_workqueue_deinit();
}
