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

#ifndef __SX_MAP_H__
#define __SX_MAP_H__

#include <linux/types.h>
#include <linux/rbtree.h>

typedef int (*sx_core_map_compare_cb_t)(const void *key1, const void *key2);

struct sx_core_map {
    rwlock_t                 lock;
    struct rb_root           map;
    sx_core_map_compare_cb_t compare_cb;
    size_t                   key_size;
    uint8_t                  use_lock;
};
struct sx_core_map_info {
    struct rb_node rb_node;
    void          *key;
};

/* returns 0 to continue traversing, otherwise traversing is stopped */
typedef int (*sx_core_map_traverse_cb_t)(const void *key, struct sx_core_map_info *info, void *context);

int sx_core_map_init(struct sx_core_map      *map,
                     sx_core_map_compare_cb_t compare_cb,
                     size_t                   key_size,
                     uint8_t                  use_lock);

int sx_core_map_insert(struct sx_core_map *map, const void *key, struct sx_core_map_info *info, gfp_t flags);
int sx_core_map_remove(struct sx_core_map *map, const void *key, struct sx_core_map_info **info);
int sx_core_map_lookup(struct sx_core_map *map, const void *key, struct sx_core_map_info **info);
int sx_core_map_traverse(struct sx_core_map *map, sx_core_map_traverse_cb_t traverse_cb, void *context);

#endif /* __SX_MAP_H__ */
