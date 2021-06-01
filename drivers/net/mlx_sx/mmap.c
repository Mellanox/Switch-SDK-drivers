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

#include <linux/hashtable.h>
#include <linux/seq_file.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/sched.h>
#include "sx.h"

#define HASH_SIZE_IN_BITS (6) /* 64 buckets */

static DEFINE_HASHTABLE(__mmap_entries, HASH_SIZE_IN_BITS);
static DEFINE_MUTEX(__mmap_entries_lock);

struct sx_mmap_metadata {
    pid_t             pid;      /* the PID of the mmap() caller */
    void             *realdata; /* the real allocation for mmap() */
    void             *data;     /* the page-aligned pointer within the real allocation */
    unsigned long     user_ptr; /* user-space pointer of mmap() */
    unsigned long     size;     /* size of allocation */
    uint32_t          refcnt;   /* reference count for the mmap() allocation */
    struct hlist_node h_entry;
};
static void __sx_vm_open(struct vm_area_struct *vma)
{
    struct sx_mmap_metadata *metadata = (struct sx_mmap_metadata*)vma->vm_private_data;

    metadata->refcnt++;
}

static void __sx_vm_close(struct vm_area_struct *vma)
{
    struct sx_mmap_metadata *metadata = (struct sx_mmap_metadata*)vma->vm_private_data;

    if (--metadata->refcnt == 0) {
        mutex_lock(&__mmap_entries_lock);
        hash_del(&metadata->h_entry);
        mutex_unlock(&__mmap_entries_lock);

        kfree(metadata->realdata);
        kfree(metadata);
    }
}

const struct vm_operations_struct __sx_vm_ops = {
    .open = __sx_vm_open,
    .close = __sx_vm_close
};

int sx_core_mmap(struct file *filp, struct vm_area_struct *vma)
{
    unsigned long            pfn, size;
    struct sx_mmap_metadata *metadata = NULL;
    void                    *alloc = NULL;
    int                      ret = 0;

    if (!PAGE_ALIGNED(vma->vm_start) || !PAGE_ALIGNED(vma->vm_end)) {
        printk(KERN_ERR "mapped area is not aligned with PAGE_SIZE\n");
        ret = -EINVAL;
        goto out;
    }

    size = vma->vm_end - vma->vm_start; /* size is multiple of PAGE_SIZE */
    if (size == 0) {
        printk(KERN_ERR "size of mapped area is 0\n");
        ret = -EINVAL;
        goto out;
    }

    metadata = kzalloc(sizeof(*metadata), GFP_KERNEL);
    if (!metadata) {
        ret = -ENOMEM;
        goto out;
    }

    /* on debug-kernel, the allocation that is mapped to userspace MUST be aligned to PAGE_SIZE.
     * thus, we're allocating enough space that we can return a page-aligned pointer */
    metadata->realdata = kmalloc(size + PAGE_SIZE, GFP_KERNEL);
    if (!metadata->realdata) {
        ret = -ENOMEM;
        goto out;
    }

    /* if allocation succeeded, get the page-aligned pointer within the allocated area */
    alloc = (void*)PAGE_ALIGN((unsigned long)metadata->realdata);

    pfn = virt_to_phys(alloc) >> PAGE_SHIFT;
    ret = remap_pfn_range(vma,
                          vma->vm_start,
                          pfn,
                          size,
                          vma->vm_page_prot);
    if (ret) {
        goto out;
    }

    metadata->pid = current->pid;
    metadata->refcnt = 1;
    metadata->data = alloc;
    metadata->user_ptr = vma->vm_start;
    metadata->size = size;

    mutex_lock(&__mmap_entries_lock);
    hash_add(__mmap_entries, &metadata->h_entry, metadata->user_ptr);
    mutex_unlock(&__mmap_entries_lock);

    vma->vm_ops = &__sx_vm_ops;
    vma->vm_private_data = metadata;

out:
    if (ret) {
        if (metadata) {
            if (metadata->realdata) {
                kfree(metadata->realdata);
            }

            kfree(metadata);
        }
    }

    return ret;
}


void* sx_mmap_user_to_kernel(pid_t pid, unsigned long user_ptr)
{
    struct sx_mmap_metadata *iter;
    void                    *ptr = NULL;

    mutex_lock(&__mmap_entries_lock);

    hash_for_each_possible(__mmap_entries, iter, h_entry, user_ptr) {
        if ((iter->pid == pid) && (iter->user_ptr == user_ptr)) {
            ptr = iter->data;
            break;
        }
    }

    mutex_unlock(&__mmap_entries_lock);
    return ptr;
}


int sx_mmap_dump(struct seq_file *m, void *v)
{
    struct sx_mmap_metadata *iter;
    int                      bucket;

    seq_printf(m, "----------------------------------------------------------------------\n");
    seq_printf(m, "%-8s   %-18s   %-8s   %-6s\n",
               "owner", "allocation", "size", "refcnt");
    seq_printf(m, "----------------------------------------------------------------------\n");

    mutex_lock(&__mmap_entries_lock);

    hash_for_each(__mmap_entries, bucket, iter, h_entry) {
        seq_printf(m, "%-8u   0x%-16p   %-8lu   %-6u\n",
                   iter->pid,
                   iter->data,
                   iter->size,
                   iter->refcnt);
    }

    mutex_unlock(&__mmap_entries_lock);
    return 0;
}
