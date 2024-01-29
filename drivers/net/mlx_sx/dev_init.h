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

#ifndef __SX_DEV_INIT_H__
#define __SX_DEV_INIT_H__

#include <linux/types.h>

struct sx_dev;
struct sx_priv;
struct pci_restart_saved_params;

int sx_dev_init_core_pci(bool do_reset, u32 *total_probes, u32 *successful_probes);
void sx_dev_deinit_core_pci(u32 *total_removes);
int sx_dev_init_oob_pci(void);
void sx_dev_deinit_oob_pci(void);
int sx_restart_one_pci(struct sx_dev *dev);
int sx_core_init_one(struct sx_priv **sx_priv, struct pci_restart_saved_params *saved_params);
void sx_core_remove_one(struct sx_priv *priv, bool keep_listeners);
int sx_core_create_fake_device(struct sx_priv **priv_pp);
int sx_core_dev_init_switchx_cb(struct sx_dev *dev, enum sxd_chip_types chip_type, bool force);

#endif /* __SX_DEV_INIT_H__ */
