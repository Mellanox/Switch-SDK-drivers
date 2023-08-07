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

#ifndef _MLXSW_ITEM_H
#define _MLXSW_ITEM_H

#include <linux/types.h>
#include <linux/string.h>
#include <linux/bitops.h>
#include <linux/module.h>

/*
 * Create a contiguous bitmask starting at bit position @l and ending at
 * position @h. For example
 * GEN_MASK_ULL(39, 21) gives us the 64bit vector 0x000000ffffe00000.
 */
#define GEN_MASK(h, l) \
    (((~0UL) - (1UL << (l)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

#define GEN_MASK_ULL(h, l) \
    (((~0ULL) - (1ULL << (l)) + 1) & (~0ULL >> (BITS_PER_LONG_LONG - 1 - (h))))

struct mlxsw_item {
    unsigned short offset;                /* bytes in container */
    unsigned short step;                  /* step in bytes for indexed items */
    unsigned short in_step_offset;        /* offset within one step */
    unsigned short double_step;           /* step in bytes for indexed items that are member of indexed items */
    unsigned short double_in_step_offset; /* offset within one step */
    unsigned char  shift;                 /* shift in bits */
    unsigned char  element_size;          /* size of element in bit array */
    union {
        unsigned char  bits;
        unsigned short bytes;
    } size;
    const char *name;
};

/* returns 0 for big endian, 1 for little endian. */
static inline unsigned int __little_endian_order(void)
{
    volatile u32 i = 0xff;
    return (*((u8*)(&i))) == 0xff;
}

static inline unsigned int __mlxsw_item_offset(const struct mlxsw_item *item, unsigned short outer_index,
                                               unsigned short index, size_t typesize)
{
    BUG_ON(index && !item->step);
    if ((item->offset % typesize != 0) ||
        (item->step % typesize != 0) ||
        (item->in_step_offset % typesize != 0)) {
        pr_err("mlxsw: item bug (name=%s,offset=%x,step=%x,in_step_offset=%x,typesize=%zx)\n",
               item->name, item->offset, item->step,
               item->in_step_offset, typesize);
        BUG();
    }

    return ((item->offset + (unsigned int)item->step * index + item->in_step_offset + (unsigned int)item->double_step * outer_index + item->double_in_step_offset) / typesize);
}

static inline unsigned int __mlxsw_item_offset_no_checks(const struct mlxsw_item *item, unsigned short outer_index,
                                                         unsigned short index, size_t typesize)
{
    BUG_ON(index && !item->step);

    return ((item->offset + (unsigned int)item->step * index + item->in_step_offset + (unsigned int)item->double_step * outer_index + item->double_in_step_offset) / typesize);
}

static inline u8 __mlxsw_item_get8(const char *buf, const struct mlxsw_item *item,
                                   unsigned short outer_index, unsigned short index)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u8));
    u8 *b = (u8 *)buf;
    u8  tmp;

    tmp = b[offset];
    tmp >>= item->shift;
    tmp &= GEN_MASK(item->size.bits - 1, 0);
    return tmp;
}

static inline void __mlxsw_item_set8(char *buf, const struct mlxsw_item *item,
                                     unsigned short outer_index, unsigned short index, u8 val)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u8));
    u8 *b = (u8 *)buf;
    u8  mask = GEN_MASK(item->size.bits - 1, 0) << item->shift;
    u8  tmp;

    val <<= item->shift;
    val &= mask;
    tmp = b[offset];
    tmp &= ~mask;
    tmp |= val;
    b[offset] = tmp;
}

static inline u16 __mlxsw_item_get16(const char *buf, const struct mlxsw_item *item,
                                     unsigned short outer_index, unsigned short index)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u16));
    __be16 *b = (__be16 *)buf;
    u16     tmp;

    tmp = be16_to_cpu(b[offset]);
    tmp >>= item->shift;
    tmp &= GEN_MASK(item->size.bits - 1, 0);
    return tmp;
}

static inline void __mlxsw_item_set16(char *buf, const struct mlxsw_item *item,
                                      unsigned short outer_index, unsigned short index, u16 val)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u16));
    __be16 *b = (__be16 *)buf;
    u16     mask = GEN_MASK(item->size.bits - 1, 0) << item->shift;
    u16     tmp;

    val <<= item->shift;
    val &= mask;
    tmp = be16_to_cpu(b[offset]);
    tmp &= ~mask;
    tmp |= val;
    b[offset] = cpu_to_be16(tmp);
}

static inline u32 __mlxsw_item_get32(const char *buf, const struct mlxsw_item *item,
                                     unsigned short outer_index, unsigned short index)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u32));
    __be32 *b = (__be32 *)buf;
    u32     tmp;

    tmp = be32_to_cpu(b[offset]);
    tmp >>= item->shift;
    tmp &= GEN_MASK(item->size.bits - 1, 0);
    return tmp;
}

static inline void __mlxsw_item_set32(char *buf, const struct mlxsw_item *item,
                                      unsigned short outer_index, unsigned short index, u32 val)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u32));
    __be32 *b = (__be32 *)buf;
    u32     mask = GEN_MASK(item->size.bits - 1, 0) << item->shift;
    u32     tmp;

    val <<= item->shift;
    val &= mask;
    tmp = be32_to_cpu(b[offset]);
    tmp &= ~mask;
    tmp |= val;
    b[offset] = cpu_to_be32(tmp);
}

static inline u64 __mlxsw_item_get64(const char *buf, const struct mlxsw_item *item,
                                     unsigned short outer_index, unsigned short index)
{
    size_t  typesize = sizeof(u64);
    unsigned int offset = __mlxsw_item_offset_no_checks(item, outer_index, index, typesize);
    __be64 *b = (__be64 *)buf;
    u64     tmp;
    u32     tmp32;

    if ((item->step % typesize != 0) ||
        (item->in_step_offset % typesize != 0)) {
        pr_err("mlxsw: item bug (name=%s,offset=%x,step=%x,in_step_offset=%x,typesize=%zx)\n",
               item->name, item->offset, item->step,
               item->in_step_offset, typesize);
        BUG();
    }

    if (item->offset % typesize == 0) {
        tmp = be64_to_cpu(b[offset]);
        tmp >>= item->shift;
        tmp &= GEN_MASK_ULL(item->size.bits - 1, 0);
    } else if (item->offset % sizeof(u32) != 0) {
        /* If not aligned to 4 bytes then raise error. */
        pr_err("mlxsw: item bug (name=%s,offset=%x,step=%x,in_step_offset=%x,typesize=%zx)\n",
               item->name, item->offset, item->step,
               item->in_step_offset, typesize);
        BUG();
    } else {
        /* This is a hack to work around not aligned u64 fields.
           Emulate access to __be64 *b as it was pair of __be32.
           Expect that this is a full 8 byte long field.
           Thus no shift is required. */
        offset = __mlxsw_item_offset_no_checks(item, outer_index, index, sizeof(u32));
        if (__little_endian_order()) {
            tmp32 = be32_to_cpu(((__be32 *)b)[offset]);
            tmp = (u64)tmp32 << 32;
            tmp += be32_to_cpu(((__be32 *)b)[offset + 1]);
        } else {
            tmp32 = be32_to_cpu(((__be32 *)b)[offset + 1]);
            tmp = (u64)tmp32 << 32;
            tmp += be32_to_cpu(((__be32 *)b)[offset]);
        }
    }
    return tmp;
}

static inline void __mlxsw_item_set64(char *buf, const struct mlxsw_item *item,
                                      unsigned short outer_index, unsigned short index, u64 val)
{
    size_t  typesize = sizeof(u64);
    unsigned int offset = __mlxsw_item_offset_no_checks(item, outer_index, index, typesize);
    __be64 *b = (__be64 *)buf;
    u64     mask = GEN_MASK_ULL(item->size.bits - 1, 0) << item->shift;
    u64     tmp;

    if ((item->step % typesize != 0) ||
        (item->in_step_offset % typesize != 0)) {
        pr_err("mlxsw: item bug (name=%s,offset=%x,step=%x,in_step_offset=%x,typesize=%zx)\n",
               item->name, item->offset, item->step,
               item->in_step_offset, typesize);
        BUG();
    }

    if (item->offset % typesize == 0) {
        val <<= item->shift;
        val &= mask;
        tmp = be64_to_cpu(b[offset]);
        tmp &= ~mask;
        tmp |= val;
        b[offset] = cpu_to_be64(tmp);
    } else if (item->offset % sizeof(u32) != 0) {
        /* If not aligned to 4 bytes then raise error. */
        pr_err("mlxsw: item bug (name=%s,offset=%x,step=%x,in_step_offset=%x,typesize=%zx)\n",
               item->name, item->offset, item->step,
               item->in_step_offset, typesize);
        BUG();
    } else {
        /* This is a hack to work around not aligned u64 fields.
           Emulate access to __be64 *b as it was pair of __be32.
           Expect that this is a full 8 byte long field.
           Thus no shift or mask is required. */
        offset = __mlxsw_item_offset_no_checks(item, outer_index, index, sizeof(u32));
        if (__little_endian_order()) {
            ((__be32 *)b)[offset] = cpu_to_be32(((uint32_t *)&val)[1]);
            ((__be32 *)b)[offset + 1] = cpu_to_be32((uint32_t)val);
        } else {
            ((__be32 *)b)[offset] = cpu_to_be32((uint32_t)val);
            ((__be32 *)b)[offset + 1] = cpu_to_be32(((uint32_t *)&val)[1]);
        }
    }
}

static inline void __mlxsw_item_memcpy_from(const char              *buf,
                                            char                    *dst,
                                            const struct mlxsw_item *item,
                                            unsigned short           outer_index,
                                            unsigned short           index)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(char));

    memcpy(dst, &buf[offset], item->size.bytes);
}

static inline void __mlxsw_item_memcpy_to(char                    *buf,
                                          const char              *src,
                                          const struct mlxsw_item *item,
                                          unsigned short           outer_index,
                                          unsigned short           index)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(char));

    memcpy(&buf[offset], src, item->size.bytes);
}

static inline char * __mlxsw_item_data(char *buf, const struct mlxsw_item *item, unsigned short index)
{
    unsigned int offset = __mlxsw_item_offset(item, 0, index, sizeof(char));

    return &buf[offset];
}

static inline u16 __mlxsw_item_bit_array_offset(const struct mlxsw_item *item, u16 outer_index, u16 index, u8 *shift)
{
    u16 items_per_byte;
    u16 offset;        /* byte offset inside the array */
    u8  in_byte_index;

    BUG_ON(index && !item->element_size);
    if ((item->offset % sizeof(u32) != 0) ||
        (BITS_PER_BYTE % item->element_size != 0)) {
        pr_err("mlxsw: item bug (name=%s,offset=%x,element_size=%x)\n",
               item->name, item->offset, item->element_size);
        BUG();
    }

    items_per_byte = BITS_PER_BYTE / item->element_size;
    offset = index / items_per_byte;
    in_byte_index = items_per_byte - index % items_per_byte - 1;
    *shift = in_byte_index * item->element_size;

    return item->offset + offset;
}

static inline u8 __mlxsw_item_bit_array_get(const char *buf, const struct mlxsw_item *item, u16 outer_index, u16 index)
{
    u8  shift, tmp;
    u16 offset = __mlxsw_item_bit_array_offset(item, outer_index, index, &shift);

    tmp = buf[offset];
    tmp >>= shift;
    tmp &= GEN_MASK(item->element_size - 1, 0);
    return tmp;
}

static inline void __mlxsw_item_bit_array_set(char *buf, const struct mlxsw_item *item, u16 outer_index, u16 index, u8 val)
{
    u8  shift, tmp;
    u16 offset = __mlxsw_item_bit_array_offset(item, outer_index, index, &shift);
    u8  mask = GEN_MASK(item->element_size - 1, 0) << shift;

    val <<= shift;
    val &= mask;
    tmp = buf[offset];
    tmp &= ~mask;
    tmp |= val;
    buf[offset] = tmp;
}

#define __ITEM_NAME(_type, _cname, _iname) \
    mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _item

/* _type: cmd_mbox, reg, etc.
 * _cname: container name (e.g. command name, register name)
 * _iname: item name within the container
 */

#define MLXSW_ITEM8(_type, _cname, _iname, _offset, _shift, _sizebits)                              \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                 \
        .offset = _offset,                                                                          \
        .shift = _shift,                                                                            \
        .size = {.bits = _sizebits, },                                                              \
        .name = #_type "_" #_cname "_" #_iname,                                                     \
    };                                                                                              \
    u8   mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf)                     \
    {                                                                                               \
        return __mlxsw_item_get8(buf, &__ITEM_NAME(_type, _cname, _iname), 0, 0);                   \
    }                                                                                               \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, u8 val)                   \
    {                                                                                               \
        __mlxsw_item_set8(buf, &__ITEM_NAME(_type, _cname, _iname), 0, 0, val);                     \
    }

/*
 *  _type = "reg"
 *  _cname = register name
 *  _iname = field name
 *  _offset = field offset or node offset if node is indexed (bytes)
 *  _shift =
 *  _sizebits = field size in bits
 *  _step = field size or node size if node is indexed
 *  _instepoffset = 0 if one field is indexed
 *                 sizeof(node) if node is indexed
 */
#define MLXSW_ITEM8_INDEXED(_type, _cname, _iname, _offset, _shift, _sizebits,                              \
                            _step, _instepoffset, _double_step, _double_instepoffset)                       \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                         \
        .offset = _offset,                                                                                  \
        .step = _step,                                                                                      \
        .in_step_offset = _instepoffset,                                                                    \
        .double_step = _double_step,                                                                        \
        .double_in_step_offset = _double_instepoffset,                                                      \
        .shift = _shift,                                                                                    \
        .size = {.bits = _sizebits, },                                                                      \
        .name = #_type "_" #_cname "_" #_iname,                                                             \
    };                                                                                                      \
    u8   mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf, unsigned short outer_index, \
                                                               unsigned short index)                        \
    {                                                                                                       \
        return __mlxsw_item_get8(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);             \
    }                                                                                                       \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, unsigned short outer_index,       \
                                                               unsigned short index, u8 val)                \
    {                                                                                                       \
        __mlxsw_item_set8(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index, val);               \
    }

#define MLXSW_ITEM16(_type, _cname, _iname, _offset, _shift, _sizebits)                             \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                 \
        .offset = _offset,                                                                          \
        .shift = _shift,                                                                            \
        .size = {.bits = _sizebits, },                                                              \
        .name = #_type "_" #_cname "_" #_iname,                                                     \
    };                                                                                              \
    u16  mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf)                     \
    {                                                                                               \
        return __mlxsw_item_get16(buf, &__ITEM_NAME(_type, _cname, _iname), 0, 0);                  \
    }                                                                                               \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, u16 val)                  \
    {                                                                                               \
        __mlxsw_item_set16(buf, &__ITEM_NAME(_type, _cname, _iname), 0, 0, val);                    \
    }

/*
 *  _type = "reg"
 *  _cname = register name
 *  _iname = field name
 *  _offset = field offset or node offset if node is indexed (bytes)
 *  _shift =
 *  _sizebits = field size in bits
 *  _step = field size or node size if node is indexed
 *  _instepoffset = 0 if one field is indexed
 *                 sizeof(node) if node is indexed
 */
#define MLXSW_ITEM16_INDEXED(_type, _cname, _iname, _offset, _shift, _sizebits,                             \
                             _step, _instepoffset, _double_step, _double_instepoffset)                      \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                         \
        .offset = _offset,                                                                                  \
        .step = _step,                                                                                      \
        .in_step_offset = _instepoffset,                                                                    \
        .double_step = _double_step,                                                                        \
        .double_in_step_offset = _double_instepoffset,                                                      \
        .shift = _shift,                                                                                    \
        .size = {.bits = _sizebits, },                                                                      \
        .name = #_type "_" #_cname "_" #_iname,                                                             \
    };                                                                                                      \
    u16  mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf, unsigned short outer_index, \
                                                               unsigned short index)                        \
    {                                                                                                       \
        return __mlxsw_item_get16(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);            \
    }                                                                                                       \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, unsigned short outer_index,       \
                                                               unsigned short index, u16 val)               \
    {                                                                                                       \
        __mlxsw_item_set16(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index, val);              \
    }

#define MLXSW_ITEM32(_type, _cname, _iname, _offset, _shift, _sizebits)                             \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                 \
        .offset = _offset,                                                                          \
        .shift = _shift,                                                                            \
        .size = {.bits = _sizebits, },                                                              \
        .name = #_type "_" #_cname "_" #_iname,                                                     \
    };                                                                                              \
    u32  mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf)                     \
    {                                                                                               \
        return __mlxsw_item_get32(buf, &__ITEM_NAME(_type, _cname, _iname), 0, 0);                  \
    }                                                                                               \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, u32 val)                  \
    {                                                                                               \
        __mlxsw_item_set32(buf, &__ITEM_NAME(_type, _cname, _iname), 0, 0, val);                    \
    }

/*
 *  _type = "reg"
 *  _cname = register name
 *  _iname = field name
 *  _offset = field offset or node offset if node is indexed (bytes)
 *  _shift =
 *  _sizebits = field size in bits
 *  _step = field size or node size if node is indexed
 *  _instepoffset = 0 if one field is indexed
 *                 sizeof(node) if node is indexed
 */
#define MLXSW_ITEM32_INDEXED(_type, _cname, _iname, _offset, _shift, _sizebits,                             \
                             _step, _instepoffset, _double_step, _double_instepoffset)                      \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                         \
        .offset = _offset,                                                                                  \
        .step = _step,                                                                                      \
        .in_step_offset = _instepoffset,                                                                    \
        .double_step = _double_step,                                                                        \
        .double_in_step_offset = _double_instepoffset,                                                      \
        .shift = _shift,                                                                                    \
        .size = {.bits = _sizebits, },                                                                      \
        .name = #_type "_" #_cname "_" #_iname,                                                             \
    };                                                                                                      \
    u32  mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf, unsigned short outer_index, \
                                                               unsigned short index)                        \
    {                                                                                                       \
        return __mlxsw_item_get32(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);            \
    }                                                                                                       \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, unsigned short outer_index,       \
                                                               unsigned short index, u32 val)               \
    {                                                                                                       \
        __mlxsw_item_set32(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index, val);              \
    }

#define MLXSW_ITEM64(_type, _cname, _iname, _offset, _shift, _sizebits)                             \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                 \
        .offset = _offset,                                                                          \
        .shift = _shift,                                                                            \
        .size = {.bits = _sizebits, },                                                              \
        .name = #_type "_" #_cname "_" #_iname,                                                     \
    };                                                                                              \
    u64  mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf)                     \
    {                                                                                               \
        return __mlxsw_item_get64(buf, &__ITEM_NAME(_type, _cname, _iname), 0, 0);                  \
    }                                                                                               \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, u64 val)                  \
    {                                                                                               \
        __mlxsw_item_set64(buf, &__ITEM_NAME(_type, _cname, _iname), 0, 0, val);                    \
    }

/*
 *  _type = "reg"
 *  _cname = register name
 *  _iname = field name
 *  _offset = field offset or node offset if node is indexed (bytes)
 *  _shift =
 *  _sizebits = field size in bits
 *  _step = field size or node size if node is indexed
 *  _instepoffset = 0 if one field is indexed
 *                 sizeof(node) if node is indexed
 */
#define MLXSW_ITEM64_INDEXED(_type, _cname, _iname, _offset, _shift,                                        \
                             _sizebits, _step, _instepoffset, _double_step, _double_instepoffset)           \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                         \
        .offset = _offset,                                                                                  \
        .step = _step,                                                                                      \
        .in_step_offset = _instepoffset,                                                                    \
        .double_step = _double_step,                                                                        \
        .double_in_step_offset = _double_instepoffset,                                                      \
        .shift = _shift,                                                                                    \
        .size = {.bits = _sizebits, },                                                                      \
        .name = #_type "_" #_cname "_" #_iname,                                                             \
    };                                                                                                      \
    u64  mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf, unsigned short outer_index, \
                                                               unsigned short index)                        \
    {                                                                                                       \
        return __mlxsw_item_get64(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);            \
    }                                                                                                       \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, unsigned short outer_index,       \
                                                               unsigned short index, u64 val)               \
    {                                                                                                       \
        __mlxsw_item_set64(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index, val);              \
    }

#define MLXSW_ITEM_BUF(_type, _cname, _iname, _offset, _sizebytes)                                          \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                         \
        .offset = _offset,                                                                                  \
        .size = {.bytes = _sizebytes, },                                                                    \
        .name = #_type "_" #_cname "_" #_iname,                                                             \
    };                                                                                                      \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _memcpy_from(const char *buf, char *dst)          \
    {                                                                                                       \
        __mlxsw_item_memcpy_from(buf, dst, &__ITEM_NAME(_type, _cname, _iname), 0, 0);                      \
    }                                                                                                       \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _memcpy_to(char *buf, const char *src)            \
    {                                                                                                       \
        __mlxsw_item_memcpy_to(buf, src, &__ITEM_NAME(_type, _cname, _iname), 0, 0);                        \
    }                                                                                                       \
    char * mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _data(char *buf)                                \
    {                                                                                                       \
        return __mlxsw_item_data(buf, &__ITEM_NAME(_type, _cname, _iname), 0);                              \
    }

#define MLXSW_ITEM_BUF_INDEXED(_type, _cname, _iname, _offset, _sizebytes, _step, _instepoffset,            \
                               _double_step, _double_instepoffset)                                          \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                         \
        .offset = _offset,                                                                                  \
        .step = _step,                                                                                      \
        .in_step_offset = _instepoffset,                                                                    \
        .double_step = _double_step,                                                                        \
        .double_in_step_offset = _double_instepoffset,                                                      \
        .size = {.bytes = _sizebytes, },                                                                    \
        .name = #_type "_" #_cname "_" #_iname,                                                             \
    };                                                                                                      \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _memcpy_from(const char *buf,                     \
                                                                       unsigned short outer_index,          \
                                                                       unsigned short index,                \
                                                                       char *dst)                           \
    {                                                                                                       \
        __mlxsw_item_memcpy_from(buf, dst, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);        \
    }                                                                                                       \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _memcpy_to(char *buf,                             \
                                                                     unsigned short outer_index,            \
                                                                     unsigned short index,                  \
                                                                     const char *src)                       \
    {                                                                                                       \
        __mlxsw_item_memcpy_to(buf, src, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);          \
    }                                                                                                       \
    char * mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _data(char *buf, unsigned short index)          \
    {                                                                                                       \
        return __mlxsw_item_data(buf, &__ITEM_NAME(_type, _cname, _iname), index);                          \
    }

/*
 *  _type = "reg"
 *  _cname = register name
 *  _iname = field name
 *  _offset = array offset in bytes
 *  _sizebytes = size of the array in bytes
 *  _element_size = size in bits of single element of the array
 */
#define MLXSW_ITEM_BIT_ARRAY(_type, _cname, _iname, _offset, _sizebytes, _element_size)                        \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                            \
        .offset = _offset,                                                                                     \
        .element_size = _element_size,                                                                         \
        .size = {.bytes = _sizebytes, },                                                                       \
        .name = #_type "_" #_cname "_" #_iname,                                                                \
    };                                                                                                         \
    u8   mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf, u16 outer_index, u16 index)    \
    {                                                                                                          \
        return __mlxsw_item_bit_array_get(buf,                                                                 \
                                          &__ITEM_NAME(_type, _cname, _iname),                                 \
                                          outer_index, index);                                                 \
    }                                                                                                          \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, u16 outer_index, u16 index, u8 val)  \
    {                                                                                                          \
        return __mlxsw_item_bit_array_set(buf,                                                                 \
                                          &__ITEM_NAME(_type, _cname, _iname),                                 \
                                          outer_index, index, val);                                            \
    }                                                                                                          \

#endif /* ifndef _MLXSW_ITEM_H */
