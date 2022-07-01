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

#ifndef SX_ICM_H
#define SX_ICM_H

#include <linux/list.h>
#include <linux/pci.h>
#include <linux/mutex.h>

#define SX_ICM_CHUNK_LEN                                  \
    ((256 - sizeof(struct list_head) - 2 * sizeof(int)) / \
     (sizeof(struct scatterlist)))

enum {
    SX_ICM_PAGE_SHIFT = 12,
    SX_ICM_PAGE_SIZE  = 1 << SX_ICM_PAGE_SHIFT,
    SX_ICM_TYPE_SHIFT = 8
};

struct sx_icm_chunk {
    struct list_head   list;
    int                npages;
    int                nsg;
    struct scatterlist mem[SX_ICM_CHUNK_LEN];
};
struct sx_icm {
    struct list_head chunk_list;
    int              refcount;
};
struct sx_icm_iter {
    struct sx_icm       *icm;
    struct sx_icm_chunk *chunk;
    int                  page_idx;
};
struct sx_dev;
struct sx_icm * sx_alloc_icm(struct sx_dev *dev, int npages,
                             gfp_t gfp_mask, int coherent);
void sx_free_icm(struct sx_dev *dev, struct sx_icm *icm, int coherent);

static inline void sx_icm_first(struct sx_icm *icm, struct sx_icm_iter *iter)
{
    iter->icm = icm;
    iter->chunk = list_empty(&icm->chunk_list) ?
                  NULL : list_entry(icm->chunk_list.next,
                                    struct sx_icm_chunk, list);
    iter->page_idx = 0;
}

static inline int sx_icm_last(struct sx_icm_iter *iter)
{
    return !iter->chunk;
}

static inline void sx_icm_next(struct sx_icm_iter *iter)
{
    if (++iter->page_idx >= iter->chunk->nsg) {
        if (iter->chunk->list.next == &iter->icm->chunk_list) {
            iter->chunk = NULL;
            return;
        }

        iter->chunk = list_entry(iter->chunk->list.next,
                                 struct sx_icm_chunk, list);
        iter->page_idx = 0;
    }
}

static inline dma_addr_t sx_icm_addr(struct sx_icm_iter *iter)
{
    return sg_dma_address(&iter->chunk->mem[iter->page_idx]);
}

static inline unsigned long sx_icm_size(struct sx_icm_iter *iter)
{
    return sg_dma_len(&iter->chunk->mem[iter->page_idx]);
}

#endif /* SX_ICM_H */
