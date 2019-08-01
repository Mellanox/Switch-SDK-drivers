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

#ifndef SKB_HOOK_H
#define SKB_HOOK_H

struct sk_buff;
struct sx_dev;

typedef void (*sx_skb_hook_cb_t)(struct sx_dev *sx_dev, struct sk_buff *skb, void *user_context);

void sx_core_skb_hook_init(void);

int sx_core_skb_hook_rx_register(sx_skb_hook_cb_t hook_cb, void *user_context);
int sx_core_skb_hook_rx_unregister(sx_skb_hook_cb_t hook_cb);
void sx_core_skb_hook_rx_call(struct sx_dev *sx_dev, struct sk_buff *skb);

int sx_core_skb_hook_tx_register(sx_skb_hook_cb_t hook_cb, void *user_context);
int sx_core_skb_hook_tx_unregister(sx_skb_hook_cb_t hook_cb);
void sx_core_skb_hook_tx_call(struct sx_dev *sx_dev, struct sk_buff *skb);

#endif /* SKB_HOOK_H */
