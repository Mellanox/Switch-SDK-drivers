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
