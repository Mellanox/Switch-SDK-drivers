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

#ifndef __SX_BFD_WORKQUEUE_H
#define __SX_BFD_WORKQUEUE_H

typedef struct sx_bfd_delayed_work sx_bfd_delayed_work_t;
typedef void (*handler_func)(uint32_t data);

int sx_bfd_create_delayed_work(sx_bfd_delayed_work_t ** dwork, handler_func func, uint32_t data);

void sx_bfd_destroy_delayed_work(sx_bfd_delayed_work_t * dwork);
void sx_bfd_destroy_delayed_work_sync(sx_bfd_delayed_work_t * dwork);

void sx_bfd_delayed_work_dispatch(sx_bfd_delayed_work_t * dwork, unsigned long delay);
void sx_bfd_delayed_work_cancel(sx_bfd_delayed_work_t * dwork);

int sx_bfd_workqueue_init(void);

void sx_bfd_workqueue_deinit(void);


#endif /* __sx_bfd_WORKQUEUE_H */
