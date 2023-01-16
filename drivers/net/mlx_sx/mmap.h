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

#ifndef __SX_CORE_MMAP_H__
#define __SX_CORE_MMAP_H__

struct file;
struct vm_area_struct;
struct seq_file;

int sx_core_mmap(struct file *filp, struct vm_area_struct *vma);
void* sx_mmap_user_to_kernel(pid_t pid, unsigned long user_ptr);
int sx_mmap_dump(struct seq_file *m, void *v, void *context);

#endif /* __SX_CORE_MMAP_H__ */
