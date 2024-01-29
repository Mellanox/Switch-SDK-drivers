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
