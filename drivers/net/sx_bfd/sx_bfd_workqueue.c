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

#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/mlx_sx/device.h>

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

bail:
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
        workqueue = sx_health_check_create_monitored_workqueue("sx_bfd_workqueue");
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
        sx_health_check_destroy_monitored_workqueue(workqueue);
        g_initialized = false;
    }
}
