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

#ifndef __mtrack_h_
#define __mtrack_h_

#include "memtrack.h"

#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/io.h>           /* For ioremap_nocache, ioremap, iounmap */
#include <linux/random.h>
#include <linux/io-mapping.h>  /* For ioremap_nocache, ioremap, iounmap */
#include <linux/mm.h>           /* For all page handling */
#include <linux/workqueue.h>    /* For all work-queue handling */
#include <linux/scatterlist.h>  /* For using scatter lists */
#include <linux/skbuff.h>       /* For skbufs handling */
#include <asm/uaccess.h>    /* For copy from/to user */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
/* on ARM64 ioremap is a definition to call another function, so we need to wrap it before the undef */
static inline void *memtrack_ioremap(unsigned long phys_addr, unsigned long size)
{
    return ioremap(phys_addr, size);
}

#undef ioremap
#undef iounmap
#undef ioremap_nocache
#else /* LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0) */
#define memtrack_ioremap ioremap
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0) */

#define MEMTRACK_ERROR_INJECTION_MESSAGE(file, line, func)                    \
    ({                                                                        \
         printk(KERN_ERR "%s failure injected at %s:%d\n", func, file, line); \
         dump_stack();                                                        \
     })

#define kzalloc(size, flags)                                                                                           \
    ({                                                                                                                 \
         void *__memtrack_addr = NULL;                                                                                 \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kzalloc"); }                                        \
         else {                                                                                                        \
             __memtrack_addr = kzalloc(size, flags); }                                                                 \
         if (__memtrack_addr && !is_non_trackable_alloc_func(__func__)) {                                              \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            flags);                                                                                    \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })

#define kzalloc_node(size, flags, node)                                                                                \
    ({                                                                                                                 \
         void *__memtrack_addr = NULL;                                                                                 \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kzalloc_node"); }                                   \
         else {                                                                                                        \
             __memtrack_addr = kzalloc_node(size, flags, node); }                                                      \
         if (__memtrack_addr && (size) &&                                                                              \
             !is_non_trackable_alloc_func(__func__)) {                                                                 \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            flags);                                                                                    \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })

#define kcalloc(n, size, flags)                                                                                      \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kcalloc"); }                                      \
         else {                                                                                                      \
             __memtrack_addr = kcalloc(n, size, flags); }                                                            \
         if (__memtrack_addr && (size)) {                                                                            \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), (n) * (size), 0UL, 0, __FILE__, \
                            __LINE__, flags);                                                                        \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })


#ifdef ZERO_OR_NULL_PTR
#define kmalloc(sz, flgs)                                                                                            \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kmalloc"); }                                      \
         else {                                                                                                      \
             __memtrack_addr = kmalloc(sz, flgs); }                                                                  \
         if (!ZERO_OR_NULL_PTR(__memtrack_addr)) {                                                                   \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), sz, 0UL, 0, __FILE__, __LINE__, \
                            flgs);                                                                                   \
             if (memtrack_randomize_mem()) {                                                                         \
                 memset(__memtrack_addr, 0x5A, sz); }                                                                \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })
#else
#define kmalloc(sz, flgs)                                                                                            \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kmalloc"); }                                      \
         else {                                                                                                      \
             __memtrack_addr = kmalloc(sz, flgs); }                                                                  \
         if (__memtrack_addr) {                                                                                      \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), sz, 0UL, 0, __FILE__, __LINE__, \
                            flgs);                                                                                   \
             if (memtrack_randomize_mem()) {                                                                         \
                 memset(__memtrack_addr, 0x5A, sz); }                                                                \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })

#endif

#define kmalloc_node(sz, flgs, node)                                                                                 \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kmalloc_node"); }                                 \
         else {                                                                                                      \
             __memtrack_addr = kmalloc_node(sz, flgs, node); }                                                       \
         if (__memtrack_addr) {                                                                                      \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), sz, 0UL, 0, __FILE__, __LINE__, \
                            flgs);                                                                                   \
             if (memtrack_randomize_mem() && ((flgs) == GFP_KERNEL)) {                                               \
                 memset(__memtrack_addr, 0x5A, sz); }                                                                \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })

#ifdef ZERO_OR_NULL_PTR
#define kmemdup(src, sz, flgs)                                                                                       \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kmemdup"); }                                      \
         else {                                                                                                      \
             __memtrack_addr = kmemdup(src, sz, flgs); }                                                             \
         if (!ZERO_OR_NULL_PTR(__memtrack_addr)) {                                                                   \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), sz, 0UL, 0, __FILE__, __LINE__, \
                            flgs);                                                                                   \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })
#else
#define kmemdup(src, sz, flgs)                                                                                       \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kmemdup"); }                                      \
         else {                                                                                                      \
             __memtrack_addr = kmemdup(src, sz, flgs); }                                                             \
         if (__memtrack_addr) {                                                                                      \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), sz, 0UL, 0, __FILE__, __LINE__, \
                            flgs);                                                                                   \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })
#endif

#ifdef ZERO_OR_NULL_PTR
#define kstrdup(src, flgs)                                                                                           \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
         unsigned int sz;                                                                                            \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kstrdup"); }                                      \
         else {                                                                                                      \
             __memtrack_addr = kstrdup(src, flgs); }                                                                 \
         if (!ZERO_OR_NULL_PTR(__memtrack_addr)) {                                                                   \
             sz = strlen(src) + 1;                                                                                   \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), sz, 0UL, 0, __FILE__, __LINE__, \
                            flgs);                                                                                   \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })
#else
#define kstrdup(src, flgs)                                                                                           \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
         unsigned int sz;                                                                                            \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kstrdup"); }                                      \
         else {                                                                                                      \
             __memtrack_addr = kstrdup(src, flgs); }                                                                 \
         if (__memtrack_addr) {                                                                                      \
             sz = strlen(src) + 1;                                                                                   \
             memtrack_alloc(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), sz, 0UL, 0, __FILE__, __LINE__, \
                            flgs);                                                                                   \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })
#endif

#ifdef ZERO_OR_NULL_PTR
#define kfree(addr)                                                                                              \
    ({                                                                                                           \
         void *__memtrack_addr = (void*)addr;                                                                    \
                                                                                                                 \
         if (!ZERO_OR_NULL_PTR(__memtrack_addr) &&                                                               \
             !is_non_trackable_free_func(__func__)) {                                                            \
             memtrack_free(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                       \
         kfree(__memtrack_addr);                                                                                 \
     })
#else
#define kfree(addr)                                                                                              \
    ({                                                                                                           \
         void *__memtrack_addr = (void*)addr;                                                                    \
                                                                                                                 \
         if (__memtrack_addr && !is_non_trackable_free_func(__func__)) {                                         \
             memtrack_free(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                       \
         kfree(__memtrack_addr);                                                                                 \
     })
#endif

#ifdef CONFIG_COMPAT_RCU
#ifdef kfree_rcu
    #undef kfree_rcu
#endif

#ifdef ZERO_OR_NULL_PTR
#define kfree_rcu(addr, rcu_head)                                                                                \
    ({                                                                                                           \
         void *__memtrack_addr = (void*)addr;                                                                    \
                                                                                                                 \
         if (!ZERO_OR_NULL_PTR(__memtrack_addr) &&                                                               \
             !is_non_trackable_free_func(__func__)) {                                                            \
             memtrack_free(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                       \
         __kfree_rcu(&((addr)->rcu_head), offsetof(typeof(*(addr)), rcu_head));                                  \
     })
#else
#define kfree_rcu(addr, rcu_head)                                                                                \
    ({                                                                                                           \
         void *__memtrack_addr = (void*)addr;                                                                    \
                                                                                                                 \
         if (__memtrack_addr && !is_non_trackable_free_func(__func__)) {                                         \
             memtrack_free(MEMTRACK_KMALLOC, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                       \
         __kfree_rcu(&((addr)->rcu_head), offsetof(typeof(*(addr)), rcu_head));                                  \
     })
#endif
#endif /* CONFIG_COMPAT_RCU */

#define vmalloc(size)                                                                                                  \
    ({                                                                                                                 \
         void *__memtrack_addr = NULL;                                                                                 \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "vmalloc"); }                                        \
         else {                                                                                                        \
             __memtrack_addr = vmalloc(size); }                                                                        \
         if (__memtrack_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_VMALLOC, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                               \
             if (memtrack_randomize_mem()) {                                                                           \
                 memset(__memtrack_addr, 0x5A, size); }                                                                \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })

#ifndef vzalloc
#define vzalloc(size)                                                                                                  \
    ({                                                                                                                 \
         void *__memtrack_addr = NULL;                                                                                 \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "vzalloc"); }                                        \
         else {                                                                                                        \
             __memtrack_addr = vzalloc(size); }                                                                        \
         if (__memtrack_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_VMALLOC, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                               \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })
#endif

#ifndef vzalloc_node
#define vzalloc_node(size, node)                                                                                       \
    ({                                                                                                                 \
         void *__memtrack_addr = NULL;                                                                                 \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "vzalloc_node"); }                                   \
         else {                                                                                                        \
             __memtrack_addr = vzalloc_node(size, node); }                                                             \
         if (__memtrack_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_VMALLOC, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                               \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })
#endif

#define vmalloc_node(size, node)                                                                                       \
    ({                                                                                                                 \
         void *__memtrack_addr = NULL;                                                                                 \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "vmalloc_node"); }                                   \
         else {                                                                                                        \
             __memtrack_addr = vmalloc_node(size, node); }                                                             \
         if (__memtrack_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_VMALLOC, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                               \
             if (memtrack_randomize_mem()) {                                                                           \
                 memset(__memtrack_addr, 0x5A, size); }                                                                \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })

#define vfree(addr)                                                                                              \
    ({                                                                                                           \
         void *__memtrack_addr = (void*)addr;                                                                    \
         if (__memtrack_addr) {                                                                                  \
             memtrack_free(MEMTRACK_VMALLOC, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                       \
         vfree(__memtrack_addr);                                                                                 \
     })


#define kmem_cache_alloc(cache, flags)                                                                               \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kmem_cache_alloc"); }                             \
         else {                                                                                                      \
             __memtrack_addr = kmem_cache_alloc(cache, flags); }                                                     \
         if (__memtrack_addr) {                                                                                      \
             memtrack_alloc(MEMTRACK_KMEM_OBJ, 0UL, (unsigned long)(__memtrack_addr), 1, 0UL, 0, __FILE__, __LINE__, \
                            flags);                                                                                  \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })

#define kmem_cache_zalloc(cache, flags)                                                                              \
    ({                                                                                                               \
         void *__memtrack_addr = NULL;                                                                               \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "kmem_cache_zalloc"); }                            \
         else {                                                                                                      \
             __memtrack_addr = kmem_cache_zalloc(cache, flags); }                                                    \
         if (__memtrack_addr) {                                                                                      \
             memtrack_alloc(MEMTRACK_KMEM_OBJ, 0UL, (unsigned long)(__memtrack_addr), 1, 0UL, 0, __FILE__, __LINE__, \
                            flags);                                                                                  \
         }                                                                                                           \
         __memtrack_addr;                                                                                            \
     })

#define kmem_cache_free(cache, addr)                                                                              \
    ({                                                                                                            \
         void *__memtrack_addr = (void*)addr;                                                                     \
                                                                                                                  \
         if (__memtrack_addr) {                                                                                   \
             memtrack_free(MEMTRACK_KMEM_OBJ, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                        \
         kmem_cache_free(cache, __memtrack_addr);                                                                 \
     })


/* All IO-MAP handling */
#define ioremap(phys_addr, size)                                                                                       \
    ({                                                                                                                 \
         void __iomem *__memtrack_addr = NULL;                                                                         \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "ioremap"); }                                        \
         else {                                                                                                        \
             __memtrack_addr = memtrack_ioremap(phys_addr, size); }                                                    \
         if (__memtrack_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_IOREMAP, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                               \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })

#define io_mapping_create_wc(base, size)                                                                               \
    ({                                                                                                                 \
         void __iomem *__memtrack_addr = NULL;                                                                         \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "io_mapping_create_wc"); }                           \
         else {                                                                                                        \
             __memtrack_addr = io_mapping_create_wc(base, size); }                                                     \
         if (__memtrack_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_IOREMAP, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                               \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })

#define io_mapping_free(addr)                                                                                    \
    ({                                                                                                           \
         void *__memtrack_addr = (void*)addr;                                                                    \
                                                                                                                 \
         if (__memtrack_addr) {                                                                                  \
             memtrack_free(MEMTRACK_IOREMAP, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                       \
         io_mapping_free(__memtrack_addr);                                                                       \
     })

#define ioremap_nocache(phys_addr, size)                                                                               \
    ({                                                                                                                 \
         void __iomem *__memtrack_addr = NULL;                                                                         \
                                                                                                                       \
         if (memtrack_inject_error()) {                                                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "ioremap_nocache"); }                                \
         else {                                                                                                        \
             __memtrack_addr = ioremap_nocache(phys_addr, size); }                                                     \
         if (__memtrack_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_IOREMAP, 0UL, (unsigned long)(__memtrack_addr), size, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                               \
         }                                                                                                             \
         __memtrack_addr;                                                                                              \
     })

#define iounmap(addr)                                                                                            \
    ({                                                                                                           \
         void *__memtrack_addr = (void*)addr;                                                                    \
                                                                                                                 \
         if (__memtrack_addr) {                                                                                  \
             memtrack_free(MEMTRACK_IOREMAP, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                       \
         iounmap(__memtrack_addr);                                                                               \
     })


/* All Page handlers */
/* TODO: Catch netif_rx for page dereference */
#define alloc_pages_node(nid, gfp_mask, order)                                                                    \
    ({                                                                                                            \
         struct page *page_addr = NULL;                                                                           \
                                                                                                                  \
         if (memtrack_inject_error()) {                                                                           \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "alloc_pages_node"); }                          \
         else {                                                                                                   \
             page_addr = (struct page *)alloc_pages_node(nid, gfp_mask, order); }                                 \
         if (page_addr && !is_non_trackable_alloc_func(__func__)) {                                               \
             memtrack_alloc(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(page_addr), (unsigned long)(order), 0UL, 0, \
                            __FILE__, __LINE__, GFP_ATOMIC);                                                      \
         }                                                                                                        \
         page_addr;                                                                                               \
     })

#ifdef CONFIG_NUMA
#define alloc_pages(gfp_mask, order)                                                                              \
    ({                                                                                                            \
         struct page *page_addr = NULL;                                                                           \
                                                                                                                  \
         if (memtrack_inject_error()) {                                                                           \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "alloc_pages"); }                               \
         else {                                                                                                   \
             page_addr = (struct page *)alloc_pages(gfp_mask, order); }                                           \
         if (page_addr && !is_non_trackable_alloc_func(__func__)) {                                               \
             memtrack_alloc(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(page_addr), (unsigned long)(order), 0UL, 0, \
                            __FILE__, __LINE__, GFP_ATOMIC);                                                      \
         }                                                                                                        \
         page_addr;                                                                                               \
     })
#else
#ifdef alloc_pages
    #undef alloc_pages
#endif
#define alloc_pages(gfp_mask, order)                                                   \
    ({                                                                                 \
         struct page *page_addr;                                                       \
                                                                                       \
         page_addr = (struct page *)alloc_pages_node(numa_node_id(), gfp_mask, order); \
         page_addr;                                                                    \
     })
#endif

#define __get_free_pages(gfp_mask, order)                                                                         \
    ({                                                                                                            \
         struct page *page_addr = NULL;                                                                           \
                                                                                                                  \
         if (memtrack_inject_error()) {                                                                           \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "__get_free_pages"); }                          \
         else {                                                                                                   \
             page_addr = (struct page *)__get_free_pages(gfp_mask, order); }                                      \
         if (page_addr && !is_non_trackable_alloc_func(__func__)) {                                               \
             memtrack_alloc(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(page_addr), (unsigned long)(order), 0UL, 0, \
                            __FILE__, __LINE__, GFP_ATOMIC);                                                      \
         }                                                                                                        \
         page_addr;                                                                                               \
     })

#define get_zeroed_page(gfp_mask)                                                                                \
    ({                                                                                                           \
         struct page *page_addr = NULL;                                                                          \
                                                                                                                 \
         if (memtrack_inject_error()) {                                                                          \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "get_zeroed_page"); }                          \
         else {                                                                                                  \
             page_addr = (struct page *)get_zeroed_page(gfp_mask); }                                             \
         if (page_addr && !is_non_trackable_alloc_func(__func__)) {                                              \
             memtrack_alloc(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(page_addr), 0, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                         \
         }                                                                                                       \
         (unsigned long)page_addr;                                                                               \
     })

#define __free_pages(addr, order)                                                                                       \
    ({                                                                                                                  \
         void *__memtrack_addr = (void*)addr;                                                                           \
                                                                                                                        \
         if (__memtrack_addr && !is_non_trackable_alloc_func(__func__)) {                                               \
             if (!memtrack_check_size(MEMTRACK_PAGE_ALLOC, (unsigned long)(__memtrack_addr), (unsigned long)(order),    \
                                      __FILE__, __LINE__)) {                                                            \
                 memtrack_free(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
             }                                                                                                          \
         }                                                                                                              \
         __free_pages(addr, order);                                                                                     \
     })


#define free_pages(addr, order)                                                                                         \
    ({                                                                                                                  \
         void *__memtrack_addr = (void*)addr;                                                                           \
                                                                                                                        \
         if (__memtrack_addr && !is_non_trackable_alloc_func(__func__)) {                                               \
             if (!memtrack_check_size(MEMTRACK_PAGE_ALLOC, (unsigned long)(__memtrack_addr), (unsigned long)(order),    \
                                      __FILE__, __LINE__)) {                                                            \
                 memtrack_free(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
             }                                                                                                          \
         }                                                                                                              \
         free_pages(addr, order);                                                                                       \
     })


#define get_page(addr)                                                                                                 \
    ({                                                                                                                 \
         void *__memtrack_addr = (void*)addr;                                                                          \
                                                                                                                       \
         if (__memtrack_addr && !is_non_trackable_alloc_func(__func__)) {                                              \
             if (memtrack_is_new_addr(MEMTRACK_PAGE_ALLOC, (unsigned long)(__memtrack_addr), 0, __FILE__, __LINE__)) { \
                 memtrack_alloc(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(__memtrack_addr), 0, 0UL, 0, __FILE__,       \
                                __LINE__, GFP_ATOMIC);                                                                 \
             }                                                                                                         \
         }                                                                                                             \
         get_page(addr);                                                                                               \
     })

#define get_user_pages_fast(start, nr_pages, write, pages)                                                           \
    ({                                                                                                               \
         int __memtrack_rc = -1;                                                                                     \
                                                                                                                     \
         if (memtrack_inject_error()) {                                                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "get_user_pages_fast"); }                          \
         else {                                                                                                      \
             __memtrack_rc = get_user_pages_fast(start, nr_pages, write, pages); }                                   \
         if (__memtrack_rc > 0 && !is_non_trackable_alloc_func(__func__)) {                                          \
             int __memtrack_i;                                                                                       \
                                                                                                                     \
             for (__memtrack_i = 0; __memtrack_i < __memtrack_rc; __memtrack_i++) {                                  \
                 memtrack_alloc(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(pages[__memtrack_i]), 0, 0UL, 0, __FILE__, \
                                __LINE__, GFP_ATOMIC); }                                                             \
         }                                                                                                           \
         __memtrack_rc;                                                                                              \
     })

#define put_page(addr)                                                                                                  \
    ({                                                                                                                  \
         void *__memtrack_addr = (void*)addr;                                                                           \
                                                                                                                        \
         if (__memtrack_addr && !is_non_trackable_alloc_func(__func__)) {                                               \
             /* Check whether this is not part of umem put page & not */                                                \
             /* a new addr and the ref-count is 1 then we'll free this addr */                                          \
             /* Don't change the order these conditions */                                                              \
             if (!is_umem_put_page(__func__) &&                                                                         \
                 !memtrack_is_new_addr(MEMTRACK_PAGE_ALLOC, (unsigned long)(__memtrack_addr), 1, __FILE__, __LINE__) && \
                 (memtrack_get_page_ref_count((unsigned long)(__memtrack_addr)) == 1)) {                                \
                 memtrack_free(MEMTRACK_PAGE_ALLOC, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
             }                                                                                                          \
         }                                                                                                              \
         put_page(addr);                                                                                                \
     })


/* Work-Queue handlers */
#ifdef create_workqueue
    #undef create_workqueue
#endif
#ifdef create_rt_workqueue
    #undef create_rt_workqueue
#endif
#ifdef create_freezeable_workqueue
    #undef create_freezeable_workqueue
#endif
#ifdef create_singlethread_workqueue
    #undef create_singlethread_workqueue
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 10, 0)) && !defined(CONFIG_SX_RHEL_8_6) && !defined(CONFIG_SX_CENTOS_8_4)
#ifdef alloc_workqueue
    #undef alloc_workqueue
#endif /* alloc_workqueue */

#ifdef CONFIG_LOCKDEP
#define alloc_workqueue(name, flags, max_active)                                                               \
    ({                                                                                                         \
         static struct lock_class_key __key;                                                                   \
         const char *__lock_name;                                                                              \
         struct workqueue_struct *wq_addr = NULL;                                                              \
                                                                                                               \
         if (__builtin_constant_p(name)) {                                                                     \
             __lock_name = (name); }                                                                           \
         else {                                                                                                \
             __lock_name = #name; }                                                                            \
                                                                                                               \
         if (memtrack_inject_error()) {                                                                        \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "alloc_workqueue"); }                        \
         else {                                                                                                \
             wq_addr = __alloc_workqueue_key((name), (flags), (max_active),                                    \
                                             &__key, __lock_name); }                                           \
         if (wq_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_WORK_QUEUE, 0UL, (unsigned long)(wq_addr), 0, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                       \
         }                                                                                                     \
         wq_addr;                                                                                              \
     })
#else /* CONFIG_LOCKDEP */
#define alloc_workqueue(name, flags, max_active)                                                               \
    ({                                                                                                         \
         struct workqueue_struct *wq_addr = NULL;                                                              \
                                                                                                               \
         if (memtrack_inject_error()) {                                                                        \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "alloc_workqueue"); }                        \
         else {                                                                                                \
             wq_addr = __alloc_workqueue_key((name), (flags), (max_active), NULL, NULL); }                     \
         if (wq_addr) {                                                                                        \
             memtrack_alloc(MEMTRACK_WORK_QUEUE, 0UL, (unsigned long)(wq_addr), 0, 0UL, 0, __FILE__, __LINE__, \
                            GFP_ATOMIC);                                                                       \
         }                                                                                                     \
         wq_addr;                                                                                              \
     })
#endif /* CONFIG_LOCKDEP */
#else /* >= kernel 5.10.0 */
static inline struct workqueue_struct *alloc_workqueue_wrapper(const char *file,
                                                               int line,
                                                               const char *fmt,
                                                               unsigned int flags,
                                                               int max_active,
                                                               ...)
{
    struct workqueue_struct *wq_addr = NULL;
    va_list args;

    va_start(args, max_active);

    if (memtrack_inject_error()) {
        MEMTRACK_ERROR_INJECTION_MESSAGE(file, line, "alloc_workqueue");
    }
    else {
        wq_addr = alloc_workqueue(fmt, flags, max_active, args);

        if (wq_addr) {
            memtrack_alloc(MEMTRACK_WORK_QUEUE, 0UL, (unsigned long)(wq_addr), 0, 0UL, 0, file, line, GFP_ATOMIC);
        }
    }

    va_end(args);
    return wq_addr;
}

#define alloc_workqueue(fmt, flags, max_active, args ...) alloc_workqueue_wrapper(__FILE__, __LINE__, (fmt), (flags), (max_active), ## args)
#endif /* < kernel 5.10.0 */

#define WQ_RESCUER WQ_MEM_RECLAIM /* internal: workqueue has rescuer */

#define create_workqueue(name) \
    alloc_workqueue((name), WQ_RESCUER, 1);

#define create_freezeable_workqueue(name) \
    alloc_workqueue((name), WQ_FREEZEABLE | WQ_UNBOUND | WQ_RESCUER, 1);

#define create_singlethread_workqueue(name) \
    alloc_workqueue((name), WQ_UNBOUND | WQ_RESCUER, 1);

#define destroy_workqueue(wq_addr)                                                                                  \
    ({                                                                                                              \
         void *__memtrack_addr = (void*)wq_addr;                                                                    \
                                                                                                                    \
         if (__memtrack_addr) {                                                                                     \
             memtrack_free(MEMTRACK_WORK_QUEUE, 0UL, (unsigned long)(__memtrack_addr), 0UL, 0, __FILE__, __LINE__); \
         }                                                                                                          \
         destroy_workqueue(wq_addr);                                                                                \
     })

/* ONLY error injection to functions that we don't monitor */
#define alloc_skb(size, prio)                                                     \
    ({                                                                            \
         struct sk_buff *__memtrack_skb = NULL;                                   \
                                                                                  \
         if (memtrack_inject_error()) {                                           \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "alloc_skb"); } \
         else {                                                                   \
             __memtrack_skb = alloc_skb(size, prio); }                            \
         __memtrack_skb;                                                          \
     })

#define dev_alloc_skb(size)                                                           \
    ({                                                                                \
         struct sk_buff *__memtrack_skb = NULL;                                       \
                                                                                      \
         if (memtrack_inject_error()) {                                               \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "dev_alloc_skb"); } \
         else {                                                                       \
             __memtrack_skb = dev_alloc_skb(size); }                                  \
         __memtrack_skb;                                                              \
     })

#define alloc_skb_fclone(size, prio)                                                     \
    ({                                                                                   \
         struct sk_buff *__memtrack_skb = NULL;                                          \
                                                                                         \
         if (memtrack_inject_error()) {                                                  \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "alloc_skb_fclone"); } \
         else {                                                                          \
             __memtrack_skb = alloc_skb_fclone(size, prio); }                            \
         __memtrack_skb;                                                                 \
     })

#define copy_from_user(to, from, n)                                                    \
    ({                                                                                 \
         int ret = n;                                                                  \
                                                                                       \
         if (memtrack_inject_error()) {                                                \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "copy_from_user"); } \
         else {                                                                        \
             ret = copy_from_user(to, from, n); }                                      \
         ret;                                                                          \
     })

#define copy_to_user(to, from, n)                                                    \
    ({                                                                               \
         int ret = n;                                                                \
                                                                                     \
         if (memtrack_inject_error()) {                                              \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "copy_to_user"); } \
         else {                                                                      \
             ret = copy_to_user(to, from, n); }                                      \
         ret;                                                                        \
     })

#define sysfs_create_file(kobj, attr)                                                     \
    ({                                                                                    \
         int ret = -ENOSYS;                                                               \
                                                                                          \
         if (memtrack_inject_error()) {                                                   \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "sysfs_create_file"); } \
         else {                                                                           \
             ret = sysfs_create_file(kobj, attr); }                                       \
         ret;                                                                             \
     })

#define sysfs_create_link(kobj, target, name)                                             \
    ({                                                                                    \
         int ret = -ENOSYS;                                                               \
                                                                                          \
         if (memtrack_inject_error()) {                                                   \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "sysfs_create_link"); } \
         else {                                                                           \
             ret = sysfs_create_link(kobj, target, name); }                               \
         ret;                                                                             \
     })

#define sysfs_create_group(kobj, grp)                                                      \
    ({                                                                                     \
         int ret = -ENOSYS;                                                                \
                                                                                           \
         if (memtrack_inject_error()) {                                                    \
             MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "sysfs_create_group"); } \
         else {                                                                            \
             ret = sysfs_create_group(kobj, grp); }                                        \
         ret;                                                                              \
     })

#define sysfs_create_bin_file(kobj, attr)                                                           \
        ({                                                                                          \
             int ret = -ENOSYS;                                                                     \
                                                                                                    \
             if (memtrack_inject_error()) {                                                         \
                 MEMTRACK_ERROR_INJECTION_MESSAGE(__FILE__, __LINE__, "sysfs_create_bin_file"); }   \
             else {                                                                                 \
                 ret = sysfs_create_bin_file(kobj, attr); }                                         \
             ret;                                                                                   \
         })

#endif /* __mtrack_h_ */
