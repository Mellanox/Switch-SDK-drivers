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

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/rwlock_types.h>
#include <linux/rwlock.h>
#include "map.h"

#define R_LOCK(map)                                              \
    do { if ((map)->use_lock) { read_lock_bh(&(map)->lock);    } \
    } while (0)
#define R_UNLOCK(map)                                            \
    do { if ((map)->use_lock) { read_unlock_bh(&(map)->lock);  } \
    } while (0)
#define W_LOCK(map)                                              \
    do { if ((map)->use_lock) { write_lock_bh(&(map)->lock);   } \
    } while (0)
#define W_UNLOCK(map)                                            \
    do { if ((map)->use_lock) { write_unlock_bh(&(map)->lock); } \
    } while (0)


int sx_core_map_init(struct sx_core_map *map, sx_core_map_compare_cb_t compare_cb, size_t key_size, uint8_t use_lock)
{
    if (!map || !compare_cb || (key_size == 0)) {
        return -EINVAL;
    }

    map->map = RB_ROOT;
    map->compare_cb = compare_cb;
    map->key_size = key_size;
    map->use_lock = use_lock;

    if (map->use_lock) {
        rwlock_init(&map->lock);
    }

    return 0;
}


int sx_core_map_insert(struct sx_core_map *map, const void *key, struct sx_core_map_info *info, gfp_t flags)
{
    struct rb_node               **new_node, *parent = NULL;
    const struct sx_core_map_info *curr;
    int                            cmp, ret = 0;

    if (!map || !key || !info) {
        return -EINVAL;
    }

    info->key = kmalloc(map->key_size, flags);
    if (!info->key) {
        printk(KERN_ERR "failed to allocate map key\n");
        return -ENOMEM;
    }

    memcpy(info->key, key, map->key_size);

    W_LOCK(map);

    new_node = &map->map.rb_node;

    while (*new_node) {
        curr = container_of((*new_node), struct sx_core_map_info, rb_node);
        cmp = map->compare_cb(key, curr->key);

        if (cmp == 0) {
            printk(KERN_ERR "key already exists:\n");
            print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1, key, map->key_size, 0);

            kfree(info->key);
            ret = -EEXIST;
            goto out;
        }

        parent = *new_node;
        if (cmp < 0) {
            new_node = &(*new_node)->rb_left;
        } else {
            new_node = &(*new_node)->rb_right;
        }
    }

    rb_link_node(&info->rb_node, parent, new_node);
    rb_insert_color(&info->rb_node, &map->map);

out:
    W_UNLOCK(map);
    return ret;
}


/* should be called under lock (if case map is using lock) */
struct sx_core_map_info * __sx_core_map_lookup(struct sx_core_map *map, const void *key)
{
    struct sx_core_map_info *info;
    struct rb_node          *node;
    int                      cmp;

    node = map->map.rb_node;

    while (node) {
        info = container_of(node, struct sx_core_map_info, rb_node);
        cmp = map->compare_cb(key, info->key);

        if (cmp == 0) {
            return info;
        }

        if (cmp < 0) {
            node = node->rb_left;
        } else {
            node = node->rb_right;
        }
    }

    return NULL;
}


int sx_core_map_remove(struct sx_core_map *map, const void *key, struct sx_core_map_info **info)
{
    struct sx_core_map_info *_info;
    int                      ret = 0;

    if (!map || !key) {
        return -EINVAL;
    }

    W_LOCK(map);

    _info = __sx_core_map_lookup(map, key);
    if (info) {
        *info = _info;
    }

    if (!_info) {
        ret = -ENOENT;
        goto out;
    }

    rb_erase(&_info->rb_node, &map->map);
    kfree((_info)->key);

out:
    W_UNLOCK(map);
    return ret;
}


int sx_core_map_lookup(struct sx_core_map *map, const void *key, struct sx_core_map_info **info)
{
    struct sx_core_map_info *_info;

    if (!map || !key) {
        return -EINVAL;
    }

    R_LOCK(map);

    _info = __sx_core_map_lookup(map, key);
    if (info) {
        *info = _info;
    }

    R_UNLOCK(map);

    return (_info != NULL) ? 0 : -ENOENT;
}


int sx_core_map_traverse(struct sx_core_map *map, sx_core_map_traverse_cb_t traverse_cb, void *context)
{
    struct rb_node          *node;
    struct sx_core_map_info *info;
    int                      ret = 0;

    if (!map || !traverse_cb) {
        return -EINVAL;
    }

    R_LOCK(map);

    for (node = rb_first(&map->map); node; node = rb_next(node)) {
        info = container_of(node, struct sx_core_map_info, rb_node);
        if (traverse_cb(info->key, info, context) != 0) {
            ret = 1; /* iteration stopped */
            break;
        }
    }

    R_UNLOCK(map);
    return ret;
}
