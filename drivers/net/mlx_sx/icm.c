/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#include <linux/init.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/mlx_sx/cmd.h>
#include "sx.h"
#include "icm.h"
#include "fw.h"

static void sx_free_icm_pages(struct sx_dev *dev, struct sx_icm_chunk *chunk)
{
    int i;

    if (chunk->nsg > 0) {
        dma_unmap_sg(&dev->pdev->dev, chunk->mem, chunk->npages,
                     DMA_BIDIRECTIONAL);
    }

    for (i = 0; i < chunk->npages; ++i) {
        __free_pages(sg_page(&chunk->mem[i]),
                     get_order(chunk->mem[i].length));
    }
}

static void sx_free_icm_coherent(struct sx_dev *dev, struct sx_icm_chunk *chunk)
{
    int i;

    for (i = 0; i < chunk->npages; ++i) {
        dma_free_coherent(&dev->pdev->dev, chunk->mem[i].length,
                          lowmem_page_address(sg_page(&chunk->mem[i])),
                          sg_dma_address(&chunk->mem[i]));
    }
}

void sx_free_icm(struct sx_dev *dev, struct sx_icm *icm, int coherent)
{
    struct sx_icm_chunk *chunk, *tmp;

    if (!icm) {
        return;
    }

    list_for_each_entry_safe(chunk, tmp, &icm->chunk_list, list) {
        if (coherent) {
            sx_free_icm_coherent(dev, chunk);
        } else {
            sx_free_icm_pages(dev, chunk);
        }

        kfree(chunk);
    }

    kfree(icm);
}

static int sx_alloc_icm_pages(struct scatterlist *mem, int order, gfp_t gfp_mask)
{
    struct page *page;

    page = alloc_pages(gfp_mask, order);
    if (!page) {
        return -ENOMEM;
    }

    sg_set_page(mem, page, PAGE_SIZE << order, 0);
    return 0;
}

static int sx_alloc_icm_coherent(struct device *dev, struct scatterlist *mem, int order, gfp_t gfp_mask)
{
    void *buf = dma_alloc_coherent(dev, PAGE_SIZE << order,
                                   &sg_dma_address(mem), gfp_mask);

    if (!buf) {
        return -ENOMEM;
    }

    sg_set_buf(mem, buf, PAGE_SIZE << order);
    BUG_ON(mem->offset);
    sg_dma_len(mem) = PAGE_SIZE << order;
    return 0;
}

struct sx_icm * sx_alloc_icm(struct sx_dev *dev, int npages, gfp_t gfp_mask, int coherent)
{
    struct sx_icm       *icm;
    struct sx_icm_chunk *chunk = NULL;
    int                  cur_order;
    int                  ret;

    /* We use sg_set_buf for coherent allocations, which assumes low memory */
    BUG_ON(coherent && (gfp_mask & __GFP_HIGHMEM));

    icm = kmalloc(sizeof *icm, gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
    if (!icm) {
        return NULL;
    }

    icm->refcount = 0;
    INIT_LIST_HEAD(&icm->chunk_list);

    cur_order = get_order(SX_ICM_ALLOC_SIZE);
    dma_set_max_seg_size(&dev->pdev->dev, PAGE_SIZE << cur_order);

    while (npages > 0) {
        if (!chunk) {
            chunk = kmalloc(sizeof *chunk,
                            gfp_mask &
                            ~(__GFP_HIGHMEM | __GFP_NOWARN));
            if (!chunk) {
                goto fail;
            }

            sg_init_table(chunk->mem, SX_ICM_CHUNK_LEN);
            chunk->npages = 0;
            chunk->nsg = 0;
            list_add_tail(&chunk->list, &icm->chunk_list);
        }

        /* coverity[negative_shift] */
        while (1 << cur_order > npages) {
            --cur_order;
        }

        if (coherent) {
            ret = sx_alloc_icm_coherent(&dev->pdev->dev,
                                        &chunk->mem[chunk->npages],
                                        cur_order, gfp_mask);
        } else {
            ret = sx_alloc_icm_pages(&chunk->mem[chunk->npages],
                                     cur_order, gfp_mask);
        }

        if (!ret) {
            ++chunk->npages;

            if (coherent) {
                ++chunk->nsg;
            } else if (chunk->npages == SX_ICM_CHUNK_LEN) {
                chunk->nsg = dma_map_sg(&dev->pdev->dev, chunk->mem,
                                        chunk->npages,
                                        DMA_BIDIRECTIONAL);

                if (chunk->nsg <= 0) {
                    goto fail;
                }

                chunk = NULL;
            }

            npages -= 1 << cur_order;
        } else {
            --cur_order;
            if (cur_order < 0) {
                goto fail;
            }
        }
    }

    if (!coherent && chunk) {
        chunk->nsg = dma_map_sg(&dev->pdev->dev, chunk->mem,
                                chunk->npages,
                                DMA_BIDIRECTIONAL);

        if (chunk->nsg <= 0) {
            goto fail;
        }
    }

    return icm;

fail:
    sx_free_icm(dev, icm, coherent);
    return NULL;
}
