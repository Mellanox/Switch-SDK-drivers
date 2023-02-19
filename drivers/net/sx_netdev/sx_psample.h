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

#ifndef SX_PSAMPLE_H
#define SX_PSAMPLE_H

#if IS_ENABLED(CONFIG_PSAMPLE)

void sx_psample_set_synd(struct sx_dev       *dev,
                         u16                  synd,
                         enum sx_dev_event    event,
                         union sx_event_data *event_data);
void sx_psample_set_port_sample_ret(u16 local_port,
                                    u32 rate);
void sx_psample_init(void);
void sx_psample_cleanup(void);

#if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0))
int sx_psample_setup_tc(struct net_device *dev, enum tc_setup_type type, void *type_data);
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

#else /* IS_ENABLED(CONFIG_PSAMPLE) */

void sx_psample_set_synd(struct sx_dev *dev, u16 synd, enum sx_dev_event event, union sx_event_data *event_data)
{
}

void sx_psample_set_port_sample_ret(u16 local_port, u32 rate)
{
}

void sx_psample_init(void)
{
}

void sx_psample_cleanup(void)
{
}

#if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0))
int sx_psample_setup_tc(struct net_device *dev, enum tc_setup_type type, void *type_data)
{
    return 0;
}
#endif /* defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

#endif /* IS_ENABLED(CONFIG_PSAMPLE) */

#endif /* SX_PSAMPLE_H */
