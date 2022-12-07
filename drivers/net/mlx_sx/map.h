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

#ifndef __SX_MAP_H__
#define __SX_MAP_H__

#include <linux/types.h>
#include <linux/rbtree.h>

typedef int (*sx_core_map_compare_cb_t)(const void *key1, const void *key2);

struct sx_core_map {
    struct rb_root           map;
    sx_core_map_compare_cb_t compare_cb;
    size_t                   key_size;
};
struct sx_core_map_info {
    struct rb_node rb_node;
    void          *key;
};

/* returns 0 to continue traversing, otherwise traversing is stopped */
typedef int (*sx_core_map_traverse_cb_t)(const void *key, struct sx_core_map_info *info, void *context);

int sx_core_map_init(struct sx_core_map      *map,
                     sx_core_map_compare_cb_t compare_cb,
                     size_t                   key_size);

int sx_core_map_is_empty(struct sx_core_map* map, bool *is_empty);
int sx_core_map_get_first(struct sx_core_map *map, struct sx_core_map_info **info);
int sx_core_map_get_next(struct sx_core_map *map, struct sx_core_map_info *curr, struct sx_core_map_info **info);
int sx_core_map_insert(struct sx_core_map *map, const void *key, struct sx_core_map_info *info, gfp_t flags);
int sx_core_map_remove(struct sx_core_map *map, const void *key, struct sx_core_map_info **info);
int sx_core_map_remove_all(struct sx_core_map *map, sx_core_map_traverse_cb_t destructor_cb, void *context);
int sx_core_map_lookup(struct sx_core_map *map, const void *key, struct sx_core_map_info **info);
int sx_core_map_traverse(struct sx_core_map *map, sx_core_map_traverse_cb_t traverse_cb, void *context);

#endif /* __SX_MAP_H__ */
