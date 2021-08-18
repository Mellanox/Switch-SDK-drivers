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
        printk(KERN_DEBUG "Unsupported sx bfd command");
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
        printk(KERN_ERR "Kernel BFD DB initialization failed.\n");
        goto bail;
    }

    err = sx_bfd_tx_session_init();
    if (err < 0) {
        printk(KERN_ERR "Kernel BFD DB initialization failed.\n");
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
