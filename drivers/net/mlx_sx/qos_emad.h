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

#ifndef __SX_QOS_EMAD_H_
#define __SX_QOS_EMAD_H_

#include <linux/seq_file.h>

/************************************************
 *  Local Defines
 ***********************************************/

/************************************************
 *  Local Macros
 ***********************************************/

/************************************************
 *  Local Type definitions
 ***********************************************/

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 *  Macros
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Function declarations
 ***********************************************/

int sx_qos_emad_init(void);
void sx_qos_emad_deinit(void);
int sx_qos_emad_dump(struct seq_file *m, void *v, void *context);
int sx_qos_emad_counter_clear(int argc, const char *argv[], void *context);

#endif /*__SX_QOS_EMAD_H_ */
