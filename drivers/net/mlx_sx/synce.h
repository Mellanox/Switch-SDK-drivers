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

#ifndef SX_CORE_SYNCE_H
#define SX_CORE_SYNCE_H

#include <linux/seq_file.h>

int sx_core_synce_init(void);
void sx_core_synce_deinit(void);
int sx_core_synce_init_spectrum(void);
void sx_core_synce_deinit_spectrum(void);
int sx_core_synce_dump(struct seq_file *m, void *v, void *context);


#endif /* SX_CORE_SYNCE_H */
