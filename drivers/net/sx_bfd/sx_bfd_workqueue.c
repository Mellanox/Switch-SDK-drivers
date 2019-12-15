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

#include <linux/slab.h>
#include <linux/workqueue.h>

#include "sx_bfd_workqueue.h"

static struct workqueue_struct * workqueue = NULL;
static bool                      g_initialized = false;
struct sx_bfd_delayed_work {
    struct delayed_work work;
    handler_func        func;
    uint32_t            data;
};
static void handler(struct work_struct * work)
{
    /*
     *  <work> is actually of type <struct delayed_work> and it is the <work> field of <struct sx_bfd_delayed_work>.
     *  So we need to retrieve the parent struct of <work> and we will get <struct sx_bfd_delayed_work>.
     */
    struct sx_bfd_delayed_work * sx_bfd_work = container_of((struct delayed_work*)work,
                                                            struct sx_bfd_delayed_work,
                                                            work);

    /* printk(KERN_ERR "sx_bfd_work %p.\n", sx_bfd_work); */
    /* printk(KERN_ERR "sx_bfd_work->data %d.\n", sx_bfd_work->data); */


    /* Call function with data as argument */
    sx_bfd_work->func(sx_bfd_work->data);
}

int sx_bfd_create_delayed_work(sx_bfd_delayed_work_t ** dwork, handler_func func, uint32_t data)
{
    int                          err = 0;
    struct sx_bfd_delayed_work * t_dwork = NULL;

    t_dwork = (struct sx_bfd_delayed_work*)kmalloc(sizeof(struct sx_bfd_delayed_work), GFP_KERNEL);
    if (t_dwork == NULL) {
        printk(KERN_ERR "Memory allocation for delayed work failed.\n");
        err = -ENOMEM;
        goto bail;
    }

    INIT_DELAYED_WORK(&t_dwork->work, handler);
    t_dwork->func = func;
    t_dwork->data = data;

    *dwork = t_dwork;
    t_dwork = NULL;

bail:
    if (t_dwork) {
        kfree(t_dwork);
    }
    return err;
}

void sx_bfd_destroy_delayed_work(sx_bfd_delayed_work_t * dwork)
{
    if (delayed_work_pending(&dwork->work)) {
        cancel_delayed_work(&dwork->work);
    }
    kfree(dwork);
}

void sx_bfd_destroy_delayed_work_sync(sx_bfd_delayed_work_t * dwork)
{
    if (delayed_work_pending(&dwork->work)) {
        cancel_delayed_work_sync(&dwork->work);
    }
    kfree(dwork);
}
void sx_bfd_delayed_work_dispatch(sx_bfd_delayed_work_t * dwork, unsigned long delay)
{
    queue_delayed_work(workqueue, &dwork->work, delay);
}

void sx_bfd_delayed_work_cancel(sx_bfd_delayed_work_t * dwork)
{
    cancel_delayed_work(&dwork->work);
}


int sx_bfd_workqueue_init(void)
{
    int err = 0;

    if (!g_initialized) {
        workqueue = create_singlethread_workqueue("sx_bfd_workqueue");
        if (workqueue == NULL) {
            printk(KERN_ERR "Kernel BFD work queue initialization failed.\n");
            err = -EIO;
            goto bail;
        }

        g_initialized = true;
    }

bail:
    return err;
}

void sx_bfd_workqueue_deinit(void)
{
    if (g_initialized) {
        flush_workqueue(workqueue);
        destroy_workqueue(workqueue);
        g_initialized = false;
    }
}
