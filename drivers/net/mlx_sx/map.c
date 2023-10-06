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

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/mlx_sx/map.h>

int sx_core_map_init(struct sx_core_map *map, sx_core_map_compare_cb_t compare_cb, size_t key_size)
{
    if (!map || !compare_cb || (key_size == 0)) {
        return -EINVAL;
    }

    map->map = RB_ROOT;
    map->compare_cb = compare_cb;
    map->key_size = key_size;

    return 0;
}

EXPORT_SYMBOL(sx_core_map_init); /*to be access to other drivers e.g SPICE */

int sx_core_map_is_empty(struct sx_core_map* map, bool *is_empty)
{
    if (!map || !is_empty) {
        return -EINVAL;
    }

    *is_empty = (rb_first(&map->map) == NULL);
    return 0;
}

EXPORT_SYMBOL(sx_core_map_is_empty); /*to be access to other drivers e.g SPICE */

int sx_core_map_get_first(struct sx_core_map *map, struct sx_core_map_info **info)
{
    struct rb_node *node;

    if (!map || !info) {
        return -EINVAL;
    }

    node = rb_first(&map->map);
    if (!node) {
        return -ENOENT;
    }

    *info = container_of(node, struct sx_core_map_info, rb_node);
    return 0;
}

EXPORT_SYMBOL(sx_core_map_get_first); /*to be access to other drivers e.g SPICE */

int sx_core_map_get_next(struct sx_core_map *map, struct sx_core_map_info *curr, struct sx_core_map_info **info)
{
    struct rb_node *node;

    if (!map || !curr || !info) {
        return -EINVAL;
    }

    node = rb_next(&curr->rb_node);
    if (!node) {
        return -ENOENT;
    }

    *info = container_of(node, struct sx_core_map_info, rb_node);
    return 0;
}

EXPORT_SYMBOL(sx_core_map_get_next); /*to be access to other drivers e.g SPICE */

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
    return ret;
}

EXPORT_SYMBOL(sx_core_map_insert); /*to be access to other drivers e.g SPICE */

static struct sx_core_map_info * __sx_core_map_lookup(struct sx_core_map *map, const void *key)
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
    return ret;
}

EXPORT_SYMBOL(sx_core_map_remove); /*to be access to other drivers e.g SPICE */

int sx_core_map_remove_all(struct sx_core_map *map, sx_core_map_traverse_cb_t destructor_cb, void *context)
{
    struct rb_node          *node;
    struct sx_core_map_info *info;
    void                    *key;

    if (!map) {
        return -EINVAL;
    }

    while ((node = rb_first(&map->map)) != NULL) {
        info = container_of(node, struct sx_core_map_info, rb_node);

        /* keep info->key because 'info' is about to be deallocated */
        key = info->key;

        rb_erase(&info->rb_node, &map->map);
        if (destructor_cb) {
            /* the following line may deallocate 'info', so we must not use 'info' after that. */
            destructor_cb(key, info, context);
        }

        /* it is OK to use key as it is an internal allocation done by the map API itself and not by the user */
        kfree(key);
    }

    return 0;
}

EXPORT_SYMBOL(sx_core_map_remove_all); /*to be access to other drivers e.g SPICE */

int sx_core_map_lookup(struct sx_core_map *map, const void *key, struct sx_core_map_info **info)
{
    struct sx_core_map_info *_info;

    if (!map || !key) {
        return -EINVAL;
    }

    _info = __sx_core_map_lookup(map, key);
    if (info) {
        *info = _info;
    }

    return (_info != NULL) ? 0 : -ENOENT;
}

EXPORT_SYMBOL(sx_core_map_lookup); /*to be access to other drivers e.g SPICE */

int sx_core_map_traverse(struct sx_core_map *map, sx_core_map_traverse_cb_t traverse_cb, void *context)
{
    struct rb_node          *node;
    struct sx_core_map_info *info;
    int                      ret = 0;

    if (!map || !traverse_cb) {
        return -EINVAL;
    }

    for (node = rb_first(&map->map); node; node = rb_next(node)) {
        info = container_of(node, struct sx_core_map_info, rb_node);
        if (traverse_cb(info->key, info, context) != 0) {
            ret = 1; /* iteration stopped */
            break;
        }
    }

    return ret;
}

EXPORT_SYMBOL(sx_core_map_traverse); /*to be access to other drivers e.g SPICE */
