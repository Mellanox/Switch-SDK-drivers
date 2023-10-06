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

#include "fw.h"
#include "sx.h"
#include "sgmii.h"
#include "cq.h"
#include "fw_internal.h"
#include "emad.h"
#include "dev_init.h"
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>

#include <linux/types.h>
#include <linux/string.h>
#include <linux/bitops.h>
#include <linux/module.h>

#define REG_START_OFFSET 0x14

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
    unsigned short offset;           /* bytes in container */
    unsigned short step;           /* step in bytes for indexed items */
    unsigned short in_step_offset;    /* offset within one step */
    unsigned char  shift;          /* shift in bits */
    unsigned char  element_size;      /* size of element in bit array */
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

static inline unsigned int __mlxsw_item_offset(const struct mlxsw_item *item,
                                               unsigned short           outer_index,
                                               unsigned short           index,
                                               size_t                   typesize)
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

    return ((item->offset + outer_index * typesize + (unsigned int)item->step * index + item->in_step_offset) /
            typesize);
}

static inline unsigned int __mlxsw_item_offset_no_checks(const struct mlxsw_item *item,
                                                         unsigned short           outer_index,
                                                         unsigned short           index,
                                                         size_t                   typesize)
{
    BUG_ON(index && !item->step);

    return ((item->offset + outer_index * typesize + (unsigned int)item->step * index + item->in_step_offset) /
            typesize);
}

static inline u8 __mlxsw_item_get8(const char              *buf,
                                   const struct mlxsw_item *item,
                                   unsigned short           outer_index,
                                   unsigned short           index)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u8));
    u8          *b = (u8 *)buf;
    u8           tmp;

    tmp = b[offset];
    tmp >>= item->shift;
    tmp &= GEN_MASK(item->size.bits - 1, 0);
    return tmp;
}

static inline void __mlxsw_item_set8(char                    *buf,
                                     const struct mlxsw_item *item,
                                     unsigned short           outer_index,
                                     unsigned short           index,
                                     u8                       val)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u8));
    u8          *b = (u8 *)buf;
    u8           mask = GEN_MASK(item->size.bits - 1, 0) << item->shift;
    u8           tmp;

    val <<= item->shift;
    val &= mask;
    tmp = b[offset];
    tmp &= ~mask;
    tmp |= val;
    b[offset] = tmp;
}

static inline u16 __mlxsw_item_get16(const char              *buf,
                                     const struct mlxsw_item *item,
                                     unsigned short           outer_index,
                                     unsigned short           index)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u16));
    __be16      *b = (__be16 *)buf;
    u16          tmp;

    tmp = be16_to_cpu(b[offset]);
    tmp >>= item->shift;
    tmp &= GEN_MASK(item->size.bits - 1, 0);
    return tmp;
}

static inline void __mlxsw_item_set16(char                    *buf,
                                      const struct mlxsw_item *item,
                                      unsigned short           outer_index,
                                      unsigned short           index,
                                      u16                      val)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u16));
    __be16      *b = (__be16 *)buf;
    u16          mask = GEN_MASK(item->size.bits - 1, 0) << item->shift;
    u16          tmp;

    val <<= item->shift;
    val &= mask;
    tmp = be16_to_cpu(b[offset]);
    tmp &= ~mask;
    tmp |= val;
    b[offset] = cpu_to_be16(tmp);
}

static inline u32 __mlxsw_item_get32(const char              *buf,
                                     const struct mlxsw_item *item,
                                     unsigned short           outer_index,
                                     unsigned short           index)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u32));
    __be32      *b = (__be32 *)buf;
    u32          tmp;

    tmp = be32_to_cpu(b[offset]);
    tmp >>= item->shift;
    tmp &= GEN_MASK(item->size.bits - 1, 0);
    return tmp;
}

static inline void __mlxsw_item_set32(char                    *buf,
                                      const struct mlxsw_item *item,
                                      unsigned short           outer_index,
                                      unsigned short           index,
                                      u32                      val)
{
    unsigned int offset = __mlxsw_item_offset(item, outer_index, index, sizeof(u32));
    __be32      *b = (__be32 *)buf;
    u32          mask = GEN_MASK(item->size.bits - 1, 0) << item->shift;
    u32          tmp;

    val <<= item->shift;
    val &= mask;
    tmp = be32_to_cpu(b[offset]);
    tmp &= ~mask;
    tmp |= val;
    b[offset] = cpu_to_be32(tmp);
}

static inline u64 __mlxsw_item_get64(const char              *buf,
                                     const struct mlxsw_item *item,
                                     unsigned short           outer_index,
                                     unsigned short           index)
{
    size_t       typesize = sizeof(u64);
    unsigned int offset = __mlxsw_item_offset_no_checks(item, outer_index, index, typesize);
    __be64      *b = (__be64 *)buf;
    u64          tmp;
    u32          tmp32;

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
         *  Emulate access to __be64 *b as it was pair of __be32.
         *  Expect that this is a full 8 byte long field.
         *  Thus no shift is required. */
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

static inline void __mlxsw_item_set64(char                    *buf,
                                      const struct mlxsw_item *item,
                                      unsigned short           outer_index,
                                      unsigned short           index,
                                      u64                      val)
{
    size_t       typesize = sizeof(u64);
    unsigned int offset = __mlxsw_item_offset_no_checks(item, outer_index, index, typesize);
    __be64      *b = (__be64 *)buf;
    u64          mask = GEN_MASK_ULL(item->size.bits - 1, 0) << item->shift;
    u64          tmp;

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
         *  Emulate access to __be64 *b as it was pair of __be32.
         *  Expect that this is a full 8 byte long field.
         *  Thus no shift or mask is required. */
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

static inline void __mlxsw_item_bit_array_set(char                    *buf,
                                              const struct mlxsw_item *item,
                                              u16                      outer_index,
                                              u16                      index,
                                              u8                       val)
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
    u8                       mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf) \
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
#define MLXSW_ITEM8_INDEXED(_type, _cname, _iname, _offset, _shift, _sizebits,                                 \
                            _step, _instepoffset)                                                              \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                            \
        .offset = _offset,                                                                                     \
        .step = _step,                                                                                         \
        .in_step_offset = _instepoffset,                                                                       \
        .shift = _shift,                                                                                       \
        .size = {.bits = _sizebits, },                                                                         \
        .name = #_type "_" #_cname "_" #_iname,                                                                \
    };                                                                                                         \
    u8                       mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf,            \
                                                                                   unsigned short outer_index, \
                                                                                   unsigned short index)       \
    {                                                                                                          \
        return __mlxsw_item_get8(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);                \
    }                                                                                                          \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, unsigned short outer_index,          \
                                                               unsigned short index, u8 val)                   \
    {                                                                                                          \
        __mlxsw_item_set8(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index, val);                  \
    }

#define MLXSW_ITEM16(_type, _cname, _iname, _offset, _shift, _sizebits)                             \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                 \
        .offset = _offset,                                                                          \
        .shift = _shift,                                                                            \
        .size = {.bits = _sizebits, },                                                              \
        .name = #_type "_" #_cname "_" #_iname,                                                     \
    };                                                                                              \
    u16                      mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf) \
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
#define MLXSW_ITEM16_INDEXED(_type, _cname, _iname, _offset, _shift, _sizebits,                                \
                             _step, _instepoffset)                                                             \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                            \
        .offset = _offset,                                                                                     \
        .step = _step,                                                                                         \
        .in_step_offset = _instepoffset,                                                                       \
        .shift = _shift,                                                                                       \
        .size = {.bits = _sizebits, },                                                                         \
        .name = #_type "_" #_cname "_" #_iname,                                                                \
    };                                                                                                         \
    u16                      mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf,            \
                                                                                   unsigned short outer_index, \
                                                                                   unsigned short index)       \
    {                                                                                                          \
        return __mlxsw_item_get16(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);               \
    }                                                                                                          \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, unsigned short outer_index,          \
                                                               unsigned short index, u16 val)                  \
    {                                                                                                          \
        __mlxsw_item_set16(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index, val);                 \
    }

#define MLXSW_ITEM32(_type, _cname, _iname, _offset, _shift, _sizebits)                             \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                 \
        .offset = _offset,                                                                          \
        .shift = _shift,                                                                            \
        .size = {.bits = _sizebits, },                                                              \
        .name = #_type "_" #_cname "_" #_iname,                                                     \
    };                                                                                              \
    u32                      mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf) \
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
#define MLXSW_ITEM32_INDEXED(_type, _cname, _iname, _offset, _shift, _sizebits,                                \
                             _step, _instepoffset)                                                             \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                            \
        .offset = _offset,                                                                                     \
        .step = _step,                                                                                         \
        .in_step_offset = _instepoffset,                                                                       \
        .shift = _shift,                                                                                       \
        .size = {.bits = _sizebits, },                                                                         \
        .name = #_type "_" #_cname "_" #_iname,                                                                \
    };                                                                                                         \
    u32                      mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf,            \
                                                                                   unsigned short outer_index, \
                                                                                   unsigned short index)       \
    {                                                                                                          \
        return __mlxsw_item_get32(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);               \
    }                                                                                                          \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, unsigned short outer_index,          \
                                                               unsigned short index, u32 val)                  \
    {                                                                                                          \
        __mlxsw_item_set32(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index, val);                 \
    }

#define MLXSW_ITEM64(_type, _cname, _iname, _offset, _shift, _sizebits)                             \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                 \
        .offset = _offset,                                                                          \
        .shift = _shift,                                                                            \
        .size = {.bits = _sizebits, },                                                              \
        .name = #_type "_" #_cname "_" #_iname,                                                     \
    };                                                                                              \
    u64                      mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf) \
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
#define MLXSW_ITEM64_INDEXED(_type, _cname, _iname, _offset, _shift,                                           \
                             _sizebits, _step, _instepoffset)                                                  \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                            \
        .offset = _offset,                                                                                     \
        .step = _step,                                                                                         \
        .in_step_offset = _instepoffset,                                                                       \
        .shift = _shift,                                                                                       \
        .size = {.bits = _sizebits, },                                                                         \
        .name = #_type "_" #_cname "_" #_iname,                                                                \
    };                                                                                                         \
    u64                      mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf,            \
                                                                                   unsigned short outer_index, \
                                                                                   unsigned short index)       \
    {                                                                                                          \
        return __mlxsw_item_get64(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);               \
    }                                                                                                          \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, unsigned short outer_index,          \
                                                               unsigned short index, u64 val)                  \
    {                                                                                                          \
        __mlxsw_item_set64(buf, &__ITEM_NAME(_type, _cname, _iname), outer_index, index, val);                 \
    }

#define MLXSW_ITEM_BUF(_type, _cname, _iname, _offset, _sizebytes)                                                     \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                                    \
        .offset = _offset,                                                                                             \
        .size = {.bytes = _sizebytes, },                                                                               \
        .name = #_type "_" #_cname "_" #_iname,                                                                        \
    };                                                                                                                 \
    void                     mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _memcpy_from(const char *buf, char *dst) \
    {                                                                                                                  \
        __mlxsw_item_memcpy_from(buf, dst, &__ITEM_NAME(_type, _cname, _iname), 0, 0);                                 \
    }                                                                                                                  \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _memcpy_to(char *buf, const char *src)                       \
    {                                                                                                                  \
        __mlxsw_item_memcpy_to(buf, src, &__ITEM_NAME(_type, _cname, _iname), 0, 0);                                   \
    }                                                                                                                  \
    char * mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _data(char *buf)                                           \
    {                                                                                                                  \
        return __mlxsw_item_data(buf, &__ITEM_NAME(_type, _cname, _iname), 0);                                         \
    }

#define MLXSW_ITEM_BUF_INDEXED(_type, _cname, _iname, _offset, _sizebytes, _step, _instepoffset)                       \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                                    \
        .offset = _offset,                                                                                             \
        .step = _step,                                                                                                 \
        .in_step_offset = _instepoffset,                                                                               \
        .size = {.bytes = _sizebytes, },                                                                               \
        .name = #_type "_" #_cname "_" #_iname,                                                                        \
    };                                                                                                                 \
    void                     mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _memcpy_from(const char *buf,            \
                                                                                           unsigned short outer_index, \
                                                                                           unsigned short index,       \
                                                                                           char *dst)                  \
    {                                                                                                                  \
        __mlxsw_item_memcpy_from(buf, dst, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);                   \
    }                                                                                                                  \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _memcpy_to(char *buf,                                        \
                                                                     unsigned short outer_index,                       \
                                                                     unsigned short index,                             \
                                                                     const char *src)                                  \
    {                                                                                                                  \
        __mlxsw_item_memcpy_to(buf, src, &__ITEM_NAME(_type, _cname, _iname), outer_index, index);                     \
    }                                                                                                                  \
    char * mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _data(char *buf, unsigned short index)                     \
    {                                                                                                                  \
        return __mlxsw_item_data(buf, &__ITEM_NAME(_type, _cname, _iname), index);                                     \
    }

/*
 *  _type = "reg"
 *  _cname = register name
 *  _iname = field name
 *  _offset = array offset in bytes
 *  _sizebytes = size of the array in bytes
 *  _element_size = size in bits of single element of the array
 */
#define MLXSW_ITEM_BIT_ARRAY(_type, _cname, _iname, _offset, _sizebytes, _element_size)                       \
    static struct mlxsw_item __ITEM_NAME(_type, _cname, _iname) = {                                           \
        .offset = _offset,                                                                                    \
        .element_size = _element_size,                                                                        \
        .size = {.bytes = _sizebytes, },                                                                      \
        .name = #_type "_" #_cname "_" #_iname,                                                               \
    };                                                                                                        \
    u8                       mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _get(const char *buf,           \
                                                                                   u16 outer_index,           \
                                                                                   u16 index)                 \
    {                                                                                                         \
        return __mlxsw_item_bit_array_get(buf,                                                                \
                                          &__ITEM_NAME(_type, _cname, _iname),                                \
                                          outer_index, index);                                                \
    }                                                                                                         \
    void mlxsw_ ## _type ## _ ## _cname ## _ ## _iname ## _set(char *buf, u16 outer_index, u16 index, u8 val) \
    {                                                                                                         \
        return __mlxsw_item_bit_array_set(buf,                                                                \
                                          &__ITEM_NAME(_type, _cname, _iname),                                \
                                          outer_index, index, val);                                           \
    }                                                                                                         \


/* old implementation defined all register field's offsets from the beginning of the buffer (inbox/outbox)
 * and not from the beginning of the register area itself. 'auto-reg' infrastructure works with functions that
 * get the pointer to the beginning of the register area. the two definitions below adapts old implementation to
 * new one so we don't have to recalculate all offsets.
 */
#define SX_PUT_REG_FIELD(dest, source, offset) SX_PUT(dest, source, ((offset) - REG_START_OFFSET))
#define SX_GET_REG_FIELD(dest, source, offset) SX_GET(dest, source, ((offset) - REG_START_OFFSET))

int sx_ACCESS_REG_internal(struct sx_dev           *dev,
                           uint8_t                  dev_id,
                           uint32_t                 flags,
                           struct ku_operation_tlv *op_tlv,
                           access_reg_encode_cb_t   reg_encode_cb,
                           access_reg_decode_cb_t   reg_decode_cb,
                           u16                      reg_len_in_dwords,
                           void                    *ku_reg,
                           void                    *context)
{
#define REG_TLV_OFFSET     0x10
#define REG_TLV_TYPE       0x03
#define OPERATION_TLV_SIZE 0x10
#define REG_TLV_SIZE       0x04

#define IN_MB_SIZE(reg_dword_size) (((reg_dword_size) * 4) + REG_TLV_SIZE + OPERATION_TLV_SIZE)

    struct sx_cmd_mailbox *in_mailbox;
    struct sx_cmd_mailbox *out_mailbox;
    u8                    *inbox;
    u8                    *outbox;
    int                    err;
    u16                    type_len;

    if (!dev || !op_tlv || !ku_reg) {
        return -EINVAL;
    }

    if (sx_core_fw_is_faulty(dev)) {
        printk(KERN_NOTICE "Access Reg: Faulty FW - ignoring\n");
        return 0;
    }

    in_mailbox = sx_alloc_cmd_mailbox(dev, dev_id);
    if (IS_ERR(in_mailbox)) {
        return PTR_ERR(in_mailbox);
    }

    out_mailbox = sx_alloc_cmd_mailbox(dev, dev_id);
    if (IS_ERR(out_mailbox)) {
        err = PTR_ERR(out_mailbox);
        goto out_free;
    }

    inbox = in_mailbox->buf;
    memset(inbox, 0, SX_MAILBOX_SIZE);
    outbox = out_mailbox->buf;

    set_operation_tlv(inbox, op_tlv);
    type_len = (REG_TLV_TYPE << 11) | (reg_len_in_dwords + 1); /* +1 for the REG_TLV size itself (1 dword) */
    SX_PUT(inbox, type_len, REG_TLV_OFFSET);

    if (reg_encode_cb) {
        err = reg_encode_cb(inbox + REG_START_OFFSET, ku_reg, context);
        if (err) {
            goto out;
        }
    }

    err = sx_cmd_box(dev, dev_id, in_mailbox, out_mailbox, 0, 0,
                     SX_CMD_ACCESS_REG, SX_CMD_TIME_CLASS_A,
                     IN_MB_SIZE(reg_len_in_dwords));
    if (err) {
        if (flags & SX_ACCESS_REG_F_IGNORE_FW_RET_CODE) {
            err = 0;
        }

        goto out;
    }

    get_operation_tlv(outbox, op_tlv);
    if (op_tlv->status) {
        if ((op_tlv->status == SX_EMAD_STATUS_BUSY_E) || (op_tlv->status == SX_EMAD_STATUS_ISSU_ONGOING_E)) {
            printk(KERN_INFO "Register access notice (reg_id=0x%04x, status=0x%x)\n",
                   op_tlv->register_id,
                   op_tlv->status);
        } else {
            printk(KERN_ERR "Register access failed (reg_id=0x%04x, status=0x%x)\n",
                   op_tlv->register_id,
                   op_tlv->status);
            print_hex_dump(KERN_NOTICE, "", DUMP_PREFIX_OFFSET, 16, 1, inbox, IN_MB_SIZE(reg_len_in_dwords), 0);
        }
    }
    if (reg_decode_cb && ((flags & SX_ACCESS_REG_F_SET_AND_GET) || (op_tlv->method == 0x01))) { /* 0x01 = Query */
        err = reg_decode_cb(outbox + REG_START_OFFSET, ku_reg, context);
        if (err) {
            goto out;
        }
    }

out:
    sx_free_cmd_mailbox(dev, out_mailbox);

out_free:
    sx_free_cmd_mailbox(dev, in_mailbox);
    return err;
}

/****************************************************
 * SPZR (wrapper)
 *
 * sx_ib module is calling the SPZR wrapper.
 * on OOB system, it will call the register by EMAD
 * Otherwise, it will call it with Command Interface
 ***************************************************/
int sx_ACCESS_REG_SPZR_wrapper(struct sx_dev *dev, struct ku_access_spzr_reg *reg_data)
{
    if (is_sgmii_supported()) {
        /* SPZR is called in bootstrap and when working with OOB, we don't have PCI to work with, only I2C.
         * The problem is that I2C is enabled only on one management board. We must call this register from both
         * management boards and the only way to do that is with SGMII.
         */
        return sgmii_emad_access_spzr(reg_data->dev_id, &reg_data->spzr_reg);
    }

    return sx_ACCESS_REG_SPZR(dev, reg_data);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPZR_wrapper);

/************************************************
 * PLIB
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET     0x15
#define REG_LOCAL_PORT_MSB_OFFSET 0x16
#define REG_IB_PORT_OFFSET        0x17

static int __PLIB_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_plib_reg *plib_reg = (struct ku_plib_reg*)ku_reg;
    u8                  tmp_u8 = 0;

    SX_PUT_REG_FIELD(inbox, plib_reg->local_port, REG_LOCAL_PORT_OFFSET);
    tmp_u8 = (plib_reg->lp_msb & 0x3) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, plib_reg->ib_port, REG_IB_PORT_OFFSET);

    return 0;
}

static int __PLIB_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_plib_reg *plib_reg = (struct ku_plib_reg*)ku_reg;

    SX_GET_REG_FIELD(plib_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(plib_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    plib_reg->lp_msb >>= 4;
    plib_reg->lp_msb &= 0x3;
    SX_GET_REG_FIELD(plib_reg->ib_port, outbox, REG_IB_PORT_OFFSET);

    return 0;
}

int sx_ACCESS_REG_PLIB(struct sx_dev *dev, struct ku_access_plib_reg *reg_data)
{
#define PLIB_REG_LEN 0x05

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PLIB_encode,
                                  __PLIB_decode,
                                  PLIB_REG_LEN,
                                  &reg_data->plib_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PLIB);

/************************************************
 * PMLP
 ***********************************************/
#define PMLP_DIFF_RX_TX_OFFSET     0x14
#define PMLP_LOCAL_PORT_OFFSET     0x15
#define PMLP_LOCAL_PORT_MSB_OFFSET 0x16

#define PMLP_WIDTH_OFFSET  0x17
#define PMLP_ROW0_OFFSET   0x18
#define PMLP_BYTES_PER_ROW 4
#define PMLP_REG_LEN       0x10

static int __PMLP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmlp_reg *pmlp_reg = (struct ku_pmlp_reg*)ku_reg;
    u8                  tmp_u8;
    u32                 tmp_u32;
    int                 i;

    tmp_u8 = (pmlp_reg->use_different_rx_tx << 7) | (pmlp_reg->autosplit << 6);
    SX_PUT_REG_FIELD(inbox, tmp_u8, PMLP_DIFF_RX_TX_OFFSET);

    SX_PUT_REG_FIELD(inbox, pmlp_reg->local_port, PMLP_LOCAL_PORT_OFFSET);

    tmp_u8 = (pmlp_reg->lp_msb & 0x3) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, PMLP_LOCAL_PORT_MSB_OFFSET);

    SX_PUT_REG_FIELD(inbox, pmlp_reg->width, PMLP_WIDTH_OFFSET);

    for (i = 0; i < 8; i++) {
        tmp_u32 = (((u32)(pmlp_reg->rx_lane[i] & 0xf)) << 24) |
                  (((u32)(pmlp_reg->lane[i] & 0xf)) << 16) |
                  (((u32)(pmlp_reg->slot[i] & 0xf)) << 8) |
                  pmlp_reg->module[i];

        SX_PUT_REG_FIELD(inbox, tmp_u32, PMLP_ROW0_OFFSET + i * PMLP_BYTES_PER_ROW);
    }
    return 0;
}

static int __PMLP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmlp_reg *pmlp_reg = (struct ku_pmlp_reg*)ku_reg;
    u8                  tmp_u8;
    u32                 tmp_u32;
    int                 i;

    SX_GET_REG_FIELD(tmp_u8, outbox, PMLP_DIFF_RX_TX_OFFSET);
    pmlp_reg->use_different_rx_tx = tmp_u8 >> 7;
    pmlp_reg->autosplit = tmp_u8 >> 6;

    SX_GET_REG_FIELD(pmlp_reg->local_port, outbox, PMLP_LOCAL_PORT_OFFSET);

    SX_GET_REG_FIELD(tmp_u8, outbox, PMLP_LOCAL_PORT_MSB_OFFSET);
    pmlp_reg->lp_msb = (tmp_u8 >> 4) & 0x3;

    SX_GET_REG_FIELD(pmlp_reg->width, outbox, PMLP_WIDTH_OFFSET);

    for (i = 0; i < 8; i++) {
        SX_GET_REG_FIELD(tmp_u32, outbox, PMLP_ROW0_OFFSET + i * PMLP_BYTES_PER_ROW);
        pmlp_reg->rx_lane[i] = (tmp_u32 >> 24) & 0xf;
        pmlp_reg->lane[i] = (tmp_u32 >> 16) & 0xf;
        pmlp_reg->slot[i] = (tmp_u32 >> 8) & 0xf;
        pmlp_reg->module[i] = tmp_u32 & 0xff;
    }
    return 0;
}

int sx_ACCESS_REG_PMLP(struct sx_dev *dev, struct ku_access_pmlp_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMLP_encode,
                                  __PMLP_decode,
                                  PMLP_REG_LEN,
                                  &reg_data->pmlp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMLP);


/************************************************
 * MHSR
 ***********************************************/
#define REG_HEALTH_OFFSET 0x17
#define MHSR_REG_LEN      0x2

static int __MHSR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mhsr_reg *mhsr_reg = (struct ku_mhsr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mhsr_reg->health, REG_HEALTH_OFFSET);
    return 0;
}

static int __MHSR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mhsr_reg *mhsr_reg = (struct ku_mhsr_reg*)ku_reg;

    SX_GET_REG_FIELD(mhsr_reg->health, outbox, REG_HEALTH_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MHSR(struct sx_dev *dev, struct ku_access_mhsr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MHSR_encode,
                                  __MHSR_decode,
                                  MHSR_REG_LEN,
                                  &reg_data->mhsr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MHSR);

/************************************************
 * PSPA
 ***********************************************/
#define REG_SWID_OFFSET                0x14
#define REG_LOCAL_PORT_OFFSET          0x15
#define REG_SUB_PORT_OFFSET            0x16
#define PSPA_REG_LOCAL_PORT_MSB_OFFSET 0x17
#define PSPA_REG_LEN                   0x03

static int __PSPA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pspa_reg *pspa_reg = (struct ku_pspa_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pspa_reg->swid, REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, pspa_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pspa_reg->sub_port, REG_SUB_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pspa_reg->lp_msb, PSPA_REG_LOCAL_PORT_MSB_OFFSET);
    return 0;
}

static int __PSPA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pspa_reg *pspa_reg = (struct ku_pspa_reg*)ku_reg;

    SX_GET_REG_FIELD(pspa_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(pspa_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pspa_reg->sub_port, outbox, REG_SUB_PORT_OFFSET);
    SX_GET_REG_FIELD(pspa_reg->lp_msb, outbox, PSPA_REG_LOCAL_PORT_MSB_OFFSET);
    pspa_reg->lp_msb &= 0x3;
    return 0;
}

int sx_ACCESS_REG_PSPA(struct sx_dev *dev, struct ku_access_pspa_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PSPA_encode,
                                  __PSPA_decode,
                                  PSPA_REG_LEN,
                                  &reg_data->pspa_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PSPA);

/************************************************
 * MJTAG
 ***********************************************/
#define MJTAG_REG_CMD_OFFSET               0x14
#define MJTAG_REG_CMD_BIT_N                6
#define MJTAG_REG_SEQ_NUM_BIT_N            0x0f
#define MJTAG_REG_SEQ_NUM_OFFSET           0x14
#define MJTAG_REG_TRANSACTIONS_SIZE_OFFSET 0x17
#define MJTAG_REG_JTAG_TRANSACTION_OFFSET  0x18
#define MJTAG_REG_TRANSACTION_TDO_BIT_N    0x03
#define MJTAG_REG_TRANSACTION_TDI_BIT_N    0x01
#define MJTAG_REG_LEN                      0x0c

static int __MJTAG_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mjtag_reg *mjtag_reg = (struct ku_mjtag_reg*)ku_reg;
    u8                   tmp_val_u8 = 0;
    int                  counter;

    tmp_val_u8 |= mjtag_reg->cmd << MJTAG_REG_CMD_BIT_N;
    tmp_val_u8 |= mjtag_reg->seq_num;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, MJTAG_REG_CMD_OFFSET);
    SX_PUT_REG_FIELD(inbox, mjtag_reg->size, MJTAG_REG_TRANSACTIONS_SIZE_OFFSET);

    for (counter = 0; counter < mjtag_reg->size; counter++) {
        tmp_val_u8 = 0;
        tmp_val_u8 |= (mjtag_reg->jtag_transaction_sets[counter].tdo & 0x01) << MJTAG_REG_TRANSACTION_TDO_BIT_N;
        tmp_val_u8 |= (mjtag_reg->jtag_transaction_sets[counter].tdi & 0x01) << MJTAG_REG_TRANSACTION_TDI_BIT_N;
        tmp_val_u8 |= (mjtag_reg->jtag_transaction_sets[counter].tms & 0x01);
        SX_PUT_REG_FIELD(inbox, tmp_val_u8, MJTAG_REG_JTAG_TRANSACTION_OFFSET + counter);
    }

    return 0;
}

static int __MJTAG_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mjtag_reg *mjtag_reg = (struct ku_mjtag_reg*)ku_reg;
    u8                   tmp_val_u8 = 0;
    int                  counter;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, MJTAG_REG_CMD_OFFSET);
    mjtag_reg->cmd = tmp_val_u8 & (1 << MJTAG_REG_CMD_BIT_N) ? 1 : 0;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, MJTAG_REG_SEQ_NUM_OFFSET);
    mjtag_reg->seq_num = tmp_val_u8 & MJTAG_REG_SEQ_NUM_BIT_N ? 1 : 0;
    SX_GET_REG_FIELD(mjtag_reg->size, outbox, MJTAG_REG_TRANSACTIONS_SIZE_OFFSET);

    for (counter = 0; counter < mjtag_reg->size; counter++) {
        SX_GET_REG_FIELD(tmp_val_u8, outbox, MJTAG_REG_JTAG_TRANSACTION_OFFSET);
        mjtag_reg->jtag_transaction_sets[counter].tdi = tmp_val_u8 & (1 << MJTAG_REG_TRANSACTION_TDI_BIT_N) ? 1 : 0;
        mjtag_reg->jtag_transaction_sets[counter].tdo = tmp_val_u8 & (1 << MJTAG_REG_TRANSACTION_TDO_BIT_N) ? 1 : 0;
        mjtag_reg->jtag_transaction_sets[counter].tms = tmp_val_u8 & 1 ? 1 : 0;
    }

    return 0;
}

int sx_ACCESS_REG_MJTAG(struct sx_dev *dev, struct ku_access_mjtag_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MJTAG_encode,
                                  __MJTAG_decode,
                                  MJTAG_REG_LEN,
                                  &reg_data->mjtag_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MJTAG);


/************************************************
 * PPSC
 ***********************************************/
#define PPSC_REG_LOCAL_PORT_OFFSET     0x15
#define PPSC_REG_LOCAL_PORT_MSB_OFFSET 0x16
#define PPSC_REG_LOCAL_PORT_N          0x08
#define PPSC_REG_WRPS_ADMIN_OFFSET     0x27
#define PPSC_REG_WRPS_ADMIN_N          0x04
#define PPSC_REG_WRPS_STATUS_OFFSET    0x2B
#define PPSC_REG_WRPS_STATUS_N         0x04
#define PPSC_REG_UP_THRESHOLD_OFFSET   0x2D
#define PPSC_REG_UP_THRESHOLD_N        0x08
#define PPSC_REG_DOWN_THRESHOLD_OFFSET 0x2D
#define PPSC_REG_DOWN_THRESHOLD_N      0x08
#define PPSC_REG_SRPS_ADMIN_OFFSET     0x35
#define PPSC_REG_SRPS_ADMIN_N          0x04
#define PPSC_REG_SRPS_STATUS_OFFSET    0x39
#define PPSC_REG_SRPS_STATUS_N         0x04
#define PPSC_REG_LEN                   0x0D

static int __PPSC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppsc_reg *ppsc_reg = (struct ku_ppsc_reg*)ku_reg;
    u8                  tmp_u8 = 0;

    SX_PUT_REG_FIELD(inbox, ppsc_reg->local_port, PPSC_REG_LOCAL_PORT_OFFSET);
    tmp_u8 = (ppsc_reg->lp_msb & 0x3) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, PPSC_REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->wrps_admin, PPSC_REG_WRPS_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->wrps_status, PPSC_REG_WRPS_STATUS_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->up_threshold, PPSC_REG_UP_THRESHOLD_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->down_threshold, PPSC_REG_DOWN_THRESHOLD_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->srps_admin, PPSC_REG_SRPS_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->srps_status, PPSC_REG_SRPS_STATUS_OFFSET);
    return 0;
}

static int __PPSC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppsc_reg *ppsc_reg = (struct ku_ppsc_reg*)ku_reg;

    SX_GET_REG_FIELD(ppsc_reg->local_port, outbox, PPSC_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->lp_msb, outbox, PPSC_REG_LOCAL_PORT_MSB_OFFSET);
    ppsc_reg->lp_msb >>= 4;
    ppsc_reg->lp_msb &= 0x3;
    SX_GET_REG_FIELD(ppsc_reg->wrps_admin, outbox, PPSC_REG_WRPS_ADMIN_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->wrps_status, outbox, PPSC_REG_WRPS_STATUS_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->up_threshold, outbox, PPSC_REG_UP_THRESHOLD_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->down_threshold, outbox, PPSC_REG_DOWN_THRESHOLD_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->srps_admin, outbox, PPSC_REG_SRPS_ADMIN_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->srps_status, outbox, PPSC_REG_SRPS_STATUS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPSC(struct sx_dev *dev, struct ku_access_ppsc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPSC_encode,
                                  __PPSC_decode,
                                  PPSC_REG_LEN,
                                  &reg_data->ppsc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPSC);


/************************************************
 * PCNR
 ***********************************************/
#define REG_TUNING_OFFSET         0x17
#define REG_LOCAL_PORT_OFFSET     0x15
#define REG_LOCAL_PORT_MSB_OFFSET 0x16
#define PCNR_REG_LEN              0x04

static int __PCNR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pcnr_reg *pcnr_reg = (struct ku_pcnr_reg*)ku_reg;
    u8                  tmp_u8 = 0;

    SX_PUT_REG_FIELD(inbox, pcnr_reg->local_port, REG_LOCAL_PORT_OFFSET);
    tmp_u8 = (pcnr_reg->lp_msb & 0x03) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, pcnr_reg->tuning_override, REG_TUNING_OFFSET);
    return 0;
}

static int __PCNR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pcnr_reg *pcnr_reg = (struct ku_pcnr_reg*)ku_reg;

    SX_GET_REG_FIELD(pcnr_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pcnr_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    pcnr_reg->lp_msb >>= 4;
    pcnr_reg->lp_msb &= 0x3;
    SX_GET_REG_FIELD(pcnr_reg->tuning_override, outbox, REG_TUNING_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PCNR(struct sx_dev *dev, struct ku_access_pcnr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PCNR_encode,
                                  __PCNR_decode,
                                  PCNR_REG_LEN,
                                  &reg_data->pcnr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PCNR);


/************************************************
 * PPLM
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET            0x15
#define REG_LOCAL_PORT_MSB_OFFSET        0x16
#define REG_PORT_PROFILE_MODE_OFFSET     0x1C
#define REG_STATIC_PORT_PROFILE_OFFSET   0x1D
#define REG_ACTIVE_PORT_PROFILE_OFFSET   0x1E
#define REG_RETRANSMISSION_ACTIVE_OFFSET 0x20
#define REG_IB_FEC_OVERRIDE_ADMIN_HDR    0x4C
#define REG_IB_FEC_OVERRIDE_ADMIN_EDR    0x4E
#define REG_IB_FEC_OVERRIDE_ADMIN_FDR    0x50
#define REG_IB_FEC_OVERRIDE_ADMIN_NDR    0x56
#define REG_IB_FEC_OVERRIDE_ADMIN_XDR    0x62
#define PPLM_REG_LEN                     0x14

static int __PPLM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pplm_reg *pplm_reg = (struct ku_pplm_reg*)ku_reg;
    u8                  tmp_u8 = 0;

    SX_PUT_REG_FIELD(inbox, pplm_reg->local_port, REG_LOCAL_PORT_OFFSET);
    tmp_u8 = (pplm_reg->lp_msb & 0x03) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, pplm_reg->port_profile_mode, REG_PORT_PROFILE_MODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pplm_reg->static_port_profile, REG_STATIC_PORT_PROFILE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pplm_reg->ib_fec_override_admin_edr, REG_IB_FEC_OVERRIDE_ADMIN_EDR);
    SX_PUT_REG_FIELD(inbox, pplm_reg->ib_fec_override_admin_fdr, REG_IB_FEC_OVERRIDE_ADMIN_FDR);
    SX_PUT_REG_FIELD(inbox, pplm_reg->ib_fec_override_admin_hdr, REG_IB_FEC_OVERRIDE_ADMIN_HDR);
    SX_PUT_REG_FIELD(inbox, pplm_reg->ib_fec_override_admin_ndr, REG_IB_FEC_OVERRIDE_ADMIN_NDR);
    SX_PUT_REG_FIELD(inbox, pplm_reg->ib_fec_override_admin_xdr, REG_IB_FEC_OVERRIDE_ADMIN_XDR);
    return 0;
}

static int __PPLM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pplm_reg *pplm_reg = (struct ku_pplm_reg*)ku_reg;
    u32                 retransmission_active_and_fec_mode_active;

    SX_GET_REG_FIELD(pplm_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pplm_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    pplm_reg->lp_msb >>= 4;
    pplm_reg->lp_msb &= 0x3;
    SX_GET_REG_FIELD(pplm_reg->port_profile_mode, outbox, REG_PORT_PROFILE_MODE_OFFSET);
    SX_GET_REG_FIELD(pplm_reg->static_port_profile, outbox, REG_STATIC_PORT_PROFILE_OFFSET);
    SX_GET_REG_FIELD(pplm_reg->active_port_profile, outbox, REG_ACTIVE_PORT_PROFILE_OFFSET);
    SX_GET_REG_FIELD(retransmission_active_and_fec_mode_active, outbox, REG_RETRANSMISSION_ACTIVE_OFFSET);
    pplm_reg->retransmission_active = (retransmission_active_and_fec_mode_active >> 24) & 0xFF;
    pplm_reg->fec_mode_active = retransmission_active_and_fec_mode_active & 0xFFFFFF;
    SX_GET_REG_FIELD(pplm_reg->ib_fec_override_admin_edr, outbox, REG_IB_FEC_OVERRIDE_ADMIN_EDR);
    SX_GET_REG_FIELD(pplm_reg->ib_fec_override_admin_fdr, outbox, REG_IB_FEC_OVERRIDE_ADMIN_FDR);
    SX_GET_REG_FIELD(pplm_reg->ib_fec_override_admin_hdr, outbox, REG_IB_FEC_OVERRIDE_ADMIN_HDR);
    SX_GET_REG_FIELD(pplm_reg->ib_fec_override_admin_ndr, outbox, REG_IB_FEC_OVERRIDE_ADMIN_NDR);
    SX_GET_REG_FIELD(pplm_reg->ib_fec_override_admin_xdr, outbox, REG_IB_FEC_OVERRIDE_ADMIN_XDR);
    return 0;
}

int sx_ACCESS_REG_PPLM(struct sx_dev *dev, struct ku_access_pplm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPLM_encode,
                                  __PPLM_decode,
                                  PPLM_REG_LEN,
                                  &reg_data->pplm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPLM);


/************************************************
 * PLPC
 ***********************************************/
#define REG_PROFILE_ID_OFFSET                   0x14
#define REG_PLPC_PROTO_MASK_OFFSET              0x16
#define REG_LANE_SPEED_OFFSET                   0x1A
#define REG_LPBF_OFFSET                         0x1E
#define REG_FEC_MODE_POLICY_OFFSET              0x1F
#define REG_RETRANSMISSION_CAPABILITY_OFFSET    0x20
#define REG_FEC_MODE_CAPABILITY_OFFSET          0x21
#define REG_RETRANSMISSION_SUPPORT_ADMIN_OFFSET 0x24
#define REG_FEC_MODE_SUPPORT_ADMIN_OFFSET       0x25
#define REG_RETRANSMISSION_REQUEST_ADMIN_OFFSET 0x28
#define REG_FEC_MODE_REQUEST_ADMIN_OFFSET       0x29
#define PLPC_REG_LEN                            0xB

static int __PLPC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_plpc_reg *plpc_reg = (struct ku_plpc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, plpc_reg->profile_id, REG_PROFILE_ID_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->proto_mask, REG_PLPC_PROTO_MASK_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->lane_speed, REG_LANE_SPEED_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->lpbf, REG_LPBF_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->fec_mode_policy, REG_FEC_MODE_POLICY_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->retransmission_capability, REG_RETRANSMISSION_CAPABILITY_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->fec_mode_capability, REG_FEC_MODE_CAPABILITY_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->retransmission_support_admin, REG_RETRANSMISSION_SUPPORT_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->fec_mode_support_admin, REG_FEC_MODE_SUPPORT_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->retransmission_request_admin, REG_RETRANSMISSION_REQUEST_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->fec_mode_request_admin, REG_FEC_MODE_REQUEST_ADMIN_OFFSET);
    return 0;
}

static int __PLPC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_plpc_reg *plpc_reg = (struct ku_plpc_reg*)ku_reg;

    SX_GET_REG_FIELD(plpc_reg->profile_id, outbox, REG_PROFILE_ID_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->proto_mask, outbox, REG_PLPC_PROTO_MASK_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->lane_speed, outbox, REG_LANE_SPEED_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->lpbf, outbox, REG_LPBF_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->fec_mode_policy, outbox, REG_FEC_MODE_POLICY_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->retransmission_capability, outbox, REG_RETRANSMISSION_CAPABILITY_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->fec_mode_capability, outbox, REG_FEC_MODE_CAPABILITY_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->retransmission_support_admin, outbox, REG_RETRANSMISSION_SUPPORT_ADMIN_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->fec_mode_support_admin, outbox, REG_FEC_MODE_SUPPORT_ADMIN_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->retransmission_request_admin, outbox, REG_RETRANSMISSION_REQUEST_ADMIN_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->fec_mode_request_admin, outbox, REG_FEC_MODE_REQUEST_ADMIN_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PLPC(struct sx_dev *dev, struct ku_access_plpc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PLPC_encode,
                                  __PLPC_decode,
                                  PLPC_REG_LEN,
                                  &reg_data->plpc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PLPC);


/************************************************
 * PMPC
 ***********************************************/
#define REG_MODULE_STATE_UPDATED_OFFSET 0x14
#define PMPC_REG_LEN                    0x09

static int __PMPC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmpc_reg *pmpc_reg = (struct ku_pmpc_reg*)ku_reg;
    int                 i;

    for (i = 0; i < 8; i++) {
        SX_PUT_REG_FIELD(inbox, pmpc_reg->module_state_updated_bitmap[i], REG_MODULE_STATE_UPDATED_OFFSET + (i * 4));
    }

    return 0;
}

static int __PMPC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmpc_reg *pmpc_reg = (struct ku_pmpc_reg*)ku_reg;
    int                 i;

    for (i = 0; i < 8; i++) {
        SX_GET_REG_FIELD(pmpc_reg->module_state_updated_bitmap[i], outbox, REG_MODULE_STATE_UPDATED_OFFSET + (i * 4));
    }

    return 0;
}

int sx_ACCESS_REG_PMPC(struct sx_dev *dev, struct ku_access_pmpc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMPC_encode,
                                  __PMPC_decode,
                                  PMPC_REG_LEN,
                                  &reg_data->pmpc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMPC);


/************************************************
 * PMPR
 ***********************************************/
#define PMPR_REG_MODULE_OFFSET          0x15
#define PMPR_REG_ATTENUATION_5G_OFFSET  0x1B
#define PMPR_REG_ATTENUATION_7G_OFFSET  0x1F
#define PMPR_REG_ATTENUATION_12G_OFFSET 0x23
#define PMPR_REG_LEN                    0x05

static int __PMPR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmpr_reg *pmpr_reg = (struct ku_pmpr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pmpr_reg->module, PMPR_REG_MODULE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmpr_reg->attenuation5g, PMPR_REG_ATTENUATION_5G_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmpr_reg->attenuation7g, PMPR_REG_ATTENUATION_7G_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmpr_reg->attenuation12g, PMPR_REG_ATTENUATION_12G_OFFSET);
    return 0;
}

static int __PMPR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmpr_reg *pmpr_reg = (struct ku_pmpr_reg*)ku_reg;

    SX_GET_REG_FIELD(pmpr_reg->module, outbox, PMPR_REG_MODULE_OFFSET);
    SX_GET_REG_FIELD(pmpr_reg->attenuation5g, outbox, PMPR_REG_ATTENUATION_5G_OFFSET);
    SX_GET_REG_FIELD(pmpr_reg->attenuation7g, outbox, PMPR_REG_ATTENUATION_7G_OFFSET);
    SX_GET_REG_FIELD(pmpr_reg->attenuation12g, outbox, PMPR_REG_ATTENUATION_12G_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PMPR(struct sx_dev *dev, struct ku_access_pmpr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMPR_encode,
                                  __PMPR_decode,
                                  PMPR_REG_LEN,
                                  &reg_data->pmpr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMPR);

/************************************************
 *
 * PELC
 ***********************************************/
#define REG_PELC_OP_OFFSET             0x14
#define REG_PELC_LOCAL_PORT_OFFSET     0x15
#define REG_PELC_LOCAL_PORT_MSB_OFFSET 0x16
/* 0x17 reserved not in use */

#define REG_PELC_OP_ADMIN_OFFSET      0x18
#define REG_PELC_OP_CAPABILITY_OFFSET 0x19
#define REG_PELC_OP_REQUEST_OFFSET    0x1a
#define REG_PELC_OP_ACTIVE_OFFSET     0x1b

#define REG_PELC_ADMIN_OFFSET      0x1c
#define REG_PELC_CAPABILITY_OFFSET 0x24
#define REG_PELC_REQUEST_OFFSET    0x2c
#define REG_PELC_ACTIVE_OFFSET     0x34
#define PELC_REG_LEN               0x0b

static int __PELC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pelc_reg *pelc_reg = (struct ku_pelc_reg*)ku_reg;
    u8                  tmp_u8 = 0;

    tmp_u8 = pelc_reg->op << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_PELC_OP_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->local_port, REG_PELC_LOCAL_PORT_OFFSET);
    tmp_u8 = (pelc_reg->lp_msb & 0x03) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_PELC_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->op_admin, REG_PELC_OP_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->op_capability, REG_PELC_OP_CAPABILITY_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->op_request, REG_PELC_OP_REQUEST_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->op_active, REG_PELC_OP_ACTIVE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->admin, REG_PELC_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->capability, REG_PELC_CAPABILITY_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->request, REG_PELC_REQUEST_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->active, REG_PELC_ACTIVE_OFFSET);
    return 0;
}

static int __PELC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pelc_reg *pelc_reg = (struct ku_pelc_reg*)ku_reg;

    SX_GET_REG_FIELD(pelc_reg->op, outbox, REG_PELC_OP_OFFSET);
    pelc_reg->op >>= 4;
    SX_GET_REG_FIELD(pelc_reg->local_port, outbox, REG_PELC_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->lp_msb, outbox, REG_PELC_LOCAL_PORT_MSB_OFFSET);
    pelc_reg->lp_msb >>= 4;
    pelc_reg->lp_msb &= 0x3;
    SX_GET_REG_FIELD(pelc_reg->op_admin, outbox, REG_PELC_OP_ADMIN_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->op_capability, outbox, REG_PELC_OP_CAPABILITY_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->op_request, outbox, REG_PELC_OP_REQUEST_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->op_active, outbox, REG_PELC_OP_ACTIVE_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->admin, outbox, REG_PELC_ADMIN_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->capability, outbox, REG_PELC_CAPABILITY_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->request, outbox, REG_PELC_REQUEST_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->active, outbox, REG_PELC_ACTIVE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PELC(struct sx_dev *dev, struct ku_access_pelc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PELC_encode,
                                  __PELC_decode,
                                  PELC_REG_LEN,
                                  &reg_data->pelc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PELC);


/************************************************
 * PVLC
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET     0x15
#define REG_VL_CAP_OFFSET         0x1b
#define REG_VL_ADMIN_OFFSET       0x1f
#define REG_VL_OPERATIONAL_OFFSET 0x23
#define PVLC_REG_LEN              0x05

static int __PVLC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pvlc_reg *pvlc_reg = (struct ku_pvlc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pvlc_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pvlc_reg->vl_cap, REG_VL_CAP_OFFSET);
    SX_PUT_REG_FIELD(inbox, pvlc_reg->vl_admin, REG_VL_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, pvlc_reg->vl_operational, REG_VL_OPERATIONAL_OFFSET);
    return 0;
}

static int __PVLC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pvlc_reg *pvlc_reg = (struct ku_pvlc_reg*)ku_reg;

    SX_GET_REG_FIELD(pvlc_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pvlc_reg->vl_cap, outbox, REG_VL_CAP_OFFSET);
    SX_GET_REG_FIELD(pvlc_reg->vl_admin, outbox, REG_VL_ADMIN_OFFSET);
    SX_GET_REG_FIELD(pvlc_reg->vl_operational, outbox, REG_VL_OPERATIONAL_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PVLC(struct sx_dev *dev, struct ku_access_pvlc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PVLC_encode,
                                  __PVLC_decode,
                                  PVLC_REG_LEN,
                                  &reg_data->pvlc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PVLC);


/************************************************
 * MCIA
 ***********************************************/
#define REG_L_OFFSET                  0x14
#define REG_MODULE_OFFSET             0x15
#define REG_SLOT_INDEX_OFFSET         0x16
#define REG_STATUS_OFFSET             0x17
#define REG_I2C_DEVICE_ADDRESS_OFFSET 0x18
#define REG_PAGE_NUMBER_OFFSET        0x19
#define REG_DEVICE_ADDRESS_OFFSET     0x1a
#define REG_SIZE_OFFSET               0x1e
#define REG_DWORD_0_OFFSET            0x24
#define REG_DWORD_1_OFFSET            0x28
#define REG_DWORD_2_OFFSET            0x2c
#define REG_DWORD_3_OFFSET            0x30
#define REG_DWORD_4_OFFSET            0x34
#define REG_DWORD_5_OFFSET            0x38
#define REG_DWORD_6_OFFSET            0x3c
#define REG_DWORD_7_OFFSET            0x40
#define REG_DWORD_8_OFFSET            0x44
#define REG_DWORD_9_OFFSET            0x48
#define REG_DWORD_10_OFFSET           0x4c
#define REG_DWORD_11_OFFSET           0x50
#define MCIA_REG_LEN                  0x11

static int __MCIA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcia_reg *mcia_reg = (struct ku_mcia_reg*)ku_reg;
    u8                  tmp_u8 = 0;

    tmp_u8 = (mcia_reg->l & 0x1) << 7;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_L_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->module, REG_MODULE_OFFSET);
    tmp_u8 = (mcia_reg->slot_index & 0x0F) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_SLOT_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->i2c_device_address, REG_I2C_DEVICE_ADDRESS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->page_number, REG_PAGE_NUMBER_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->device_address, REG_DEVICE_ADDRESS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->size, REG_SIZE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_0, REG_DWORD_0_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_1, REG_DWORD_1_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_2, REG_DWORD_2_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_3, REG_DWORD_3_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_4, REG_DWORD_4_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_5, REG_DWORD_5_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_6, REG_DWORD_6_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_7, REG_DWORD_7_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_8, REG_DWORD_8_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_9, REG_DWORD_9_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_10, REG_DWORD_10_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_11, REG_DWORD_11_OFFSET);
    return 0;
}

static int __MCIA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcia_reg *mcia_reg = (struct ku_mcia_reg*)ku_reg;
    u8                  tmp_u8 = 0;

    SX_GET_REG_FIELD(tmp_u8, outbox, REG_L_OFFSET);
    mcia_reg->l = tmp_u8 >> 7;
    SX_GET_REG_FIELD(mcia_reg->module, outbox, REG_MODULE_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, REG_SLOT_INDEX_OFFSET);
    mcia_reg->slot_index = tmp_u8 >> 4;
    SX_GET_REG_FIELD(mcia_reg->status, outbox, REG_STATUS_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->i2c_device_address, outbox, REG_I2C_DEVICE_ADDRESS_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->page_number, outbox, REG_PAGE_NUMBER_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->device_address, outbox, REG_DEVICE_ADDRESS_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->size, outbox, REG_SIZE_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_0, outbox, REG_DWORD_0_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_1, outbox, REG_DWORD_1_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_2, outbox, REG_DWORD_2_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_3, outbox, REG_DWORD_3_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_4, outbox, REG_DWORD_4_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_5, outbox, REG_DWORD_5_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_6, outbox, REG_DWORD_6_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_7, outbox, REG_DWORD_7_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_8, outbox, REG_DWORD_8_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_9, outbox, REG_DWORD_9_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_10, outbox, REG_DWORD_10_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_11, outbox, REG_DWORD_11_OFFSET);
    return 0;
}

static const char * __mcia_err_str(u8 status)
{
    switch (status) {
    case 0:
        return "Ok";

    case 1:
        return "No EEPROM Module";

    case 2:
        return "Module not supported";

    case 3:
        return "Module not connected";

    case 4:
        return "Invalid module type";

    case 5:
        return "Module not accessible";

    case 9:
        return "I2C error";

    case 16:
        return "Module disabled";

    case 17:
        return "Page access failed";

    default:
        break;
    }

    return "N/A";
}

int sx_ACCESS_REG_MCIA(struct sx_dev *dev, struct ku_access_mcia_reg *reg_data)
{
    const char *err_msg = NULL;
    int         err = sx_ACCESS_REG_internal(dev,
                                             reg_data->dev_id,
                                             0,
                                             &reg_data->op_tlv,
                                             __MCIA_encode,
                                             __MCIA_decode,
                                             MCIA_REG_LEN,
                                             &reg_data->mcia_reg,
                                             NULL);

    if (!err && reg_data->op_tlv.status &&
        (reg_data->op_tlv.status != SX_EMAD_STATUS_BUSY_E) &&
        (reg_data->op_tlv.status != SX_EMAD_STATUS_ISSU_ONGOING_E)) {
        err_msg = __mcia_err_str(reg_data->mcia_reg.status);

        printk(KERN_WARNING "MCIA failed (fw_err=%u, mcia_status=%u ['%s'])\n",
               reg_data->op_tlv.status,
               reg_data->mcia_reg.status,
               err_msg);
    }

    return err;
}
EXPORT_SYMBOL(sx_ACCESS_REG_MCIA);

/************************************************
 * HPKT
 ***********************************************/
#define REG_ACK_BITN         24
#define REG_ACTION_BITN      20
#define REG_TRAP_GROUP_BITN  12
#define REG_TRAP_INFO_OFFSET 0x14
#define REG_HPKT_CTRL_OFFSET 0x19
#define HPKT_REG_LEN         0x05

static int __HPKT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hpkt_reg *hpkt_reg = (struct ku_hpkt_reg*)ku_reg;
    u32                 trap_info;

    trap_info = ((u32)(hpkt_reg->ack) & 0x1) << REG_ACK_BITN;
    trap_info |= ((u32)(hpkt_reg->action) & 0xF) << REG_ACTION_BITN;
    trap_info |= ((u32)(hpkt_reg->trap_group) & 0x3f) << REG_TRAP_GROUP_BITN;
    trap_info |= (u32)(hpkt_reg->trap_id) & 0x3FF;
    SX_PUT_REG_FIELD(inbox, trap_info, REG_TRAP_INFO_OFFSET);
    SX_PUT_REG_FIELD(inbox, hpkt_reg->control, REG_HPKT_CTRL_OFFSET);
    return 0;
}

static int __HPKT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hpkt_reg *hpkt_reg = (struct ku_hpkt_reg*)ku_reg;
    u32                 trap_info;

    SX_GET_REG_FIELD(trap_info, outbox, REG_TRAP_INFO_OFFSET);
    hpkt_reg->ack = (trap_info >> REG_ACK_BITN) & 0x1;
    hpkt_reg->action = (trap_info >> REG_ACTION_BITN) & 0xF;
    hpkt_reg->trap_group = (trap_info >> REG_TRAP_GROUP_BITN) & 0x3F;
    hpkt_reg->trap_id = trap_info & 0x3FF;
    SX_GET_REG_FIELD(hpkt_reg->control, outbox, REG_HPKT_CTRL_OFFSET);
    return 0;
}

int sx_ACCESS_REG_HPKT(struct sx_dev *dev, struct ku_access_hpkt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HPKT_encode,
                                  __HPKT_decode,
                                  HPKT_REG_LEN,
                                  &reg_data->hpkt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HPKT);


/************************************************
 * HCAP
 ***********************************************/
#define REG_MAX_CPU_EGRESS_TCS_OFFSET  0x1b
#define REG_MAX_CPU_INGRESS_TCS_OFFSET 0x1f
#define REG_MAX_TRAP_GROUPS_OFFSET     0x23
#define REG_DR_PATHS_OFFSET            0x27
#define HCAP_REG_LEN                   0x09

static int __HCAP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hcap_reg *hcap_reg = (struct ku_hcap_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, hcap_reg->max_cpu_egress_tclass, REG_MAX_CPU_EGRESS_TCS_OFFSET);
    SX_PUT_REG_FIELD(inbox, hcap_reg->max_cpu_ingress_tclass, REG_MAX_CPU_INGRESS_TCS_OFFSET);
    SX_PUT_REG_FIELD(inbox, hcap_reg->max_num_trap_groups, REG_MAX_TRAP_GROUPS_OFFSET);
    SX_PUT_REG_FIELD(inbox, hcap_reg->max_num_dr_paths, REG_DR_PATHS_OFFSET);
    return 0;
}

static int __HCAP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hcap_reg *hcap_reg = (struct ku_hcap_reg*)ku_reg;

    SX_GET_REG_FIELD(hcap_reg->max_cpu_egress_tclass, outbox, REG_MAX_CPU_EGRESS_TCS_OFFSET);
    SX_GET_REG_FIELD(hcap_reg->max_cpu_ingress_tclass, outbox, REG_MAX_CPU_INGRESS_TCS_OFFSET);
    SX_GET_REG_FIELD(hcap_reg->max_num_trap_groups, outbox, REG_MAX_TRAP_GROUPS_OFFSET);
    SX_GET_REG_FIELD(hcap_reg->max_num_dr_paths, outbox, REG_DR_PATHS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_HCAP(struct sx_dev *dev, struct ku_access_hcap_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HCAP_encode,
                                  __HCAP_decode,
                                  HCAP_REG_LEN,
                                  &reg_data->hcap_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HCAP);


/************************************************
 * MFSC
 ***********************************************/
#define REG_FAN_OFFSET 0x14
#define REG_PWM_OFFSET 0x1b
#define MFSC_REG_LEN   0x3

static int __MFSC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfsc_reg *mfsc_reg = (struct ku_mfsc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mfsc_reg->pwm, REG_FAN_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsc_reg->pwm_duty_cycle, REG_PWM_OFFSET);
    return 0;
}

static int __MFSC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfsc_reg *mfsc_reg = (struct ku_mfsc_reg*)ku_reg;

    SX_GET_REG_FIELD(mfsc_reg->pwm, outbox, REG_FAN_OFFSET);
    SX_GET_REG_FIELD(mfsc_reg->pwm_duty_cycle, outbox, REG_PWM_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFSC(struct sx_dev *dev, struct ku_access_mfsc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFSC_encode,
                                  __MFSC_decode,
                                  MFSC_REG_LEN,
                                  &reg_data->mfsc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFSC);


/************************************************
 * MFSM
 ***********************************************/
#define REG_TACHO_OFFSET 0x14
#define REG_N_OFFSET     0x17
#define REG_RPM_OFFSET   0x1a
#define MFSM_REG_LEN     0x3

static int __MFSM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfsm_reg *mfsm_reg = (struct ku_mfsm_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mfsm_reg->tacho, REG_TACHO_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsm_reg->n, REG_N_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsm_reg->rpm, REG_RPM_OFFSET);
    return 0;
}

static int __MFSM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfsm_reg *mfsm_reg = (struct ku_mfsm_reg*)ku_reg;

    SX_GET_REG_FIELD(mfsm_reg->tacho, outbox, REG_TACHO_OFFSET);
    SX_GET_REG_FIELD(mfsm_reg->n, outbox, REG_N_OFFSET);
    SX_GET_REG_FIELD(mfsm_reg->rpm, outbox, REG_RPM_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFSM(struct sx_dev *dev, struct ku_access_mfsm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFSM_encode,
                                  __MFSM_decode,
                                  MFSM_REG_LEN,
                                  &reg_data->mfsm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFSM);


/************************************************
 * MFSL
 ***********************************************/
#define REG_FAN_OFFSET      0x14
#define REG_EE_SHIFT        2
#define REG_FLAGS_OFFSET    0x17
#define REG_TACH_MIN_OFFSET 0x1a
#define REG_TACH_MAX_OFFSET 0x1e
#define MFSL_REG_LEN        0x3

static int __MFSL_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfsl_reg *mfsl_reg = (struct ku_mfsl_reg*)ku_reg;
    u8                  flags;

    SX_PUT_REG_FIELD(inbox, mfsl_reg->fan, REG_FAN_OFFSET);
    flags = (mfsl_reg->ee << REG_EE_SHIFT);
    flags |= mfsl_reg->ie;
    SX_PUT_REG_FIELD(inbox, flags, REG_FLAGS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsl_reg->tach_min, REG_TACH_MIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsl_reg->tach_max, REG_TACH_MAX_OFFSET);
    return 0;
}

static int __MFSL_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfsl_reg *mfsl_reg = (struct ku_mfsl_reg*)ku_reg;
    u8                  flags;

    SX_GET_REG_FIELD(mfsl_reg->fan, outbox, REG_FAN_OFFSET);
    SX_GET_REG_FIELD(flags, outbox, REG_FLAGS_OFFSET);
    mfsl_reg->ee = (flags >> REG_EE_SHIFT) & 0x3;
    mfsl_reg->ie = flags & 0x1;
    SX_GET_REG_FIELD(mfsl_reg->tach_min, outbox, REG_TACH_MIN_OFFSET);
    SX_GET_REG_FIELD(mfsl_reg->tach_max, outbox, REG_TACH_MAX_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFSL(struct sx_dev *dev, struct ku_access_mfsl_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFSL_encode,
                                  __MFSL_decode,
                                  MFSL_REG_LEN,
                                  &reg_data->mfsl_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFSL);


/************************************************
 * HDRT
 ***********************************************/
#define REG_DR_INDEX_OFFSET    0x14
#define REG_HOP_CNT_OFFSET     0x16
#define REG_FIRST_PATH_OFFSET  0x18
#define REG_NUM_OF_PATHS       0x40
#define REG_FIRST_RPATH_OFFSET (REG_FIRST_PATH_OFFSET + REG_NUM_OF_PATHS)
#define HDRT_REG_LEN           0x17

static int __HDRT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hdrt_reg *hdrt_reg = (struct ku_hdrt_reg*)ku_reg;
    int                 i;

    SX_PUT_REG_FIELD(inbox, hdrt_reg->dr_index, REG_DR_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, hdrt_reg->hop_cnt, REG_HOP_CNT_OFFSET);
    for (i = 0; i < REG_NUM_OF_PATHS; i++) {
        SX_PUT_REG_FIELD(inbox, hdrt_reg->path[i], REG_FIRST_PATH_OFFSET + i);
    }

    for (i = 0; i < REG_NUM_OF_PATHS; i++) {
        SX_PUT_REG_FIELD(inbox, hdrt_reg->rpath[i], REG_FIRST_RPATH_OFFSET + i);
    }

    return 0;
}

static int __HDRT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hdrt_reg *hdrt_reg = (struct ku_hdrt_reg*)ku_reg;
    int                 i;

    SX_GET_REG_FIELD(hdrt_reg->dr_index, outbox, REG_DR_INDEX_OFFSET);
    SX_GET_REG_FIELD(hdrt_reg->hop_cnt, outbox, REG_HOP_CNT_OFFSET);
    for (i = 0; i < REG_NUM_OF_PATHS; i++) {
        SX_GET_REG_FIELD(hdrt_reg->path[i], outbox, REG_FIRST_PATH_OFFSET + i);
    }

    for (i = 0; i < REG_NUM_OF_PATHS; i++) {
        SX_GET_REG_FIELD(hdrt_reg->rpath[i], outbox, REG_FIRST_RPATH_OFFSET + i);
    }

    return 0;
}

int sx_ACCESS_REG_HDRT(struct sx_dev *dev, struct ku_access_hdrt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HDRT_encode,
                                  __HDRT_decode,
                                  HDRT_REG_LEN,
                                  &reg_data->hdrt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HDRT);


/************************************************
 * MTBR
 ***********************************************/
#define REG_BASE_SENSOR_INDEX_OFFSET 0x16
#define REG_MTBR_SLOT_INDEX_OFFSET   0x15
#define REG_NUM_REC_OFFSET           0x1b
#define REG_TEMP_RECORD_OFFSET       0x24
#define REG_TEMP_IN_REC_OFFSET       0x26

static int __MTBR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtbr_reg *mtbr_reg = (struct ku_mtbr_reg*)ku_reg;
    u8                  slot_idx;
    u16                 tmp_idx;

    slot_idx = mtbr_reg->slot_index & 0xF;
    tmp_idx = mtbr_reg->base_sensor_index & 0xFFF;
    SX_PUT_REG_FIELD(inbox, slot_idx, REG_MTBR_SLOT_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, tmp_idx, REG_BASE_SENSOR_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtbr_reg->num_rec, REG_NUM_REC_OFFSET);
    return 0;
}

static int __MTBR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtbr_reg *mtbr_reg = (struct ku_mtbr_reg*)ku_reg;
    int                 counter;
    u8                  slot_idx;
    u16                 tmp_idx;

    SX_GET_REG_FIELD(slot_idx, outbox, REG_MTBR_SLOT_INDEX_OFFSET);
    mtbr_reg->slot_index = slot_idx & 0xF;
    SX_GET_REG_FIELD(tmp_idx, outbox, REG_BASE_SENSOR_INDEX_OFFSET);
    mtbr_reg->base_sensor_index = tmp_idx & 0xFFF;
    SX_GET_REG_FIELD(mtbr_reg->num_rec, outbox, REG_NUM_REC_OFFSET);
    if (mtbr_reg->num_rec > MTBR_MAX_TEMPERATURE_RECORDS) {
        printk(KERN_ERR PFX "response MTBR num_rec %d is greater than max records %d.\n",
               mtbr_reg->num_rec, MTBR_MAX_TEMPERATURE_RECORDS);
        return -EINVAL;
    }
    for (counter = 0; counter < mtbr_reg->num_rec; counter++) {
        SX_GET_REG_FIELD(mtbr_reg->temperature_record[counter].max_temperature,
                         outbox,
                         REG_TEMP_RECORD_OFFSET + (counter * sizeof(mtbr_reg->temperature_record[0])));
        SX_GET_REG_FIELD(mtbr_reg->temperature_record[counter].temperature,
                         outbox,
                         REG_TEMP_IN_REC_OFFSET + (counter * sizeof(mtbr_reg->temperature_record[0])));
    }

    return 0;
}

int sx_ACCESS_REG_MTBR(struct sx_dev *dev, struct ku_access_mtbr_reg *reg_data)
{
    u16 mtbr_len;

    if (reg_data->mtbr_reg.num_rec > MTBR_MAX_TEMPERATURE_RECORDS) {
        printk(KERN_ERR PFX "request MTBR num_rec %d is greater than max records %d.\n",
               reg_data->mtbr_reg.num_rec, MTBR_MAX_TEMPERATURE_RECORDS);
        return -EINVAL;
    }

    /* records + 5 lines according to PRM */
    mtbr_len = 5 + reg_data->mtbr_reg.num_rec;

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTBR_encode,
                                  __MTBR_decode,
                                  mtbr_len,
                                  &reg_data->mtbr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTBR);


/************************************************
 * MMDIO
 ***********************************************/
#define REG_MDIO_INDEX_OFFSET 0x15
#define REG_OPERATION_OFFSET  0x17
#define REG_ADDRESS_OFFSET    0x18
#define REG_DATA_OFFSET       0x1c
#define MMDIO_REG_LEN         0x4

static int __MMDIO_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mmdio_reg *mmdio_reg = (struct ku_mmdio_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mmdio_reg->mdio_index, REG_MDIO_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, mmdio_reg->operation, REG_OPERATION_OFFSET);
    SX_PUT_REG_FIELD(inbox, mmdio_reg->address, REG_ADDRESS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mmdio_reg->data, REG_DATA_OFFSET);
    return 0;
}

static int __MMDIO_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mmdio_reg *mmdio_reg = (struct ku_mmdio_reg*)ku_reg;

    SX_GET_REG_FIELD(mmdio_reg->mdio_index, outbox, REG_MDIO_INDEX_OFFSET);
    SX_GET_REG_FIELD(mmdio_reg->operation, outbox, REG_OPERATION_OFFSET);
    SX_GET_REG_FIELD(mmdio_reg->address, outbox, REG_ADDRESS_OFFSET);
    SX_GET_REG_FIELD(mmdio_reg->data, outbox, REG_DATA_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MMDIO(struct sx_dev *dev, struct ku_access_mmdio_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MMDIO_encode,
                                  __MMDIO_decode,
                                  MMDIO_REG_LEN,
                                  &reg_data->mmdio_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MMDIO);


/************************************************
 * MMIA
 ***********************************************/
#define REG_OPERATION_OFFSET 0x17
#define REG_DATA_OFFSET      0x1c
#define MMIA_REG_LEN         0x4

static int __MMIA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mmia_reg *mmia_reg = (struct ku_mmia_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mmia_reg->operation, REG_OPERATION_OFFSET);
    SX_PUT_REG_FIELD(inbox, mmia_reg->data, REG_DATA_OFFSET);
    return 0;
}

static int __MMIA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mmia_reg *mmia_reg = (struct ku_mmia_reg*)ku_reg;

    SX_GET_REG_FIELD(mmia_reg->operation, outbox, REG_OPERATION_OFFSET);
    SX_GET_REG_FIELD(mmia_reg->data, outbox, REG_DATA_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MMIA(struct sx_dev *dev, struct ku_access_mmia_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MMIA_encode,
                                  __MMIA_decode,
                                  MMIA_REG_LEN,
                                  &reg_data->mmia_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MMIA);


/************************************************
 * MFPA
 ***********************************************/
#define REG_P_OFFSET                0x16
#define REG_FS_OFFSET               0x17
#define REG_FS_BITS_SHIFT           4
#define REG_BOOT_ADDRESS_OFFSET     0x18
#define REG_FLASH_NUM_OFFSET        0x27
#define REG_JEDEC_ID_OFFSET         0x28
#define REG_BLOCK_ALLIGNMENT_OFFSET 0x2d
#define REG_SECTOR_SIZE_OFFSET      0x2f
#define REG_CAPABILITY_MASK_OFFSET  0x30
#define REG_CAPABILITY_MASK_BIT_N   7
#define MFPA_REG_LEN                0x40

static int __MFPA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfpa_reg *mfpa_reg = (struct ku_mfpa_reg*)ku_reg;
    u8                  flag;

    SX_PUT_REG_FIELD(inbox, mfpa_reg->p, REG_P_OFFSET);
    flag = (u8)(mfpa_reg->fs << REG_FS_BITS_SHIFT);
    SX_PUT_REG_FIELD(inbox, flag, REG_FS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfpa_reg->boot_address, REG_BOOT_ADDRESS_OFFSET);
    return 0;
}

static int __MFPA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfpa_reg *mfpa_reg = (struct ku_mfpa_reg*)ku_reg;
    u8                  flag;

    SX_GET_REG_FIELD(mfpa_reg->p, outbox, REG_P_OFFSET);
    SX_GET_REG_FIELD(flag, outbox, REG_FS_OFFSET);
    mfpa_reg->fs = (u8)(flag >> REG_FS_BITS_SHIFT);
    SX_GET_REG_FIELD(mfpa_reg->boot_address, outbox, REG_BOOT_ADDRESS_OFFSET);
    SX_GET_REG_FIELD(mfpa_reg->flash_num, outbox, REG_FLASH_NUM_OFFSET);
    SX_GET_REG_FIELD(mfpa_reg->jedec_id, outbox, REG_JEDEC_ID_OFFSET);
    SX_GET_REG_FIELD(mfpa_reg->block_allignment, outbox, REG_BLOCK_ALLIGNMENT_OFFSET);
    SX_GET_REG_FIELD(mfpa_reg->sector_size, outbox, REG_SECTOR_SIZE_OFFSET);
    SX_GET_REG_FIELD(flag, outbox, REG_CAPABILITY_MASK_OFFSET);
    mfpa_reg->capability_mask = (u8)(flag >> REG_CAPABILITY_MASK_BIT_N);
    return 0;
}

int sx_ACCESS_REG_MFPA(struct sx_dev *dev, struct ku_access_mfpa_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFPA_encode,
                                  __MFPA_decode,
                                  MFPA_REG_LEN,
                                  &reg_data->mfpa_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFPA);


/************************************************
 * MFBE
 ***********************************************/
#define REG_P_OFFSET            0x16
#define REG_FS_OFFSET           0x17
#define REG_FS_BITS_SHIFT       4
#define REG_MFBE_ADDRESS_OFFSET 0x1c
#define MFBE_REG_LEN            0x4

static int __MFBE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfbe_reg *mfbe_reg = (struct ku_mfbe_reg*)ku_reg;
    u8                  flag;

    SX_PUT_REG_FIELD(inbox, mfbe_reg->p, REG_P_OFFSET);
    flag = (u8)(mfbe_reg->fs << REG_FS_BITS_SHIFT);
    SX_PUT_REG_FIELD(inbox, flag, REG_FS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfbe_reg->address, REG_MFBE_ADDRESS_OFFSET);
    return 0;
}

static int __MFBE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfbe_reg *mfbe_reg = (struct ku_mfbe_reg*)ku_reg;
    u8                  flag;

    SX_GET_REG_FIELD(mfbe_reg->p, outbox, REG_P_OFFSET);
    SX_GET_REG_FIELD(flag, outbox, REG_FS_OFFSET);
    mfbe_reg->fs = (u8)(flag >> REG_FS_BITS_SHIFT);
    SX_GET_REG_FIELD(mfbe_reg->address, outbox, REG_MFBE_ADDRESS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFBE(struct sx_dev *dev, struct ku_access_mfbe_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFBE_encode,
                                  __MFBE_decode,
                                  MFBE_REG_LEN,
                                  &reg_data->mfbe_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFBE);


/************************************************
 * MFBA
 ***********************************************/
#define REG_P_OFFSET            0x16
#define REG_FS_OFFSET           0x17
#define REG_FS_BITS_SHIFT       4
#define REG_MFBA_SIZE_OFFSET    0x1a
#define REG_MFBA_ADDRESS_OFFSET 0x1c
#define REG_MFBA_DATA_OFFSET    0x20
#define MFBA_REG_LEN            0x40

static int __MFBA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfba_reg *mfba_reg = (struct ku_mfba_reg*)ku_reg;
    u8                  flag;
    int                 i;

    SX_PUT_REG_FIELD(inbox, mfba_reg->p, REG_P_OFFSET);
    flag = (u8)(mfba_reg->fs << REG_FS_BITS_SHIFT);
    SX_PUT_REG_FIELD(inbox, flag, REG_FS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfba_reg->size, REG_MFBA_SIZE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfba_reg->address, REG_MFBA_ADDRESS_OFFSET);
    for (i = 0; i < 192; i++) {
        SX_PUT_REG_FIELD(inbox, mfba_reg->data[i], REG_MFBA_DATA_OFFSET + i);
    }

    return 0;
}

static int __MFBA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfba_reg *mfba_reg = (struct ku_mfba_reg*)ku_reg;
    u8                  flag;
    int                 i;

    SX_GET_REG_FIELD(mfba_reg->p, outbox, REG_P_OFFSET);
    SX_GET_REG_FIELD(flag, outbox, REG_FS_OFFSET);
    mfba_reg->fs = (u8)(flag >> REG_FS_BITS_SHIFT);
    SX_GET_REG_FIELD(mfba_reg->size, outbox, REG_MFBA_SIZE_OFFSET);
    SX_GET_REG_FIELD(mfba_reg->address, outbox, REG_MFBA_ADDRESS_OFFSET);
    for (i = 0; i < 192; i++) {
        SX_GET_REG_FIELD(mfba_reg->data[i], outbox, REG_MFBA_DATA_OFFSET + i);
    }

    return 0;
}

int sx_ACCESS_REG_MFBA(struct sx_dev *dev, struct ku_access_mfba_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFBA_encode,
                                  __MFBA_decode,
                                  MFBA_REG_LEN,
                                  &reg_data->mfba_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFBA);


/************************************************
 * RAW
 ***********************************************/
#define OP_TLV_SIZE 0x10

static int __RAW_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_raw_reg *raw_reg = (struct ku_raw_reg*)ku_reg;

    return copy_from_user(inbox, raw_reg->buff, raw_reg->size);
}

static int __RAW_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_raw_reg *raw_reg = (struct ku_raw_reg*)ku_reg;

    return copy_to_user(raw_reg->buff, outbox, raw_reg->size);
}

int sx_ACCESS_REG_RAW(struct sx_dev *dev, struct ku_access_raw_reg *reg_data)
{
    u16 reg_len;

    if (SX_MAILBOX_SIZE < OP_TLV_SIZE + reg_data->raw_reg.size) {
        sx_warn(dev, "Cannot send the raw register access request "
                "since the mailbox size %d is too small (need %d)\n",
                SX_MAILBOX_SIZE, OP_TLV_SIZE + reg_data->raw_reg.size);
        return -ENOMEM;
    }

    reg_len = reg_data->raw_reg.size / 4 + 1;

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  SX_ACCESS_REG_F_SET_AND_GET,
                                  &reg_data->op_tlv,
                                  __RAW_encode,
                                  __RAW_decode,
                                  reg_len,
                                  &reg_data->raw_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RAW);


/************************************************
 * FORE
 ***********************************************/
#define REG_FAN_UNDER_LIMIT_OFFSET 0x14
#define REG_FAN_OVER_LIMIT_OFFSET  0x18
#define FORE_REG_LEN               0x4

static int __FORE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_fore_reg *fore_reg = (struct ku_fore_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, fore_reg->fan_under_limit, REG_FAN_UNDER_LIMIT_OFFSET);
    SX_PUT_REG_FIELD(inbox, fore_reg->fan_over_limit, REG_FAN_OVER_LIMIT_OFFSET);

    return 0;
}

static int __FORE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_fore_reg *fore_reg = (struct ku_fore_reg*)ku_reg;

    SX_GET_REG_FIELD(fore_reg->fan_under_limit, outbox, REG_FAN_UNDER_LIMIT_OFFSET);
    SX_GET_REG_FIELD(fore_reg->fan_over_limit, outbox, REG_FAN_OVER_LIMIT_OFFSET);
    return 0;
}

int sx_ACCESS_REG_FORE(struct sx_dev *dev, struct ku_access_fore_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __FORE_encode,
                                  __FORE_decode,
                                  FORE_REG_LEN,
                                  &reg_data->fore_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_FORE);


/************************************************
 * MFCR
 ***********************************************/
#define REG_PWM_FREQ_OFFSET     0x17
#define REG_TACHO_ACTIVE_OFFSET 0x18
#define REG_PWM_ACTIVE_OFFSET   0x1b
#define MFCR_REG_LEN            0x3

static int __MFCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfcr_reg *mfcr_reg = (struct ku_mfcr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mfcr_reg->pwm_frequency, REG_PWM_FREQ_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfcr_reg->tacho_active, REG_TACHO_ACTIVE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfcr_reg->pwm_active, REG_PWM_ACTIVE_OFFSET);
    return 0;
}

static int __MFCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfcr_reg *mfcr_reg = (struct ku_mfcr_reg*)ku_reg;

    SX_GET_REG_FIELD(mfcr_reg->pwm_frequency, outbox, REG_PWM_FREQ_OFFSET);
    SX_GET_REG_FIELD(mfcr_reg->tacho_active, outbox, REG_TACHO_ACTIVE_OFFSET);
    SX_GET_REG_FIELD(mfcr_reg->pwm_active, outbox, REG_PWM_ACTIVE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFCR(struct sx_dev *dev, struct ku_access_mfcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFCR_encode,
                                  __MFCR_decode,
                                  MFCR_REG_LEN,
                                  &reg_data->mfcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFCR);


/************************************************
 * MFM
 ***********************************************/
#define REG_MFM_INDEX_OFFSET   0x17
#define REG_MEMORY_OFFSET      0x1c
#define REG_MEMORY_MASK_OFFSET 0x24
#define MFM_REG_LEN            0x7

static int __MFM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfm_reg *mfm_reg = (struct ku_mfm_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mfm_reg->index, REG_MFM_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfm_reg->memory, REG_MEMORY_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfm_reg->memory_mask, REG_MEMORY_MASK_OFFSET);
    return 0;
}

static int __MFM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfm_reg *mfm_reg = (struct ku_mfm_reg*)ku_reg;

    SX_GET_REG_FIELD(mfm_reg->index, outbox, REG_MFM_INDEX_OFFSET);
    SX_GET_REG_FIELD(mfm_reg->memory, outbox, REG_MEMORY_OFFSET);
    SX_GET_REG_FIELD(mfm_reg->memory_mask, outbox, REG_MEMORY_MASK_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFM(struct sx_dev *dev, struct ku_access_mfm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFM_encode,
                                  __MFM_decode,
                                  MFM_REG_LEN,
                                  &reg_data->mfm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFM);

/************************************************
 * HTGT
 ***********************************************/
#define REG_HTGT_SWID_OFFSET         0x14
#define REG_HTGT_TYPE_OFFSET         0x16
#define REG_HTGT_GRP_OFFSET          0x17
#define REG_HTGT_PIDE_OFFSET         0x1A
#define REG_HTGT_PID_OFFSET          0x1B
#define REG_HTGT_MRR_ACTION_OFFSET   0x1E
#define REG_HTGT_MRR_AGENT_OFFSET    0x1F
#define REG_HTGT_PRIO_OFFSET         0x23
#define REG_HTGT_PATH_OFFSET         0x24
#define REG_HTGT_LP_CPU_TC_OFFSET    (REG_HTGT_PATH_OFFSET + 1)
#define REG_HTGT_LP_RDQ_OFFSET       (REG_HTGT_PATH_OFFSET + 3)
#define REG_HTGT_SP_STK_TC_OFFSET    (REG_HTGT_PATH_OFFSET + 0)
#define REG_HTGT_SP_CPU_TC_OFFSET    (REG_HTGT_PATH_OFFSET + 1)
#define REG_HTGT_SP_RDQ_OFFSET       (REG_HTGT_PATH_OFFSET + 3)
#define REG_HTGT_SP_SYS_PORT_OFFSET  (REG_HTGT_PATH_OFFSET + 7)
#define REG_HTGT_DRP_DR_PTR_OFFSET   (REG_HTGT_PATH_OFFSET + 3)
#define REG_HTGT_EP_MAC_47_32_OFFSET (REG_HTGT_PATH_OFFSET + 3)
#define REG_HTGT_EP_MAC_31_0_OFFSET  (REG_HTGT_PATH_OFFSET + 7)
#define REG_HTGT_EP_VID_OFFSET       (REG_HTGT_PATH_OFFSET + 0xb)
#define REG_HTGT_MRR_PRO_RATE_OFFSET 0x54
#define HTGT_REG_LEN                 0x11 /* number of 32-bits words that the register holds */

static int __HTGT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_htgt_reg *htgt_reg = (struct ku_htgt_reg*)ku_reg;
    u16                 mac_47_32;
    u32                 mac_31_0;
    u8                  tmp;

    SX_PUT_REG_FIELD(inbox, htgt_reg->swid, REG_HTGT_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->type, REG_HTGT_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->trap_group, REG_HTGT_GRP_OFFSET);
    tmp = (htgt_reg->pide & 0x1) << 7;
    SX_PUT_REG_FIELD(inbox, tmp, REG_HTGT_PIDE_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->pid, REG_HTGT_PID_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->mirror_action, REG_HTGT_MRR_ACTION_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->mirror_agent, REG_HTGT_MRR_AGENT_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->priority, REG_HTGT_PRIO_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->mirror_probability_rate, REG_HTGT_MRR_PRO_RATE_OFFSET);

    switch (htgt_reg->type) {
    case HTGT_LOCAL_PATH:
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.local_path.cpu_tclass, REG_HTGT_LP_CPU_TC_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.local_path.rdq, REG_HTGT_LP_RDQ_OFFSET);
        break;

    case HTGT_STACKING_PATH:
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.stacking_path.stacking_tclass, REG_HTGT_SP_STK_TC_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.stacking_path.cpu_tclass, REG_HTGT_SP_CPU_TC_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.stacking_path.rdq, REG_HTGT_SP_RDQ_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.stacking_path.cpu_sys_port, REG_HTGT_SP_SYS_PORT_OFFSET);
        break;

    case HTGT_DR_PATH:
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.dr_path.dr_ptr, REG_HTGT_DRP_DR_PTR_OFFSET);
        break;

    case HTGT_ETH_PATH:
        mac_47_32 = (htgt_reg->path.eth_path.mac >> 32) & 0xFFFF;
        mac_31_0 = htgt_reg->path.eth_path.mac & 0xFFFFFFFF;
        SX_PUT_REG_FIELD(inbox, mac_47_32, REG_HTGT_EP_MAC_47_32_OFFSET);
        SX_PUT_REG_FIELD(inbox, mac_31_0, REG_HTGT_EP_MAC_31_0_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.eth_path.vid, REG_HTGT_EP_VID_OFFSET);
        break;

    case HTGT_NULL_PATH:
        break;

    default:
        printk(KERN_ERR "%s(): Incorrect HTGT path type: %d \n", __func__, htgt_reg->type);
        return -EINVAL;
    }

    return 0;
}

static int __HTGT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_htgt_reg *htgt_reg = (struct ku_htgt_reg*)ku_reg;
    u16                 mac_47_32;
    u32                 mac_31_0;
    u8                  tmp;

    SX_GET_REG_FIELD(htgt_reg->swid, outbox, REG_HTGT_SWID_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->type, outbox, REG_HTGT_TYPE_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->trap_group, outbox, REG_HTGT_GRP_OFFSET);
    SX_GET_REG_FIELD(tmp, outbox, REG_HTGT_PIDE_OFFSET);
    htgt_reg->pide = (tmp >> 0x7) & 0x1;
    SX_GET_REG_FIELD(htgt_reg->pid, outbox, REG_HTGT_PID_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->mirror_action, outbox, REG_HTGT_MRR_ACTION_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->mirror_agent, outbox, REG_HTGT_MRR_AGENT_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->priority, outbox, REG_HTGT_PRIO_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->mirror_probability_rate, outbox, REG_HTGT_MRR_PRO_RATE_OFFSET);

    switch (htgt_reg->type) {
    case HTGT_LOCAL_PATH:
        SX_GET_REG_FIELD(htgt_reg->path.local_path.cpu_tclass, outbox, REG_HTGT_LP_CPU_TC_OFFSET);
        SX_GET_REG_FIELD(htgt_reg->path.local_path.rdq, outbox, REG_HTGT_LP_RDQ_OFFSET);
        break;

    case HTGT_STACKING_PATH:
        SX_GET_REG_FIELD(htgt_reg->path.stacking_path.stacking_tclass, outbox, REG_HTGT_SP_STK_TC_OFFSET);
        SX_GET_REG_FIELD(htgt_reg->path.stacking_path.cpu_tclass, outbox, REG_HTGT_SP_CPU_TC_OFFSET);
        SX_GET_REG_FIELD(htgt_reg->path.stacking_path.rdq, outbox, REG_HTGT_SP_RDQ_OFFSET);
        SX_GET_REG_FIELD(htgt_reg->path.stacking_path.cpu_sys_port, outbox, REG_HTGT_SP_SYS_PORT_OFFSET);
        break;

    case HTGT_DR_PATH:
        SX_GET_REG_FIELD(htgt_reg->path.dr_path.dr_ptr, outbox, REG_HTGT_DRP_DR_PTR_OFFSET);
        break;

    case HTGT_ETH_PATH:
        SX_GET_REG_FIELD(mac_47_32, outbox, REG_HTGT_EP_MAC_47_32_OFFSET);
        SX_GET_REG_FIELD(mac_31_0, outbox, REG_HTGT_EP_MAC_31_0_OFFSET);
        htgt_reg->path.eth_path.mac = mac_47_32;
        htgt_reg->path.eth_path.mac = (htgt_reg->path.eth_path.mac << 32) | mac_31_0;
        SX_GET_REG_FIELD(htgt_reg->path.eth_path.vid, outbox, REG_HTGT_EP_VID_OFFSET);
        break;

    case HTGT_NULL_PATH:
        break;

    default:
        printk(KERN_ERR "%s(): Incorrect HTGT path type: %d on query\n", __func__, htgt_reg->type);
        return -EINVAL;
    }

    return 0;
}

int sx_ACCESS_REG_HTGT(struct sx_dev *dev, struct ku_access_htgt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HTGT_encode,
                                  __HTGT_decode,
                                  HTGT_REG_LEN,
                                  &reg_data->htgt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HTGT);

/************************************************
 * SSPR
 ***********************************************/
#define SSPR_REG_MASTER_BIT_OFFSET     0x14
#define SSPR_REG_MASTER_BIT_N          7
#define SSPR_REG_LOCAL_PORT_OFFSET     0x15
#define SSPR_REG_LOCAL_PORT_MSB_OFFSET 0x16
#define SSPR_REG_SYSTEM_PORT           0x1a
#define SSPR_REG_LEN                   0x03

static int __SSPR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sspr_reg *sspr_reg = (struct ku_sspr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;

    tmp_val_u8 = sspr_reg->is_master ? (1 << SSPR_REG_MASTER_BIT_N) : 0;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, SSPR_REG_MASTER_BIT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sspr_reg->local_port, SSPR_REG_LOCAL_PORT_OFFSET);
    tmp_val_u8 = (sspr_reg->lp_msb & 0x03) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, SSPR_REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, sspr_reg->system_port, SSPR_REG_SYSTEM_PORT);
    return 0;
}

static int __SSPR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sspr_reg *sspr_reg = (struct ku_sspr_reg*)ku_reg;
    u8                  tmp_val_u8;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, SSPR_REG_MASTER_BIT_OFFSET);
    if (tmp_val_u8 & (1 << SSPR_REG_MASTER_BIT_N)) {
        sspr_reg->is_master = 1;
    }
    SX_GET_REG_FIELD(sspr_reg->local_port, outbox, SSPR_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(sspr_reg->lp_msb, outbox, SSPR_REG_LOCAL_PORT_MSB_OFFSET);
    sspr_reg->lp_msb = (sspr_reg->lp_msb >> 4) & 0x03;
    SX_GET_REG_FIELD(sspr_reg->system_port, outbox, SSPR_REG_SYSTEM_PORT);
    return 0;
}

int sx_ACCESS_REG_SSPR(struct sx_dev *dev, struct ku_access_sspr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SSPR_encode,
                                  __SSPR_decode,
                                  SSPR_REG_LEN,
                                  &reg_data->sspr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SSPR);


/************************************************
 * SPMCR
 ***********************************************/
#define SPMCR_REG_SWID_OFFSET          0x14
#define SPMCR_REG_LOCAL_PORT_OFFSET    0x15
#define SPMCR_REG_MAX_SUB_PORT_OFFSET  0x16
#define SPMCR_REG_BASE_STAG_VID_OFFSET 0x1a
#define SPMCR_REG_LEN                  0x03

static int __SPMCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spmcr_reg *spmcr_reg = (struct ku_spmcr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, spmcr_reg->swid, SPMCR_REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, spmcr_reg->local_port, SPMCR_REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, spmcr_reg->max_sub_port, SPMCR_REG_MAX_SUB_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, spmcr_reg->base_stag_vid, SPMCR_REG_BASE_STAG_VID_OFFSET);
    return 0;
}

static int __SPMCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spmcr_reg *spmcr_reg = (struct ku_spmcr_reg*)ku_reg;

    SX_GET_REG_FIELD(spmcr_reg->swid, outbox, SPMCR_REG_SWID_OFFSET);
    SX_GET_REG_FIELD(spmcr_reg->local_port, outbox, SPMCR_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(spmcr_reg->max_sub_port, outbox, SPMCR_REG_MAX_SUB_PORT_OFFSET);
    SX_GET_REG_FIELD(spmcr_reg->swid, outbox, SPMCR_REG_BASE_STAG_VID_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SPMCR(struct sx_dev *dev, struct ku_access_spmcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPMCR_encode,
                                  __SPMCR_decode,
                                  SPMCR_REG_LEN,
                                  &reg_data->spmcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPMCR);

/************************************************
 * SMID
 ***********************************************/
#define SMID_REG_SWID_OFFSET 0x14
#define SMID_REG_MID_OFFSET  0x16

#define SMID_REG_PORTS_255_224_OFFSET 0x34
#define SMID_REG_PORTS_223_192_OFFSET 0x38
#define SMID_REG_PORTS_191_160_OFFSET 0x3c
#define SMID_REG_PORTS_159_128_OFFSET 0x40
#define SMID_REG_PORTS_127_96_OFFSET  0x44
#define SMID_REG_PORTS_95_64_OFFSET   0x48
#define SMID_REG_PORTS_63_32_OFFSET   0x4c
#define SMID_REG_PORTS_31_0_OFFSET    0x50

#define SMID_REG_PORTS_255_224_MASK_OFFSET 0x54
#define SMID_REG_PORTS_223_192_MASK_OFFSET 0x58
#define SMID_REG_PORTS_191_160_MASK_OFFSET 0x5c
#define SMID_REG_PORTS_159_128_MASK_OFFSET 0x60
#define SMID_REG_PORTS_127_96_MASK_OFFSET  0x64
#define SMID_REG_PORTS_95_64_MASK_OFFSET   0x68
#define SMID_REG_PORTS_63_32_MASK_OFFSET   0x6c
#define SMID_REG_PORTS_31_0_MASK_OFFSET    0x70

#define SMID_REG_LEN 0x19

static int __SMID_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_smid_reg *smid_reg = (struct ku_smid_reg*)ku_reg;
    u32                 tmp_val_u32;
    u32                 tmp_mask_u32;
    int                 i, j;

    SX_PUT_REG_FIELD(inbox, smid_reg->swid, SMID_REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, smid_reg->mid, SMID_REG_MID_OFFSET);

    for (j = 0; j < 256; j += 32) {
        tmp_val_u32 = 0;
        tmp_mask_u32 = 0;

        for (i = 0; i < 32; i++) {
            tmp_val_u32 |= (smid_reg->ports_bitmap[j + i] ? (1 << i) : 0);
            tmp_mask_u32 |= (smid_reg->mask_bitmap[j + i] ? (1 << i) : 0);
        }

        if (j == 0) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_31_0_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_31_0_MASK_OFFSET);
        } else if (j == 32) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_63_32_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_63_32_MASK_OFFSET);
        } else if (j == 64) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_95_64_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_95_64_MASK_OFFSET);
        } else if (j == 96) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_127_96_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_127_96_MASK_OFFSET);
        } else if (j == 128) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_159_128_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_159_128_MASK_OFFSET);
        } else if (j == 160) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_191_160_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_191_160_MASK_OFFSET);
        } else if (j == 192) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_223_192_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_223_192_MASK_OFFSET);
        } else if (j == 224) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_255_224_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_255_224_MASK_OFFSET);
        }
    }

    return 0;
}

static int __SMID_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_smid_reg *smid_reg = (struct ku_smid_reg*)ku_reg;
    u32                 tmp_val_u32;
    int                 i;

    SX_GET_REG_FIELD(smid_reg->swid, outbox, SMID_REG_SWID_OFFSET);
    SX_GET_REG_FIELD(smid_reg->mid, outbox, SMID_REG_MID_OFFSET);
    /*
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_255_224_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_223_192_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_191_160_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_159_128_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_127_96_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_95_64_OFFSET);
     */
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SMID_REG_PORTS_63_32_OFFSET);
    for (i = 0; i < 32; i++) {
        if (tmp_val_u32 & (1 << i)) {
            smid_reg->ports_bitmap[32 + i] = 1;
        }
    }
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SMID_REG_PORTS_31_0_OFFSET);
    for (i = 0; i < 32; i++) {
        if (tmp_val_u32 & (1 << i)) {
            smid_reg->ports_bitmap[i] = 1;
        }
    }

    return 0;
}

int sx_ACCESS_REG_SMID(struct sx_dev *dev, struct ku_access_smid_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SMID_encode,
                                  __SMID_decode,
                                  SMID_REG_LEN,
                                  &reg_data->smid_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SMID);


/************************************************
 * SPMS
 ***********************************************/
#define SPMS_DWORD0_OFFSET 0x14
#define SPMS_DWORD1_OFFSET 0x18
#define SPMS_REG_LEN       0x101 /* in dwords */

static int __SPMS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spms_reg *spms_reg = (struct ku_spms_reg*)ku_reg;
    u32                 tmp_u32;
    int                 i, j, vlan = 4095;

    tmp_u32 = (((u32)(spms_reg->local_port & 0xff)) << 16) |
              (((u32)(spms_reg->lp_msb & 0x3)) << 12);
    SX_PUT_REG_FIELD(inbox, tmp_u32, SPMS_DWORD0_OFFSET);

    for (i = 0; i < 256; i++) { /* dwords */
        tmp_u32 = 0;
        for (j = 30; j >= 0; j -= 2) { /* states per dword */
            tmp_u32 |= ((u32)(spms_reg->state[vlan--] & 0x3)) << j;
        }
        SX_PUT_REG_FIELD(inbox, tmp_u32, (SPMS_DWORD1_OFFSET + (i * 4)));
    }

    return 0;
}

static int __SPMS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spms_reg *spms_reg = (struct ku_spms_reg*)ku_reg;
    u32                 tmp_u32;
    int                 i, j, vlan = 4095;

    SX_GET_REG_FIELD(tmp_u32, outbox, SPMS_DWORD0_OFFSET);
    spms_reg->local_port = (tmp_u32 >> 16) & 0xff;
    spms_reg->lp_msb = (tmp_u32 >> 12) & 0x3;

    for (i = 0; i < 256; i++) { /* dwords */
        SX_GET_REG_FIELD(tmp_u32, outbox, (SPMS_DWORD1_OFFSET + (i * 4)));
        for (j = 30; j >= 0; j -= 2) { /* states per dword */
            spms_reg->state[vlan--] = (tmp_u32 >> j) & 0x3;
        }
    }

    return 0;
}

int sx_ACCESS_REG_SPMS(struct sx_dev *dev, struct ku_access_spms_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPMS_encode,
                                  __SPMS_decode,
                                  SPMS_REG_LEN,
                                  &reg_data->spms_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPMS);

/************************************************
 * PLBF
 ***********************************************/
#define PLBF_LOCAL_PORT_OFFSET     0x15
#define PLBF_LOCAL_PORT_MSB_OFFSET 0x16
#define PLBF_LBF_MODE_OFFSET       0x17
#define PLBF_REG_LEN               0x03

static int __PLBF_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_plbf_reg *plbf_reg = (struct ku_plbf_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, plbf_reg->port, PLBF_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ((plbf_reg->lp_msb & 0x3) << 4), PLBF_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, plbf_reg->lbf_mode, PLBF_LBF_MODE_OFFSET);
    return 0;
}

static int __PLBF_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_plbf_reg *plbf_reg = (struct ku_plbf_reg*)ku_reg;
    u8                  temp = 0;

    SX_GET_REG_FIELD(plbf_reg->port, outbox, PLBF_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(temp, outbox, PLBF_LOCAL_PORT_MSB_OFFSET);
    plbf_reg->lp_msb = (temp >> 4) & 0x3;
    SX_GET_REG_FIELD(plbf_reg->lbf_mode, outbox, PLBF_LBF_MODE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PLBF(struct sx_dev *dev, struct ku_access_plbf_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PLBF_encode,
                                  __PLBF_decode,
                                  PLBF_REG_LEN,
                                  &reg_data->plbf_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PLBF);

/************************************************
 * MSCI
 ***********************************************/
#define MSCI_INDEX_OFFSET   0x17
#define MSCI_VERSION_OFFSET 0x18
#define MSCI_REG_LEN        0x5

static int __MSCI_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_msci_reg *msci_reg = (struct ku_msci_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, msci_reg->index, MSCI_INDEX_OFFSET);
    return 0;
}

static int __MSCI_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_msci_reg *msci_reg = (struct ku_msci_reg*)ku_reg;

    SX_GET_REG_FIELD(msci_reg->index, outbox, MSCI_INDEX_OFFSET);
    SX_GET_REG_FIELD(msci_reg->version, outbox, MSCI_VERSION_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MSCI(struct sx_dev *dev, struct ku_access_msci_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MSCI_encode,
                                  __MSCI_decode,
                                  MSCI_REG_LEN,
                                  &reg_data->msci_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MSCI);


/************************************************
 * MRSR
 ***********************************************/
#define MRSR_COMMAND_OFFSET 0x17
#define MRSR_REG_LEN        0x3

static int __MRSR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mrsr_reg *mrsr_reg = (struct ku_mrsr_reg*)ku_reg;
    u8                  tmp;

    tmp = (u8)mrsr_reg->command;
    SX_PUT_REG_FIELD(inbox, tmp, MRSR_COMMAND_OFFSET);
    return 0;
}


int sx_ACCESS_REG_MRSR(struct sx_dev *dev, struct ku_access_mrsr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  /* Ignore the error from FW regarding MRSR register */
                                  SX_ACCESS_REG_F_IGNORE_FW_RET_CODE,
                                  &reg_data->op_tlv,
                                  __MRSR_encode,
                                  NULL,
                                  MRSR_REG_LEN,
                                  &reg_data->mrsr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MRSR);


/************************************************
 * RGCR
 ***********************************************/
#define RGCR_DWORD0_OFFSET 0x14
#define RGCR_REG_LEN       0xb /* in dwords */

static int __RGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_rgcr_reg *rgcr_reg = (struct ku_rgcr_reg*)ku_reg;
    u32                 tmp_u32;

    tmp_u32 = (((u32)(rgcr_reg->ipv4_enable & 0x1)) << 31) |
              (((u32)(rgcr_reg->ipv6_enable & 0x1)) << 30) |
              (((u32)(rgcr_reg->mpls_enable & 0x1)) << 29);
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET);

    tmp_u32 = rgcr_reg->max_vlan_router_interfaces & 0xffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 4);

    tmp_u32 = rgcr_reg->max_port_router_interfaces & 0xffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 8);

    tmp_u32 = rgcr_reg->max_pkey_router_interfaces & 0xffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 12);

    tmp_u32 = rgcr_reg->max_router_interfaces & 0xffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 16);

    tmp_u32 = rgcr_reg->max_virtual_routers & 0xffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 20);

    tmp_u32 = (((u32)(rgcr_reg->grht & 0xf)) << 24) |
              (((u32)(rgcr_reg->usp & 0x1)) << 20) |
              (((u32)(rgcr_reg->pcp_rw & 0x3)) << 16) |
              (((u32)(rgcr_reg->ipb & 0x1)) << 9) |
              (((u32)(rgcr_reg->allr & 0x1)) << 8) |
              (((u32)(rgcr_reg->mcsi & 0x1)) << 4) |
              (rgcr_reg->rpf & 0x1);
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 24);

    tmp_u32 = (((u32)(rgcr_reg->ipv6_op_type & 0x3)) << 24) |
              (((u32)(rgcr_reg->ipv6_packet_rate & 0x1f)) << 16) |
              (((u32)(rgcr_reg->ipv4_op_type & 0x3)) << 8) |
              (rgcr_reg->ipv4_packet_rate & 0x1f);
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 28);

    tmp_u32 = (((u32)(rgcr_reg->grh_hop_limit & 0xff)) << 16);
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 32);

    tmp_u32 = rgcr_reg->expected_irif_list_index_base & 0xffffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, RGCR_DWORD0_OFFSET + 36);

    return 0;
}

static int __RGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_rgcr_reg *rgcr_reg = (struct ku_rgcr_reg*)ku_reg;
    u32                 tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET);
    rgcr_reg->ipv4_enable = (tmp_u32 >> 31) & 0x1;
    rgcr_reg->ipv6_enable = (tmp_u32 >> 30) & 0x1;
    rgcr_reg->mpls_enable = (tmp_u32 >> 29) & 0x1;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 4);
    rgcr_reg->max_vlan_router_interfaces = tmp_u32 & 0xffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 8);
    rgcr_reg->max_port_router_interfaces = tmp_u32 & 0xffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 12);
    rgcr_reg->max_pkey_router_interfaces = tmp_u32 & 0xffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 16);
    rgcr_reg->max_router_interfaces = tmp_u32 & 0xffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 20);
    rgcr_reg->max_virtual_routers = tmp_u32 & 0xffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 24);
    rgcr_reg->grht = (tmp_u32 >> 24) & 0xf;
    rgcr_reg->usp = (tmp_u32 >> 20) & 0x1;
    rgcr_reg->pcp_rw = (tmp_u32 >> 16) & 0x3;
    rgcr_reg->ipb = (tmp_u32 >> 9) & 0x1;
    rgcr_reg->allr = (tmp_u32 >> 8) & 0x1;
    rgcr_reg->mcsi = (tmp_u32 >> 4) & 0x1;
    rgcr_reg->rpf = tmp_u32 & 0x1;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 28);
    rgcr_reg->ipv6_op_type = (tmp_u32 >> 24) & 0x3;
    rgcr_reg->ipv6_packet_rate = (tmp_u32 >> 16) & 0x1f;
    rgcr_reg->ipv4_op_type = (tmp_u32 >> 8) & 0x3;
    rgcr_reg->ipv4_packet_rate = tmp_u32 & 0x1f;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 32);
    rgcr_reg->grh_hop_limit = (tmp_u32 >> 16) & 0xff;

    SX_GET_REG_FIELD(tmp_u32, outbox, RGCR_DWORD0_OFFSET + 36);
    rgcr_reg->expected_irif_list_index_base = tmp_u32 & 0xffffff;

    return 0;
}

int sx_ACCESS_REG_RGCR(struct sx_dev *dev, struct ku_access_rgcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RGCR_encode,
                                  __RGCR_decode,
                                  RGCR_REG_LEN,
                                  &reg_data->rgcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RGCR);


/************************************************
 * RTPS
 ***********************************************/
#define REG_SWID_OFFSET        0x14
#define REG_TCA_PHY_LOG_OFFSET 0x17
#define REG_SW_PHY_LOG_OFFSET  0x1B
#define RTPS_REG_LEN           0x03

static int __RTPS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_rtps_reg *rtps_reg = (struct ku_rtps_reg*)ku_reg;
    u8                  tmp_val_u8;

    SX_PUT_REG_FIELD(inbox, rtps_reg->swid, REG_SWID_OFFSET);
    tmp_val_u8 = (rtps_reg->tca_log_pstate & 0xF) << 4;
    tmp_val_u8 |= rtps_reg->tca_phy_pstate & 0xF;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_TCA_PHY_LOG_OFFSET);
    return 0;
}

static int __RTPS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_rtps_reg *rtps_reg = (struct ku_rtps_reg*)ku_reg;
    u8                  tmp_val_u8;

    SX_GET_REG_FIELD(rtps_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_TCA_PHY_LOG_OFFSET);
    rtps_reg->tca_log_pstate = (tmp_val_u8 >> 4) & 0xF;
    rtps_reg->tca_phy_pstate = tmp_val_u8 & 0xF;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_SW_PHY_LOG_OFFSET);
    rtps_reg->switch_log_pstate = (tmp_val_u8 >> 4) & 0xF;
    rtps_reg->switch_phy_pstate = tmp_val_u8 & 0xF;
    return 0;
}

int sx_ACCESS_REG_RTPS(struct sx_dev *dev, struct ku_access_rtps_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RTPS_encode,
                                  __RTPS_decode,
                                  RTPS_REG_LEN,
                                  &reg_data->rtps_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RTPS);


/************************************************
 * RTCA
 ***********************************************/
#define REG_SWID_OFFSET 0x14
#define REG_LMC_OFFSET  0x15
#define REG_LID_OFFSET  0x16
#define REG_GID_OFFSET  0x18
#define GID_SIZE        16
#define RTCA_REG_LEN    0x08

static int __RTCA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_rtca_reg *rtca_reg = (struct ku_rtca_reg*)ku_reg;
    int                 i;

    SX_PUT_REG_FIELD(inbox, rtca_reg->swid, REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, rtca_reg->lmc, REG_LMC_OFFSET);
    SX_PUT_REG_FIELD(inbox, rtca_reg->lid, REG_LID_OFFSET);
    for (i = 0; i < GID_SIZE; i++) {
        SX_PUT_REG_FIELD(inbox, rtca_reg->gid.addr_octet[i], i + REG_GID_OFFSET);
    }
    return 0;
}

static int __RTCA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_rtca_reg *rtca_reg = (struct ku_rtca_reg*)ku_reg;
    int                 i;

    SX_GET_REG_FIELD(rtca_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(rtca_reg->lmc, outbox, REG_LMC_OFFSET);
    SX_GET_REG_FIELD(rtca_reg->lid, outbox, REG_LID_OFFSET);

    for (i = 0; i < GID_SIZE; i++) {
        SX_GET_REG_FIELD(rtca_reg->gid.addr_octet[i], outbox, i + REG_GID_OFFSET);
    }

    return 0;
}

int sx_ACCESS_REG_RTCA(struct sx_dev *dev, struct ku_access_rtca_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RTCA_encode,
                                  __RTCA_decode,
                                  RTCA_REG_LEN,
                                  &reg_data->rtca_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RTCA);

/************************************************
 * RUFT
 ***********************************************/
#define REG_VALID_TYPE_OFFSET     0x14
#define REG_OP_ACT_OFFSET         0x15
#define REG_OFFSET                0x16
#define REG_RUFT_VRID_OFFSET      0x18
#define REG_DIP_OFFSET            0x24
#define REG_DIP_MASK_OFFSET       0x34
#define REG_ECMP_HASH_OFFSET      0x68
#define REG_ECMP_HASH_MASK_OFFSET 0x6C
#define REG_TRAP_ACTION_OFFSET    0x74
#define REG_TRAP_GROUP_OFFSET     0x75
#define REG_TRAP_ID_OFFSET        0x76
#define REG_MIRROR_DST_OFFSET     0x78
#define REG_PRIO_QOS_OFFSET       0x79
#define REG_EGRESS_RIF_OFFSET     0x86
#define REG_ECMP_SIZE_OFFSET      0x88
#define REG_TABLE_OFFSET          0x89
#define REG_ADJ_IDX_OFFSET        0x8A
#define RUFT_REG_LEN              0x1F

static int __RUFT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ruft_reg *ruft_reg = (struct ku_ruft_reg*)ku_reg;
    u8                  tmp_val_u8;
    u16                 tmp_val_u16;
    int                 i;

    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->valid & 1) << 7;
    tmp_val_u8 |= (ruft_reg->route_type & 3);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_VALID_TYPE_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->operation & 7) << 4;
    tmp_val_u8 |= (ruft_reg->activity & 1);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_OP_ACT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->offset, REG_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->router, REG_RUFT_VRID_OFFSET);
    for (i = 0; i <= 3; i++) {
        SX_PUT_REG_FIELD(inbox, ruft_reg->destination_ip[i], (REG_DIP_OFFSET + (i * 4)));
        SX_PUT_REG_FIELD(inbox, ruft_reg->destination_ip_mask[i], (REG_DIP_MASK_OFFSET + (i * 4)));
    }
    SX_PUT_REG_FIELD(inbox, ruft_reg->ecmp_hash, REG_ECMP_HASH_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->ecmp_hash_mask, REG_ECMP_HASH_MASK_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->route_action & 0xf) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_TRAP_ACTION_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->trap_group & 0xf);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_TRAP_GROUP_OFFSET);
    tmp_val_u16 = 0;
    tmp_val_u16 |= (ruft_reg->trap_id & 0x01ff);
    SX_PUT_REG_FIELD(inbox, tmp_val_u16, REG_TRAP_ID_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->mirror_enable & 1) << 7;
    tmp_val_u8 |= (ruft_reg->mirror_dst & 7);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_MIRROR_DST_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->prio & 7) << 4;
    tmp_val_u8 |= (ruft_reg->qos & 3);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_PRIO_QOS_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->egress_rif, REG_EGRESS_RIF_OFFSET);
    tmp_val_u8 = ruft_reg->ecmp_size;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_ECMP_SIZE_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->table & 7);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_TABLE_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->adjacency_index, REG_ADJ_IDX_OFFSET);
    return 0;
}

static int __RUFT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ruft_reg *ruft_reg = (struct ku_ruft_reg*)ku_reg;
    u8                  tmp_val_u8;
    u16                 tmp_val_u16;
    int                 i;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_VALID_TYPE_OFFSET);
    ruft_reg->valid = (tmp_val_u8 >> 7) & 1;
    ruft_reg->route_type = tmp_val_u8 & 3;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_OP_ACT_OFFSET);
    ruft_reg->operation = (tmp_val_u8 >> 4) & 7;
    ruft_reg->activity = tmp_val_u8 & 1;
    SX_GET_REG_FIELD(ruft_reg->offset, outbox, REG_OFFSET);
    SX_GET_REG_FIELD(ruft_reg->router, outbox, REG_RUFT_VRID_OFFSET);
    for (i = 0; i <= 3; i++) {
        SX_GET_REG_FIELD(ruft_reg->destination_ip[i], outbox, (REG_DIP_OFFSET + (i * 4)));
        SX_GET_REG_FIELD(ruft_reg->destination_ip_mask[i], outbox, (REG_DIP_MASK_OFFSET + (i * 4)));
    }
    SX_GET_REG_FIELD(ruft_reg->ecmp_hash, outbox, REG_ECMP_HASH_OFFSET);
    SX_GET_REG_FIELD(ruft_reg->ecmp_hash_mask, outbox, REG_ECMP_HASH_MASK_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_TRAP_ACTION_OFFSET);
    ruft_reg->route_action = (tmp_val_u8 >> 4) & 0xf;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_TRAP_GROUP_OFFSET);
    ruft_reg->trap_group = tmp_val_u8 & 0xf;
    SX_GET_REG_FIELD(tmp_val_u16, outbox, REG_TRAP_ID_OFFSET);
    ruft_reg->trap_id = tmp_val_u16 & 0x01ff;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_MIRROR_DST_OFFSET);
    ruft_reg->mirror_enable = (tmp_val_u8 >> 7) & 1;
    ruft_reg->mirror_dst = tmp_val_u8 & 7;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_PRIO_QOS_OFFSET);
    ruft_reg->prio = (tmp_val_u8 >> 4) & 7;
    ruft_reg->qos = tmp_val_u8 & 3;
    SX_GET_REG_FIELD(ruft_reg->egress_rif, outbox, REG_EGRESS_RIF_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_ECMP_SIZE_OFFSET);
    ruft_reg->ecmp_size = tmp_val_u8;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_TABLE_OFFSET);
    ruft_reg->table = tmp_val_u8 & 7;
    SX_GET_REG_FIELD(ruft_reg->adjacency_index, outbox, REG_ADJ_IDX_OFFSET);
    return 0;
}

int sx_ACCESS_REG_RUFT(struct sx_dev *dev, struct ku_access_ruft_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RUFT_encode,
                                  __RUFT_decode,
                                  RUFT_REG_LEN,
                                  &reg_data->ruft_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RUFT);


/************************************************
 * MPSC
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET     0x15
#define REG_LOCAL_PORT_MSB_OFFSET 0x16
#define REG_C_E_CONG_OFFSET       0x18
#define REG_C_BIT_N               7
#define REG_E_BIT_N               6
#define REG_CONG_BIT_N            5
#define REG_RATE_OFFSET           0x1C
#define REG_COUNT_DROP_OFFSET     0x20
#define MPSC_REG_LEN              0x6

static int __MPSC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mpsc_reg *mpsc_reg = (struct ku_mpsc_reg*)ku_reg;
    u8                  tmp = 0;

    SX_PUT_REG_FIELD(inbox, mpsc_reg->local_port, REG_LOCAL_PORT_OFFSET);
    tmp = (mpsc_reg->lp_msb & 0x03) << 4;
    SX_PUT_REG_FIELD(inbox, tmp, REG_LOCAL_PORT_MSB_OFFSET);
    tmp = mpsc_reg->clear_count ? (1 << REG_C_BIT_N) : 0;
    tmp |= mpsc_reg->enable ? (1 << REG_E_BIT_N) : 0;
    tmp |= mpsc_reg->cong ? (1 << REG_CONG_BIT_N) : 0;
    SX_PUT_REG_FIELD(inbox, tmp, REG_C_E_CONG_OFFSET);
    SX_PUT_REG_FIELD(inbox, mpsc_reg->rate, REG_RATE_OFFSET);
    return 0;
}

static int __MPSC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mpsc_reg *mpsc_reg = (struct ku_mpsc_reg*)ku_reg;
    u8                  tmp;

    SX_GET_REG_FIELD(mpsc_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(mpsc_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    mpsc_reg->lp_msb = (mpsc_reg->lp_msb >> 4) & 0x03;
    SX_GET_REG_FIELD(tmp, outbox, REG_C_E_CONG_OFFSET);
    mpsc_reg->enable = tmp & (1 << REG_E_BIT_N) ? 1 : 0;
    mpsc_reg->cong = tmp & (1 << REG_CONG_BIT_N) ? 1 : 0;
    SX_GET_REG_FIELD(mpsc_reg->rate, outbox, REG_RATE_OFFSET);
    SX_GET_REG_FIELD(mpsc_reg->count_drops, outbox, REG_COUNT_DROP_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MPSC(struct sx_dev *dev, struct ku_access_mpsc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MPSC_encode,
                                  __MPSC_decode,
                                  MPSC_REG_LEN,
                                  &reg_data->mpsc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MPSC);


/************************************************
 * MLCR
 ***********************************************/
#define REG_LP_MSB_OFFSET               0x14
#define REG_LOCAL_PORT_OFFSET           0x15
#define REG_LED_TYPE_OFFSET             0x17
#define REG_BEACON_DURATION_OFFSET      0x1a
#define REG_BEACON_REMAIN_OFFSET        0x1e
#define REG_CAP_LOCAL_OR_UID_ONLY_BIT_N 4
#define MLCR_REG_LEN                    0x4

static int __MLCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mlcr_reg *mlcr_reg = (struct ku_mlcr_reg*)ku_reg;
    u8                  tmp_u8 = 0;

    SX_PUT_REG_FIELD(inbox, mlcr_reg->local_port, REG_LOCAL_PORT_OFFSET);
    tmp_u8 = mlcr_reg->lp_msb & 0x3;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_LP_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, mlcr_reg->led_type, REG_LED_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mlcr_reg->beacon_duration, REG_BEACON_DURATION_OFFSET);
    SX_PUT_REG_FIELD(inbox, mlcr_reg->beacon_remain, REG_BEACON_REMAIN_OFFSET);
    return 0;
}

static int __MLCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mlcr_reg *mlcr_reg = (struct ku_mlcr_reg*)ku_reg;
    u8                  tmp_u8;

    SX_GET_REG_FIELD(mlcr_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(mlcr_reg->lp_msb, outbox, REG_LP_MSB_OFFSET);
    mlcr_reg->lp_msb &= 0x3;
    SX_GET_REG_FIELD(tmp_u8, outbox, REG_LED_TYPE_OFFSET);
    mlcr_reg->cap_local_or_uid_only = tmp_u8 & (1 << REG_CAP_LOCAL_OR_UID_ONLY_BIT_N) ? 1 : 0;
    mlcr_reg->led_type = tmp_u8 & 0xf;
    SX_GET_REG_FIELD(mlcr_reg->beacon_duration, outbox, REG_BEACON_DURATION_OFFSET);
    SX_GET_REG_FIELD(mlcr_reg->beacon_remain, outbox, REG_BEACON_REMAIN_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MLCR(struct sx_dev *dev, struct ku_access_mlcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MLCR_encode,
                                  __MLCR_decode,
                                  MLCR_REG_LEN,
                                  &reg_data->mlcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MLCR);

/************************************************
 * MTPPPC
 ***********************************************/
#define REG_MTPPPC_WRITE_ENABLE_OFFSET           0x17
#define REG_MTPPPC_ING_TIMESTAMP_MSG_TYPE_OFFSET 0x1E
#define REG_MTPPPC_EGR_TIMESTAMP_MSG_TYPE_OFFSET 0x22
#define REG_MTPPPC_GM_LOCAL_PORT_0_OFFSET        0x37
#define REG_MTPPPC_GM_LOCAL_PORT_1_OFFSET        0x3A
#define MTPPPC_REG_LEN                           0x6

static int __MTPPPC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpppc_reg *mtpppc_reg = (struct ku_mtpppc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mtpppc_reg->we, REG_MTPPPC_WRITE_ENABLE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpppc_reg->ing_timestape_message_type, REG_MTPPPC_ING_TIMESTAMP_MSG_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpppc_reg->egr_timestape_message_type, REG_MTPPPC_EGR_TIMESTAMP_MSG_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpppc_reg->gm_local_port_0, REG_MTPPPC_GM_LOCAL_PORT_0_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpppc_reg->gm_local_port_1, REG_MTPPPC_GM_LOCAL_PORT_1_OFFSET);
    return 0;
}

static int __MTPPPC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtpppc_reg *mtpppc_reg = (struct ku_mtpppc_reg*)ku_reg;

    SX_GET_REG_FIELD(mtpppc_reg->ing_timestape_message_type, outbox, REG_MTPPPC_ING_TIMESTAMP_MSG_TYPE_OFFSET);
    SX_GET_REG_FIELD(mtpppc_reg->egr_timestape_message_type, outbox, REG_MTPPPC_EGR_TIMESTAMP_MSG_TYPE_OFFSET);
    SX_GET_REG_FIELD(mtpppc_reg->gm_local_port_0, outbox, REG_MTPPPC_GM_LOCAL_PORT_0_OFFSET);
    SX_GET_REG_FIELD(mtpppc_reg->gm_local_port_1, outbox, REG_MTPPPC_GM_LOCAL_PORT_1_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MTPPPC(struct sx_dev *dev, struct ku_access_mtpppc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPPPC_encode,
                                  __MTPPPC_decode,
                                  MTPPPC_REG_LEN,
                                  &reg_data->mtpppc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPPPC);


/************************************************
 * MTPTPT
 ***********************************************/
#define REG_MTPTPT_TRAP_ID_OFFSET  0x17
#define REG_MTPTPT_MSG_TYPE_OFFSET 0x1a
#define MTPTPT_REG_LEN             0x6

static int __MTPTPT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtptpt_reg *mtptpt_reg = (struct ku_mtptpt_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mtptpt_reg->trap_id, REG_MTPTPT_TRAP_ID_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtptpt_reg->message_type, REG_MTPTPT_MSG_TYPE_OFFSET);
    return 0;
}

static int __MTPTPT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtptpt_reg *mtptpt_reg = (struct ku_mtptpt_reg*)ku_reg;

    SX_GET_REG_FIELD(mtptpt_reg->trap_id, outbox, REG_MTPTPT_TRAP_ID_OFFSET);
    SX_GET_REG_FIELD(mtptpt_reg->message_type, outbox, REG_MTPTPT_MSG_TYPE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MTPTPT(struct sx_dev *dev, struct ku_access_mtptpt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPTPT_encode,
                                  __MTPTPT_decode,
                                  MTPTPT_REG_LEN,
                                  &reg_data->mtptpt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPTPT);


/************************************************
 * MTPPTR
 ***********************************************/
#define REG_MTPPTR_LOCAL_PORT_OFFSET     0x15
#define REG_MTPPTR_LOCAL_PORT_MSB_OFFSET 0x16
#define REG_MTPPTR_DIR_OFFSET            0x17
#define REG_MTPPTR_CLR_READ_ONE_OFFSET   0x18
#define REG_MTPPTR_OVF_OFFSET            0x1b
#define REG_MTPPTR_NUM_REC_OFFSET        0x1F
#define REG_MTPPTR_RECORDS_OFFSET        0x24
#define REG_CLR_BITN                     7
#define MTPPTR_REG_LEN                   0x14

static int __MTPPTR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpptr_reg *mtpptr_reg = (struct ku_mtpptr_reg*)ku_reg;
    u8                    clear_read_one;
    u8                    tmp_u8 = 0;

    clear_read_one = mtpptr_reg->clr << REG_CLR_BITN;
    SX_PUT_REG_FIELD(inbox, mtpptr_reg->dir, REG_MTPPTR_DIR_OFFSET);
    SX_PUT_REG_FIELD(inbox, clear_read_one, REG_MTPPTR_CLR_READ_ONE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpptr_reg->local_port, REG_MTPPTR_LOCAL_PORT_OFFSET);
    tmp_u8 = (mtpptr_reg->lp_msb & 0x03) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_MTPPTR_LOCAL_PORT_MSB_OFFSET);
    return 0;
}

static int __MTPPTR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtpptr_reg *mtpptr_reg = (struct ku_mtpptr_reg*)ku_reg;
    u8                    to_host_order = *(u8*)context;
    int                   start_record_offset = REG_MTPPTR_RECORDS_OFFSET;
    int                   i;

    if (to_host_order) {
        SX_GET_REG_FIELD(mtpptr_reg->num_record, outbox, REG_MTPPTR_NUM_REC_OFFSET);
        SX_GET_REG_FIELD(mtpptr_reg->ovf, outbox, REG_MTPPTR_OVF_OFFSET);
        start_record_offset = REG_MTPPTR_RECORDS_OFFSET;
        for (i = 0; i < mtpptr_reg->num_record; i++) {
            SX_GET_REG_FIELD(mtpptr_reg->records[i].domain_number, outbox, start_record_offset + 3);
            SX_GET_REG_FIELD(mtpptr_reg->records[i].message_type, outbox, start_record_offset + 2);
            SX_GET_REG_FIELD(mtpptr_reg->records[i].sequence_id, outbox, start_record_offset + 6);
            SX_GET_REG_FIELD(mtpptr_reg->records[i].timestamp, outbox, start_record_offset + 8);
            start_record_offset += 16;
        }
    } else {
        /* keep it in network order */
        memcpy(mtpptr_reg, outbox, sizeof(*mtpptr_reg));
    }

    return 0;
}

int sx_ACCESS_REG_MTPPTR(struct sx_dev *dev, struct ku_access_mtpptr_reg *reg_data, u8 to_host_order)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPPTR_encode,
                                  __MTPPTR_decode,
                                  MTPPTR_REG_LEN,
                                  &reg_data->mtpptr_reg,
                                  (void*)&to_host_order);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPPTR);

/************************************************
 * SBCTC
 ***********************************************/
#define REG_SBCTC_DIR_ING_OFFSET        0x14
#define REG_SBCTC_LOCAL_PORT_OFFSET     0x15
#define REG_SBCTC_LOCAL_PORT_MSB_OFFSET 0x16
#define REG_SBCTC_MODE_OFFSET           0x17
#define REG_SBCTC_EN_CONFIG_OFFSET      0x18
#define REG_SBCTC_EVENT_OFFSET          0x1B
#define REG_SBCTC_TCLASS_EN_OFFSET      0x1C
#define REG_SBCTC_THR_MAX_OFFSET        0x24
#define REG_SBCTC_THR_MIN_OFFSET        0x28
#define SBCTC_REG_LEN                   0x7

static int __SBCTC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbctc_reg *sbctc_reg = (struct ku_sbctc_reg*)ku_reg;
    u8                   en_config;
    u8                   tmp_val_u8 = 0;

    SX_PUT_REG_FIELD(inbox, sbctc_reg->dir_ing, REG_SBCTC_DIR_ING_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->local_port, REG_SBCTC_LOCAL_PORT_OFFSET);
    tmp_val_u8 |= ((sbctc_reg->lp_msb & 0x3) << 4);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_SBCTC_LOCAL_PORT_MSB_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (sbctc_reg->res & 1) << 4;
    tmp_val_u8 |= (sbctc_reg->mode & 1);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_SBCTC_MODE_OFFSET);
    en_config = sbctc_reg->en_config << 7;
    SX_PUT_REG_FIELD(inbox, en_config, REG_SBCTC_EN_CONFIG_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->event, REG_SBCTC_EVENT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->tclass_en, REG_SBCTC_TCLASS_EN_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->thr_max, REG_SBCTC_THR_MAX_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->thr_min, REG_SBCTC_THR_MIN_OFFSET);
    return 0;
}

static int __SBCTC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbctc_reg *sbctc_reg = (struct ku_sbctc_reg*)ku_reg;
    u8                   tmp_val_u8 = 0;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_SBCTC_MODE_OFFSET);
    sbctc_reg->res = (tmp_val_u8 >> 4) & 1;
    sbctc_reg->mode = tmp_val_u8 & 1;
    SX_GET_REG_FIELD(sbctc_reg->event, outbox, REG_SBCTC_EVENT_OFFSET);
    SX_GET_REG_FIELD(sbctc_reg->tclass_en, outbox, REG_SBCTC_TCLASS_EN_OFFSET);
    SX_GET_REG_FIELD(sbctc_reg->thr_max, outbox, REG_SBCTC_THR_MAX_OFFSET);
    SX_GET_REG_FIELD(sbctc_reg->thr_min, outbox, REG_SBCTC_THR_MIN_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SBCTC(struct sx_dev *dev, struct ku_access_sbctc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBCTC_encode,
                                  __SBCTC_decode,
                                  SBCTC_REG_LEN,
                                  &reg_data->sbctc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBCTC);


/************************************************
 * PPBMP
 ***********************************************/
#define REG_PPBMP_LOCAL_PORT_OFFSET          0x15
#define REG_PPBMP_PNAT_MSB_OFFSET            0x16
#define REG_PPBMP_MONITOR_GROUP_OFFSET       0x17
#define REG_PPBMP_ALARM_TH_MANTISSA_OFFSET   0x18
#define REG_PPBMP_ALARM_TH_EXP_OFFSET        0x19
#define REG_PPBMP_WARNING_TH_MANTISSA_OFFSET 0x1A
#define REG_PPBMP_WARNING_TH_EXP_OFFSET      0x1B
#define REG_PPBMP_NORMAL_TH_MANTISSA_OFFSET  0x1C
#define REG_PPBMP_NORMAL_TH_EXP_OFFSET       0x1D
#define PPBMP_REG_LEN                        16

static int __PPBMP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppbmp_reg *ppbmp_reg = (struct ku_ppbmp_reg*)ku_reg;
    u8                   pnat_lp_msb;

    pnat_lp_msb = ((ppbmp_reg->pnat & 0x03) << 6) | ((ppbmp_reg->lp_msb & 0x03) << 4);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->local_port, REG_PPBMP_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pnat_lp_msb, REG_PPBMP_PNAT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_group, REG_PPBMP_MONITOR_GROUP_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.alarm_th_mantissa, REG_PPBMP_ALARM_TH_MANTISSA_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.alarm_th_exp, REG_PPBMP_ALARM_TH_EXP_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.warning_th_mantissa, REG_PPBMP_WARNING_TH_MANTISSA_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.warning_th_exp, REG_PPBMP_WARNING_TH_EXP_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.normal_th_mantissa, REG_PPBMP_NORMAL_TH_MANTISSA_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.normal_th_exp, REG_PPBMP_NORMAL_TH_EXP_OFFSET);
    return 0;
}

static int __PPBMP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppbmp_reg *ppbmp_reg = (struct ku_ppbmp_reg*)ku_reg;

    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.alarm_th_mantissa, outbox, REG_PPBMP_ALARM_TH_MANTISSA_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.alarm_th_exp, outbox, REG_PPBMP_ALARM_TH_EXP_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.warning_th_mantissa, outbox, REG_PPBMP_WARNING_TH_MANTISSA_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.warning_th_exp, outbox, REG_PPBMP_WARNING_TH_EXP_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.normal_th_mantissa, outbox, REG_PPBMP_NORMAL_TH_MANTISSA_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.normal_th_exp, outbox, REG_PPBMP_NORMAL_TH_EXP_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPBMP(struct sx_dev *dev, struct ku_access_ppbmp_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPBMP_encode,
                                  __PPBMP_decode,
                                  PPBMP_REG_LEN,
                                  &reg_data->ppbmp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPBMP);


/************************************************
 * PPBMC
 ***********************************************/
#define REG_PPBMC_LOCAL_PORT_OFFSET            0x15
#define REG_PPBMC_PNAT_MSB_MONITOR_TYPE_OFFSET 0x16
#define REG_PPBMC_E_EVENT_CTRL_OFFSET          0x18
#define REG_PPBMC_MONITOR_CTRL_OFFSET          0x19
#define REG_PPBMC_MONITOR_STATE_OFFSET         0x1B
#define PPBMC_REG_LEN                          0x3

int __PPBMC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppbmc_reg *ppbmc_reg = (struct ku_ppbmc_reg*)ku_reg;
    u8                   e_event_ctrl;
    u8                   pnat_msb_monitor_type = 0;

    SX_PUT_REG_FIELD(inbox, ppbmc_reg->local_port, REG_PPBMC_LOCAL_PORT_OFFSET);
    pnat_msb_monitor_type = (ppbmc_reg->monitor_type & 0xF);
    pnat_msb_monitor_type |= ((ppbmc_reg->pnat & 0x3) << 6);
    pnat_msb_monitor_type |= ((ppbmc_reg->lp_msb & 0x3) << 4);
    SX_PUT_REG_FIELD(inbox, pnat_msb_monitor_type, REG_PPBMC_PNAT_MSB_MONITOR_TYPE_OFFSET);
    e_event_ctrl = ppbmc_reg->e << 6 | ((ppbmc_reg->event_ctrl) & 0xF);
    SX_PUT_REG_FIELD(inbox, e_event_ctrl, REG_PPBMC_E_EVENT_CTRL_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmc_reg->monitor_ctrl, REG_PPBMC_MONITOR_CTRL_OFFSET);
    return 0;
}

int __PPBMC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppbmc_reg *ppbmc_reg = (struct ku_ppbmc_reg*)ku_reg;
    u8                   e_event_ctrl;
    u8                   pnat_msb_monitor_type;

    SX_GET_REG_FIELD(pnat_msb_monitor_type, outbox, REG_PPBMC_PNAT_MSB_MONITOR_TYPE_OFFSET);
    ppbmc_reg->monitor_type = pnat_msb_monitor_type & 0xF;
    SX_GET_REG_FIELD(e_event_ctrl, outbox, REG_PPBMC_E_EVENT_CTRL_OFFSET);
    ppbmc_reg->e = (e_event_ctrl >> 6) & 0x3;
    ppbmc_reg->event_ctrl = e_event_ctrl & 0xF;
    SX_GET_REG_FIELD(ppbmc_reg->monitor_ctrl, outbox, REG_PPBMC_MONITOR_CTRL_OFFSET);
    SX_GET_REG_FIELD(ppbmc_reg->monitor_state, outbox, REG_PPBMC_MONITOR_STATE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPBMC(struct sx_dev *dev, struct ku_access_ppbmc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPBMC_encode,
                                  __PPBMC_decode,
                                  PPBMC_REG_LEN,
                                  &reg_data->ppbmc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPBMC);

/****************************************************
 * PPBMC (wrapper)
 *
 * on OOB system, it will call the register by EMAD
 * Otherwise, it will call it with Command Interface
 ***************************************************/
int sx_ACCESS_REG_PPBMC_wrapper(struct sx_dev *dev, u8 method, struct ku_access_ppbmc_reg *reg_data)
{
    if (is_sgmii_supported()) {
        /* PPBMC is common for all switch types. Some switches support command-interface over PCI and
         * Mantaray, that is using OOB, is using SGMII. Since the common call (sx_ACCESS_REG_PPBMC) is
         * auto generated, we must use a wrapper to decide which path to take.
         */
        return sgmii_emad_access_ppbmc(reg_data->dev_id, method, PPBMC_REG_LEN, &reg_data->ppbmc_reg);
    }

    return sx_ACCESS_REG_PPBMC(dev, reg_data);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPBMC_wrapper);

/************************************************
 * PPBME
 ***********************************************/
#define REG_PPBME_LOCAL_PORT_OFFSET            0x15
#define REG_PPBME_PNAT_MSB_MONITOR_TYPE_OFFSET 0x16
#define REG_PPBME_MONITOR_STATE_OFFSET         0x1B
#define PPBME_REG_LEN                          0x3

static int __PPBME_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppbme_reg *ppbme_reg = (struct ku_ppbme_reg*)ku_reg;
    u8                   pnat_msb_monitor_type;

    SX_PUT_REG_FIELD(inbox, ppbme_reg->local_port, REG_PPBME_LOCAL_PORT_OFFSET);
    pnat_msb_monitor_type = ((ppbme_reg->pnat & 0x3) << 6);
    pnat_msb_monitor_type |= ((ppbme_reg->lp_msb & 0x3) << 4);
    SX_PUT_REG_FIELD(inbox, pnat_msb_monitor_type, REG_PPBME_PNAT_MSB_MONITOR_TYPE_OFFSET);
    return 0;
}

static int __PPBME_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppbme_reg *ppbme_reg = (struct ku_ppbme_reg*)ku_reg;
    u8                   pnat_monitor_type;

    SX_GET_REG_FIELD(pnat_monitor_type, outbox, REG_PPBME_PNAT_MSB_MONITOR_TYPE_OFFSET);
    ppbme_reg->monitor_type = pnat_monitor_type & 0xF;
    SX_GET_REG_FIELD(ppbme_reg->monitor_state, outbox, REG_PPBME_MONITOR_STATE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPBME(struct sx_dev *dev, struct ku_access_ppbme_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPBME_encode,
                                  __PPBME_decode,
                                  PPBME_REG_LEN,
                                  &reg_data->ppbme_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPBME);


/************************************************
 * QPCR
 ***********************************************/
#define QPCR_REG_LEN               0x28
#define QPCR_LOCAL_PORT_MSB_OFFSET 0x14
#define QPCR_LOCAL_PORT_OFFSET     0x15
#define QPCR_GLOBAL_PID_OFFSET     0x16
#define QPCR_COUNTER_OFFSET        0x18
#define QPCR_COLOR_TO_TYPE_OFFSET  0x1a
#define QPCR_MODE_OFFSET           0x1b
#define QPCR_CBS_OFFSET            0x1c
#define QPCR_EBS_OFFSET            0x1d
#define QPCR_CIR_OFFSET            0x20
#define QPCR_EIR_OFFSET            0x24
#define QPCR_EXCEED_ACTION_OFFSET  0x2b
#define QPCR_VIOLATE_ACTION_OFFSET 0x2f
#define QPCR_VIOLATE_COUNT_OFFSET  0x34

static int __QPCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qpcr_reg *qpcr_reg = (struct ku_qpcr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;
    u16                 tmp_val_u16 = 0;

    tmp_val_u8 |= (qpcr_reg->lp_msb & 0x03);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, QPCR_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->port, QPCR_LOCAL_PORT_OFFSET);
    tmp_val_u16 |= (qpcr_reg->pid & 0x3fff);
    tmp_val_u16 |= (qpcr_reg->global_policer & 3) << 14;
    SX_PUT_REG_FIELD(inbox, tmp_val_u16, QPCR_GLOBAL_PID_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (qpcr_reg->clear_counter & 1) << 7;
    tmp_val_u8 |= (qpcr_reg->add_counter & 1) << 6;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, QPCR_COUNTER_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (qpcr_reg->color_aware & 1) << 7;
    tmp_val_u8 |= (qpcr_reg->use_bytes & 1) << 6;
    tmp_val_u8 |= (qpcr_reg->ir_units & 1) << 4;
    tmp_val_u8 |= (qpcr_reg->type & 3);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, QPCR_COLOR_TO_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->mode, QPCR_MODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->committed_burst_size, QPCR_CBS_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->extended_burst_size, QPCR_EBS_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->committed_information_rate, QPCR_CIR_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->excess_information_rate, QPCR_EIR_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->exceed_action, QPCR_EXCEED_ACTION_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->violate_action, QPCR_VIOLATE_ACTION_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->violate_count, QPCR_VIOLATE_COUNT_OFFSET);
    return 0;
}

static int __QPCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qpcr_reg *qpcr_reg = (struct ku_qpcr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;
    u16                 tmp_val_u16 = 0;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, QPCR_LOCAL_PORT_MSB_OFFSET);
    qpcr_reg->lp_msb = (tmp_val_u8 & 0x03);
    SX_GET_REG_FIELD(qpcr_reg->port, outbox, QPCR_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u16, outbox, QPCR_GLOBAL_PID_OFFSET);
    qpcr_reg->global_policer = (tmp_val_u16 >> 14) & 3;
    qpcr_reg->pid = (tmp_val_u16) & 0x3fff;

    tmp_val_u8 = 0;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, QPCR_COUNTER_OFFSET);
    qpcr_reg->clear_counter = (tmp_val_u8 >> 7) & 1;
    qpcr_reg->add_counter = (tmp_val_u8 >> 6) & 1;

    tmp_val_u8 = 0;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, QPCR_COLOR_TO_TYPE_OFFSET);
    qpcr_reg->color_aware = (tmp_val_u8 >> 7) & 1;
    qpcr_reg->use_bytes = (tmp_val_u8 >> 6) & 1;
    qpcr_reg->ir_units = (tmp_val_u8 >> 4) & 1;
    qpcr_reg->type = (tmp_val_u8) & 3;

    SX_GET_REG_FIELD(qpcr_reg->mode, outbox, QPCR_MODE_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->committed_burst_size, outbox, QPCR_CBS_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->extended_burst_size, outbox, QPCR_EBS_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->committed_information_rate, outbox, QPCR_CIR_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->excess_information_rate, outbox, QPCR_EIR_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->exceed_action, outbox, QPCR_EXCEED_ACTION_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->violate_action, outbox, QPCR_VIOLATE_ACTION_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->violate_count, outbox, QPCR_VIOLATE_COUNT_OFFSET);
    return 0;
}

int sx_ACCESS_REG_QPCR(struct sx_dev *dev, struct ku_access_qpcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QPCR_encode,
                                  __QPCR_decode,
                                  QPCR_REG_LEN,
                                  &reg_data->qpcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QPCR);

/************************************************
 * QPEM
 ***********************************************/
#define QPEM_LOCAL_PORT_OFFSET     0x15
#define QPEM_LOCAL_PORT_MSB_OFFSET 0x16
#define QPEM_RECORD0_OFFSET        0x18
#define QPEM_REG_LEN               65

static int __QPEM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qpem_reg *qpem_reg = (struct ku_qpem_reg*)ku_reg;
    u8                 *curr_switch_prio, *curr_ecn, *curr_color;
    u8                  tmp_u8 = 0;
    u32                 i, j, k;

    SX_PUT_REG_FIELD(inbox, qpem_reg->local_port, QPEM_LOCAL_PORT_OFFSET);
    tmp_u8 = (qpem_reg->lp_msb & 0x3) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, QPEM_LOCAL_PORT_MSB_OFFSET);

    for (i = 0; i < 16; i++) {
        curr_switch_prio = inbox + 4 + i * 16; /* 16 is the size of switch_prio record */
        for (j = 0; j < 4; j++) {
            curr_ecn = curr_switch_prio + j * 4; /* 4 is the size of ecn record */
            for (k = 0; k < 3; k++) {
                curr_color = curr_ecn + k; /* size of color record is 1 byte */
                *curr_color = ((qpem_reg->switch_prio[i].ecn[j].color[k].enable_exp & 0x1) << 7) |
                              (qpem_reg->switch_prio[i].ecn[j].color[k].exp & 0x7);
            }
        }
    }

    return 0;
}

static int __QPEM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qpem_reg *qpem_reg = (struct ku_qpem_reg*)ku_reg;
    u8                 *curr_switch_prio, *curr_ecn, *curr_color;
    u8                  tmp_u8 = 0;
    u32                 i, j, k;

    SX_GET_REG_FIELD(qpem_reg->local_port, outbox, QPEM_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, QPEM_LOCAL_PORT_MSB_OFFSET);
    qpem_reg->lp_msb = (tmp_u8 >> 4) & 0x3;

    for (i = 0; i < 16; i++) {
        curr_switch_prio = outbox + 4 + i * 16; /* 16 is the size of switch_prio record */
        for (j = 0; j < 4; j++) {
            curr_ecn = curr_switch_prio + j * 4; /* 4 is the size of ecn record */
            for (k = 0; k < 3; k++) {
                curr_color = curr_ecn + k; /* size of color record is 1 byte */
                qpem_reg->switch_prio[i].ecn[j].color[k].enable_exp = (*curr_color >> 7) & 0x1;
                qpem_reg->switch_prio[i].ecn[j].color[k].exp = (*curr_color) & 0x7;
            }
        }
    }

    return 0;
}

int sx_ACCESS_REG_QPEM(struct sx_dev *dev, struct ku_access_qpem_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QPEM_encode,
                                  __QPEM_decode,
                                  QPEM_REG_LEN,
                                  &reg_data->qpem_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QPEM);

/************************************************
 * SLRIP
 ***********************************************/
/* slrip
 * -----
 *
 */
/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, slrip, status, 0x0, 4, 4);

/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, slrip, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrip, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrip, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrip, lp_msb, 0x2, 4, 2);

/* lane
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrip, lane, 0x2, 0, 4);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrip, port_type, 0x3, 4, 4);

/* page_data_slrip_16nm_ib_sel
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ib_sel, 0x4, 5, 3);

/* page_data_slrip_16nm_ffe_tap0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap0, 0x8, 0, 8);

/* page_data_slrip_16nm_ffe_tap1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap1, 0x9, 0, 8);

/* page_data_slrip_16nm_ffe_tap2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap2, 0xa, 0, 8);

/* page_data_slrip_16nm_ffe_tap3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap3, 0xb, 0, 8);

/* page_data_slrip_16nm_ffe_tap4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap4, 0xc, 0, 8);

/* page_data_slrip_16nm_ffe_tap5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap5, 0xd, 0, 8);

/* page_data_slrip_16nm_ffe_tap6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap6, 0xe, 0, 8);

/* page_data_slrip_16nm_ffe_tap7
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap7, 0xf, 0, 8);

/* page_data_slrip_16nm_ffe_tap8
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_ffe_tap8, 0x10, 0, 8);

/* page_data_slrip_16nm_sel_enc0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_sel_enc0, 0x11, 0, 8);

/* page_data_slrip_16nm_ffe_tap_en
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_16nm_ffe_tap_en, 0x12, 0, 9);

/* page_data_slrip_16nm_sel_enc1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_sel_enc1, 0x14, 0, 8);

/* page_data_slrip_16nm_sel_enc2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_sel_enc2, 0x15, 0, 8);

/* page_data_slrip_16nm_mixer_offset0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_mixer_offset0, 0x16, 0, 8);

/* page_data_slrip_16nm_mixer_offset1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_mixer_offset1, 0x17, 0, 8);

/* page_data_slrip_16nm_saved0_sel_enc0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_saved0_sel_enc0, 0x18, 0, 8);

/* page_data_slrip_16nm_saved0_mixer_offset0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_saved0_mixer_offset0, 0x19, 0, 8);

/* page_data_slrip_16nm_saved1_sel_enc0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_saved1_sel_enc0, 0x1a, 0, 8);

/* page_data_slrip_16nm_saved1_mixer_offset0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_16nm_saved1_mixer_offset0, 0x1b, 0, 8);

/* page_data_slrip_7nm_feq_train_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_feq_train_mode, 0x7, 0, 4);

/* page_data_slrip_7nm_term_lpf_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_term_lpf_override_ctrl, 0x8, 4, 2);

/* page_data_slrip_7nm_vref_val_mode_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_vref_val_mode_ctrl, 0x8, 0, 2);

/* page_data_slrip_7nm_dffe_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_override_ctrl, 0x9, 4, 2);

/* page_data_slrip_7nm_vga_gain_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_vga_gain_override_ctrl, 0xa, 6, 2);

/* page_data_slrip_7nm_hf_gain_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_hf_gain_override_ctrl, 0xa, 4, 2);

/* page_data_slrip_7nm_mf_pole_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_mf_pole_override_ctrl, 0xa, 2, 2);

/* page_data_slrip_7nm_mf_gain_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_mf_gain_override_ctrl, 0xa, 0, 2);

/* page_data_slrip_7nm_lf_pole_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_lf_pole_override_ctrl, 0xb, 6, 2);

/* page_data_slrip_7nm_lf_gain_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_lf_gain_override_ctrl, 0xb, 4, 2);

/* page_data_slrip_7nm_dc_gain_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dc_gain_override_ctrl, 0xb, 2, 2);

/* page_data_slrip_7nm_term_attn_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_term_attn_override_ctrl, 0xb, 0, 2);

/* page_data_slrip_7nm_f1_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_f1_override_ctrl, 0xc, 6, 2);

/* page_data_slrip_7nm_f2_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_f2_override_ctrl, 0xc, 4, 2);

/* page_data_slrip_7nm_f3_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_f3_override_ctrl, 0xc, 2, 2);

/* page_data_slrip_7nm_f4_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_f4_override_ctrl, 0xc, 0, 2);

/* page_data_slrip_7nm_f5_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_f5_override_ctrl, 0xd, 6, 2);

/* page_data_slrip_7nm_f6_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_f6_override_ctrl, 0xd, 4, 2);

/* page_data_slrip_7nm_f7_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_f7_override_ctrl, 0xd, 2, 2);

/* page_data_slrip_7nm_f8_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_f8_override_ctrl, 0xd, 0, 2);

/* page_data_slrip_7nm_fm1_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_fm1_override_ctrl, 0xe, 6, 2);

/* page_data_slrip_7nm_fm2_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_fm2_override_ctrl, 0xe, 4, 2);

/* page_data_slrip_7nm_fm3_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_fm3_override_ctrl, 0xe, 2, 2);

/* page_data_slrip_7nm_eth_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_eth_override_ctrl, 0xf, 0, 8);

/* page_data_slrip_7nm_mf_pole
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_mf_pole, 0x10, 4, 3);

/* page_data_slrip_7nm_mf_gain
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_mf_gain, 0x10, 0, 3);

/* page_data_slrip_7nm_lf_pole
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_lf_pole, 0x11, 4, 3);

/* page_data_slrip_7nm_lf_gain
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_lf_gain, 0x11, 0, 3);

/* page_data_slrip_7nm_term_attn_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_term_attn_ctrl, 0x12, 0, 2);

/* page_data_slrip_7nm_hf_gain
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_hf_gain, 0x13, 4, 4);

/* page_data_slrip_7nm_dc_gain
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dc_gain, 0x13, 0, 3);

/* page_data_slrip_7nm_adc_vref_val
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_adc_vref_val, 0x16, 0, 6);

/* page_data_slrip_7nm_vga_gain
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_vga_gain, 0x17, 0, 3);

/* page_data_slrip_7nm_ffe_fm1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_fm1, 0x18, 0, 8);

/* page_data_slrip_7nm_ffe_fm2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_fm2, 0x19, 1, 7);

/* page_data_slrip_7nm_ffe_fm3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_fm3, 0x1a, 3, 5);

/* page_data_slrip_7nm_ffe_f4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_f4, 0x1c, 0, 6);

/* page_data_slrip_7nm_ffe_f3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_f3, 0x1d, 0, 6);

/* page_data_slrip_7nm_ffe_f2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_f2, 0x1e, 0, 7);

/* page_data_slrip_7nm_ffe_f1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_f1, 0x1f, 0, 8);

/* page_data_slrip_7nm_ffe_f8
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_f8, 0x20, 0, 4);

/* page_data_slrip_7nm_ffe_f7
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_f7, 0x21, 0, 5);

/* page_data_slrip_7nm_ffe_f6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_f6, 0x22, 0, 5);

/* page_data_slrip_7nm_ffe_f5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_ffe_f5, 0x23, 0, 6);

/* page_data_slrip_7nm_dffe_dsel3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel3, 0x24, 4, 3);

/* page_data_slrip_7nm_dffe_coef3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef3, 0x24, 0, 4);

/* page_data_slrip_7nm_dffe_dsel2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel2, 0x25, 4, 3);

/* page_data_slrip_7nm_dffe_coef2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef2, 0x25, 0, 4);

/* page_data_slrip_7nm_dffe_dsel1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel1, 0x26, 4, 3);

/* page_data_slrip_7nm_dffe_coef1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef1, 0x26, 0, 4);

/* page_data_slrip_7nm_dffe_dsel0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel0, 0x27, 4, 3);

/* page_data_slrip_7nm_dffe_coef0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef0, 0x27, 0, 4);

/* page_data_slrip_7nm_dffe_dsel7
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel7, 0x28, 4, 3);

/* page_data_slrip_7nm_dffe_coef7
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef7, 0x28, 0, 4);

/* page_data_slrip_7nm_dffe_dsel6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel6, 0x29, 4, 3);

/* page_data_slrip_7nm_dffe_coef6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef6, 0x29, 0, 4);

/* page_data_slrip_7nm_dffe_dsel5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel5, 0x2a, 4, 3);

/* page_data_slrip_7nm_dffe_coef5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef5, 0x2a, 0, 4);

/* page_data_slrip_7nm_dffe_dsel4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel4, 0x2b, 4, 3);

/* page_data_slrip_7nm_dffe_coef4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef4, 0x2b, 0, 4);

/* page_data_slrip_7nm_dffe_dsel8
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_dsel8, 0x2f, 4, 5);

/* page_data_slrip_7nm_dffe_coef8
 * Access: RW
 */
MLXSW_ITEM8(reg, slrip, page_data_slrip_7nm_dffe_coef8, 0x2f, 0, 4);

/* page_data_slrip_7nm_th1
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th1, 0x30, 0, 11);

/* page_data_slrip_7nm_th0
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th0, 0x32, 0, 11);

/* page_data_slrip_7nm_th3
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th3, 0x34, 0, 11);

/* page_data_slrip_7nm_th2
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th2, 0x36, 0, 11);

/* page_data_slrip_7nm_th5
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th5, 0x38, 0, 11);

/* page_data_slrip_7nm_th4
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th4, 0x3a, 0, 11);

/* page_data_slrip_7nm_th7
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th7, 0x3c, 0, 11);

/* page_data_slrip_7nm_th6
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th6, 0x3e, 0, 11);

/* page_data_slrip_7nm_th9
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th9, 0x40, 0, 11);

/* page_data_slrip_7nm_th8
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th8, 0x42, 0, 11);

/* page_data_slrip_7nm_th11
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th11, 0x44, 0, 11);

/* page_data_slrip_7nm_th10
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th10, 0x46, 0, 11);

/* page_data_slrip_7nm_th13
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th13, 0x48, 0, 11);

/* page_data_slrip_7nm_th12
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th12, 0x4a, 0, 11);

/* page_data_slrip_7nm_th15
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th15, 0x4c, 0, 11);

/* page_data_slrip_7nm_th14
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th14, 0x4e, 0, 11);

/* page_data_slrip_7nm_th17
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th17, 0x50, 0, 11);

/* page_data_slrip_7nm_th16
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th16, 0x52, 0, 11);

/* page_data_slrip_7nm_th19
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th19, 0x54, 0, 11);

/* page_data_slrip_7nm_th18
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th18, 0x56, 0, 11);

/* page_data_slrip_7nm_th21
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th21, 0x58, 0, 11);

/* page_data_slrip_7nm_th20
 * Access: RW
 */
MLXSW_ITEM16(reg, slrip, page_data_slrip_7nm_th20, 0x5a, 0, 11);

/* slrip
 * -----
 *
 */
#define MLXSW_SLRIP_ID  0x5057
#define MLXSW_SLRIP_LEN 0x5c

uint8_t mlxsw_reg_slrip_status_get(const char *buf);

uint8_t mlxsw_reg_slrip_version_get(const char *buf);

uint8_t mlxsw_reg_slrip_local_port_get(const char *buf);

void mlxsw_reg_slrip_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_pnat_get(const char *buf);

void mlxsw_reg_slrip_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_lp_msb_get(const char *buf);

void mlxsw_reg_slrip_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_lane_get(const char *buf);

void mlxsw_reg_slrip_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_port_type_get(const char *buf);

void mlxsw_reg_slrip_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ib_sel_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ib_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap1_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap2_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap3_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap4_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap5_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap6_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap7_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap7_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap8_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap8_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc0_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap_en_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap_en_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc1_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc2_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_mixer_offset0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_mixer_offset0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_mixer_offset1_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_mixer_offset1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_saved0_sel_enc0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_saved0_sel_enc0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_saved0_mixer_offset0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_saved0_mixer_offset0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_saved1_sel_enc0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_saved1_sel_enc0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_16nm_saved1_mixer_offset0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_16nm_saved1_mixer_offset0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_feq_train_mode_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_feq_train_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_term_lpf_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_term_lpf_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_vref_val_mode_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_vref_val_mode_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_vga_gain_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_vga_gain_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_hf_gain_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_hf_gain_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_mf_pole_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_mf_pole_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_mf_gain_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_mf_gain_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_lf_pole_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_lf_pole_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_lf_gain_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_lf_gain_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dc_gain_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dc_gain_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_term_attn_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_term_attn_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_f1_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_f1_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_f2_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_f2_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_f3_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_f3_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_f4_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_f4_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_f5_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_f5_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_f6_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_f6_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_f7_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_f7_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_f8_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_f8_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_fm1_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_fm1_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_fm2_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_fm2_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_fm3_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_fm3_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_eth_override_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_eth_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_mf_pole_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_mf_pole_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_mf_gain_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_mf_gain_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_lf_pole_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_lf_pole_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_lf_gain_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_lf_gain_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_term_attn_ctrl_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_term_attn_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_hf_gain_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_hf_gain_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dc_gain_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dc_gain_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_adc_vref_val_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_adc_vref_val_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_vga_gain_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_vga_gain_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm1_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm2_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm3_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f4_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f3_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f2_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f1_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f8_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f8_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f7_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f7_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f6_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f5_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel3_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef3_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel2_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef2_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel1_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef1_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel7_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel7_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef7_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef7_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel6_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef6_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel5_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef5_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel4_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef4_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel8_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel8_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef8_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef8_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th1_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th1_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th0_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th0_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th3_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th3_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th2_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th2_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th5_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th5_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th4_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th4_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th7_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th7_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th6_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th6_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th9_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th9_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th8_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th8_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th11_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th11_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th10_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th10_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th13_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th13_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th12_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th12_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th15_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th15_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th14_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th14_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th17_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th17_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th16_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th16_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th19_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th19_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th18_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th18_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th21_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th21_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrip_page_data_slrip_7nm_th20_get(const char *buf);

void mlxsw_reg_slrip_page_data_slrip_7nm_th20_set(char *buf, uint16_t val);

int __SLRIP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_slrip_reg *slrip_reg = (struct ku_slrip_reg*)ku_reg;

    mlxsw_reg_slrip_local_port_set(inbox, slrip_reg->local_port);
    mlxsw_reg_slrip_pnat_set(inbox, slrip_reg->pnat);
    mlxsw_reg_slrip_lp_msb_set(inbox, slrip_reg->lp_msb);
    mlxsw_reg_slrip_lane_set(inbox, slrip_reg->lane);
    mlxsw_reg_slrip_port_type_set(inbox, slrip_reg->port_type);
    switch (slrip_reg->version) {
    case 3: /*16nm*/
        mlxsw_reg_slrip_page_data_slrip_16nm_ib_sel_set(inbox, slrip_reg->page_data.slrip_16nm.ib_sel);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap0_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap0);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap1_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap1);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap2_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap2);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap3_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap3);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap4_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap4);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap5_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap5);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap6_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap6);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap7_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap7);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap8_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap8);
        mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc0_set(inbox, slrip_reg->page_data.slrip_16nm.sel_enc0);
        mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap_en_set(inbox, slrip_reg->page_data.slrip_16nm.ffe_tap_en);
        mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc1_set(inbox, slrip_reg->page_data.slrip_16nm.sel_enc1);
        mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc2_set(inbox, slrip_reg->page_data.slrip_16nm.sel_enc2);
        mlxsw_reg_slrip_page_data_slrip_16nm_mixer_offset0_set(inbox, slrip_reg->page_data.slrip_16nm.mixer_offset0);
        mlxsw_reg_slrip_page_data_slrip_16nm_mixer_offset1_set(inbox, slrip_reg->page_data.slrip_16nm.mixer_offset1);
        mlxsw_reg_slrip_page_data_slrip_16nm_saved0_sel_enc0_set(inbox,
                                                                 slrip_reg->page_data.slrip_16nm.saved0_sel_enc0);
        mlxsw_reg_slrip_page_data_slrip_16nm_saved0_mixer_offset0_set(inbox,
                                                                      slrip_reg->page_data.slrip_16nm.saved0_mixer_offset0);
        mlxsw_reg_slrip_page_data_slrip_16nm_saved1_sel_enc0_set(inbox,
                                                                 slrip_reg->page_data.slrip_16nm.saved1_sel_enc0);
        mlxsw_reg_slrip_page_data_slrip_16nm_saved1_mixer_offset0_set(inbox,
                                                                      slrip_reg->page_data.slrip_16nm.saved1_mixer_offset0);
        break;

    case 4: /*7nm*/
        mlxsw_reg_slrip_page_data_slrip_7nm_feq_train_mode_set(inbox, slrip_reg->page_data.slrip_7nm.feq_train_mode);
        mlxsw_reg_slrip_page_data_slrip_7nm_term_lpf_override_ctrl_set(inbox,
                                                                       slrip_reg->page_data.slrip_7nm.term_lpf_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_vref_val_mode_ctrl_set(inbox,
                                                                   slrip_reg->page_data.slrip_7nm.vref_val_mode_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_override_ctrl_set(inbox,
                                                                   slrip_reg->page_data.slrip_7nm.dffe_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_vga_gain_override_ctrl_set(inbox,
                                                                       slrip_reg->page_data.slrip_7nm.vga_gain_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_hf_gain_override_ctrl_set(inbox,
                                                                      slrip_reg->page_data.slrip_7nm.hf_gain_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_mf_pole_override_ctrl_set(inbox,
                                                                      slrip_reg->page_data.slrip_7nm.mf_pole_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_mf_gain_override_ctrl_set(inbox,
                                                                      slrip_reg->page_data.slrip_7nm.mf_gain_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_lf_pole_override_ctrl_set(inbox,
                                                                      slrip_reg->page_data.slrip_7nm.lf_pole_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_lf_gain_override_ctrl_set(inbox,
                                                                      slrip_reg->page_data.slrip_7nm.lf_gain_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_dc_gain_override_ctrl_set(inbox,
                                                                      slrip_reg->page_data.slrip_7nm.dc_gain_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_term_attn_override_ctrl_set(inbox,
                                                                        slrip_reg->page_data.slrip_7nm.term_attn_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_f1_override_ctrl_set(inbox,
                                                                 slrip_reg->page_data.slrip_7nm.f1_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_f2_override_ctrl_set(inbox,
                                                                 slrip_reg->page_data.slrip_7nm.f2_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_f3_override_ctrl_set(inbox,
                                                                 slrip_reg->page_data.slrip_7nm.f3_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_f4_override_ctrl_set(inbox,
                                                                 slrip_reg->page_data.slrip_7nm.f4_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_f5_override_ctrl_set(inbox,
                                                                 slrip_reg->page_data.slrip_7nm.f5_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_f6_override_ctrl_set(inbox,
                                                                 slrip_reg->page_data.slrip_7nm.f6_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_f7_override_ctrl_set(inbox,
                                                                 slrip_reg->page_data.slrip_7nm.f7_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_f8_override_ctrl_set(inbox,
                                                                 slrip_reg->page_data.slrip_7nm.f8_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_fm1_override_ctrl_set(inbox,
                                                                  slrip_reg->page_data.slrip_7nm.fm1_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_fm2_override_ctrl_set(inbox,
                                                                  slrip_reg->page_data.slrip_7nm.fm2_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_fm3_override_ctrl_set(inbox,
                                                                  slrip_reg->page_data.slrip_7nm.fm3_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_eth_override_ctrl_set(inbox,
                                                                  slrip_reg->page_data.slrip_7nm.eth_override_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_mf_pole_set(inbox, slrip_reg->page_data.slrip_7nm.mf_pole);
        mlxsw_reg_slrip_page_data_slrip_7nm_mf_gain_set(inbox, slrip_reg->page_data.slrip_7nm.mf_gain);
        mlxsw_reg_slrip_page_data_slrip_7nm_lf_pole_set(inbox, slrip_reg->page_data.slrip_7nm.lf_pole);
        mlxsw_reg_slrip_page_data_slrip_7nm_lf_gain_set(inbox, slrip_reg->page_data.slrip_7nm.lf_gain);
        mlxsw_reg_slrip_page_data_slrip_7nm_term_attn_ctrl_set(inbox, slrip_reg->page_data.slrip_7nm.term_attn_ctrl);
        mlxsw_reg_slrip_page_data_slrip_7nm_hf_gain_set(inbox, slrip_reg->page_data.slrip_7nm.hf_gain);
        mlxsw_reg_slrip_page_data_slrip_7nm_dc_gain_set(inbox, slrip_reg->page_data.slrip_7nm.dc_gain);
        mlxsw_reg_slrip_page_data_slrip_7nm_adc_vref_val_set(inbox, slrip_reg->page_data.slrip_7nm.adc_vref_val);
        mlxsw_reg_slrip_page_data_slrip_7nm_vga_gain_set(inbox, slrip_reg->page_data.slrip_7nm.vga_gain);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm1_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_fm1);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm2_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_fm2);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm3_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_fm3);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f4_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_f4);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f3_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_f3);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f2_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_f2);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f1_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_f1);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f8_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_f8);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f7_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_f7);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f6_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_f6);
        mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f5_set(inbox, slrip_reg->page_data.slrip_7nm.ffe_f5);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel3_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel3);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef3_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef3);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel2_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel2);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef2_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef2);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel1_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel1);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef1_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef1);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel0_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel0);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef0_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef0);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel7_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel7);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef7_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef7);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel6_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel6);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef6_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef6);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel5_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel5);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef5_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef5);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel4_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel4);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef4_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef4);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel8_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_dsel8);
        mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef8_set(inbox, slrip_reg->page_data.slrip_7nm.dffe_coef8);
        mlxsw_reg_slrip_page_data_slrip_7nm_th1_set(inbox, slrip_reg->page_data.slrip_7nm.th1);
        mlxsw_reg_slrip_page_data_slrip_7nm_th0_set(inbox, slrip_reg->page_data.slrip_7nm.th0);
        mlxsw_reg_slrip_page_data_slrip_7nm_th3_set(inbox, slrip_reg->page_data.slrip_7nm.th3);
        mlxsw_reg_slrip_page_data_slrip_7nm_th2_set(inbox, slrip_reg->page_data.slrip_7nm.th2);
        mlxsw_reg_slrip_page_data_slrip_7nm_th5_set(inbox, slrip_reg->page_data.slrip_7nm.th5);
        mlxsw_reg_slrip_page_data_slrip_7nm_th4_set(inbox, slrip_reg->page_data.slrip_7nm.th4);
        mlxsw_reg_slrip_page_data_slrip_7nm_th7_set(inbox, slrip_reg->page_data.slrip_7nm.th7);
        mlxsw_reg_slrip_page_data_slrip_7nm_th6_set(inbox, slrip_reg->page_data.slrip_7nm.th6);
        mlxsw_reg_slrip_page_data_slrip_7nm_th9_set(inbox, slrip_reg->page_data.slrip_7nm.th9);
        mlxsw_reg_slrip_page_data_slrip_7nm_th8_set(inbox, slrip_reg->page_data.slrip_7nm.th8);
        mlxsw_reg_slrip_page_data_slrip_7nm_th11_set(inbox, slrip_reg->page_data.slrip_7nm.th11);
        mlxsw_reg_slrip_page_data_slrip_7nm_th10_set(inbox, slrip_reg->page_data.slrip_7nm.th10);
        mlxsw_reg_slrip_page_data_slrip_7nm_th13_set(inbox, slrip_reg->page_data.slrip_7nm.th13);
        mlxsw_reg_slrip_page_data_slrip_7nm_th12_set(inbox, slrip_reg->page_data.slrip_7nm.th12);
        mlxsw_reg_slrip_page_data_slrip_7nm_th15_set(inbox, slrip_reg->page_data.slrip_7nm.th15);
        mlxsw_reg_slrip_page_data_slrip_7nm_th14_set(inbox, slrip_reg->page_data.slrip_7nm.th14);
        mlxsw_reg_slrip_page_data_slrip_7nm_th17_set(inbox, slrip_reg->page_data.slrip_7nm.th17);
        mlxsw_reg_slrip_page_data_slrip_7nm_th16_set(inbox, slrip_reg->page_data.slrip_7nm.th16);
        mlxsw_reg_slrip_page_data_slrip_7nm_th19_set(inbox, slrip_reg->page_data.slrip_7nm.th19);
        mlxsw_reg_slrip_page_data_slrip_7nm_th18_set(inbox, slrip_reg->page_data.slrip_7nm.th18);
        mlxsw_reg_slrip_page_data_slrip_7nm_th21_set(inbox, slrip_reg->page_data.slrip_7nm.th21);
        mlxsw_reg_slrip_page_data_slrip_7nm_th20_set(inbox, slrip_reg->page_data.slrip_7nm.th20);
        break;

    default:
        break;
    }

    return 0;
}

int __SLRIP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_slrip_reg *slrip_reg = (struct ku_slrip_reg*)ku_reg;

    slrip_reg->status = mlxsw_reg_slrip_status_get(outbox);
    slrip_reg->version = mlxsw_reg_slrip_version_get(outbox);
    slrip_reg->local_port = mlxsw_reg_slrip_local_port_get(outbox);
    slrip_reg->pnat = mlxsw_reg_slrip_pnat_get(outbox);
    slrip_reg->lp_msb = mlxsw_reg_slrip_lp_msb_get(outbox);
    slrip_reg->lane = mlxsw_reg_slrip_lane_get(outbox);
    slrip_reg->port_type = mlxsw_reg_slrip_port_type_get(outbox);
    switch (slrip_reg->version) {
    case 3: /* 16nm */
        slrip_reg->page_data.slrip_16nm.ib_sel = mlxsw_reg_slrip_page_data_slrip_16nm_ib_sel_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap0 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap0_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap1 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap1_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap2 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap2_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap3 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap3_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap4 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap4_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap5 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap5_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap6 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap6_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap7 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap7_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap8 = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap8_get(outbox);
        slrip_reg->page_data.slrip_16nm.sel_enc0 = mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc0_get(outbox);
        slrip_reg->page_data.slrip_16nm.ffe_tap_en = mlxsw_reg_slrip_page_data_slrip_16nm_ffe_tap_en_get(outbox);
        slrip_reg->page_data.slrip_16nm.sel_enc1 = mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc1_get(outbox);
        slrip_reg->page_data.slrip_16nm.sel_enc2 = mlxsw_reg_slrip_page_data_slrip_16nm_sel_enc2_get(outbox);
        slrip_reg->page_data.slrip_16nm.mixer_offset0 = mlxsw_reg_slrip_page_data_slrip_16nm_mixer_offset0_get(outbox);
        slrip_reg->page_data.slrip_16nm.mixer_offset1 = mlxsw_reg_slrip_page_data_slrip_16nm_mixer_offset1_get(outbox);
        slrip_reg->page_data.slrip_16nm.saved0_sel_enc0 = mlxsw_reg_slrip_page_data_slrip_16nm_saved0_sel_enc0_get(
            outbox);
        slrip_reg->page_data.slrip_16nm.saved0_mixer_offset0 =
            mlxsw_reg_slrip_page_data_slrip_16nm_saved0_mixer_offset0_get(outbox);
        slrip_reg->page_data.slrip_16nm.saved1_sel_enc0 = mlxsw_reg_slrip_page_data_slrip_16nm_saved1_sel_enc0_get(
            outbox);
        slrip_reg->page_data.slrip_16nm.saved1_mixer_offset0 =
            mlxsw_reg_slrip_page_data_slrip_16nm_saved1_mixer_offset0_get(outbox);
        break;

    case 4: /* 7nm */
        slrip_reg->page_data.slrip_7nm.feq_train_mode = mlxsw_reg_slrip_page_data_slrip_7nm_feq_train_mode_get(outbox);
        slrip_reg->page_data.slrip_7nm.term_lpf_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_term_lpf_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.vref_val_mode_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_vref_val_mode_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.dffe_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.vga_gain_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_vga_gain_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.hf_gain_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_hf_gain_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.mf_pole_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_mf_pole_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.mf_gain_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_mf_gain_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.lf_pole_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_lf_pole_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.lf_gain_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_lf_gain_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.dc_gain_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_dc_gain_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.term_attn_override_ctrl =
            mlxsw_reg_slrip_page_data_slrip_7nm_term_attn_override_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.f1_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_f1_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.f2_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_f2_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.f3_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_f3_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.f4_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_f4_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.f5_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_f5_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.f6_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_f6_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.f7_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_f7_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.f8_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_f8_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.fm1_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_fm1_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.fm2_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_fm2_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.fm3_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_fm3_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.eth_override_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_eth_override_ctrl_get(
            outbox);
        slrip_reg->page_data.slrip_7nm.mf_pole = mlxsw_reg_slrip_page_data_slrip_7nm_mf_pole_get(outbox);
        slrip_reg->page_data.slrip_7nm.mf_gain = mlxsw_reg_slrip_page_data_slrip_7nm_mf_gain_get(outbox);
        slrip_reg->page_data.slrip_7nm.lf_pole = mlxsw_reg_slrip_page_data_slrip_7nm_lf_pole_get(outbox);
        slrip_reg->page_data.slrip_7nm.lf_gain = mlxsw_reg_slrip_page_data_slrip_7nm_lf_gain_get(outbox);
        slrip_reg->page_data.slrip_7nm.term_attn_ctrl = mlxsw_reg_slrip_page_data_slrip_7nm_term_attn_ctrl_get(outbox);
        slrip_reg->page_data.slrip_7nm.hf_gain = mlxsw_reg_slrip_page_data_slrip_7nm_hf_gain_get(outbox);
        slrip_reg->page_data.slrip_7nm.dc_gain = mlxsw_reg_slrip_page_data_slrip_7nm_dc_gain_get(outbox);
        slrip_reg->page_data.slrip_7nm.adc_vref_val = mlxsw_reg_slrip_page_data_slrip_7nm_adc_vref_val_get(outbox);
        slrip_reg->page_data.slrip_7nm.vga_gain = mlxsw_reg_slrip_page_data_slrip_7nm_vga_gain_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_fm1 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm1_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_fm2 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm2_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_fm3 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_fm3_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_f4 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f4_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_f3 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f3_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_f2 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f2_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_f1 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f1_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_f8 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f8_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_f7 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f7_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_f6 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f6_get(outbox);
        slrip_reg->page_data.slrip_7nm.ffe_f5 = mlxsw_reg_slrip_page_data_slrip_7nm_ffe_f5_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel3 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel3_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef3 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef3_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel2 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel2_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef2 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef2_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel1 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel1_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef1 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef1_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel0 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel0_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef0 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef0_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel7 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel7_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef7 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef7_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel6 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel6_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef6 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef6_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel5 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel5_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef5 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef5_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel4 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel4_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef4 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef4_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_dsel8 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_dsel8_get(outbox);
        slrip_reg->page_data.slrip_7nm.dffe_coef8 = mlxsw_reg_slrip_page_data_slrip_7nm_dffe_coef8_get(outbox);
        slrip_reg->page_data.slrip_7nm.th1 = mlxsw_reg_slrip_page_data_slrip_7nm_th1_get(outbox);
        slrip_reg->page_data.slrip_7nm.th0 = mlxsw_reg_slrip_page_data_slrip_7nm_th0_get(outbox);
        slrip_reg->page_data.slrip_7nm.th3 = mlxsw_reg_slrip_page_data_slrip_7nm_th3_get(outbox);
        slrip_reg->page_data.slrip_7nm.th2 = mlxsw_reg_slrip_page_data_slrip_7nm_th2_get(outbox);
        slrip_reg->page_data.slrip_7nm.th5 = mlxsw_reg_slrip_page_data_slrip_7nm_th5_get(outbox);
        slrip_reg->page_data.slrip_7nm.th4 = mlxsw_reg_slrip_page_data_slrip_7nm_th4_get(outbox);
        slrip_reg->page_data.slrip_7nm.th7 = mlxsw_reg_slrip_page_data_slrip_7nm_th7_get(outbox);
        slrip_reg->page_data.slrip_7nm.th6 = mlxsw_reg_slrip_page_data_slrip_7nm_th6_get(outbox);
        slrip_reg->page_data.slrip_7nm.th9 = mlxsw_reg_slrip_page_data_slrip_7nm_th9_get(outbox);
        slrip_reg->page_data.slrip_7nm.th8 = mlxsw_reg_slrip_page_data_slrip_7nm_th8_get(outbox);
        slrip_reg->page_data.slrip_7nm.th11 = mlxsw_reg_slrip_page_data_slrip_7nm_th11_get(outbox);
        slrip_reg->page_data.slrip_7nm.th10 = mlxsw_reg_slrip_page_data_slrip_7nm_th10_get(outbox);
        slrip_reg->page_data.slrip_7nm.th13 = mlxsw_reg_slrip_page_data_slrip_7nm_th13_get(outbox);
        slrip_reg->page_data.slrip_7nm.th12 = mlxsw_reg_slrip_page_data_slrip_7nm_th12_get(outbox);
        slrip_reg->page_data.slrip_7nm.th15 = mlxsw_reg_slrip_page_data_slrip_7nm_th15_get(outbox);
        slrip_reg->page_data.slrip_7nm.th14 = mlxsw_reg_slrip_page_data_slrip_7nm_th14_get(outbox);
        slrip_reg->page_data.slrip_7nm.th17 = mlxsw_reg_slrip_page_data_slrip_7nm_th17_get(outbox);
        slrip_reg->page_data.slrip_7nm.th16 = mlxsw_reg_slrip_page_data_slrip_7nm_th16_get(outbox);
        slrip_reg->page_data.slrip_7nm.th19 = mlxsw_reg_slrip_page_data_slrip_7nm_th19_get(outbox);
        slrip_reg->page_data.slrip_7nm.th18 = mlxsw_reg_slrip_page_data_slrip_7nm_th18_get(outbox);
        slrip_reg->page_data.slrip_7nm.th21 = mlxsw_reg_slrip_page_data_slrip_7nm_th21_get(outbox);
        slrip_reg->page_data.slrip_7nm.th20 = mlxsw_reg_slrip_page_data_slrip_7nm_th20_get(outbox);
        break;

    default:
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__SLRIP_decode);

int sx_ACCESS_REG_SLRIP(struct sx_dev *dev, struct ku_access_slrip_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SLRIP_LEN >> 2) + 1;

    if (MLXSW_SLRIP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLRIP_encode,
                                  __SLRIP_decode,
                                  reg_len_dword,
                                  &reg_data->slrip_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLRIP);

int sx_EMAD_ACCESS_REG_SLRIP(struct sx_dev                  *dev,
                             emad_prio_e                     priority,
                             sx_emad_method_e                method,
                             const struct sx_emad_in_params *in_params,
                             struct sx_emad_out_params      *out_params,
                             struct ku_slrip_reg            *reg)
{
    u16 reg_len_dword = (MLXSW_SLRIP_LEN >> 2) + 1;

    if (MLXSW_SLRIP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SLRIP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SLRIP_encode,
                                     __SLRIP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SLRIP);

/************************************************
 * SLRP
 ***********************************************/

/* slrp
 * ----
 *
 */
/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, status, 0x0, 4, 4);

/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrp, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrp, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrp, lp_msb, 0x2, 4, 2);

/* lane
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrp, lane, 0x2, 0, 4);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrp, port_type, 0x3, 4, 4);

/* page_data_slrp_40nm_28nm_ib_sel
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ib_sel, 0x4, 6, 2);

/* page_data_slrp_40nm_28nm_dp_sel
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_dp_sel, 0x6, 4, 1);

/* page_data_slrp_40nm_28nm_dp90sel
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_dp90sel, 0x6, 0, 4);

/* page_data_slrp_40nm_28nm_mix90phase
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_mix90phase, 0x7, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap0, 0x8, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap1, 0x9, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap2, 0xa, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap3, 0xb, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap4, 0xc, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap5, 0xd, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap6, 0xe, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap7
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap7, 0xf, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap8
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap8, 0x10, 0, 8);

/* page_data_slrp_40nm_28nm_mixerbias_tap_amp
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_mixerbias_tap_amp, 0x11, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap_en
 * Access: RW
 */
MLXSW_ITEM16(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap_en, 0x12, 0, 9);

/* page_data_slrp_40nm_28nm_ffe_tap_offset0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap_offset0, 0x14, 0, 8);

/* page_data_slrp_40nm_28nm_ffe_tap_offset1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ffe_tap_offset1, 0x15, 0, 8);

/* page_data_slrp_40nm_28nm_slicer_offset0
 * Access: RW
 */
MLXSW_ITEM16(reg, slrp, page_data_slrp_40nm_28nm_slicer_offset0, 0x16, 0, 16);

/* page_data_slrp_40nm_28nm_mixer_offset0
 * Access: RW
 */
MLXSW_ITEM16(reg, slrp, page_data_slrp_40nm_28nm_mixer_offset0, 0x18, 0, 16);

/* page_data_slrp_40nm_28nm_mixer_offset1
 * Access: RW
 */
MLXSW_ITEM16(reg, slrp, page_data_slrp_40nm_28nm_mixer_offset1, 0x1a, 0, 16);

/* page_data_slrp_40nm_28nm_mixerbgn_inp
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_mixerbgn_inp, 0x1c, 0, 8);

/* page_data_slrp_40nm_28nm_mixerbgn_inn
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_mixerbgn_inn, 0x1d, 0, 8);

/* page_data_slrp_40nm_28nm_mixerbgn_refp
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_mixerbgn_refp, 0x1e, 0, 8);

/* page_data_slrp_40nm_28nm_mixerbgn_refn
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_mixerbgn_refn, 0x1f, 0, 8);

/* page_data_slrp_40nm_28nm_sel_slicer_lctrl_h
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_sel_slicer_lctrl_h, 0x20, 7, 1);

/* page_data_slrp_40nm_28nm_sel_slicer_lctrl_l
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_sel_slicer_lctrl_l, 0x20, 6, 1);

/* page_data_slrp_40nm_28nm_ref_mixer_vreg
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_ref_mixer_vreg, 0x20, 0, 5);

/* page_data_slrp_40nm_28nm_slicer_gctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_slicer_gctrl, 0x21, 0, 8);

/* page_data_slrp_40nm_28nm_lctrl_input
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_lctrl_input, 0x22, 0, 8);

/* page_data_slrp_40nm_28nm_mixer_offset_cm1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_mixer_offset_cm1, 0x23, 0, 8);

/* page_data_slrp_40nm_28nm_common_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_40nm_28nm_common_mode, 0x24, 2, 6);

/* page_data_slrp_40nm_28nm_mixer_offset_cm0
 * Access: RW
 */
MLXSW_ITEM16(reg, slrp, page_data_slrp_40nm_28nm_mixer_offset_cm0, 0x24, 0, 9);

/* page_data_slrp_40nm_28nm_slicer_offset_cm
 * Access: RW
 */
MLXSW_ITEM16(reg, slrp, page_data_slrp_40nm_28nm_slicer_offset_cm, 0x26, 0, 9);

/* page_data_slrp_16nm_mixer_offset_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_mixer_offset_up, 0x4, 0, 8);

/* page_data_slrp_16nm_mixer_offset_down
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_mixer_offset_down, 0x5, 0, 8);

/* page_data_slrp_16nm_sel_enc
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_enc, 0x6, 0, 8);

/* page_data_slrp_16nm_dp_sel
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_dp_sel, 0x7, 0, 2);

/* page_data_slrp_16nm_sel_ref_in_mixer_biasgen_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_ref_in_mixer_biasgen_up, 0x8, 4, 4);

/* page_data_slrp_16nm_sel_ref_in_mixer_biasgen_mid
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_ref_in_mixer_biasgen_mid, 0x8, 0, 4);

/* page_data_slrp_16nm_sel_ref_in_mixer_biasgen_down
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_ref_in_mixer_biasgen_down, 0x9, 4, 4);

/* page_data_slrp_16nm_sel_ref_in_mixer_biasgen_eo
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_ref_in_mixer_biasgen_eo, 0x9, 0, 4);

/* page_data_slrp_16nm_sel_ref_out_mixer_biasgen_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_ref_out_mixer_biasgen_up, 0xa, 4, 4);

/* page_data_slrp_16nm_sel_ref_out_mixer_biasgen_mid
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_ref_out_mixer_biasgen_mid, 0xa, 0, 4);

/* page_data_slrp_16nm_sel_ref_out_mixer_biasgen_down
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_ref_out_mixer_biasgen_down, 0xb, 4, 4);

/* page_data_slrp_16nm_sel_ref_out_mixer_biasgen_eo
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_ref_out_mixer_biasgen_eo, 0xb, 0, 4);

/* page_data_slrp_16nm_sel_amp_mixer_biasgen_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_amp_mixer_biasgen_up, 0xc, 6, 2);

/* page_data_slrp_16nm_sel_amp_mixer_biasgen_mid
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_amp_mixer_biasgen_mid, 0xc, 4, 2);

/* page_data_slrp_16nm_sel_amp_mixer_biasgen_down
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_amp_mixer_biasgen_down, 0xc, 2, 2);

/* page_data_slrp_16nm_sel_amp_mixer_biasgen_eo
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_amp_mixer_biasgen_eo, 0xc, 0, 2);

/* page_data_slrp_16nm_mixer_offset_eye_scan
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_mixer_offset_eye_scan, 0xd, 0, 8);

/* page_data_slrp_16nm_gctrl_bin_bgn0_n
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_gctrl_bin_bgn0_n, 0xe, 4, 4);

/* page_data_slrp_16nm_gctrl_bin_bgn0_p
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_gctrl_bin_bgn0_p, 0xe, 0, 4);

/* page_data_slrp_16nm_gctrl_bin_bgn1_n
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_gctrl_bin_bgn1_n, 0xf, 4, 4);

/* page_data_slrp_16nm_gctrl_bin_bgn1_p
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_gctrl_bin_bgn1_p, 0xf, 0, 4);

/* page_data_slrp_16nm_sel_digital_gctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_digital_gctrl, 0x10, 7, 1);

/* page_data_slrp_16nm_sel_bias2ctle
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_bias2ctle, 0x10, 0, 7);

/* page_data_slrp_16nm_selgc_ref_op0_alev_ctle
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_selgc_ref_op0_alev_ctle, 0x11, 3, 5);

/* page_data_slrp_16nm_selgc_ref_op1_alev_ctle
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_selgc_ref_op1_alev_ctle, 0x12, 6, 5);

/* page_data_slrp_16nm_sel_bias_en_0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_bias_en_0, 0x12, 2, 4);

/* page_data_slrp_16nm_sel_bias_en_1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_bias_en_1, 0x13, 6, 4);

/* page_data_slrp_16nm_sel_bias_en_2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_bias_en_2, 0x13, 2, 4);

/* page_data_slrp_16nm_sel_bias_en_3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_bias_en_3, 0x14, 4, 4);

/* page_data_slrp_16nm_sel_bias_en_4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_bias_en_4, 0x14, 0, 4);

/* page_data_slrp_16nm_sel_bias_en_5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_bias_en_5, 0x15, 4, 4);

/* page_data_slrp_16nm_sel_bias_en_6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_bias_en_6, 0x16, 7, 5);

/* page_data_slrp_16nm_sel_gctrln_en_0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrln_en_0, 0x16, 3, 4);

/* page_data_slrp_16nm_sel_gctrln_en_1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrln_en_1, 0x17, 7, 4);

/* page_data_slrp_16nm_sel_gctrln_en_2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrln_en_2, 0x17, 3, 4);

/* page_data_slrp_16nm_sel_gctrln_en_3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrln_en_3, 0x18, 4, 4);

/* page_data_slrp_16nm_sel_gctrln_en_4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrln_en_4, 0x18, 0, 4);

/* page_data_slrp_16nm_sel_gctrln_en_5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrln_en_5, 0x19, 4, 4);

/* page_data_slrp_16nm_sel_gctrln_en_6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrln_en_6, 0x19, 0, 4);

/* page_data_slrp_16nm_sel_gctrlp_en_0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrlp_en_0, 0x1a, 4, 4);

/* page_data_slrp_16nm_sel_gctrlp_en_1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrlp_en_1, 0x1a, 0, 4);

/* page_data_slrp_16nm_sel_gctrlp_en_2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrlp_en_2, 0x1b, 4, 4);

/* page_data_slrp_16nm_sel_gctrlp_en_3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrlp_en_3, 0x1b, 0, 4);

/* page_data_slrp_16nm_sel_gctrlp_en_4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrlp_en_4, 0x1c, 4, 4);

/* page_data_slrp_16nm_sel_gctrlp_en_5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrlp_en_5, 0x1c, 0, 4);

/* page_data_slrp_16nm_sel_gctrlp_en_6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_sel_gctrlp_en_6, 0x1d, 4, 4);

/* page_data_slrp_16nm_crnt_bgn_offset_p1
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_crnt_bgn_offset_p1, 0x1e, 7, 5);

/* page_data_slrp_16nm_crnt_bgn_offset_n1
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_crnt_bgn_offset_n1, 0x1e, 2, 5);

/* page_data_slrp_16nm_crnt_bgn_offset_p0
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_crnt_bgn_offset_p0, 0x1f, 5, 5);

/* page_data_slrp_16nm_crnt_bgn_offset_n0
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_16nm_crnt_bgn_offset_n0, 0x1f, 0, 5);

/* page_data_slrp_gearbox_ffe_tap_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_ffe_tap_index, 0x6, 0, 4);

/* page_data_slrp_gearbox_ffe_sub_channel
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_ffe_sub_channel, 0x7, 0, 5);

/* page_data_slrp_gearbox_snr_en
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_snr_en, 0x8, 7, 1);

/* page_data_slrp_gearbox_dsp_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_dsp_mode, 0x9, 7, 4);

/* page_data_slrp_gearbox_afe_trim
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_afe_trim, 0x9, 0, 4);

/* page_data_slrp_gearbox_ctle
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_ctle, 0xb, 0, 8);

/* page_data_slrp_gearbox_raw_snr_value
 * Access: RO
 */
MLXSW_ITEM16(reg, slrp, page_data_slrp_gearbox_raw_snr_value, 0xc, 0, 16);

/* page_data_slrp_gearbox_dsp_err_gen
 * Access: WO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_dsp_err_gen, 0xe, 0, 2);

/* page_data_slrp_gearbox_snr_sym_cnt
 * Access: WO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_snr_sym_cnt, 0xf, 0, 3);

/* page_data_slrp_gearbox_db_snr_value
 * Access: RO
 */
MLXSW_ITEM32(reg, slrp, page_data_slrp_gearbox_db_snr_value, 0x10, 0, 32);

/* page_data_slrp_gearbox_ffe_tap_value
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_gearbox_ffe_tap_value, 0x17, 0, 8);

/* page_data_slrp_usr_mixer00
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_mixer00, 0x4, 1, 7);

/* page_data_slrp_usr_mixer90
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_mixer90, 0x5, 2, 7);

/* page_data_slrp_usr_termination
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_termination, 0x6, 6, 4);

/* page_data_slrp_usr_neg_cap_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_neg_cap_up, 0x8, 6, 2);

/* page_data_slrp_usr_neg_cap_mid
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_neg_cap_mid, 0x8, 4, 2);

/* page_data_slrp_usr_neg_cap_dn
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_neg_cap_dn, 0x8, 2, 2);

/* page_data_slrp_usr_offset_coarse_polarity_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_coarse_polarity_up, 0x8, 1, 1);

/* page_data_slrp_usr_offset_coarse_polarity_mid
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_coarse_polarity_mid, 0x8, 0, 1);

/* page_data_slrp_usr_offset_coarse_polarity_dn
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_coarse_polarity_dn, 0x9, 7, 1);

/* page_data_slrp_usr_offset_fine_polarity_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_fine_polarity_up, 0x9, 6, 1);

/* page_data_slrp_usr_offset_fine_polarity_mid
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_fine_polarity_mid, 0x9, 5, 1);

/* page_data_slrp_usr_offset_fine_polarity_dn
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_fine_polarity_dn, 0x9, 4, 1);

/* page_data_slrp_usr_amp_vga
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_amp_vga, 0xa, 0, 5);

/* page_data_slrp_usr_amp_vga_last_stage
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_amp_vga_last_stage, 0xb, 0, 5);

/* page_data_slrp_usr_offset_coarse_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_coarse_up, 0xc, 2, 6);

/* page_data_slrp_usr_offset_coarse_mid
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_coarse_mid, 0xd, 4, 6);

/* page_data_slrp_usr_offset_coarse_dn
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_coarse_dn, 0xe, 6, 6);

/* page_data_slrp_usr_offset_fine_up
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_fine_up, 0xe, 2, 4);

/* page_data_slrp_usr_offset_fine_mid
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_fine_mid, 0xf, 6, 4);

/* page_data_slrp_usr_offset_fine_dn
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_usr_offset_fine_dn, 0xf, 2, 4);

/* page_data_slrp_7nm_adc_recording_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_adc_recording_admin, 0x4, 4, 2);

/* page_data_slrp_7nm_adc_recording_status
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_adc_recording_status, 0x4, 0, 2);

/* page_data_slrp_7nm_adc_rocording_lanes
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_adc_rocording_lanes, 0x5, 0, 2);

/* page_data_slrp_7nm_edge_vos_ccal_en
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_edge_vos_ccal_en, 0x6, 1, 1);

/* page_data_slrp_7nm_adc_gain_shift_auto
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_adc_gain_shift_auto, 0x6, 0, 1);

/* page_data_slrp_7nm_ccal_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_ccal_mode, 0x7, 4, 3);

/* page_data_slrp_7nm_ctle_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_ctle_override_ctrl, 0x8, 6, 2);

/* page_data_slrp_7nm_vga_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_vga_override_ctrl, 0x8, 4, 2);

/* page_data_slrp_7nm_adc_vos_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_adc_vos_override_ctrl, 0x8, 2, 2);

/* page_data_slrp_7nm_adc_gain_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_adc_gain_override_ctrl, 0x8, 0, 2);

/* page_data_slrp_7nm_phos_override_ctrl
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos_override_ctrl, 0x9, 6, 2);

/* page_data_slrp_7nm_cal_error_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_cal_error_cnt, 0xa, 0, 8);

/* page_data_slrp_7nm_ccal_state
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_ccal_state, 0xb, 4, 2);

/* page_data_slrp_7nm_ccal_op
 * Access: RO
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_ccal_op, 0xb, 0, 2);

/* page_data_slrp_7nm_phos
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos, 0xc, 1, 5);

/* page_data_slrp_7nm_vga_vos1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_vga_vos1, 0xd, 0, 6);

/* page_data_slrp_7nm_vga_vos0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_vga_vos0, 0xe, 0, 6);

/* page_data_slrp_7nm_ctle_vos0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_ctle_vos0, 0xf, 0, 7);

/* page_data_slrp_7nm_adc_vos
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, slrp, page_data_slrp_7nm_adc_vos, 0x10, 64);

/* page_data_slrp_7nm_adc_gos
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, slrp, page_data_slrp_7nm_adc_gos, 0x50, 64);

/* page_data_slrp_7nm_phos3
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos3, 0x90, 0, 5);

/* page_data_slrp_7nm_phos2
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos2, 0x91, 0, 5);

/* page_data_slrp_7nm_phos1
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos1, 0x92, 0, 5);

/* page_data_slrp_7nm_phos0
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos0, 0x93, 0, 5);

/* page_data_slrp_7nm_phos7
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos7, 0x94, 0, 5);

/* page_data_slrp_7nm_phos6
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos6, 0x95, 0, 5);

/* page_data_slrp_7nm_phos5
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos5, 0x96, 0, 5);

/* page_data_slrp_7nm_phos4
 * Access: RW
 */
MLXSW_ITEM8(reg, slrp, page_data_slrp_7nm_phos4, 0x97, 0, 5);

/* slrp
 * ----
 *
 */

#define MLXSW_SLRP_ID  0x5026
#define MLXSW_SLRP_LEN 0x98

uint8_t mlxsw_reg_slrp_status_get(const char *buf);

uint8_t mlxsw_reg_slrp_version_get(const char *buf);

uint8_t mlxsw_reg_slrp_local_port_get(const char *buf);

void mlxsw_reg_slrp_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_pnat_get(const char *buf);

void mlxsw_reg_slrp_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_lp_msb_get(const char *buf);

void mlxsw_reg_slrp_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_lane_get(const char *buf);

void mlxsw_reg_slrp_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_port_type_get(const char *buf);

void mlxsw_reg_slrp_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ib_sel_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ib_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_dp_sel_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_dp_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_dp90sel_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_dp90sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mix90phase_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mix90phase_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap2_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap3_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap4_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap5_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap6_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap7_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap7_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap8_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap8_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbias_tap_amp_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbias_tap_amp_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_en_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_en_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_offset0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_offset0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_offset1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_offset1_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_offset0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_offset0_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset0_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset1_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_inp_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_inp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_inn_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_inn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_refp_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_refp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_refn_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_refn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_sel_slicer_lctrl_h_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_sel_slicer_lctrl_h_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_sel_slicer_lctrl_l_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_sel_slicer_lctrl_l_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ref_mixer_vreg_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ref_mixer_vreg_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_gctrl_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_gctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_lctrl_input_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_lctrl_input_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset_cm1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset_cm1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_common_mode_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_common_mode_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset_cm0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset_cm0_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_offset_cm_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_offset_cm_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_down_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_down_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_enc_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_enc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_dp_sel_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_dp_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_mid_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_mid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_down_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_down_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_eo_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_eo_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_mid_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_mid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_down_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_down_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_eo_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_eo_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_mid_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_mid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_down_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_down_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_eo_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_eo_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_eye_scan_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_eye_scan_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn0_n_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn0_n_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn0_p_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn0_p_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn1_n_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn1_n_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn1_p_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn1_p_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_digital_gctrl_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_digital_gctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias2ctle_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias2ctle_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_selgc_ref_op0_alev_ctle_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_selgc_ref_op0_alev_ctle_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_selgc_ref_op1_alev_ctle_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_selgc_ref_op1_alev_ctle_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_2_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_3_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_4_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_5_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_6_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_2_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_3_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_4_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_5_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_6_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_2_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_3_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_4_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_5_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_6_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_crnt_bgn_offset_p1_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_crnt_bgn_offset_n1_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_crnt_bgn_offset_p0_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_16nm_crnt_bgn_offset_n0_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_tap_index_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_tap_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_sub_channel_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_sub_channel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_gearbox_snr_en_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_gearbox_snr_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_gearbox_dsp_mode_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_gearbox_dsp_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_gearbox_afe_trim_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_gearbox_afe_trim_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_gearbox_ctle_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_gearbox_ctle_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_slrp_page_data_slrp_gearbox_raw_snr_value_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_gearbox_dsp_err_gen_set(char *buf, uint8_t val);

void mlxsw_reg_slrp_page_data_slrp_gearbox_snr_sym_cnt_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_slrp_page_data_slrp_gearbox_db_snr_value_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_tap_value_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_mixer00_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_mixer00_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_mixer90_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_mixer90_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_termination_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_termination_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_mid_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_mid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_dn_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_dn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_mid_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_mid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_dn_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_dn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_mid_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_mid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_dn_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_dn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_amp_vga_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_amp_vga_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_amp_vga_last_stage_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_amp_vga_last_stage_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_mid_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_mid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_dn_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_dn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_up_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_up_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_mid_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_mid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_dn_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_dn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_adc_recording_admin_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_recording_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_adc_recording_status_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_adc_rocording_lanes_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_rocording_lanes_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_edge_vos_ccal_en_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_edge_vos_ccal_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_adc_gain_shift_auto_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_gain_shift_auto_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_ccal_mode_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_ccal_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_ctle_override_ctrl_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_ctle_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_vga_override_ctrl_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_vga_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_adc_vos_override_ctrl_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_vos_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_adc_gain_override_ctrl_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_gain_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos_override_ctrl_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos_override_ctrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_cal_error_cnt_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_ccal_state_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_ccal_op_get(const char *buf);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_vga_vos1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_vga_vos1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_vga_vos0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_vga_vos0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_ctle_vos0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_ctle_vos0_set(char *buf, uint8_t val);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_vos_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_vos_memcpy_to(char *buf, const char *src);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_gos_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_slrp_page_data_slrp_7nm_adc_gos_memcpy_to(char *buf, const char *src);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos3_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos2_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos1_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos0_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos7_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos7_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos6_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos5_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrp_page_data_slrp_7nm_phos4_get(const char *buf);

void mlxsw_reg_slrp_page_data_slrp_7nm_phos4_set(char *buf, uint8_t val);

int __SLRP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_slrp_reg *slrp_reg = (struct ku_slrp_reg*)ku_reg;

    mlxsw_reg_slrp_local_port_set(inbox, slrp_reg->local_port);
    mlxsw_reg_slrp_pnat_set(inbox, slrp_reg->pnat);
    mlxsw_reg_slrp_lp_msb_set(inbox, slrp_reg->lp_msb);
    mlxsw_reg_slrp_lane_set(inbox, slrp_reg->lane);
    mlxsw_reg_slrp_port_type_set(inbox, slrp_reg->port_type);
    switch (slrp_reg->port_type) {
    case 0: /* Network port */
    case 2: /* Internal IC LR Port */
        switch (slrp_reg->version) {
        case 0: /* 40nm */
        case 1: /* 28nm */
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ib_sel_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ib_sel);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_dp_sel_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.dp_sel);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_dp90sel_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.dp90sel);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mix90phase_set(inbox,
                                                                   slrp_reg->page_data.slrp_40nm_28nm.mix90phase);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap0_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap0);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap1_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap1);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap2_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap2);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap3_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap3);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap4_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap4);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap5_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap5);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap6_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap6);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap7_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap7);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap8_set(inbox, slrp_reg->page_data.slrp_40nm_28nm.ffe_tap8);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbias_tap_amp_set(inbox,
                                                                          slrp_reg->page_data.slrp_40nm_28nm.mixerbias_tap_amp);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_en_set(inbox,
                                                                   slrp_reg->page_data.slrp_40nm_28nm.ffe_tap_en);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_offset0_set(inbox,
                                                                        slrp_reg->page_data.slrp_40nm_28nm.ffe_tap_offset0);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_offset1_set(inbox,
                                                                        slrp_reg->page_data.slrp_40nm_28nm.ffe_tap_offset1);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_offset0_set(inbox,
                                                                       slrp_reg->page_data.slrp_40nm_28nm.slicer_offset0);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset0_set(inbox,
                                                                      slrp_reg->page_data.slrp_40nm_28nm.mixer_offset0);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset1_set(inbox,
                                                                      slrp_reg->page_data.slrp_40nm_28nm.mixer_offset1);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_inp_set(inbox,
                                                                     slrp_reg->page_data.slrp_40nm_28nm.mixerbgn_inp);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_inn_set(inbox,
                                                                     slrp_reg->page_data.slrp_40nm_28nm.mixerbgn_inn);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_refp_set(inbox,
                                                                      slrp_reg->page_data.slrp_40nm_28nm.mixerbgn_refp);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_refn_set(inbox,
                                                                      slrp_reg->page_data.slrp_40nm_28nm.mixerbgn_refn);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_sel_slicer_lctrl_h_set(inbox,
                                                                           slrp_reg->page_data.slrp_40nm_28nm.sel_slicer_lctrl_h);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_sel_slicer_lctrl_l_set(inbox,
                                                                           slrp_reg->page_data.slrp_40nm_28nm.sel_slicer_lctrl_l);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ref_mixer_vreg_set(inbox,
                                                                       slrp_reg->page_data.slrp_40nm_28nm.ref_mixer_vreg);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_gctrl_set(inbox,
                                                                     slrp_reg->page_data.slrp_40nm_28nm.slicer_gctrl);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_lctrl_input_set(inbox,
                                                                    slrp_reg->page_data.slrp_40nm_28nm.lctrl_input);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset_cm1_set(inbox,
                                                                         slrp_reg->page_data.slrp_40nm_28nm.mixer_offset_cm1);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_common_mode_set(inbox,
                                                                    slrp_reg->page_data.slrp_40nm_28nm.common_mode);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset_cm0_set(inbox,
                                                                         slrp_reg->page_data.slrp_40nm_28nm.mixer_offset_cm0);
            mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_offset_cm_set(inbox,
                                                                         slrp_reg->page_data.slrp_40nm_28nm.slicer_offset_cm);
            break;

        case 3: /* 16nm */
            mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_up_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.mixer_offset_up);
            mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_down_set(inbox,
                                                                     slrp_reg->page_data.slrp_16nm.mixer_offset_down);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_enc_set(inbox, slrp_reg->page_data.slrp_16nm.sel_enc);
            mlxsw_reg_slrp_page_data_slrp_16nm_dp_sel_set(inbox, slrp_reg->page_data.slrp_16nm.dp_sel);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_up_set(inbox,
                                                                               slrp_reg->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_up);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_mid_set(inbox,
                                                                                slrp_reg->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_mid);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_down_set(inbox,
                                                                                 slrp_reg->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_down);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_eo_set(inbox,
                                                                               slrp_reg->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_eo);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_up_set(inbox,
                                                                                slrp_reg->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_up);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_mid_set(inbox,
                                                                                 slrp_reg->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_mid);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_down_set(inbox,
                                                                                  slrp_reg->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_down);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_eo_set(inbox,
                                                                                slrp_reg->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_eo);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_up_set(inbox,
                                                                            slrp_reg->page_data.slrp_16nm.sel_amp_mixer_biasgen_up);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_mid_set(inbox,
                                                                             slrp_reg->page_data.slrp_16nm.sel_amp_mixer_biasgen_mid);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_down_set(inbox,
                                                                              slrp_reg->page_data.slrp_16nm.sel_amp_mixer_biasgen_down);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_eo_set(inbox,
                                                                            slrp_reg->page_data.slrp_16nm.sel_amp_mixer_biasgen_eo);
            mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_eye_scan_set(inbox,
                                                                         slrp_reg->page_data.slrp_16nm.mixer_offset_eye_scan);
            mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn0_n_set(inbox,
                                                                    slrp_reg->page_data.slrp_16nm.gctrl_bin_bgn0_n);
            mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn0_p_set(inbox,
                                                                    slrp_reg->page_data.slrp_16nm.gctrl_bin_bgn0_p);
            mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn1_n_set(inbox,
                                                                    slrp_reg->page_data.slrp_16nm.gctrl_bin_bgn1_n);
            mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn1_p_set(inbox,
                                                                    slrp_reg->page_data.slrp_16nm.gctrl_bin_bgn1_p);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_digital_gctrl_set(inbox,
                                                                     slrp_reg->page_data.slrp_16nm.sel_digital_gctrl);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias2ctle_set(inbox, slrp_reg->page_data.slrp_16nm.sel_bias2ctle);
            mlxsw_reg_slrp_page_data_slrp_16nm_selgc_ref_op0_alev_ctle_set(inbox,
                                                                           slrp_reg->page_data.slrp_16nm.selgc_ref_op0_alev_ctle);
            mlxsw_reg_slrp_page_data_slrp_16nm_selgc_ref_op1_alev_ctle_set(inbox,
                                                                           slrp_reg->page_data.slrp_16nm.selgc_ref_op1_alev_ctle);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_0_set(inbox, slrp_reg->page_data.slrp_16nm.sel_bias_en_0);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_1_set(inbox, slrp_reg->page_data.slrp_16nm.sel_bias_en_1);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_2_set(inbox, slrp_reg->page_data.slrp_16nm.sel_bias_en_2);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_3_set(inbox, slrp_reg->page_data.slrp_16nm.sel_bias_en_3);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_4_set(inbox, slrp_reg->page_data.slrp_16nm.sel_bias_en_4);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_5_set(inbox, slrp_reg->page_data.slrp_16nm.sel_bias_en_5);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_6_set(inbox, slrp_reg->page_data.slrp_16nm.sel_bias_en_6);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_0_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrln_en_0);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_1_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrln_en_1);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_2_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrln_en_2);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_3_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrln_en_3);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_4_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrln_en_4);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_5_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrln_en_5);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_6_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrln_en_6);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_0_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_0);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_1_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_1);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_2_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_2);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_3_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_3);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_4_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_4);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_5_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_5);
            mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_6_set(inbox,
                                                                   slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_6);
            break;

        case 4: /* 7nm */
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_recording_admin_set(inbox,
                                                                      slrp_reg->page_data.slrp_7nm.adc_recording_admin);
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_rocording_lanes_set(inbox,
                                                                      slrp_reg->page_data.slrp_7nm.adc_rocording_lanes);
            mlxsw_reg_slrp_page_data_slrp_7nm_edge_vos_ccal_en_set(inbox,
                                                                   slrp_reg->page_data.slrp_7nm.edge_vos_ccal_en);
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_gain_shift_auto_set(inbox,
                                                                      slrp_reg->page_data.slrp_7nm.adc_gain_shift_auto);
            mlxsw_reg_slrp_page_data_slrp_7nm_ccal_mode_set(inbox, slrp_reg->page_data.slrp_7nm.ccal_mode);
            mlxsw_reg_slrp_page_data_slrp_7nm_ctle_override_ctrl_set(inbox,
                                                                     slrp_reg->page_data.slrp_7nm.ctle_override_ctrl);
            mlxsw_reg_slrp_page_data_slrp_7nm_vga_override_ctrl_set(inbox,
                                                                    slrp_reg->page_data.slrp_7nm.vga_override_ctrl);
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_vos_override_ctrl_set(inbox,
                                                                        slrp_reg->page_data.slrp_7nm.adc_vos_override_ctrl);
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_gain_override_ctrl_set(inbox,
                                                                         slrp_reg->page_data.slrp_7nm.adc_gain_override_ctrl);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos_override_ctrl_set(inbox,
                                                                     slrp_reg->page_data.slrp_7nm.phos_override_ctrl);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos_set(inbox, slrp_reg->page_data.slrp_7nm.phos);
            mlxsw_reg_slrp_page_data_slrp_7nm_vga_vos1_set(inbox, slrp_reg->page_data.slrp_7nm.vga_vos1);
            mlxsw_reg_slrp_page_data_slrp_7nm_vga_vos0_set(inbox, slrp_reg->page_data.slrp_7nm.vga_vos0);
            mlxsw_reg_slrp_page_data_slrp_7nm_ctle_vos0_set(inbox, slrp_reg->page_data.slrp_7nm.ctle_vos0);
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_vos_memcpy_to(inbox, (char *)slrp_reg->page_data.slrp_7nm.adc_vos);
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_gos_memcpy_to(inbox, (char *)slrp_reg->page_data.slrp_7nm.adc_gos);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos3_set(inbox, slrp_reg->page_data.slrp_7nm.phos3);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos2_set(inbox, slrp_reg->page_data.slrp_7nm.phos2);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos1_set(inbox, slrp_reg->page_data.slrp_7nm.phos1);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos0_set(inbox, slrp_reg->page_data.slrp_7nm.phos0);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos7_set(inbox, slrp_reg->page_data.slrp_7nm.phos7);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos6_set(inbox, slrp_reg->page_data.slrp_7nm.phos6);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos5_set(inbox, slrp_reg->page_data.slrp_7nm.phos5);
            mlxsw_reg_slrp_page_data_slrp_7nm_phos4_set(inbox, slrp_reg->page_data.slrp_7nm.phos4);
            break;

        default:
            break;
        }
        break;

    case 1: /* Near-End Port (For Retimer/Gearbox - Host side) */
    case 3: /* Far-End Port (For Retimer/Gearbox - Line side) */
        mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_tap_index_set(inbox, slrp_reg->page_data.slrp_gearbox.ffe_tap_index);
        mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_sub_channel_set(inbox,
                                                                  slrp_reg->page_data.slrp_gearbox.ffe_sub_channel);
        mlxsw_reg_slrp_page_data_slrp_gearbox_snr_en_set(inbox, slrp_reg->page_data.slrp_gearbox.snr_en);
        mlxsw_reg_slrp_page_data_slrp_gearbox_dsp_mode_set(inbox, slrp_reg->page_data.slrp_gearbox.dsp_mode);
        mlxsw_reg_slrp_page_data_slrp_gearbox_afe_trim_set(inbox, slrp_reg->page_data.slrp_gearbox.afe_trim);
        mlxsw_reg_slrp_page_data_slrp_gearbox_ctle_set(inbox, slrp_reg->page_data.slrp_gearbox.ctle);
        mlxsw_reg_slrp_page_data_slrp_gearbox_dsp_err_gen_set(inbox, slrp_reg->page_data.slrp_gearbox.dsp_err_gen);
        mlxsw_reg_slrp_page_data_slrp_gearbox_snr_sym_cnt_set(inbox, slrp_reg->page_data.slrp_gearbox.snr_sym_cnt);
        break;

    case 4: /* USR Main */
    case 5: /* USR Tile */
        mlxsw_reg_slrp_page_data_slrp_usr_mixer00_set(inbox, slrp_reg->page_data.slrp_usr.mixer00);
        mlxsw_reg_slrp_page_data_slrp_usr_mixer90_set(inbox, slrp_reg->page_data.slrp_usr.mixer90);
        mlxsw_reg_slrp_page_data_slrp_usr_termination_set(inbox, slrp_reg->page_data.slrp_usr.termination);
        mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_up_set(inbox, slrp_reg->page_data.slrp_usr.neg_cap_up);
        mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_mid_set(inbox, slrp_reg->page_data.slrp_usr.neg_cap_mid);
        mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_dn_set(inbox, slrp_reg->page_data.slrp_usr.neg_cap_dn);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_up_set(inbox,
                                                                        slrp_reg->page_data.slrp_usr.offset_coarse_polarity_up);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_mid_set(inbox,
                                                                         slrp_reg->page_data.slrp_usr.offset_coarse_polarity_mid);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_dn_set(inbox,
                                                                        slrp_reg->page_data.slrp_usr.offset_coarse_polarity_dn);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_up_set(inbox,
                                                                      slrp_reg->page_data.slrp_usr.offset_fine_polarity_up);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_mid_set(inbox,
                                                                       slrp_reg->page_data.slrp_usr.offset_fine_polarity_mid);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_dn_set(inbox,
                                                                      slrp_reg->page_data.slrp_usr.offset_fine_polarity_dn);
        mlxsw_reg_slrp_page_data_slrp_usr_amp_vga_set(inbox, slrp_reg->page_data.slrp_usr.amp_vga);
        mlxsw_reg_slrp_page_data_slrp_usr_amp_vga_last_stage_set(inbox,
                                                                 slrp_reg->page_data.slrp_usr.amp_vga_last_stage);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_up_set(inbox, slrp_reg->page_data.slrp_usr.offset_coarse_up);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_mid_set(inbox, slrp_reg->page_data.slrp_usr.offset_coarse_mid);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_dn_set(inbox, slrp_reg->page_data.slrp_usr.offset_coarse_dn);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_up_set(inbox, slrp_reg->page_data.slrp_usr.offset_fine_up);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_mid_set(inbox, slrp_reg->page_data.slrp_usr.offset_fine_mid);
        mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_dn_set(inbox, slrp_reg->page_data.slrp_usr.offset_fine_dn);
        break;

    default:
        break;
    }

    return 0;
}

int __SLRP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_slrp_reg *slrp_reg = (struct ku_slrp_reg*)ku_reg;

    slrp_reg->status = mlxsw_reg_slrp_status_get(outbox);
    slrp_reg->version = mlxsw_reg_slrp_version_get(outbox);
    slrp_reg->local_port = mlxsw_reg_slrp_local_port_get(outbox);
    slrp_reg->pnat = mlxsw_reg_slrp_pnat_get(outbox);
    slrp_reg->lp_msb = mlxsw_reg_slrp_lp_msb_get(outbox);
    slrp_reg->lane = mlxsw_reg_slrp_lane_get(outbox);
    slrp_reg->port_type = mlxsw_reg_slrp_port_type_get(outbox);

    switch (slrp_reg->port_type) {
    case 0:     /* Network port */
    case 2:     /* Internal IC LR Port */
        switch (slrp_reg->version) {
        case 0:         /* 40nm */
        case 1:         /* 28nm */
            slrp_reg->page_data.slrp_40nm_28nm.ib_sel = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ib_sel_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.dp_sel = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_dp_sel_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.dp90sel = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_dp90sel_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mix90phase = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mix90phase_get(
                outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap0 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap0_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap1 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap1_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap2 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap2_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap3 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap3_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap4 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap4_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap5 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap5_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap6 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap6_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap7 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap7_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap8 = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap8_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixerbias_tap_amp =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbias_tap_amp_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap_en = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_en_get(
                outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap_offset0 =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_offset0_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ffe_tap_offset1 =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ffe_tap_offset1_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.slicer_offset0 =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_offset0_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixer_offset0 =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset0_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixer_offset1 =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset1_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixerbgn_inp = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_inp_get(
                outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixerbgn_inn = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_inn_get(
                outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixerbgn_refp =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_refp_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixerbgn_refn =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixerbgn_refn_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.sel_slicer_lctrl_h =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_sel_slicer_lctrl_h_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.sel_slicer_lctrl_l =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_sel_slicer_lctrl_l_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.ref_mixer_vreg =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_ref_mixer_vreg_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.slicer_gctrl = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_gctrl_get(
                outbox);
            slrp_reg->page_data.slrp_40nm_28nm.lctrl_input = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_lctrl_input_get(
                outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixer_offset_cm1 =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset_cm1_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.common_mode = mlxsw_reg_slrp_page_data_slrp_40nm_28nm_common_mode_get(
                outbox);
            slrp_reg->page_data.slrp_40nm_28nm.mixer_offset_cm0 =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_mixer_offset_cm0_get(outbox);
            slrp_reg->page_data.slrp_40nm_28nm.slicer_offset_cm =
                mlxsw_reg_slrp_page_data_slrp_40nm_28nm_slicer_offset_cm_get(outbox);
            break;

        case 3:         /* 16nm */
            slrp_reg->page_data.slrp_16nm.mixer_offset_up = mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_up_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.mixer_offset_down = mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_down_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_enc = mlxsw_reg_slrp_page_data_slrp_16nm_sel_enc_get(outbox);
            slrp_reg->page_data.slrp_16nm.dp_sel = mlxsw_reg_slrp_page_data_slrp_16nm_dp_sel_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_up =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_up_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_mid =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_mid_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_down =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_down_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_eo =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_in_mixer_biasgen_eo_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_up =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_up_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_mid =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_mid_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_down =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_down_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_eo =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_ref_out_mixer_biasgen_eo_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_amp_mixer_biasgen_up =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_up_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_amp_mixer_biasgen_mid =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_mid_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_amp_mixer_biasgen_down =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_down_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_amp_mixer_biasgen_eo =
                mlxsw_reg_slrp_page_data_slrp_16nm_sel_amp_mixer_biasgen_eo_get(outbox);
            slrp_reg->page_data.slrp_16nm.mixer_offset_eye_scan =
                mlxsw_reg_slrp_page_data_slrp_16nm_mixer_offset_eye_scan_get(outbox);
            slrp_reg->page_data.slrp_16nm.gctrl_bin_bgn0_n = mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn0_n_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.gctrl_bin_bgn0_p = mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn0_p_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.gctrl_bin_bgn1_n = mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn1_n_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.gctrl_bin_bgn1_p = mlxsw_reg_slrp_page_data_slrp_16nm_gctrl_bin_bgn1_p_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_digital_gctrl = mlxsw_reg_slrp_page_data_slrp_16nm_sel_digital_gctrl_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_bias2ctle = mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias2ctle_get(outbox);
            slrp_reg->page_data.slrp_16nm.selgc_ref_op0_alev_ctle =
                mlxsw_reg_slrp_page_data_slrp_16nm_selgc_ref_op0_alev_ctle_get(outbox);
            slrp_reg->page_data.slrp_16nm.selgc_ref_op1_alev_ctle =
                mlxsw_reg_slrp_page_data_slrp_16nm_selgc_ref_op1_alev_ctle_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_bias_en_0 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_0_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_bias_en_1 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_1_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_bias_en_2 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_2_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_bias_en_3 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_3_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_bias_en_4 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_4_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_bias_en_5 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_5_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_bias_en_6 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_bias_en_6_get(outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrln_en_0 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_0_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrln_en_1 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_1_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrln_en_2 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_2_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrln_en_3 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_3_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrln_en_4 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_4_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrln_en_5 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_5_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrln_en_6 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrln_en_6_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_0 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_0_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_1 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_1_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_2 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_2_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_3 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_3_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_4 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_4_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_5 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_5_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.sel_gctrlp_en_6 = mlxsw_reg_slrp_page_data_slrp_16nm_sel_gctrlp_en_6_get(
                outbox);
            slrp_reg->page_data.slrp_16nm.crnt_bgn_offset_p1 =
                mlxsw_reg_slrp_page_data_slrp_16nm_crnt_bgn_offset_p1_get(outbox);
            slrp_reg->page_data.slrp_16nm.crnt_bgn_offset_n1 =
                mlxsw_reg_slrp_page_data_slrp_16nm_crnt_bgn_offset_n1_get(outbox);
            slrp_reg->page_data.slrp_16nm.crnt_bgn_offset_p0 =
                mlxsw_reg_slrp_page_data_slrp_16nm_crnt_bgn_offset_p0_get(outbox);
            slrp_reg->page_data.slrp_16nm.crnt_bgn_offset_n0 =
                mlxsw_reg_slrp_page_data_slrp_16nm_crnt_bgn_offset_n0_get(outbox);
            break;

        case 4:         /* 7nm */
            slrp_reg->page_data.slrp_7nm.adc_recording_admin =
                mlxsw_reg_slrp_page_data_slrp_7nm_adc_recording_admin_get(outbox);
            slrp_reg->page_data.slrp_7nm.adc_recording_status =
                mlxsw_reg_slrp_page_data_slrp_7nm_adc_recording_status_get(outbox);
            slrp_reg->page_data.slrp_7nm.adc_rocording_lanes =
                mlxsw_reg_slrp_page_data_slrp_7nm_adc_rocording_lanes_get(outbox);
            slrp_reg->page_data.slrp_7nm.edge_vos_ccal_en = mlxsw_reg_slrp_page_data_slrp_7nm_edge_vos_ccal_en_get(
                outbox);
            slrp_reg->page_data.slrp_7nm.adc_gain_shift_auto =
                mlxsw_reg_slrp_page_data_slrp_7nm_adc_gain_shift_auto_get(outbox);
            slrp_reg->page_data.slrp_7nm.ccal_mode = mlxsw_reg_slrp_page_data_slrp_7nm_ccal_mode_get(outbox);
            slrp_reg->page_data.slrp_7nm.ctle_override_ctrl = mlxsw_reg_slrp_page_data_slrp_7nm_ctle_override_ctrl_get(
                outbox);
            slrp_reg->page_data.slrp_7nm.vga_override_ctrl = mlxsw_reg_slrp_page_data_slrp_7nm_vga_override_ctrl_get(
                outbox);
            slrp_reg->page_data.slrp_7nm.adc_vos_override_ctrl =
                mlxsw_reg_slrp_page_data_slrp_7nm_adc_vos_override_ctrl_get(outbox);
            slrp_reg->page_data.slrp_7nm.adc_gain_override_ctrl =
                mlxsw_reg_slrp_page_data_slrp_7nm_adc_gain_override_ctrl_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos_override_ctrl = mlxsw_reg_slrp_page_data_slrp_7nm_phos_override_ctrl_get(
                outbox);
            slrp_reg->page_data.slrp_7nm.cal_error_cnt = mlxsw_reg_slrp_page_data_slrp_7nm_cal_error_cnt_get(outbox);
            slrp_reg->page_data.slrp_7nm.ccal_state = mlxsw_reg_slrp_page_data_slrp_7nm_ccal_state_get(outbox);
            slrp_reg->page_data.slrp_7nm.ccal_op = mlxsw_reg_slrp_page_data_slrp_7nm_ccal_op_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos = mlxsw_reg_slrp_page_data_slrp_7nm_phos_get(outbox);
            slrp_reg->page_data.slrp_7nm.vga_vos1 = mlxsw_reg_slrp_page_data_slrp_7nm_vga_vos1_get(outbox);
            slrp_reg->page_data.slrp_7nm.vga_vos0 = mlxsw_reg_slrp_page_data_slrp_7nm_vga_vos0_get(outbox);
            slrp_reg->page_data.slrp_7nm.ctle_vos0 = mlxsw_reg_slrp_page_data_slrp_7nm_ctle_vos0_get(outbox);
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_vos_memcpy_from(outbox,
                                                                  (char *)slrp_reg->page_data.slrp_7nm.adc_vos);
            mlxsw_reg_slrp_page_data_slrp_7nm_adc_gos_memcpy_from(outbox,
                                                                  (char *)slrp_reg->page_data.slrp_7nm.adc_gos);
            slrp_reg->page_data.slrp_7nm.phos3 = mlxsw_reg_slrp_page_data_slrp_7nm_phos3_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos2 = mlxsw_reg_slrp_page_data_slrp_7nm_phos2_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos1 = mlxsw_reg_slrp_page_data_slrp_7nm_phos1_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos0 = mlxsw_reg_slrp_page_data_slrp_7nm_phos0_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos7 = mlxsw_reg_slrp_page_data_slrp_7nm_phos7_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos6 = mlxsw_reg_slrp_page_data_slrp_7nm_phos6_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos5 = mlxsw_reg_slrp_page_data_slrp_7nm_phos5_get(outbox);
            slrp_reg->page_data.slrp_7nm.phos4 = mlxsw_reg_slrp_page_data_slrp_7nm_phos4_get(outbox);
            break;

        default:
            break;
        }
        break;

    case 1:     /* Near-End Port (For Retimer/Gearbox - Host side) */
    case 3:     /* Far-End Port (For Retimer/Gearbox - Line side) */
        slrp_reg->page_data.slrp_gearbox.ffe_tap_index =
            mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_tap_index_get(outbox);
        slrp_reg->page_data.slrp_gearbox.ffe_sub_channel = mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_sub_channel_get(
            outbox);
        slrp_reg->page_data.slrp_gearbox.snr_en = mlxsw_reg_slrp_page_data_slrp_gearbox_snr_en_get(outbox);
        slrp_reg->page_data.slrp_gearbox.dsp_mode = mlxsw_reg_slrp_page_data_slrp_gearbox_dsp_mode_get(outbox);
        slrp_reg->page_data.slrp_gearbox.afe_trim = mlxsw_reg_slrp_page_data_slrp_gearbox_afe_trim_get(outbox);
        slrp_reg->page_data.slrp_gearbox.ctle = mlxsw_reg_slrp_page_data_slrp_gearbox_ctle_get(outbox);
        slrp_reg->page_data.slrp_gearbox.raw_snr_value =
            mlxsw_reg_slrp_page_data_slrp_gearbox_raw_snr_value_get(outbox);
        slrp_reg->page_data.slrp_gearbox.db_snr_value = mlxsw_reg_slrp_page_data_slrp_gearbox_db_snr_value_get(outbox);
        slrp_reg->page_data.slrp_gearbox.ffe_tap_value =
            mlxsw_reg_slrp_page_data_slrp_gearbox_ffe_tap_value_get(outbox);
        break;

    case 4:     /* USR Main */
    case 5:     /* USR Tile */
        slrp_reg->page_data.slrp_usr.mixer00 = mlxsw_reg_slrp_page_data_slrp_usr_mixer00_get(outbox);
        slrp_reg->page_data.slrp_usr.mixer90 = mlxsw_reg_slrp_page_data_slrp_usr_mixer90_get(outbox);
        slrp_reg->page_data.slrp_usr.termination = mlxsw_reg_slrp_page_data_slrp_usr_termination_get(outbox);
        slrp_reg->page_data.slrp_usr.neg_cap_up = mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_up_get(outbox);
        slrp_reg->page_data.slrp_usr.neg_cap_mid = mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_mid_get(outbox);
        slrp_reg->page_data.slrp_usr.neg_cap_dn = mlxsw_reg_slrp_page_data_slrp_usr_neg_cap_dn_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_coarse_polarity_up =
            mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_up_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_coarse_polarity_mid =
            mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_mid_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_coarse_polarity_dn =
            mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_polarity_dn_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_fine_polarity_up =
            mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_up_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_fine_polarity_mid =
            mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_mid_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_fine_polarity_dn =
            mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_polarity_dn_get(outbox);
        slrp_reg->page_data.slrp_usr.amp_vga = mlxsw_reg_slrp_page_data_slrp_usr_amp_vga_get(outbox);
        slrp_reg->page_data.slrp_usr.amp_vga_last_stage = mlxsw_reg_slrp_page_data_slrp_usr_amp_vga_last_stage_get(
            outbox);
        slrp_reg->page_data.slrp_usr.offset_coarse_up = mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_up_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_coarse_mid =
            mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_mid_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_coarse_dn = mlxsw_reg_slrp_page_data_slrp_usr_offset_coarse_dn_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_fine_up = mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_up_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_fine_mid = mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_mid_get(outbox);
        slrp_reg->page_data.slrp_usr.offset_fine_dn = mlxsw_reg_slrp_page_data_slrp_usr_offset_fine_dn_get(outbox);
        break;

    default:
        break;
    }

    return 0;
}
EXPORT_SYMBOL(__SLRP_decode);

int sx_ACCESS_REG_SLRP(struct sx_dev *dev, struct ku_access_slrp_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SLRP_LEN >> 2) + 1;

    if (MLXSW_SLRP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLRP_encode,
                                  __SLRP_decode,
                                  reg_len_dword,
                                  &reg_data->slrp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLRP);

int sx_EMAD_ACCESS_REG_SLRP(struct sx_dev                  *dev,
                            emad_prio_e                     priority,
                            sx_emad_method_e                method,
                            const struct sx_emad_in_params *in_params,
                            struct sx_emad_out_params      *out_params,
                            struct ku_slrp_reg             *reg)
{
    u16 reg_len_dword = (MLXSW_SLRP_LEN >> 2) + 1;

    if (MLXSW_SLRP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SLRP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SLRP_encode,
                                     __SLRP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SLRP);

/* ppll
 * ----
 *
 */

#define MLXSW_PPLL_ID                            0x5030
#define MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN      0x08 /* base length, without records */
#define MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN      0x08 /* base length, without records */
#define MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN       0x08 /* record length */
#define MLXSW_PPLL_PLL_STATUS_28NM_REC_MAX_COUNT 4
#define MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN       0x08 /* record length */
#define MLXSW_PPLL_PLL_STATUS_16NM_REC_MAX_COUNT 4
#define MLXSW_PPLL_LEN                           0x28

/* num_pll_groups
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, num_pll_groups, 0x0, 0, 8);

/* pll_group
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppll, pll_group, 0x1, 0, 8);

/* pci_oob_pll
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, pci_oob_pll, 0x2, 4, 4);

/* num_plls
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, num_plls, 0x2, 0, 4);

/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, version, 0x3, 0, 4);

/* page_data_ppll_28nm_ae
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_28nm_ae, 0x7, 0, 1);

/* page_data_ppll_28nm_lock_cal
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_28nm_lock_cal,
                    MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN,
                    6,
                    1,
                    MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                    0);

/* page_data_ppll_28nm_lock_status
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_28nm_lock_status,
                    MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN,
                    4,
                    2,
                    MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                    0);

/* page_data_ppll_28nm_algo_f_ctrl
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg,
                     ppll,
                     page_data_ppll_28nm_algo_f_ctrl,
                     MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN,
                     0,
                     10,
                     MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                     0);

/* page_data_ppll_28nm_analog_algo_num_var
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_28nm_analog_algo_num_var,
                    MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN + 2,
                    2,
                    6,
                    MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                    0);

/* page_data_ppll_28nm_f_ctrl_measure
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg,
                     ppll,
                     page_data_ppll_28nm_f_ctrl_measure,
                     MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN + 2,
                     0,
                     10,
                     MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                     0);

/* page_data_ppll_28nm_analog_var
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_28nm_analog_var,
                    MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN,
                    0,
                    6,
                    MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                    4);

/* page_data_ppll_28nm_high_var
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_28nm_high_var,
                    MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN + 1,
                    0,
                    6,
                    MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                    4);

/* page_data_ppll_28nm_low_var
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_28nm_low_var,
                    MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN + 2,
                    0,
                    6,
                    MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                    4);

/* page_data_ppll_28nm_mid_var
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_28nm_mid_var,
                    MLXSW_PPLL_PLL_STATUS_28NM_BASE_LEN + 3,
                    0,
                    6,
                    MLXSW_PPLL_PLL_STATUS_28NM_REC_LEN,
                    4);

/* page_data_ppll_reg_16nm_lock_status
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_lock_status,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN,
                    6,
                    2,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_pll_pwrup
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_pll_pwrup,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN,
                    5,
                    1,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_lock_pulse
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_lock_pulse,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN,
                    1,
                    4,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_lock_lost_counter
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg,
                     ppll,
                     page_data_ppll_reg_16nm_lock_lost_counter,
                     MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN,
                     9,
                     16,
                     MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                     0);

/* page_data_ppll_reg_16nm_ae
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_ae,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 2,
                    0,
                    1,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_clear_cause
 * Access: WO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_clear_cause,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 3,
                    7,
                    1,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_lock_clk_val_cause
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_lock_clk_val_cause,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 3,
                    5,
                    2,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_plllock_clk_val
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_plllock_clk_val,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 3,
                    4,
                    1,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_clock_valid
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_clock_valid,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 3,
                    3,
                    1,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_pll_speed
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_pll_speed,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 3,
                    0,
                    3,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    0);

/* page_data_ppll_reg_16nm_lock
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_lock,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN,
                    7,
                    1,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    4);

/* page_data_ppll_reg_16nm_analog_var
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_analog_var,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN,
                    2,
                    5,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    4);

/* page_data_ppll_reg_16nm_high_var
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg,
                     ppll,
                     page_data_ppll_reg_16nm_high_var,
                     MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN,
                     5,
                     5,
                     MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                     4);

/* page_data_ppll_reg_16nm_low_var
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_low_var,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 1,
                    0,
                    5,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    4);

/* page_data_ppll_reg_16nm_mid_var
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg,
                    ppll,
                    page_data_ppll_reg_16nm_mid_var,
                    MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 2,
                    2,
                    6,
                    MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                    4);

/* page_data_ppll_reg_16nm_fctrl_measure
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg,
                     ppll,
                     page_data_ppll_reg_16nm_fctrl_measure,
                     MLXSW_PPLL_PLL_STATUS_16NM_BASE_LEN + 2,
                     0,
                     10,
                     MLXSW_PPLL_PLL_STATUS_16NM_REC_LEN,
                     4);

/* page_data_ppll_reg_7nm_pll_ugl_state
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_pll_ugl_state, 0x7, 0, 4);

/* page_data_ppll_reg_7nm_lokcdet_error_count
 * Access: RO
 */
MLXSW_ITEM16(reg, ppll, page_data_ppll_reg_7nm_lokcdet_error_count, 0x8, 0, 16);

/* page_data_ppll_reg_7nm_lockdet_err_measure_done
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lockdet_err_measure_done, 0xb, 7, 1);

/* page_data_ppll_reg_7nm_lockdet_err_state
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lockdet_err_state, 0xb, 4, 3);

/* page_data_ppll_reg_7nm_lockdet_cnt_based_lock
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lockdet_cnt_based_lock, 0xb, 3, 1);

/* page_data_ppll_reg_7nm_lockdet_err_cnt_unlocked_sticky
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lockdet_err_cnt_unlocked_sticky, 0xb, 2, 1);

/* page_data_ppll_reg_7nm_lockdet_err_cnt_locked_sticky
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lockdet_err_cnt_locked_sticky, 0xb, 1, 1);

/* page_data_ppll_reg_7nm_lockdet_err_cnt_active_lock
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lockdet_err_cnt_active_lock, 0xb, 0, 1);

/* page_data_ppll_reg_7nm_cal_internal_state
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cal_internal_state, 0xe, 6, 2);

/* page_data_ppll_reg_7nm_cal_main_state
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cal_main_state, 0xe, 0, 6);

/* page_data_ppll_reg_7nm_pll_lockdet_state
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_pll_lockdet_state, 0xf, 5, 2);

/* page_data_ppll_reg_7nm_pwr_up_state
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_pwr_up_state, 0xf, 0, 5);

/* page_data_ppll_reg_7nm_cal_abort_sticky
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cal_abort_sticky, 0x10, 6, 1);

/* page_data_ppll_reg_7nm_cal_abort
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cal_abort, 0x10, 5, 1);

/* page_data_ppll_reg_7nm_cal_valid_sticky
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cal_valid_sticky, 0x10, 4, 1);

/* page_data_ppll_reg_7nm_dco_coarse
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_dco_coarse, 0x11, 0, 7);

/* page_data_ppll_reg_7nm_cal_done
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cal_done, 0x12, 5, 1);

/* page_data_ppll_reg_7nm_cal_en
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cal_en, 0x12, 4, 1);

/* page_data_ppll_reg_7nm_dco_coarse_bin
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_dco_coarse_bin, 0x13, 0, 7);

/* page_data_ppll_reg_7nm_cal_error_counter
 * Access: RO
 */
MLXSW_ITEM16(reg, ppll, page_data_ppll_reg_7nm_cal_error_counter, 0x16, 0, 16);

/* page_data_ppll_reg_7nm_lma_rcal_code
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lma_rcal_code, 0x18, 4, 4);

/* page_data_ppll_reg_7nm_lma_rcal_tx_p_code
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lma_rcal_tx_p_code, 0x18, 0, 4);

/* page_data_ppll_reg_7nm_lma_rcal_tx_n_code
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_lma_rcal_tx_n_code, 0x19, 4, 4);

/* page_data_ppll_reg_7nm_rcal_done_valid_sticky
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_rcal_done_valid_sticky, 0x19, 3, 1);

/* page_data_ppll_reg_7nm_rcal_tx_p_valid_sticky
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_rcal_tx_p_valid_sticky, 0x19, 2, 1);

/* page_data_ppll_reg_7nm_rcal_tx_n_valid_sticky
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_rcal_tx_n_valid_sticky, 0x19, 1, 1);

/* page_data_ppll_reg_7nm_rcal_fsm_done
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_rcal_fsm_done, 0x19, 0, 1);

/* page_data_ppll_reg_7nm_speedo_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_speedo_valid, 0x1b, 2, 1);

/* page_data_ppll_reg_7nm_cvb_trim_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cvb_trim_valid, 0x1b, 1, 1);

/* page_data_ppll_reg_7nm_bg_trim_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_bg_trim_valid, 0x1b, 0, 1);

/* page_data_ppll_reg_7nm_speedo
 * Access: RO
 */
MLXSW_ITEM16(reg, ppll, page_data_ppll_reg_7nm_speedo, 0x1c, 0, 16);

/* page_data_ppll_reg_7nm_cvb_trim
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_cvb_trim, 0x1f, 4, 4);

/* page_data_ppll_reg_7nm_bg_trim
 * Access: RO
 */
MLXSW_ITEM8(reg, ppll, page_data_ppll_reg_7nm_bg_trim, 0x1f, 0, 4);

/* ppll
 * ----
 *
 */

uint8_t mlxsw_reg_ppll_num_pll_groups_get(const char *buf);

uint8_t mlxsw_reg_ppll_pll_group_get(const char *buf);

void mlxsw_reg_ppll_pll_group_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppll_pci_oob_pll_get(const char *buf);

uint8_t mlxsw_reg_ppll_num_plls_get(const char *buf);

uint8_t mlxsw_reg_ppll_version_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_28nm_ae_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_28nm_lock_cal_get(const char    *buf,
                                                        unsigned short outer_index,
                                                        unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_28nm_lock_status_get(const char    *buf,
                                                           unsigned short outer_index,
                                                           unsigned short index);

uint16_t mlxsw_reg_ppll_page_data_ppll_28nm_algo_f_ctrl_get(const char    *buf,
                                                            unsigned short outer_index,
                                                            unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_28nm_analog_algo_num_var_get(const char    *buf,
                                                                   unsigned short outer_index,
                                                                   unsigned short index);

uint16_t mlxsw_reg_ppll_page_data_ppll_28nm_f_ctrl_measure_get(const char    *buf,
                                                               unsigned short outer_index,
                                                               unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_28nm_analog_var_get(const char    *buf,
                                                          unsigned short outer_index,
                                                          unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_28nm_high_var_get(const char    *buf,
                                                        unsigned short outer_index,
                                                        unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_28nm_low_var_get(const char    *buf,
                                                       unsigned short outer_index,
                                                       unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_28nm_mid_var_get(const char    *buf,
                                                       unsigned short outer_index,
                                                       unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_status_get(const char    *buf,
                                                               unsigned short outer_index,
                                                               unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_pll_pwrup_get(const char    *buf,
                                                             unsigned short outer_index,
                                                             unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_pulse_get(const char    *buf,
                                                              unsigned short outer_index,
                                                              unsigned short index);

void mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_pulse_set(char          *buf,
                                                           unsigned short outer_index,
                                                           unsigned short index,
                                                           uint8_t        val);

uint32_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_lost_counter_get(const char    *buf,
                                                                      unsigned short outer_index,
                                                                      unsigned short index);

void mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_lost_counter_set(char          *buf,
                                                                  unsigned short outer_index,
                                                                  unsigned short index,
                                                                  uint32_t       val);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_ae_get(const char *buf, unsigned short outer_index,
                                                      unsigned short index);

void mlxsw_reg_ppll_page_data_ppll_reg_16nm_clear_cause_set(char          *buf,
                                                            unsigned short outer_index,
                                                            unsigned short index,
                                                            uint8_t        val);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_clk_val_cause_get(const char    *buf,
                                                                      unsigned short outer_index,
                                                                      unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_plllock_clk_val_get(const char    *buf,
                                                                   unsigned short outer_index,
                                                                   unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_clock_valid_get(const char    *buf,
                                                               unsigned short outer_index,
                                                               unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_pll_speed_get(const char    *buf,
                                                             unsigned short outer_index,
                                                             unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_get(const char    *buf,
                                                        unsigned short outer_index,
                                                        unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_analog_var_get(const char    *buf,
                                                              unsigned short outer_index,
                                                              unsigned short index);

uint16_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_high_var_get(const char    *buf,
                                                             unsigned short outer_index,
                                                             unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_low_var_get(const char    *buf,
                                                           unsigned short outer_index,
                                                           unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_mid_var_get(const char    *buf,
                                                           unsigned short outer_index,
                                                           unsigned short index);

uint16_t mlxsw_reg_ppll_page_data_ppll_reg_16nm_fctrl_measure_get(const char    *buf,
                                                                  unsigned short outer_index,
                                                                  unsigned short index);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_pll_ugl_state_get(const char *buf);

uint16_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lokcdet_error_count_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_measure_done_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_state_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_cnt_based_lock_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_cnt_unlocked_sticky_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_cnt_locked_sticky_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_cnt_active_lock_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_internal_state_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_main_state_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_pll_lockdet_state_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_pwr_up_state_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_abort_sticky_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_abort_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_valid_sticky_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_dco_coarse_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_done_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_en_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_dco_coarse_bin_get(const char *buf);

uint16_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_error_counter_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lma_rcal_code_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lma_rcal_tx_p_code_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_lma_rcal_tx_n_code_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_rcal_done_valid_sticky_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_rcal_tx_p_valid_sticky_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_rcal_tx_n_valid_sticky_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_rcal_fsm_done_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_speedo_valid_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cvb_trim_valid_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_bg_trim_valid_get(const char *buf);

uint16_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_speedo_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_cvb_trim_get(const char *buf);

uint8_t mlxsw_reg_ppll_page_data_ppll_reg_7nm_bg_trim_get(const char *buf);

/************************************************
 * PPLL
 ***********************************************/
int __PPLL_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppll_reg *ppll_reg = (struct ku_ppll_reg*)ku_reg;
    uint32_t            i = 0;

    mlxsw_reg_ppll_pll_group_set(inbox, ppll_reg->pll_group);
    switch (ppll_reg->version) {
    case SXD_PPLL_VERSION_PRODUCTS_28NM_E:
        break;

    case SXD_PPLL_VERSION_PRODUCTS_16NM_E:
        for (i = 0; i < SXD_PPLL_PLL_STATUS_16NM_NUM; i++) {
            mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_pulse_set(inbox,
                                                                  0,
                                                                  i,
                                                                  ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_pulse);
            mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_lost_counter_set(inbox,
                                                                         0,
                                                                         i,
                                                                         ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[
                                                                             i].lock_lost_counter);
            mlxsw_reg_ppll_page_data_ppll_reg_16nm_clear_cause_set(inbox,
                                                                   0,
                                                                   i,
                                                                   ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].clear_cause);
        }
        break;

    case SXD_PPLL_VERSION_PRODUCTS_7NM_E:
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __PPLL_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppll_reg *ppll_reg = (struct ku_ppll_reg*)ku_reg;
    uint32_t            i = 0;

    ppll_reg->num_pll_groups = mlxsw_reg_ppll_num_pll_groups_get(outbox);
    ppll_reg->pll_group = mlxsw_reg_ppll_pll_group_get(outbox);
    ppll_reg->pci_oob_pll = mlxsw_reg_ppll_pci_oob_pll_get(outbox);
    ppll_reg->num_plls = mlxsw_reg_ppll_num_plls_get(outbox);
    ppll_reg->version = mlxsw_reg_ppll_version_get(outbox);
    switch (ppll_reg->version) {
    case SXD_PPLL_VERSION_PRODUCTS_28NM_E:
        ppll_reg->page_data.ppll_28nm.ae = mlxsw_reg_ppll_page_data_ppll_28nm_ae_get(outbox);
        for (i = 0; i < SXD_PPLL_PLL_STATUS_28NM_NUM; i++) {
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].lock_cal =
                mlxsw_reg_ppll_page_data_ppll_28nm_lock_cal_get(outbox, 0, i);
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].lock_status =
                mlxsw_reg_ppll_page_data_ppll_28nm_lock_status_get(outbox, 0, i);
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].algo_f_ctrl =
                mlxsw_reg_ppll_page_data_ppll_28nm_algo_f_ctrl_get(outbox, 0, i);
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].analog_algo_num_var =
                mlxsw_reg_ppll_page_data_ppll_28nm_analog_algo_num_var_get(outbox, 0, i);
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].f_ctrl_measure =
                mlxsw_reg_ppll_page_data_ppll_28nm_f_ctrl_measure_get(outbox, 0, i);
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].analog_var =
                mlxsw_reg_ppll_page_data_ppll_28nm_analog_var_get(outbox, 0, i);
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].high_var =
                mlxsw_reg_ppll_page_data_ppll_28nm_high_var_get(outbox, 0, i);
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].low_var =
                mlxsw_reg_ppll_page_data_ppll_28nm_low_var_get(outbox, 0, i);
            ppll_reg->page_data.ppll_28nm.pll_status_28nm[i].mid_var =
                mlxsw_reg_ppll_page_data_ppll_28nm_mid_var_get(outbox, 0, i);
        }
        break;

    case SXD_PPLL_VERSION_PRODUCTS_16NM_E:
        for (i = 0; i < SXD_PPLL_PLL_STATUS_16NM_NUM; i++) {
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_status =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_status_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].pll_pwrup =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_pll_pwrup_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_pulse =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_pulse_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_lost_counter =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_lost_counter_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].ae =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_ae_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_clk_val_cause =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_clk_val_cause_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].plllock_clk_val =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_plllock_clk_val_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].clock_valid =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_clock_valid_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].pll_speed =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_pll_speed_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].lock =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_lock_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].analog_var =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_analog_var_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].high_var =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_high_var_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].low_var =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_low_var_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].mid_var =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_mid_var_get(outbox, 0, i);
            ppll_reg->page_data.ppll_reg_16nm.pll_status_16nm[i].fctrl_measure =
                mlxsw_reg_ppll_page_data_ppll_reg_16nm_fctrl_measure_get(outbox, 0, i);
        }
        break;

    case SXD_PPLL_VERSION_PRODUCTS_7NM_E:
        ppll_reg->page_data.ppll_reg_7nm.pll_ugl_state =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_pll_ugl_state_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lokcdet_error_count =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lokcdet_error_count_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lockdet_err_measure_done =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_measure_done_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lockdet_err_state =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_state_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lockdet_cnt_based_lock =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_cnt_based_lock_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lockdet_err_cnt_unlocked_sticky =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_cnt_unlocked_sticky_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lockdet_err_cnt_locked_sticky =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_cnt_locked_sticky_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lockdet_err_cnt_active_lock =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lockdet_err_cnt_active_lock_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.cal_internal_state =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_internal_state_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.cal_main_state = mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_main_state_get(
            outbox);
        ppll_reg->page_data.ppll_reg_7nm.pll_lockdet_state =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_pll_lockdet_state_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.pwr_up_state = mlxsw_reg_ppll_page_data_ppll_reg_7nm_pwr_up_state_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.cal_abort_sticky = mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_abort_sticky_get(
            outbox);
        ppll_reg->page_data.ppll_reg_7nm.cal_abort = mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_abort_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.cal_valid_sticky = mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_valid_sticky_get(
            outbox);
        ppll_reg->page_data.ppll_reg_7nm.dco_coarse = mlxsw_reg_ppll_page_data_ppll_reg_7nm_dco_coarse_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.cal_done = mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_done_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.cal_en = mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_en_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.dco_coarse_bin = mlxsw_reg_ppll_page_data_ppll_reg_7nm_dco_coarse_bin_get(
            outbox);
        ppll_reg->page_data.ppll_reg_7nm.cal_error_counter =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_cal_error_counter_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lma_rcal_code =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lma_rcal_code_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lma_rcal_tx_p_code =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lma_rcal_tx_p_code_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.lma_rcal_tx_n_code =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_lma_rcal_tx_n_code_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.rcal_done_valid_sticky =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_rcal_done_valid_sticky_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.rcal_tx_p_valid_sticky =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_rcal_tx_p_valid_sticky_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.rcal_tx_n_valid_sticky =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_rcal_tx_n_valid_sticky_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.rcal_fsm_done =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_rcal_fsm_done_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.speedo_valid = mlxsw_reg_ppll_page_data_ppll_reg_7nm_speedo_valid_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.cvb_trim_valid = mlxsw_reg_ppll_page_data_ppll_reg_7nm_cvb_trim_valid_get(
            outbox);
        ppll_reg->page_data.ppll_reg_7nm.bg_trim_valid =
            mlxsw_reg_ppll_page_data_ppll_reg_7nm_bg_trim_valid_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.speedo = mlxsw_reg_ppll_page_data_ppll_reg_7nm_speedo_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.cvb_trim = mlxsw_reg_ppll_page_data_ppll_reg_7nm_cvb_trim_get(outbox);
        ppll_reg->page_data.ppll_reg_7nm.bg_trim = mlxsw_reg_ppll_page_data_ppll_reg_7nm_bg_trim_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__PPLL_decode);

int sx_ACCESS_REG_PPLL(struct sx_dev *dev, struct ku_access_ppll_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PPLL_LEN >> 2) + 1;

    if (MLXSW_PPLL_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPLL_encode,
                                  __PPLL_decode,
                                  reg_len_dword,
                                  &reg_data->ppll_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPLL);

int sx_EMAD_ACCESS_REG_PPLL(struct sx_dev                  *dev,
                            emad_prio_e                     priority,
                            sx_emad_method_e                method,
                            const struct sx_emad_in_params *in_params,
                            struct sx_emad_out_params      *out_params,
                            struct ku_ppll_reg             *reg)
{
    u16 reg_len_dword = (MLXSW_PPLL_LEN >> 2) + 1;

    if (MLXSW_PPLL_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PPLL_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PPLL_encode,
                                     __PPLL_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PPLL);


/* slrg
 * ----
 *
 */
/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, status, 0x0, 4, 4);

/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrg, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrg, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrg, lp_msb, 0x2, 4, 2);

/* lane
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrg, lane, 0x2, 0, 4);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrg, port_type, 0x3, 4, 4);

/* test_mode
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slrg, test_mode, 0x3, 0, 1);

/* page_data_slrg_40nm_28nm_grade_lane_speed
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_40nm_28nm_grade_lane_speed, 0x7, 0, 4);

/* page_data_slrg_40nm_28nm_grade_version
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_40nm_28nm_grade_version, 0x8, 0, 8);

/* page_data_slrg_40nm_28nm_grade
 * Access: RO
 */
MLXSW_ITEM32(reg, slrg, page_data_slrg_40nm_28nm_grade, 0x8, 0, 24);

/* page_data_slrg_40nm_28nm_offset_units
 * Access: RW
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_40nm_28nm_offset_units, 0xc, 6, 2);

/* page_data_slrg_40nm_28nm_phase_units
 * Access: RW
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_40nm_28nm_phase_units, 0xc, 4, 2);

/* page_data_slrg_40nm_28nm_height_grade_type
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_40nm_28nm_height_grade_type, 0xc, 0, 4);

/* page_data_slrg_40nm_28nm_height_grade
 * Access: RO
 */
MLXSW_ITEM32(reg, slrg, page_data_slrg_40nm_28nm_height_grade, 0xc, 0, 24);

/* page_data_slrg_40nm_28nm_height_dz
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_40nm_28nm_height_dz, 0x10, 0, 16);

/* page_data_slrg_40nm_28nm_height_dv
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_40nm_28nm_height_dv, 0x12, 0, 16);

/* page_data_slrg_40nm_28nm_height_sigma
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_40nm_28nm_height_sigma, 0x16, 0, 16);

/* page_data_slrg_40nm_28nm_height_eo_pos
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_40nm_28nm_height_eo_pos, 0x18, 0, 16);

/* page_data_slrg_40nm_28nm_height_eo_neg
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_40nm_28nm_height_eo_neg, 0x1a, 0, 16);

/* page_data_slrg_40nm_28nm_phase_grade_type
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_40nm_28nm_phase_grade_type, 0x1c, 0, 4);

/* page_data_slrg_40nm_28nm_phase_grade
 * Access: RO
 */
MLXSW_ITEM32(reg, slrg, page_data_slrg_40nm_28nm_phase_grade, 0x1c, 0, 24);

/* page_data_slrg_40nm_28nm_phase_eo_pos
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_40nm_28nm_phase_eo_pos, 0x21, 0, 8);

/* page_data_slrg_40nm_28nm_phase_eo_neg
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_40nm_28nm_phase_eo_neg, 0x23, 0, 8);

/* page_data_slrg_40nm_28nm_ffe_set_tested
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_40nm_28nm_ffe_set_tested, 0x24, 0, 16);

/* page_data_slrg_40nm_28nm_test_errors_per_lane
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_40nm_28nm_test_errors_per_lane, 0x26, 0, 16);

/* page_data_slrg_16nm_grade_lane_speed
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_16nm_grade_lane_speed, 0x7, 0, 4);

/* page_data_slrg_16nm_grade_version
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_16nm_grade_version, 0x8, 0, 8);

/* page_data_slrg_16nm_grade
 * Access: RO
 */
MLXSW_ITEM32(reg, slrg, page_data_slrg_16nm_grade, 0x8, 0, 24);

/* page_data_slrg_16nm_height_eo_pos_up
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_height_eo_pos_up, 0xc, 0, 16);

/* page_data_slrg_16nm_height_eo_neg_up
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_height_eo_neg_up, 0xe, 0, 16);

/* page_data_slrg_16nm_phase_eo_pos_up
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_16nm_phase_eo_pos_up, 0x10, 0, 8);

/* page_data_slrg_16nm_phase_eo_neg_up
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_16nm_phase_eo_neg_up, 0x11, 0, 8);

/* page_data_slrg_16nm_height_eo_pos_mid
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_height_eo_pos_mid, 0x12, 0, 16);

/* page_data_slrg_16nm_height_eo_neg_mid
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_height_eo_neg_mid, 0x14, 0, 16);

/* page_data_slrg_16nm_phase_eo_pos_mid
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_16nm_phase_eo_pos_mid, 0x16, 0, 8);

/* page_data_slrg_16nm_phase_eo_neg_mid
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_16nm_phase_eo_neg_mid, 0x17, 0, 8);

/* page_data_slrg_16nm_height_eo_pos_low
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_height_eo_pos_low, 0x18, 0, 16);

/* page_data_slrg_16nm_height_eo_neg_low
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_height_eo_neg_low, 0x1a, 0, 16);

/* page_data_slrg_16nm_phase_eo_pos_low
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_16nm_phase_eo_pos_low, 0x1c, 0, 8);

/* page_data_slrg_16nm_phase_eo_neg_low
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_16nm_phase_eo_neg_low, 0x1d, 0, 8);

/* page_data_slrg_16nm_mid_eye_grade
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_mid_eye_grade, 0x20, 0, 16);

/* page_data_slrg_16nm_up_eye_grade
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_up_eye_grade, 0x22, 0, 16);

/* page_data_slrg_16nm_dn_eye_grade
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_16nm_dn_eye_grade, 0x26, 0, 16);

/* page_data_slrg_7nm_fom_measurment
 * Access: OP
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_fom_measurment, 0x7, 0, 4);

/* page_data_slrg_7nm_fom_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_fom_mode, 0x9, 0, 3);

/* page_data_slrg_7nm_initial_fom
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_initial_fom, 0xb, 0, 8);

/* page_data_slrg_7nm_last_fom
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_last_fom, 0xc, 0, 8);

/* page_data_slrg_7nm_upper_eye
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_upper_eye, 0xd, 0, 8);

/* page_data_slrg_7nm_mid_eye
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_mid_eye, 0xe, 0, 8);

/* page_data_slrg_7nm_lower_eye
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_lower_eye, 0xf, 0, 8);

/* page_data_slrg_7nm_testing_status
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_status, 0x5, 0, 3);

/* page_data_slrg_7nm_testing_iterations
 * Access: OP
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_iterations, 0x6, 0, 10);

/* page_data_slrg_7nm_testing_upper_max
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_upper_max, 0x8, 0, 8);

/* page_data_slrg_7nm_testing_mid_max
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_mid_max, 0x9, 0, 8);

/* page_data_slrg_7nm_testing_lower_max
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_lower_max, 0xa, 0, 8);

/* page_data_slrg_7nm_testing_comp_max
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_comp_max, 0xb, 0, 8);

/* page_data_slrg_7nm_testing_upper_min
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_upper_min, 0xc, 0, 8);

/* page_data_slrg_7nm_testing_mid_min
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_mid_min, 0xd, 0, 8);

/* page_data_slrg_7nm_testing_lower_min
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_lower_min, 0xe, 0, 8);

/* page_data_slrg_7nm_testing_comp_min
 * Access: RO
 */
MLXSW_ITEM8(reg, slrg, page_data_slrg_7nm_testing_comp_min, 0xf, 0, 8);

/* page_data_slrg_7nm_testing_upper_std
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_upper_std, 0x10, 0, 16);

/* page_data_slrg_7nm_testing_mid_std
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_mid_std, 0x12, 0, 16);

/* page_data_slrg_7nm_testing_lower_std
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_lower_std, 0x14, 0, 16);

/* page_data_slrg_7nm_testing_comp_std
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_comp_std, 0x16, 0, 16);

/* page_data_slrg_7nm_testing_upper_avg
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_upper_avg, 0x18, 0, 12);

/* page_data_slrg_7nm_testing_mid_avg
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_mid_avg, 0x1a, 0, 12);

/* page_data_slrg_7nm_testing_lower_avg
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_lower_avg, 0x1c, 0, 12);

/* page_data_slrg_7nm_testing_comp_avg
 * Access: RO
 */
MLXSW_ITEM16(reg, slrg, page_data_slrg_7nm_testing_comp_avg, 0x1e, 0, 12);

/* slrg
 * ----
 *
 */

#define MLXSW_SLRG_ID  0x5028
#define MLXSW_SLRG_LEN 0x28

uint8_t mlxsw_reg_slrg_status_get(const char *buf);

uint8_t mlxsw_reg_slrg_version_get(const char *buf);

uint8_t mlxsw_reg_slrg_local_port_get(const char *buf);

void mlxsw_reg_slrg_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_pnat_get(const char *buf);

void mlxsw_reg_slrg_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_lp_msb_get(const char *buf);

void mlxsw_reg_slrg_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_lane_get(const char *buf);

void mlxsw_reg_slrg_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_port_type_get(const char *buf);

void mlxsw_reg_slrg_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_test_mode_get(const char *buf);

void mlxsw_reg_slrg_test_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_grade_lane_speed_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_grade_version_get(const char *buf);

uint32_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_grade_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_offset_units_get(const char *buf);

void mlxsw_reg_slrg_page_data_slrg_40nm_28nm_offset_units_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_units_get(const char *buf);

void mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_units_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_grade_type_get(const char *buf);

uint32_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_grade_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_dz_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_dv_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_sigma_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_eo_pos_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_eo_neg_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_grade_type_get(const char *buf);

uint32_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_grade_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_eo_pos_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_eo_neg_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_ffe_set_tested_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_40nm_28nm_test_errors_per_lane_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_16nm_grade_lane_speed_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_16nm_grade_version_get(const char *buf);

uint32_t mlxsw_reg_slrg_page_data_slrg_16nm_grade_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_pos_up_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_neg_up_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_pos_up_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_neg_up_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_pos_mid_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_neg_mid_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_pos_mid_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_neg_mid_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_pos_low_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_neg_low_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_pos_low_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_neg_low_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_mid_eye_grade_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_up_eye_grade_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_16nm_dn_eye_grade_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_fom_measurment_get(const char *buf);

void mlxsw_reg_slrg_page_data_slrg_7nm_fom_measurment_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_fom_mode_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_initial_fom_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_last_fom_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_upper_eye_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_mid_eye_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_lower_eye_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_status_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_iterations_get(const char *buf);

void mlxsw_reg_slrg_page_data_slrg_7nm_testing_iterations_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_upper_max_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_mid_max_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_lower_max_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_comp_max_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_upper_min_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_mid_min_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_lower_min_get(const char *buf);

uint8_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_comp_min_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_upper_std_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_mid_std_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_lower_std_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_comp_std_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_upper_avg_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_mid_avg_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_lower_avg_get(const char *buf);

uint16_t mlxsw_reg_slrg_page_data_slrg_7nm_testing_comp_avg_get(const char *buf);

/************************************************
 * SLRG
 ***********************************************/
int __SLRG_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_slrg_reg *slrg_reg = (struct ku_slrg_reg*)ku_reg;

    mlxsw_reg_slrg_local_port_set(inbox, slrg_reg->local_port);
    mlxsw_reg_slrg_pnat_set(inbox, slrg_reg->pnat);
    mlxsw_reg_slrg_lp_msb_set(inbox, slrg_reg->lp_msb);
    mlxsw_reg_slrg_lane_set(inbox, slrg_reg->lane);
    mlxsw_reg_slrg_port_type_set(inbox, slrg_reg->port_type);
    mlxsw_reg_slrg_test_mode_set(inbox, slrg_reg->test_mode);

    switch (slrg_reg->version) {
    case 4:     /*7nm*/
        mlxsw_reg_slrg_page_data_slrg_7nm_fom_measurment_set(inbox, slrg_reg->page_data.slrg_7nm.fom_measurment);
        mlxsw_reg_slrg_page_data_slrg_7nm_testing_iterations_set(inbox,
                                                                 slrg_reg->page_data.slrg_7nm_testing.iterations);
        break;

    case 0:     /*40nm*/
    case 1:     /*28nm*/
        mlxsw_reg_slrg_page_data_slrg_40nm_28nm_offset_units_set(inbox,
                                                                 slrg_reg->page_data.slrg_40nm_28nm.offset_units);
        mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_units_set(inbox, slrg_reg->page_data.slrg_40nm_28nm.phase_units);
        break;

    default:
        break;
    }

    return 0;
}

int __SLRG_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_slrg_reg *slrg_reg = (struct ku_slrg_reg*)ku_reg;

    slrg_reg->status = mlxsw_reg_slrg_status_get(outbox);
    slrg_reg->version = mlxsw_reg_slrg_version_get(outbox);
    slrg_reg->local_port = mlxsw_reg_slrg_local_port_get(outbox);
    slrg_reg->pnat = mlxsw_reg_slrg_pnat_get(outbox);
    slrg_reg->lp_msb = mlxsw_reg_slrg_lp_msb_get(outbox);
    slrg_reg->lane = mlxsw_reg_slrg_lane_get(outbox);
    slrg_reg->port_type = mlxsw_reg_slrg_port_type_get(outbox);
    slrg_reg->test_mode = mlxsw_reg_slrg_test_mode_get(outbox);

    switch (slrg_reg->version) {
    case 0:
    case 1:
        slrg_reg->page_data.slrg_40nm_28nm.grade_lane_speed =
            mlxsw_reg_slrg_page_data_slrg_40nm_28nm_grade_lane_speed_get(outbox);
        slrg_reg->page_data.slrg_40nm_28nm.grade_version = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_grade_version_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.grade = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_grade_get(outbox);
        slrg_reg->page_data.slrg_40nm_28nm.offset_units = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_offset_units_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.phase_units =
            mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_units_get(outbox);
        slrg_reg->page_data.slrg_40nm_28nm.height_grade_type =
            mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_grade_type_get(outbox);
        slrg_reg->page_data.slrg_40nm_28nm.height_grade = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_grade_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.height_dz = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_dz_get(outbox);
        slrg_reg->page_data.slrg_40nm_28nm.height_dv = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_dv_get(outbox);
        slrg_reg->page_data.slrg_40nm_28nm.height_sigma = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_sigma_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.height_eo_pos = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_eo_pos_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.height_eo_neg = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_height_eo_neg_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.phase_grade_type =
            mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_grade_type_get(outbox);
        slrg_reg->page_data.slrg_40nm_28nm.phase_grade =
            mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_grade_get(outbox);
        slrg_reg->page_data.slrg_40nm_28nm.phase_eo_pos = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_eo_pos_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.phase_eo_neg = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_phase_eo_neg_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.ffe_set_tested = mlxsw_reg_slrg_page_data_slrg_40nm_28nm_ffe_set_tested_get(
            outbox);
        slrg_reg->page_data.slrg_40nm_28nm.test_errors_per_lane =
            mlxsw_reg_slrg_page_data_slrg_40nm_28nm_test_errors_per_lane_get(outbox);
        break;

    case 3:     /* 16nm */
        slrg_reg->page_data.slrg_16nm.grade_lane_speed =
            mlxsw_reg_slrg_page_data_slrg_16nm_grade_lane_speed_get(outbox);
        slrg_reg->page_data.slrg_16nm.grade_version = mlxsw_reg_slrg_page_data_slrg_16nm_grade_version_get(outbox);
        slrg_reg->page_data.slrg_16nm.grade = mlxsw_reg_slrg_page_data_slrg_16nm_grade_get(outbox);
        slrg_reg->page_data.slrg_16nm.height_eo_pos_up =
            mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_pos_up_get(outbox);
        slrg_reg->page_data.slrg_16nm.height_eo_neg_up =
            mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_neg_up_get(outbox);
        slrg_reg->page_data.slrg_16nm.phase_eo_pos_up = mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_pos_up_get(outbox);
        slrg_reg->page_data.slrg_16nm.phase_eo_neg_up = mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_neg_up_get(outbox);
        slrg_reg->page_data.slrg_16nm.height_eo_pos_mid = mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_pos_mid_get(
            outbox);
        slrg_reg->page_data.slrg_16nm.height_eo_neg_mid = mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_neg_mid_get(
            outbox);
        slrg_reg->page_data.slrg_16nm.phase_eo_pos_mid =
            mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_pos_mid_get(outbox);
        slrg_reg->page_data.slrg_16nm.phase_eo_neg_mid =
            mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_neg_mid_get(outbox);
        slrg_reg->page_data.slrg_16nm.height_eo_pos_low = mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_pos_low_get(
            outbox);
        slrg_reg->page_data.slrg_16nm.height_eo_neg_low = mlxsw_reg_slrg_page_data_slrg_16nm_height_eo_neg_low_get(
            outbox);
        slrg_reg->page_data.slrg_16nm.phase_eo_pos_low =
            mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_pos_low_get(outbox);
        slrg_reg->page_data.slrg_16nm.phase_eo_neg_low =
            mlxsw_reg_slrg_page_data_slrg_16nm_phase_eo_neg_low_get(outbox);
        slrg_reg->page_data.slrg_16nm.mid_eye_grade = mlxsw_reg_slrg_page_data_slrg_16nm_mid_eye_grade_get(outbox);
        slrg_reg->page_data.slrg_16nm.up_eye_grade = mlxsw_reg_slrg_page_data_slrg_16nm_up_eye_grade_get(outbox);
        slrg_reg->page_data.slrg_16nm.dn_eye_grade = mlxsw_reg_slrg_page_data_slrg_16nm_dn_eye_grade_get(outbox);
        break;

    case 4:     /* 7nm */
        slrg_reg->page_data.slrg_7nm.fom_measurment = mlxsw_reg_slrg_page_data_slrg_7nm_fom_measurment_get(outbox);
        slrg_reg->page_data.slrg_7nm.fom_mode = mlxsw_reg_slrg_page_data_slrg_7nm_fom_mode_get(outbox);
        slrg_reg->page_data.slrg_7nm.initial_fom = mlxsw_reg_slrg_page_data_slrg_7nm_initial_fom_get(outbox);
        slrg_reg->page_data.slrg_7nm.last_fom = mlxsw_reg_slrg_page_data_slrg_7nm_last_fom_get(outbox);
        slrg_reg->page_data.slrg_7nm.upper_eye = mlxsw_reg_slrg_page_data_slrg_7nm_upper_eye_get(outbox);
        slrg_reg->page_data.slrg_7nm.mid_eye = mlxsw_reg_slrg_page_data_slrg_7nm_mid_eye_get(outbox);
        slrg_reg->page_data.slrg_7nm.lower_eye = mlxsw_reg_slrg_page_data_slrg_7nm_lower_eye_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.status = mlxsw_reg_slrg_page_data_slrg_7nm_testing_status_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.iterations = mlxsw_reg_slrg_page_data_slrg_7nm_testing_iterations_get(
            outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.upper_max =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_upper_max_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.mid_max =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_mid_max_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.lower_max =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_lower_max_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.comp_max =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_comp_max_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.upper_min =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_upper_min_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.mid_min =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_mid_min_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.lower_min =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_lower_min_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.comp_min =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_comp_min_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.upper_std =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_upper_std_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.mid_std =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_mid_std_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.lower_std =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_lower_std_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.comp_std =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_comp_std_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.upper_avg =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_upper_avg_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.mid_avg =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_mid_avg_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.lower_avg =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_lower_avg_get(outbox);
        slrg_reg->page_data.slrg_7nm_testing.lane_meas_info.comp_avg =
            mlxsw_reg_slrg_page_data_slrg_7nm_testing_comp_avg_get(outbox);
        break;

    default:
        break;
    }

    return 0;
}
EXPORT_SYMBOL(__SLRG_decode);

int sx_ACCESS_REG_SLRG(struct sx_dev *dev, struct ku_access_slrg_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SLRG_LEN >> 2) + 1;

    if (MLXSW_SLRG_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLRG_encode,
                                  __SLRG_decode,
                                  reg_len_dword,
                                  &reg_data->slrg_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLRG);

int sx_EMAD_ACCESS_REG_SLRG(struct sx_dev                  *dev,
                            emad_prio_e                     priority,
                            sx_emad_method_e                method,
                            const struct sx_emad_in_params *in_params,
                            struct sx_emad_out_params      *out_params,
                            struct ku_slrg_reg             *reg)
{
    u16 reg_len_dword = (MLXSW_SLRG_LEN >> 2) + 1;

    if (MLXSW_SLRG_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SLRG_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SLRG_encode,
                                     __SLRG_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SLRG);

/* peucg
 * -----
 *
 */

#define MLXSW_PEUCG_PAGE_DATA_BASE_LEN      0x0c /* base length, without records */
#define MLXSW_PEUCG_PAGE_DATA_REC_LEN       0x04 /* record length */
#define MLXSW_PEUCG_PAGE_DATA_REC_MAX_COUNT 47
#define MLXSW_PEUCG_ID                      0x506c
#define MLXSW_PEUCG_LEN                     0xc8
/* unit
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peucg, unit, 0x0, 0, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peucg, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peucg, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peucg, lp_msb, 0x2, 4, 2);

/* lane
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peucg, lane, 0x2, 0, 4);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, peucg, status, 0x3, 0, 3);

/* payload_size
 * Access: OP
 */
MLXSW_ITEM8(reg, peucg, payload_size, 0x4, 0, 8);

/* db
 * Access: OP
 */
MLXSW_ITEM8(reg, peucg, db, 0x5, 1, 1);

/* clr
 * Access: WO
 */
MLXSW_ITEM8(reg, peucg, clr, 0x5, 0, 1);

/* enum_init
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peucg, enum_init, 0x7, 0, 8);

/* num_of_entries
 * Access: RO
 */
MLXSW_ITEM16(reg, peucg, num_of_entries, 0x8, 0, 10);

/* db_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, peucg, db_index, 0xa, 0, 10);

/* payload_data
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg,
                     peucg,
                     payload_data,
                     MLXSW_PEUCG_PAGE_DATA_BASE_LEN,
                     0,
                     16,
                     MLXSW_PEUCG_PAGE_DATA_REC_LEN,
                     0);

/* rxtx
 * Access: INDEX
 */
MLXSW_ITEM8_INDEXED(reg, peucg, rxtx, MLXSW_PEUCG_PAGE_DATA_BASE_LEN + 2, 7, 1, MLXSW_PEUCG_PAGE_DATA_REC_LEN, 0);

/* address
 * Access: INDEX
 */
MLXSW_ITEM16_INDEXED(reg,
                     peucg,
                     address,
                     MLXSW_PEUCG_PAGE_DATA_BASE_LEN + 2,
                     0,
                     10,
                     MLXSW_PEUCG_PAGE_DATA_REC_LEN,
                     0);


uint8_t mlxsw_reg_peucg_unit_get(const char *buf);

void mlxsw_reg_peucg_unit_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peucg_local_port_get(const char *buf);

void mlxsw_reg_peucg_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peucg_pnat_get(const char *buf);

void mlxsw_reg_peucg_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peucg_lp_msb_get(const char *buf);

void mlxsw_reg_peucg_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peucg_lane_get(const char *buf);

void mlxsw_reg_peucg_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peucg_status_get(const char *buf);

uint8_t mlxsw_reg_peucg_payload_size_get(const char *buf);

void mlxsw_reg_peucg_payload_size_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peucg_db_get(const char *buf);

void mlxsw_reg_peucg_db_set(char *buf, uint8_t val);

void mlxsw_reg_peucg_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peucg_enum_init_get(const char *buf);

void mlxsw_reg_peucg_enum_init_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_peucg_num_of_entries_get(const char *buf);

uint16_t mlxsw_reg_peucg_db_index_get(const char *buf);

void mlxsw_reg_peucg_db_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_peucg_payload_data_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_peucg_payload_data_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint8_t mlxsw_reg_peucg_rxtx_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_peucg_rxtx_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_peucg_address_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_peucg_address_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

/************************************************
 * PEUCG
 ***********************************************/

int __PEUCG_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_peucg_reg *peucg_reg = (struct ku_peucg_reg*)ku_reg;
    uint32_t             index = 0;

    mlxsw_reg_peucg_unit_set(inbox, peucg_reg->unit);
    mlxsw_reg_peucg_local_port_set(inbox, peucg_reg->local_port);
    mlxsw_reg_peucg_pnat_set(inbox, peucg_reg->pnat);
    mlxsw_reg_peucg_lp_msb_set(inbox, peucg_reg->lp_msb);
    mlxsw_reg_peucg_lane_set(inbox, peucg_reg->lane);
    mlxsw_reg_peucg_payload_size_set(inbox, peucg_reg->payload_size);
    mlxsw_reg_peucg_db_set(inbox, peucg_reg->db);
    mlxsw_reg_peucg_clr_set(inbox, peucg_reg->clr);
    mlxsw_reg_peucg_enum_init_set(inbox, peucg_reg->enum_init);
    mlxsw_reg_peucg_db_index_set(inbox, peucg_reg->db_index);
    for (index = 0; index < SXD_PEUCG_PAGE_DATA_NUM; index++) {
        mlxsw_reg_peucg_payload_data_set(inbox, 0, index, peucg_reg->page_data[index].payload_data);
        mlxsw_reg_peucg_rxtx_set(inbox, 0, index, peucg_reg->page_data[index].rxtx);
        mlxsw_reg_peucg_address_set(inbox, 0, index, peucg_reg->page_data[index].address);
    }


    return 0;
}
EXPORT_SYMBOL(__PEUCG_encode);

int __PEUCG_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_peucg_reg *peucg_reg = (struct ku_peucg_reg*)ku_reg;
    uint32_t             index = 0;

    peucg_reg->unit = mlxsw_reg_peucg_unit_get(outbox);
    peucg_reg->local_port = mlxsw_reg_peucg_local_port_get(outbox);
    peucg_reg->pnat = mlxsw_reg_peucg_pnat_get(outbox);
    peucg_reg->lp_msb = mlxsw_reg_peucg_lp_msb_get(outbox);
    peucg_reg->lane = mlxsw_reg_peucg_lane_get(outbox);
    peucg_reg->status = mlxsw_reg_peucg_status_get(outbox);
    peucg_reg->payload_size = mlxsw_reg_peucg_payload_size_get(outbox);
    peucg_reg->db = mlxsw_reg_peucg_db_get(outbox);
    peucg_reg->enum_init = mlxsw_reg_peucg_enum_init_get(outbox);
    peucg_reg->num_of_entries = mlxsw_reg_peucg_num_of_entries_get(outbox);
    peucg_reg->db_index = mlxsw_reg_peucg_db_index_get(outbox);
    for (index = 0; index < SXD_PEUCG_PAGE_DATA_NUM; index++) {
        peucg_reg->page_data[index].payload_data = mlxsw_reg_peucg_payload_data_get(outbox, 0, index);
        peucg_reg->page_data[index].rxtx = mlxsw_reg_peucg_rxtx_get(outbox, 0, index);
        peucg_reg->page_data[index].address = mlxsw_reg_peucg_address_get(outbox, 0, index);
    }


    return 0;
}
EXPORT_SYMBOL(__PEUCG_decode);

int sx_ACCESS_REG_PEUCG(struct sx_dev *dev, struct ku_access_peucg_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PEUCG_LEN >> 2) + 1;

    if (MLXSW_PEUCG_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PEUCG_encode,
                                  __PEUCG_decode,
                                  reg_len_dword,
                                  &reg_data->peucg_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PEUCG);

int sx_EMAD_ACCESS_REG_PEUCG(struct sx_dev                  *dev,
                             emad_prio_e                     priority,
                             sx_emad_method_e                method,
                             const struct sx_emad_in_params *in_params,
                             struct sx_emad_out_params      *out_params,
                             struct ku_peucg_reg            *reg)
{
    u16 reg_len_dword = (MLXSW_PEUCG_LEN >> 2) + 1;

    if (MLXSW_PEUCG_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PEUCG_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PEUCG_encode,
                                     __PEUCG_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PEUCG);


/************************************************
 * IBSNI
 ***********************************************/
#define REG_IPV4_RECORDS_OFFSET             0x1c
#define REG_IPV6_RECORDS_OFFSET             0x3c
#define IBSNI_IPV4_RECORD_REC_MAX_COUNT     4
#define IBSNI_IPV6_RECORD_REC_MAX_COUNT     4
#define IBSNI_IPV6_RECORD_IPV6_MAX_COUNT    4
#define IBSNI_IPV6_RECORD_NETMASK_MAX_COUNT 4
#define IBSNI_REG_LEN                       0xa8


static int __IBSNI_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ibsni_reg *ibsni_reg = (struct ku_ibsni_reg*)ku_reg;
    int                  i, j, dword_inc = 0;

    for (i = 0; i < IBSNI_IPV4_RECORD_REC_MAX_COUNT; i++) {
        SX_PUT_REG_FIELD(inbox, ibsni_reg->ipv4_record[i].ipv4, (dword_inc++) * 4 + REG_IPV4_RECORDS_OFFSET);
        SX_PUT_REG_FIELD(inbox, ibsni_reg->ipv4_record[i].netmask, (dword_inc++) * 4 + REG_IPV4_RECORDS_OFFSET);
    }
    dword_inc = 0;
    for (i = 0; i < IBSNI_IPV6_RECORD_REC_MAX_COUNT; i++) {
        for (j = 0; j < IBSNI_IPV6_RECORD_IPV6_MAX_COUNT; j++) {
            SX_PUT_REG_FIELD(inbox, ibsni_reg->ipv6_record[i].ipv6[j], (dword_inc++) * 4 + REG_IPV6_RECORDS_OFFSET);
        }
        for (j = 0; j < IBSNI_IPV6_RECORD_NETMASK_MAX_COUNT; j++) {
            SX_PUT_REG_FIELD(inbox, ibsni_reg->ipv6_record[i].netmask[j], (dword_inc++) * 4 + REG_IPV6_RECORDS_OFFSET);
        }
    }

    return 0;
}

static int __IBSNI_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ibsni_reg *ibsni_reg = (struct ku_ibsni_reg*)ku_reg;
    int                  i, j, dword_inc = 0;

    for (i = 0; i < IBSNI_IPV4_RECORD_REC_MAX_COUNT; i++) {
        SX_GET_REG_FIELD(ibsni_reg->ipv4_record[i].ipv4, outbox, (dword_inc++) * 4 + REG_IPV4_RECORDS_OFFSET);
        SX_GET_REG_FIELD(ibsni_reg->ipv4_record[i].netmask, outbox, (dword_inc++) * 4 + REG_IPV4_RECORDS_OFFSET);
    }
    dword_inc = 0;
    for (i = 0; i < IBSNI_IPV6_RECORD_REC_MAX_COUNT; i++) {
        for (j = 0; j < IBSNI_IPV6_RECORD_IPV6_MAX_COUNT; j++) {
            SX_GET_REG_FIELD(ibsni_reg->ipv6_record[i].ipv6[j], outbox, (dword_inc++) * 4 + REG_IPV6_RECORDS_OFFSET);
        }
        for (j = 0; j < IBSNI_IPV6_RECORD_NETMASK_MAX_COUNT; j++) {
            SX_GET_REG_FIELD(ibsni_reg->ipv6_record[i].netmask[j], outbox,
                             (dword_inc++) * 4 + REG_IPV6_RECORDS_OFFSET);
        }
    }

    return 0;
}

int sx_ACCESS_REG_IBSNI(struct sx_dev *dev, struct ku_access_ibsni_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __IBSNI_encode,
                                  __IBSNI_decode,
                                  IBSNI_REG_LEN,
                                  &reg_data->ibsni_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_IBSNI);

/************************************************
 * SLCR
 ***********************************************/
#define SLCR_LOCAL_PORT_OFFEST 0x15
#define SLCR_LP_MSB_SH_OFFSET  0x16
#define SLCR_HASH_TYPE_OFFSET  0x17
#define SLCR_LAG_HASH_OFFSET   0x18
#define SLCR_SEED_OFFSET       0x1c
#define SLCR_REG_LEN           4

static int __SLCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_slcr_reg *slcr_reg = (struct ku_slcr_reg*)ku_reg;
    u8                  lp_msb_sh = ((slcr_reg->lp_msb & 0x3) << 4) | (slcr_reg->sh & 0x1);
    u8                  type = slcr_reg->hash_type & 0xf;
    u32                 lag_hash = slcr_reg->hash_configuration & 0xfffff;

    SX_PUT_REG_FIELD(inbox, slcr_reg->local_port, SLCR_LOCAL_PORT_OFFEST);
    SX_PUT_REG_FIELD(inbox, lp_msb_sh, SLCR_LP_MSB_SH_OFFSET);
    SX_PUT_REG_FIELD(inbox, type, SLCR_HASH_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, lag_hash, SLCR_LAG_HASH_OFFSET);
    SX_PUT_REG_FIELD(inbox, slcr_reg->seed, SLCR_SEED_OFFSET);

    return 0;
}

static int __SLCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_slcr_reg *slcr_reg = (struct ku_slcr_reg*)ku_reg;
    u8                  lp_msb_sh;

    SX_GET_REG_FIELD(slcr_reg->local_port, outbox, SLCR_LOCAL_PORT_OFFEST);
    SX_GET_REG_FIELD(lp_msb_sh, outbox, SLCR_LP_MSB_SH_OFFSET);
    slcr_reg->lp_msb = (lp_msb_sh >> 4) & 0x3;
    slcr_reg->sh = lp_msb_sh & 0x1;
    SX_GET_REG_FIELD(slcr_reg->hash_type, outbox, SLCR_HASH_TYPE_OFFSET);
    slcr_reg->hash_type &= 0xf;
    SX_GET_REG_FIELD(slcr_reg->hash_configuration, outbox, SLCR_LAG_HASH_OFFSET);
    slcr_reg->hash_configuration &= 0xfffff;
    SX_GET_REG_FIELD(slcr_reg->seed, outbox, SLCR_SEED_OFFSET);

    return 0;
}

int sx_ACCESS_REG_SLCR(struct sx_dev *dev, struct ku_access_slcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLCR_encode,
                                  __SLCR_decode,
                                  SLCR_REG_LEN,
                                  &reg_data->slcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLCR);

/************************************************
 * SLCR_V2
 ***********************************************/
#define SLCR_V2_LOCAL_PORT_OFFEST                 0x15
#define SLCR_V2_LP_MSB_SH_OFFSET                  0x16
#define SLCR_V2_TYPE_OFFSET                       0x17
#define SLCR_V2_SEED_OFFSET                       0x1c
#define SLCR_V2_GENERAL_FIELDS_OFFSET             0x20
#define SLCR_V2_OUTER_HEADER_ENABLES_OFFSET       0x26
#define SLCR_V2_OUTER_HEADER_FIELDS_ENABLE_OFFSET 0x28
#define SLCR_V2_INNER_HEADER_ENABLES_OFFSET       0x42
#define SLCR_V2_INNER_HEADER_FIELDS_ENABLE_OFFSET 0x44
#define SLCR_V2_REG_LEN                           20

static int __SLCR_V2_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_slcr_v2_reg *slcr_v2_reg = (struct ku_slcr_v2_reg*)ku_reg;
    u8                     lp_msb_sh = ((slcr_v2_reg->lp_msb & 0x3) << 4) | (slcr_v2_reg->sh & 0x3);
    u8                     type = slcr_v2_reg->type & 0xf;
    int                    i;

    SX_PUT_REG_FIELD(inbox, slcr_v2_reg->local_port, SLCR_V2_LOCAL_PORT_OFFEST);
    SX_PUT_REG_FIELD(inbox, lp_msb_sh, SLCR_V2_LP_MSB_SH_OFFSET);
    SX_PUT_REG_FIELD(inbox, type, SLCR_V2_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, slcr_v2_reg->seed, SLCR_V2_SEED_OFFSET);
    SX_PUT_REG_FIELD(inbox, slcr_v2_reg->general_fields, SLCR_V2_GENERAL_FIELDS_OFFSET);
    SX_PUT_REG_FIELD(inbox, slcr_v2_reg->outer_header_enables, SLCR_V2_OUTER_HEADER_ENABLES_OFFSET);
    for (i = 0; i < 5; i++) {
        SX_PUT_REG_FIELD(inbox,
                         slcr_v2_reg->outer_header_fields_enable[4 - i],
                         (SLCR_V2_OUTER_HEADER_FIELDS_ENABLE_OFFSET + (i * 4)));
    }

    SX_PUT_REG_FIELD(inbox, slcr_v2_reg->inner_header_enables, SLCR_V2_INNER_HEADER_ENABLES_OFFSET);
    SX_PUT_REG_FIELD(inbox, slcr_v2_reg->inner_header_fields_enable, SLCR_V2_INNER_HEADER_FIELDS_ENABLE_OFFSET);

    return 0;
}

static int __SLCR_V2_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_slcr_v2_reg *slcr_v2_reg = (struct ku_slcr_v2_reg*)ku_reg;
    u8                     lp_msb_sh;
    int                    i;

    SX_GET_REG_FIELD(slcr_v2_reg->local_port, outbox, SLCR_V2_LOCAL_PORT_OFFEST);
    SX_GET_REG_FIELD(lp_msb_sh, outbox, SLCR_V2_LP_MSB_SH_OFFSET);
    slcr_v2_reg->lp_msb = (lp_msb_sh >> 4) & 0x3;
    slcr_v2_reg->sh = lp_msb_sh & 0x3;
    SX_GET_REG_FIELD(slcr_v2_reg->type, outbox, SLCR_V2_TYPE_OFFSET);
    slcr_v2_reg->type &= 0xf;
    SX_GET_REG_FIELD(slcr_v2_reg->seed, outbox, SLCR_V2_SEED_OFFSET);
    SX_GET_REG_FIELD(slcr_v2_reg->general_fields, outbox, SLCR_V2_GENERAL_FIELDS_OFFSET);
    SX_GET_REG_FIELD(slcr_v2_reg->outer_header_enables, outbox, SLCR_V2_OUTER_HEADER_ENABLES_OFFSET);
    for (i = 0; i < 5; i++) {
        SX_GET_REG_FIELD(slcr_v2_reg->outer_header_fields_enable[4 - i],
                         outbox,
                         (SLCR_V2_OUTER_HEADER_FIELDS_ENABLE_OFFSET + (i * 4)));
    }

    SX_GET_REG_FIELD(slcr_v2_reg->inner_header_enables, outbox, SLCR_V2_INNER_HEADER_ENABLES_OFFSET);
    SX_GET_REG_FIELD(slcr_v2_reg->inner_header_fields_enable, outbox, SLCR_V2_INNER_HEADER_FIELDS_ENABLE_OFFSET);

    return 0;
}

int sx_ACCESS_REG_SLCR_V2(struct sx_dev *dev, struct ku_access_slcr_v2_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLCR_V2_encode,
                                  __SLCR_V2_decode,
                                  SLCR_V2_REG_LEN,
                                  &reg_data->slcr_v2_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLCR_V2);

/************************************************
 * SFN
 ***********************************************/
#define SFN_SWID_OFFSET     0x14
#define SFN_REC_TYPE_OFFSET 0x15
#define SFN_END_OFFSET      0x19
#define SFN_NUM_REC_OFFSET  0x1b
#define SFN_RECORD0_OFFSET  0x24

static int __SFN_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sfn_reg *sfn_reg = (struct ku_sfn_reg*)ku_reg;
    u8                 tmp_u8;

    SX_PUT_REG_FIELD(inbox, sfn_reg->swid, SFN_SWID_OFFSET);
    tmp_u8 = (sfn_reg->rec_type & 0x1) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, SFN_REC_TYPE_OFFSET);
    tmp_u8 = (sfn_reg->end & 0x1) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, SFN_END_OFFSET);
    SX_PUT_REG_FIELD(inbox, sfn_reg->num_records, SFN_NUM_REC_OFFSET);

    return 0;
}

static int __SFN_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sfn_reg      *sfn_reg = (struct ku_sfn_reg*)ku_reg;
    struct sfn_record_data *curr_rec_usr = NULL;
    const u8               *curr_rec_prm = outbox + SFN_RECORD0_OFFSET - REG_START_OFFSET;
    int                     i;

    SX_GET_REG_FIELD(sfn_reg->swid, outbox, SFN_SWID_OFFSET);
    SX_GET_REG_FIELD(sfn_reg->rec_type, outbox, SFN_REC_TYPE_OFFSET);
    sfn_reg->rec_type = (sfn_reg->rec_type >> 4) & 0x1;
    SX_GET_REG_FIELD(sfn_reg->num_records, outbox, SFN_NUM_REC_OFFSET);

    for (i = 0; i < sfn_reg->num_records; i++) {
        curr_rec_usr = &sfn_reg->records[i];

        curr_rec_usr->sfn_type = (curr_rec_prm[1] >> 4) & 0xf;
        switch (curr_rec_usr->sfn_type) {
        case 5: /* Learned MAC notification */
            memcpy(curr_rec_usr->sx_sfn_type.lrnt_mac.mac.ether_addr_octet, &curr_rec_prm[2], 6);
            curr_rec_usr->sx_sfn_type.lrnt_mac.fid = be16_to_cpu(*(u16*)&curr_rec_prm[10]);
            curr_rec_usr->sx_sfn_type.lrnt_mac.system_port = be16_to_cpu(*(u16*)&curr_rec_prm[14]);

            if (sfn_reg->rec_type == 1) { /* case of 32-byte record */
                curr_rec_usr->sx_sfn_type.lrnt_mac.counter_set.type = curr_rec_prm[28];
                curr_rec_usr->sx_sfn_type.lrnt_mac.counter_set.index = be32_to_cpu(*(u32*)&curr_rec_prm[28]) &
                                                                       0xffffff;
            }

            break;

        case 6: /* Learned MAC LAG notification */
            memcpy(curr_rec_usr->sx_sfn_type.lrnt_mac_lag.mac.ether_addr_octet, &curr_rec_prm[2], 6);
            curr_rec_usr->sx_sfn_type.lrnt_mac_lag.fid = be16_to_cpu(*(u16*)&curr_rec_prm[10]);
            curr_rec_usr->sx_sfn_type.lrnt_mac_lag.lag_id = be16_to_cpu(*(u16*)&curr_rec_prm[14]) & 0x1ff;
            if (sfn_reg->rec_type == 1) { /* case of 32-byte record */
                curr_rec_usr->sx_sfn_type.lrnt_mac_lag.counter_set.type = curr_rec_prm[28];
                curr_rec_usr->sx_sfn_type.lrnt_mac_lag.counter_set.index = be32_to_cpu(*(u32*)&curr_rec_prm[28]) &
                                                                           0xffffff;
            }

            break;

        case 0xd: /* Learned Unicast Tunnel FDB notification */
            memcpy(curr_rec_usr->sx_sfn_type.lrnt_uc_tunnel.mac.ether_addr_octet, &curr_rec_prm[2], 6);
            curr_rec_usr->sx_sfn_type.lrnt_uc_tunnel.udip_msb = curr_rec_prm[8];
            curr_rec_usr->sx_sfn_type.lrnt_uc_tunnel.fid = be16_to_cpu(*(u16*)&curr_rec_prm[10]);
            curr_rec_usr->sx_sfn_type.lrnt_uc_tunnel.udip_lsb = be32_to_cpu(*(u32*)&curr_rec_prm[12]) & 0xffffff;

            if (sfn_reg->rec_type == 1) { /* case of 32-byte record */
                curr_rec_usr->sx_sfn_type.lrnt_uc_tunnel.counter_set.type = curr_rec_prm[28];
                curr_rec_usr->sx_sfn_type.lrnt_uc_tunnel.counter_set.index = be32_to_cpu(*(u32*)&curr_rec_prm[28]) &
                                                                             0xffffff;
            }

            break;

        case 7: /* Aged-out MAC record */
            memcpy(curr_rec_usr->sx_sfn_type.aged_mac.mac.ether_addr_octet, &curr_rec_prm[2], 6);
            curr_rec_usr->sx_sfn_type.aged_mac.fid = be16_to_cpu(*(u16*)&curr_rec_prm[10]);
            curr_rec_usr->sx_sfn_type.aged_mac.system_port = be16_to_cpu(*(u16*)&curr_rec_prm[14]);

            if (sfn_reg->rec_type == 1) { /* case of 32-byte record */
                curr_rec_usr->sx_sfn_type.aged_mac.counter_set.type = curr_rec_prm[28];
                curr_rec_usr->sx_sfn_type.aged_mac.counter_set.index = be32_to_cpu(*(u32*)&curr_rec_prm[28]) &
                                                                       0xffffff;
            }

            break;

        case 8: /* Aged-out MAC LAG record */
            memcpy(curr_rec_usr->sx_sfn_type.aged_mac_lag.mac.ether_addr_octet, &curr_rec_prm[2], 6);
            curr_rec_usr->sx_sfn_type.aged_mac_lag.fid = be16_to_cpu(*(u16*)&curr_rec_prm[10]);
            curr_rec_usr->sx_sfn_type.aged_mac_lag.lag_id = be16_to_cpu(*(u16*)&curr_rec_prm[14]) & 0x1ff;

            if (sfn_reg->rec_type == 1) { /* case of 32-byte record */
                curr_rec_usr->sx_sfn_type.aged_mac_lag.counter_set.type = curr_rec_prm[28];
                curr_rec_usr->sx_sfn_type.aged_mac_lag.counter_set.index = be32_to_cpu(*(u32*)&curr_rec_prm[28]) &
                                                                           0xffffff;
            }

            break;

        case 0xe: /* Aged-out Unicast Tunnel FDB record */
            memcpy(curr_rec_usr->sx_sfn_type.aged_uc_tunnel.mac.ether_addr_octet, &curr_rec_prm[2], 6);
            curr_rec_usr->sx_sfn_type.aged_uc_tunnel.udip_msb = curr_rec_prm[8];
            curr_rec_usr->sx_sfn_type.aged_uc_tunnel.fid = be16_to_cpu(*(u16*)&curr_rec_prm[10]);
            curr_rec_usr->sx_sfn_type.aged_uc_tunnel.protocol = (curr_rec_prm[12] >> 3) & 0x1;
            curr_rec_usr->sx_sfn_type.aged_uc_tunnel.udip_lsb = be32_to_cpu(*(u32*)&curr_rec_prm[12]) & 0xffffff;

            if (sfn_reg->rec_type == 1) { /* case of 32-byte record */
                curr_rec_usr->sx_sfn_type.aged_uc_tunnel.counter_set.type = curr_rec_prm[28];
                curr_rec_usr->sx_sfn_type.aged_uc_tunnel.counter_set.index = be32_to_cpu(*(u32*)&curr_rec_prm[28]) &
                                                                             0xffffff;
            }

            break;

        default:
            printk(KERN_ERR "SFN type (decode) is unsupported (rec_index=%d, type=0x%x)\n", i, curr_rec_usr->sfn_type);
            break;
        }

        curr_rec_prm += (sfn_reg->rec_type == 0) ? 16 : 32;
    }

    return 0;
}

int sx_ACCESS_REG_SFN(struct sx_dev *dev, struct ku_access_sfn_reg *reg_data)
{
    u16 rec_size_dwords = (reg_data->sfn_reg.rec_type == 0) ? 4 : 8;
    u16 sfn_reg_len_dwords = 4 + ((u16)reg_data->sfn_reg.num_records) * rec_size_dwords;

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SFN_encode,
                                  __SFN_decode,
                                  sfn_reg_len_dwords,
                                  &reg_data->sfn_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SFN);

/************************************************
 * SPVTR
 ***********************************************/
#define SPVTR_TPORT_OFFSET                  0x14
#define SPVTR_LOCAL_PORT_OFFSET             0x15
#define SPVTR_LP_MSB_OFFSET                 0x16
#define SPVTR_IPPE_IPVE_EPVE_OFFSET         0x18
#define SPVTR_IPPRIO_MODE_IPVID_MODE_OFFSET 0x19
#define SPVTR_EPVID_MODE_OFFSET             0x1b
#define SPVTR_REG_LEN                       4

static int __SPVTR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spvtr_reg *spvtr_reg = (struct ku_spvtr_reg*)ku_reg;
    u8                   tmp_u8;

    tmp_u8 = spvtr_reg->tport & 0x1;
    SX_PUT_REG_FIELD(inbox, tmp_u8, SPVTR_TPORT_OFFSET);

    SX_PUT_REG_FIELD(inbox, spvtr_reg->local_port, SPVTR_LOCAL_PORT_OFFSET);
    tmp_u8 = spvtr_reg->lp_msb << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, SPVTR_LP_MSB_OFFSET);

    tmp_u8 = 0;
    tmp_u8 |= spvtr_reg->ipprio_enable ? (1 << 7) : 0;
    tmp_u8 |= spvtr_reg->ipvid_enable ? (1 << 6) : 0;
    tmp_u8 |= spvtr_reg->epvid_enable ? (1 << 5) : 0;
    SX_PUT_REG_FIELD(inbox, tmp_u8, SPVTR_IPPE_IPVE_EPVE_OFFSET);

    tmp_u8 = ((spvtr_reg->ipprio_mode & 0xf) << 4) | (spvtr_reg->ipvid_mode & 0xf);
    SX_PUT_REG_FIELD(inbox, tmp_u8, SPVTR_IPPRIO_MODE_IPVID_MODE_OFFSET);

    tmp_u8 = spvtr_reg->epvid_mode & 0xf;
    SX_PUT_REG_FIELD(inbox, tmp_u8, SPVTR_EPVID_MODE_OFFSET);

    return 0;
}

static int __SPVTR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spvtr_reg *spvtr_reg = (struct ku_spvtr_reg*)ku_reg;
    u8                   tmp_u8;

    SX_GET_REG_FIELD(tmp_u8, outbox, SPVTR_TPORT_OFFSET);
    spvtr_reg->tport = tmp_u8 & 0x1;

    SX_GET_REG_FIELD(spvtr_reg->local_port, outbox, SPVTR_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, SPVTR_LP_MSB_OFFSET);
    spvtr_reg->lp_msb = (tmp_u8 >> 4) & 0x3;

    SX_GET_REG_FIELD(tmp_u8, outbox, SPVTR_IPPE_IPVE_EPVE_OFFSET);
    spvtr_reg->ipprio_enable = (tmp_u8 >> 7) & 0x1;
    spvtr_reg->ipvid_enable = (tmp_u8 >> 6) & 0x1;
    spvtr_reg->epvid_enable = (tmp_u8 >> 5) & 0x1;

    SX_GET_REG_FIELD(tmp_u8, outbox, SPVTR_IPPRIO_MODE_IPVID_MODE_OFFSET);
    spvtr_reg->ipprio_mode = (tmp_u8 >> 4) & 0xf;
    spvtr_reg->ipvid_mode = tmp_u8 & 0xf;

    SX_GET_REG_FIELD(tmp_u8, outbox, SPVTR_EPVID_MODE_OFFSET);
    spvtr_reg->epvid_mode = tmp_u8 & 0xf;

    return 0;
}

int sx_ACCESS_REG_SPVTR(struct sx_dev *dev, struct ku_access_spvtr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPVTR_encode,
                                  __SPVTR_decode,
                                  SPVTR_REG_LEN,
                                  &reg_data->spvtr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPVTR);

/************************************************
 * CWTP
 ***********************************************/
#define CWTP_LOCAL_PORT_OFFSET              0x15
#define CWTP_LP_MSB_OFFSET                  0x16
#define CWTP_TRAFIC_CLASS_OFFSET            0x37
#define CWTP_MODE_OFFSET                    0x38
#define CWTP_PROFILE_MIN_OFFSET             0x3c
#define CWTP_PROFILE_PERCENT_AND_MAX_OFFSET 0x40
#define CWTP_REG_LEN                        20

static int __CWTP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_cwtp_reg *cwtp_reg = (struct ku_cwtp_reg*)ku_reg;
    u32                 tmp_u32;
    u8                  tmp_u8;
    int                 i;

    SX_PUT_REG_FIELD(inbox, cwtp_reg->local_port, CWTP_LOCAL_PORT_OFFSET);
    tmp_u8 = cwtp_reg->lp_msb << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, CWTP_LP_MSB_OFFSET);

    SX_PUT_REG_FIELD(inbox, cwtp_reg->traffic_class, CWTP_TRAFIC_CLASS_OFFSET);

    tmp_u8 = cwtp_reg->mode & 0x1;
    SX_PUT_REG_FIELD(inbox, tmp_u8, CWTP_MODE_OFFSET);

    for (i = 0; i < 3; i++) {
        tmp_u32 = cwtp_reg->profiles[i].profile_i_min & 0xfffff;
        SX_PUT_REG_FIELD(inbox, tmp_u32, (CWTP_PROFILE_MIN_OFFSET + (i * 8)));

        tmp_u32 = (((u32)(cwtp_reg->profiles[i].profile_i_percent & 0x7f)) << 24) |
                  (cwtp_reg->profiles[i].profile_i_max & 0xfffff);
        SX_PUT_REG_FIELD(inbox, tmp_u32, (CWTP_PROFILE_PERCENT_AND_MAX_OFFSET + (i * 8)));
    }

    return 0;
}

static int __CWTP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_cwtp_reg *cwtp_reg = (struct ku_cwtp_reg*)ku_reg;
    u32                 tmp_u32;
    u8                  tmp_u8;
    int                 i;

    SX_GET_REG_FIELD(cwtp_reg->local_port, outbox, CWTP_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, CWTP_LP_MSB_OFFSET);
    cwtp_reg->lp_msb = (tmp_u8 >> 4) & 0x3;

    SX_GET_REG_FIELD(cwtp_reg->traffic_class, outbox, CWTP_TRAFIC_CLASS_OFFSET);

    SX_GET_REG_FIELD(tmp_u8, outbox, CWTP_MODE_OFFSET);
    cwtp_reg->mode = tmp_u8 & 0x1;

    for (i = 0; i < 3; i++) {
        SX_GET_REG_FIELD(tmp_u32, outbox, (CWTP_PROFILE_MIN_OFFSET + (i * 8)));
        cwtp_reg->profiles[i].profile_i_min = tmp_u32 & 0xfffff;

        SX_GET_REG_FIELD(tmp_u32, outbox, (CWTP_PROFILE_PERCENT_AND_MAX_OFFSET + (i * 8)));
        cwtp_reg->profiles[i].profile_i_percent = (tmp_u32 >> 24) & 0x7f;
        cwtp_reg->profiles[i].profile_i_max = tmp_u32 & 0xfffff;
    }

    return 0;
}

int sx_ACCESS_REG_CWTP(struct sx_dev *dev, struct ku_access_cwtp_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __CWTP_encode,
                                  __CWTP_decode,
                                  CWTP_REG_LEN,
                                  &reg_data->cwtp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_CWTP);

/************************************************
 * PFCC
 ***********************************************/
#define PFCC_DWORD0_OFFSET 0x14
#define PFCC_DWORD1_OFFSET 0x18
#define PFCC_DWORD2_OFFSET 0x1c
#define PFCC_DWORD3_OFFSET 0x20
#define PFCC_REG_LEN       0x8

static int __PFCC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pfcc_reg *pfcc_reg = (struct ku_pfcc_reg*)ku_reg;
    u32                 tmp_u32;

    tmp_u32 = (((u32)(pfcc_reg->local_port & 0xff)) << 16) |
              (((u32)(pfcc_reg->lp_msb & 0x3)) << 12);
    SX_PUT_REG_FIELD(inbox, tmp_u32, PFCC_DWORD0_OFFSET);

    tmp_u32 = (((u32)(pfcc_reg->prio_mask_tx & 0xff)) << 16) |
              (pfcc_reg->prio_mask_rx & 0xff);
    SX_PUT_REG_FIELD(inbox, tmp_u32, PFCC_DWORD1_OFFSET);

    tmp_u32 = (((u32)(pfcc_reg->pause_policy_tx & 0x1)) << 31) |
              (((u32)(pfcc_reg->patx & 0x3)) << 27) |
              (((u32)(pfcc_reg->prio_policy_tx & 0xff)) << 16) |
              (pfcc_reg->cb_policy_tx & 0xff);
    SX_PUT_REG_FIELD(inbox, tmp_u32, PFCC_DWORD2_OFFSET);

    tmp_u32 = (((u32)(pfcc_reg->pause_policy_rx & 0x1)) << 31) |
              (((u32)(pfcc_reg->parx & 0x3)) << 27) |
              (((u32)(pfcc_reg->prio_policy_rx & 0xff)) << 16) |
              (pfcc_reg->cb_policy_rx & 0xff);
    SX_PUT_REG_FIELD(inbox, tmp_u32, PFCC_DWORD3_OFFSET);

    return 0;
}

static int __PFCC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pfcc_reg *pfcc_reg = (struct ku_pfcc_reg*)ku_reg;
    u32                 tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, PFCC_DWORD0_OFFSET);
    pfcc_reg->local_port = (tmp_u32 >> 16) & 0xff;
    pfcc_reg->lp_msb = (tmp_u32 >> 12) & 0x3;

    SX_GET_REG_FIELD(tmp_u32, outbox, PFCC_DWORD1_OFFSET);
    pfcc_reg->prio_mask_tx = (tmp_u32 >> 16) & 0xff;
    pfcc_reg->prio_mask_rx = tmp_u32 & 0xff;

    SX_GET_REG_FIELD(tmp_u32, outbox, PFCC_DWORD2_OFFSET);
    pfcc_reg->pause_policy_tx = (tmp_u32 >> 31) & 0x1;
    pfcc_reg->patx = (tmp_u32 >> 27) & 0x3;
    pfcc_reg->prio_policy_tx = (tmp_u32 >> 16) & 0xff;
    pfcc_reg->cb_policy_tx = tmp_u32 & 0xff;

    SX_GET_REG_FIELD(tmp_u32, outbox, PFCC_DWORD3_OFFSET);
    pfcc_reg->pause_policy_rx = (tmp_u32 >> 31) & 0x1;
    pfcc_reg->parx = (tmp_u32 >> 27) & 0x3;
    pfcc_reg->prio_policy_rx = (tmp_u32 >> 16) & 0xff;
    pfcc_reg->cb_policy_rx = tmp_u32 & 0xff;

    return 0;
}

int sx_ACCESS_REG_PFCC(struct sx_dev *dev, struct ku_access_pfcc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PFCC_encode,
                                  __PFCC_decode,
                                  PFCC_REG_LEN,
                                  &reg_data->pfcc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PFCC);

/************************************************
 * QPPM
 ***********************************************/
#define QPPM_LOCAL_PORT_OFFSET   0x15
#define QPPM_LP_MSB_OFFSET       0x16
#define QPPM_SWITCH_PRIO0_OFFSET 0x18
#define QPPM_REG_LEN             0x11

static int __QPPM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qppm_reg *qppm_reg = (struct ku_qppm_reg*)ku_reg;
    u32                 tmp_u32;
    u8                  tmp_u8;
    int                 i, color_idx;

    SX_PUT_REG_FIELD(inbox, qppm_reg->local_port, QPPM_LOCAL_PORT_OFFSET);
    tmp_u8 = qppm_reg->lp_msb << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, QPPM_LP_MSB_OFFSET);

    for (i = 0; i < 16; i++) {
        tmp_u32 = 0;

        for (color_idx = 0; color_idx < 3; color_idx++) {
            tmp_u8 = ((qppm_reg->switch_prio[i].color[color_idx].enable_pcp & 0x1) << 7) |
                     ((qppm_reg->switch_prio[i].color[color_idx].dei & 0x1) << 4) |
                     (qppm_reg->switch_prio[i].color[color_idx].pcp & 0x7);

            tmp_u32 |= ((u32)tmp_u8) << (8 * (3 - color_idx));
        }

        SX_PUT_REG_FIELD(inbox, tmp_u32, (QPPM_SWITCH_PRIO0_OFFSET + i * 4));
    }

    return 0;
}

static int __QPPM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qppm_reg *qppm_reg = (struct ku_qppm_reg*)ku_reg;
    u32                 tmp_u32;
    u8                  tmp_u8;
    int                 i, color_idx;

    SX_GET_REG_FIELD(qppm_reg->local_port, outbox, QPPM_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, QPPM_LP_MSB_OFFSET);
    qppm_reg->lp_msb = (tmp_u8 >> 4) & 0x3;

    for (i = 0; i < 16; i++) {
        SX_GET_REG_FIELD(tmp_u32, outbox, (QPPM_SWITCH_PRIO0_OFFSET + i * 4));

        for (color_idx = 0; color_idx < 3; color_idx++) {
            tmp_u8 = (tmp_u32 >> (8 * (3 - color_idx))) & 0xff;

            qppm_reg->switch_prio[i].color[color_idx].enable_pcp = (tmp_u8 >> 7) & 0x1;
            qppm_reg->switch_prio[i].color[color_idx].dei = (tmp_u8 >> 4) & 0x1;
            qppm_reg->switch_prio[i].color[color_idx].pcp = tmp_u8 & 0x7;
        }
    }

    return 0;
}

int sx_ACCESS_REG_QPPM(struct sx_dev *dev, struct ku_access_qppm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QPPM_encode,
                                  __QPPM_decode,
                                  QPPM_REG_LEN,
                                  &reg_data->qppm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QPPM);

/************************************************
 * SBMM
 ***********************************************/
#define SBMM_DWORD_OFFSET(x) (0x14 + (4 * (x)))
#define SBMM_REG_LEN 10

static int __SBMM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbmm_reg *sbmm_reg = (struct ku_sbmm_reg*)ku_reg;
    u32                 tmp_u32;

    tmp_u32 = (sbmm_reg->prio & 0xf) << 8;
    SX_PUT_REG_FIELD(inbox, tmp_u32, SBMM_DWORD_OFFSET(0));

    tmp_u32 = (sbmm_reg->buff_occupancy) & 0xffffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, SBMM_DWORD_OFFSET(4));

    tmp_u32 = (((u32)(sbmm_reg->clr & 0x1)) << 31) | (sbmm_reg->max_buff_occupancy & 0xffffff);
    SX_PUT_REG_FIELD(inbox, tmp_u32, SBMM_DWORD_OFFSET(5));

    tmp_u32 = (sbmm_reg->min_buff) & 0xffffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, SBMM_DWORD_OFFSET(6));

    tmp_u32 = (((u32)(sbmm_reg->infinite_size & 0x1)) << 31) | (sbmm_reg->max_buff & 0xffffff);
    SX_PUT_REG_FIELD(inbox, tmp_u32, SBMM_DWORD_OFFSET(7));

    tmp_u32 = (sbmm_reg->pool) & 0xf;
    SX_PUT_REG_FIELD(inbox, tmp_u32, SBMM_DWORD_OFFSET(9));

    return 0;
}

static int __SBMM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbmm_reg *sbmm_reg = (struct ku_sbmm_reg*)ku_reg;
    u32                 tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, SBMM_DWORD_OFFSET(0));
    sbmm_reg->prio = (tmp_u32 >> 8) & 0xf;

    SX_GET_REG_FIELD(tmp_u32, outbox, SBMM_DWORD_OFFSET(4));
    sbmm_reg->buff_occupancy = tmp_u32 & 0xffffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, SBMM_DWORD_OFFSET(5));
    sbmm_reg->clr = (tmp_u32 >> 31) & 0x1;
    sbmm_reg->max_buff_occupancy = tmp_u32 & 0xffffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, SBMM_DWORD_OFFSET(6));
    sbmm_reg->min_buff = tmp_u32 & 0xffffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, SBMM_DWORD_OFFSET(7));
    sbmm_reg->infinite_size = (tmp_u32 >> 31) & 0x1;
    sbmm_reg->max_buff = tmp_u32 & 0xffffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, SBMM_DWORD_OFFSET(9));
    sbmm_reg->pool = tmp_u32 & 0xf;

    return 0;
}

int sx_ACCESS_REG_SBMM(struct sx_dev *dev, struct ku_access_sbmm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBMM_encode,
                                  __SBMM_decode,
                                  SBMM_REG_LEN,
                                  &reg_data->sbmm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBMM);

/************************************************
 * SLECR
 ***********************************************/
#define SLECR_DWORD0_OFFSET 0x14
#define SLECR_REG_LEN       4

static int __SLECR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_slecr_reg *slecr_reg = (struct ku_slecr_reg*)ku_reg;
    u32                  tmp_u32;

    tmp_u32 = (((u32)(slecr_reg->swid & 0xff)) << 24) |
              (((u32)(slecr_reg->independent_learning & 0x1)) << 3) |
              (((u32)(slecr_reg->roaming_enable & 0x1)) << 2);
    SX_PUT_REG_FIELD(inbox, tmp_u32, SLECR_DWORD0_OFFSET);

    return 0;
}

static int __SLECR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_slecr_reg *slecr_reg = (struct ku_slecr_reg*)ku_reg;
    u32                  tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, SLECR_DWORD0_OFFSET);
    slecr_reg->swid = (tmp_u32 >> 24) & 0xff;
    slecr_reg->independent_learning = (tmp_u32 >> 3) & 0x1;
    slecr_reg->roaming_enable = (tmp_u32 >> 2) & 0x1;

    return 0;
}

int sx_ACCESS_REG_SLECR(struct sx_dev *dev, struct ku_access_slecr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLECR_encode,
                                  __SLECR_decode,
                                  SLECR_REG_LEN,
                                  &reg_data->slecr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLECR);

/************************************************
 * SPVC
 ***********************************************/
#define SPVC_LOCAL_PORT_OFFSET 0x15
#define SPVC_LP_MSB_OFFSET     0x16
#define SPVC_INFO_OFFSET       0x1d
#define SPVC_REG_LEN           3

static int __SPVC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spvc_reg *spvc_reg = (struct ku_spvc_reg*)ku_reg;
    u8                  tmp_u8;
    int                 i;

    SX_PUT_REG_FIELD(inbox, spvc_reg->local_port, SPVC_LOCAL_PORT_OFFSET);
    tmp_u8 = spvc_reg->lp_msb << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, SPVC_LP_MSB_OFFSET);

    for (i = 0; i < 3; i++) {
        tmp_u8 = ((spvc_reg->inner_et[i] & 0x1) << 1) |
                 (spvc_reg->et[i] & 0x1);
        SX_PUT_REG_FIELD(inbox, tmp_u8, (SPVC_INFO_OFFSET + 2 - i));
    }

    return 0;
}

static int __SPVC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spvc_reg *spvc_reg = (struct ku_spvc_reg*)ku_reg;
    u8                  tmp_u8;
    int                 i;

    SX_GET_REG_FIELD(spvc_reg->local_port, outbox, SPVC_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, SPVC_LP_MSB_OFFSET);
    spvc_reg->lp_msb = (tmp_u8 >> 4) & 0x3;

    for (i = 0; i < 3; i++) {
        SX_GET_REG_FIELD(tmp_u8, outbox, (SPVC_INFO_OFFSET + 2 - i));
        spvc_reg->inner_et[i] = (tmp_u8 >> 1) & 0x1;
        spvc_reg->et[i] = tmp_u8 & 0x1;
    }

    return 0;
}

int sx_ACCESS_REG_SPVC(struct sx_dev *dev, struct ku_access_spvc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPVC_encode,
                                  __SPVC_decode,
                                  SPVC_REG_LEN,
                                  &reg_data->spvc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPVC);

/************************************************
 * MPRS
 ***********************************************/
#define MPRS_DWORD0_OFFSET 0x14
#define MPRS_REG_LEN       5        /* in dwords */

static int __MPRS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mprs_reg *mprs_reg = (struct ku_mprs_reg*)ku_reg;
    u32                 tmp_u32;

    tmp_u32 = mprs_reg->parsing_depth & 0xffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, MPRS_DWORD0_OFFSET);

    tmp_u32 = mprs_reg->parsing_en & 0xffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, (MPRS_DWORD0_OFFSET + 4));

    tmp_u32 = (((u32)(mprs_reg->ctipl & 0x1)) << 8) | (mprs_reg->ctipl_l2_length & 0x7f);
    SX_PUT_REG_FIELD(inbox, tmp_u32, (MPRS_DWORD0_OFFSET + 8));

    tmp_u32 = mprs_reg->vxlan_udp_dport & 0xffff;
    SX_PUT_REG_FIELD(inbox, tmp_u32, (MPRS_DWORD0_OFFSET + 16));

    return 0;
}

static int __MPRS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mprs_reg *mprs_reg = (struct ku_mprs_reg*)ku_reg;
    u32                 tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, MPRS_DWORD0_OFFSET);
    mprs_reg->parsing_depth = tmp_u32 & 0xffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, MPRS_DWORD0_OFFSET + 4);
    mprs_reg->parsing_en = tmp_u32 & 0xffff;

    SX_GET_REG_FIELD(tmp_u32, outbox, MPRS_DWORD0_OFFSET + 8);
    mprs_reg->ctipl = (tmp_u32 >> 8) & 0x1;
    mprs_reg->ctipl_l2_length = tmp_u32 & 0x7f;

    SX_GET_REG_FIELD(tmp_u32, outbox, MPRS_DWORD0_OFFSET + 16);
    mprs_reg->vxlan_udp_dport = tmp_u32 & 0xffff;

    return 0;
}

int sx_ACCESS_REG_MPRS(struct sx_dev *dev, struct ku_access_mprs_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MPRS_encode,
                                  __MPRS_decode,
                                  MPRS_REG_LEN,
                                  &reg_data->mprs_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MPRS);

/************************************************
 * MRRR
 ***********************************************/
#define MRRR_DWORD0_OFFSET 0x14
#define MRRR_REG_LEN       2        /* in dwords */

static int __MRRR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mrrr_reg *mrrr_reg = (struct ku_mrrr_reg*)ku_reg;
    u32                 tmp_u32;

    tmp_u32 = mrrr_reg->init_rr & 0xf;
    SX_PUT_REG_FIELD(inbox, tmp_u32, MRRR_DWORD0_OFFSET);

    tmp_u32 = mrrr_reg->rr_status & 0xf;
    SX_PUT_REG_FIELD(inbox, tmp_u32, (MRRR_DWORD0_OFFSET + 4));

    return 0;
}

static int __MRRR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mrrr_reg *mrrr_reg = (struct ku_mrrr_reg*)ku_reg;
    u32                 tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, MRRR_DWORD0_OFFSET);
    mrrr_reg->init_rr = tmp_u32 & 0xf;

    SX_GET_REG_FIELD(tmp_u32, outbox, MRRR_DWORD0_OFFSET + 4);
    mrrr_reg->rr_status = tmp_u32 & 0xf;

    return 0;
}

int sx_ACCESS_REG_MRRR(struct sx_dev *dev, struct ku_access_mrrr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MRRR_encode,
                                  __MRRR_decode,
                                  MRRR_REG_LEN,
                                  &reg_data->mrrr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MRRR);

/************************************************
 * MONI
 ***********************************************/
#define MONI_DWORD0_OFFSET 0x14
#define MONI_DWORD1_OFFSET 0x18
#define MONI_REG_LEN       2        /* in dwords */

static int __MONI_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_moni_reg *moni_reg = (struct ku_moni_reg*)ku_reg;
    u32                 tmp_u32;

    tmp_u32 = (((u32)(moni_reg->local_port & 0xff)) << 16) |
              (((u32)(moni_reg->lp_msb & 0x3)) << 12);
    SX_PUT_REG_FIELD(inbox, tmp_u32, MONI_DWORD0_OFFSET);

    tmp_u32 = moni_reg->en & 0x1;
    SX_PUT_REG_FIELD(inbox, tmp_u32, MONI_DWORD1_OFFSET);

    return 0;
}

static int __MONI_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_moni_reg *moni_reg = (struct ku_moni_reg*)ku_reg;
    u32                 tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, MONI_DWORD0_OFFSET);
    moni_reg->local_port = (tmp_u32 >> 16) & 0xff;
    moni_reg->lp_msb = (tmp_u32 >> 12) & 0x3;

    SX_GET_REG_FIELD(tmp_u32, outbox, MONI_DWORD1_OFFSET);
    moni_reg->en = tmp_u32 & 0x1;

    return 0;
}

int sx_ACCESS_REG_MONI(struct sx_dev *dev, struct ku_access_moni_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MONI_encode,
                                  __MONI_decode,
                                  MONI_REG_LEN,
                                  &reg_data->moni_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MONI);

/************************************************
 * PCMR
 ***********************************************/
#define PCMR_DWORD0_OFFSET 0x14
#define PCMR_DWORD1_OFFSET 0x18
#define PCMR_DWORD2_OFFSET 0x18
#define PCMR_REG_LEN       3        /* in dwords */

static int __PCMR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pcmr_reg *pcmr_reg = (struct ku_pcmr_reg*)ku_reg;
    u32                 tmp_u32;

    tmp_u32 = (((u32)(pcmr_reg->local_port & 0xff)) << 16) |
              (((u32)(pcmr_reg->lp_msb & 0x3)) << 12);
    SX_PUT_REG_FIELD(inbox, tmp_u32, PCMR_DWORD0_OFFSET);

    tmp_u32 = (((u32)(pcmr_reg->tx_ts_over_crc_cap & 0x1)) << 16) |
              (((u32)(pcmr_reg->tx_fcs_recalc_cap & 0x1)) << 15) |
              (((u32)(pcmr_reg->rx_fcs_drop_cap & 0x1)) << 14) |
              (((u32)(pcmr_reg->rx_ts_over_crc_cap & 0x1)) << 13) |
              (((u32)(pcmr_reg->fcs_cap & 0x1)) << 1);
    SX_PUT_REG_FIELD(inbox, tmp_u32, PCMR_DWORD1_OFFSET);

    tmp_u32 = (((u32)(pcmr_reg->tx_ts_over_crc & 0x1)) << 16) |
              (((u32)(pcmr_reg->tx_fcs_recalc & 0x1)) << 15) |
              (((u32)(pcmr_reg->rx_fcs_drop & 0x1)) << 14) |
              (((u32)(pcmr_reg->rx_ts_over_crc & 0x1)) << 13) |
              (((u32)(pcmr_reg->fcs_chk & 0x1)) << 1);
    SX_PUT_REG_FIELD(inbox, tmp_u32, PCMR_DWORD2_OFFSET);

    return 0;
}

static int __PCMR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pcmr_reg *pcmr_reg = (struct ku_pcmr_reg*)ku_reg;
    u32                 tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, PCMR_DWORD0_OFFSET);
    pcmr_reg->local_port = (tmp_u32 >> 16) & 0xff;
    pcmr_reg->lp_msb = (tmp_u32 >> 12) & 0x3;

    SX_GET_REG_FIELD(tmp_u32, outbox, PCMR_DWORD1_OFFSET);
    pcmr_reg->tx_ts_over_crc_cap = (tmp_u32 >> 16) & 0x1;
    pcmr_reg->tx_fcs_recalc_cap = (tmp_u32 >> 15) & 0x1;
    pcmr_reg->rx_fcs_drop_cap = (tmp_u32 >> 14) & 0x1;
    pcmr_reg->rx_ts_over_crc_cap = (tmp_u32 >> 13) & 0x1;
    pcmr_reg->fcs_cap = (tmp_u32 >> 1) & 0x1;

    SX_GET_REG_FIELD(tmp_u32, outbox, PCMR_DWORD2_OFFSET);
    pcmr_reg->tx_ts_over_crc = (tmp_u32 >> 16) & 0x1;
    pcmr_reg->tx_fcs_recalc = (tmp_u32 >> 15) & 0x1;
    pcmr_reg->rx_fcs_drop = (tmp_u32 >> 14) & 0x1;
    pcmr_reg->rx_ts_over_crc = (tmp_u32 >> 13) & 0x1;
    pcmr_reg->fcs_chk = (tmp_u32 >> 1) & 0x1;

    return 0;
}

int sx_ACCESS_REG_PCMR(struct sx_dev *dev, struct ku_access_pcmr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PCMR_encode,
                                  __PCMR_decode,
                                  PCMR_REG_LEN,
                                  &reg_data->pcmr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PCMR);

/************************************************
 * MOPIR_V2
 ***********************************************/
#define MOPIR_V2_DWORD0_OFFSET 0x14
#define MOPIR_V2_DWORD1_OFFSET 0x18
#define MOPIR_V2_PACKET_OFFSET 0x64
#define MOPIR_V2_REG_LEN       0x1c0   /* in dwords */

static int __MOPIR_V2_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mopir_v2_reg *mopir_v2_reg = (struct ku_mopir_v2_reg*)ku_reg;
    u32                     tmp_u32;

    tmp_u32 = ((u32)(1 << 24)) /* num_pckt=1 */ |
              ((u32)(1 << 20)) /* protocol=Ethernet */ |
              (((u32)(mopir_v2_reg->is_control & 0x1)) << 18) |
              (mopir_v2_reg->dst_port & 0xffff);
    SX_PUT_REG_FIELD(inbox, tmp_u32, MOPIR_V2_DWORD0_OFFSET);

    tmp_u32 = (mopir_v2_reg->packet_length & 0x3fff);
    SX_PUT_REG_FIELD(inbox, tmp_u32, MOPIR_V2_DWORD1_OFFSET);

    memcpy(inbox + MOPIR_V2_PACKET_OFFSET - REG_START_OFFSET, mopir_v2_reg->packet, mopir_v2_reg->packet_length);
    return 0;
}

static int __MOPIR_V2_decode(u8 *outbox, void *ku_reg, void *context)
{
    /* nothing to do here */
    return 0;
}

int sx_ACCESS_REG_MOPIR_V2(struct sx_dev *dev, struct ku_access_mopir_v2_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MOPIR_V2_encode,
                                  __MOPIR_V2_decode,
                                  MOPIR_V2_REG_LEN,
                                  &reg_data->mopir_v2_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MOPIR_V2);

/************************************************
 * MOPR
 ***********************************************/
#define MOPR_DWORD0_OFFSET 0x14
#define MOPR_DWORD1_OFFSET 0x18
#define MOPR_CQE_V2_OFFSET 0x24
#define MOPR_PACKET_OFFSET 0x64
#define MOPR_REG_LEN       0x1c0 /* in dwords */

static int __MOPR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mopr_reg *mopr_reg = (struct ku_mopr_reg*)ku_reg;
    u32                 tmp_u32;

    tmp_u32 = (((u32)(mopr_reg->op & 0x7)) << 24) | 13;  /* buffer_id=tester (13)*/
    SX_PUT_REG_FIELD(inbox, tmp_u32, MOPR_DWORD0_OFFSET);

    return 0;
}

static int __MOPR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mopr_reg *mopr_reg = (struct ku_mopr_reg*)ku_reg;
    u32                 tmp_u32;

    SX_GET_REG_FIELD(tmp_u32, outbox, MOPR_DWORD0_OFFSET);
    mopr_reg->op = (tmp_u32 >> 24) & 0x7;

    SX_GET_REG_FIELD(tmp_u32, outbox, MOPR_DWORD1_OFFSET);
    mopr_reg->packet_length = tmp_u32 & 0x3fff;

    if (mopr_reg->packet != NULL) {
        memcpy(mopr_reg->cqe_v2, outbox + MOPR_CQE_V2_OFFSET - REG_START_OFFSET, sizeof(mopr_reg->cqe_v2));
        memcpy(mopr_reg->packet, outbox + MOPR_PACKET_OFFSET - REG_START_OFFSET, mopr_reg->packet_length);
    }

    return 0;
}

int sx_ACCESS_REG_MOPR(struct sx_dev *dev, struct ku_access_mopr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MOPR_encode,
                                  __MOPR_decode,
                                  MOPR_REG_LEN,
                                  &reg_data->mopr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MOPR);

/************************************************
 * RDPM
 ***********************************************/
#define RDPM_REG_LEN 0x10 /* in dwords */

static int __RDPM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_rdpm_reg *rdpm_reg = (struct ku_rdpm_reg*)ku_reg;
    u8                 *dscp;
    int                 i;

    for (dscp = inbox, i = 63; i >= 0; i--, dscp++) {
        *dscp = ((rdpm_reg->dscp_update[i] & 0x1) << 7) |
                ((rdpm_reg->color[i] & 0x3) << 5) |
                (rdpm_reg->priority[i] & 0xf);
    }

    return 0;
}

static int __RDPM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_rdpm_reg *rdpm_reg = (struct ku_rdpm_reg*)ku_reg;
    const u8           *dscp;
    int                 i;

    for (dscp = outbox, i = 63; i >= 0; i--, dscp++) {
        rdpm_reg->dscp_update[i] = ((*dscp) >> 7) & 0x1;
        rdpm_reg->color[i] = ((*dscp) >> 5) & 0x3;
        rdpm_reg->priority[i] = (*dscp) & 0xf;
    }

    return 0;
}

int sx_ACCESS_REG_RDPM(struct sx_dev *dev, struct ku_access_rdpm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RDPM_encode,
                                  __RDPM_decode,
                                  RDPM_REG_LEN,
                                  &reg_data->rdpm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RDPM);

/************************************************
 * MNVDA_NV_SWITCH_CONF
 ***********************************************/
#define NV_SWITCH_CONF_VALID_HEADER_TYPE_OFFSET 0x14
#define NV_SWITCH_CONF_LENGTH_OFFSET            0x17
#define NV_SWITCH_CONF_TYPE_CLASS_INDEX_OFFSET  0x18
#define NV_SWITCH_CONF_CRC16_OFFSET             0x1e
#define NV_SWITCH_CONF_DAS_OFFSET               0x20
#define NV_SWITCH_CONF_IS_NVLINK_OFFSET         0x21
#define NV_SWITCH_CONF_SPLIT_MODE_OFFSET        0x23
#define NV_SWITCH_CONF_REG_LEN                  0x5


static int __NV_SWITCH_CONF_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mnvda_nv_switch_conf_reg *nv_switch_conf_reg = (struct ku_mnvda_nv_switch_conf_reg*)ku_reg;
    u8                                  das = (nv_switch_conf_reg->nv_switch_conf.das) << 4;
    u8                                  valid = nv_switch_conf_reg->valid << 6;

    SX_PUT_REG_FIELD(inbox, valid, NV_SWITCH_CONF_VALID_HEADER_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, nv_switch_conf_reg->length, NV_SWITCH_CONF_LENGTH_OFFSET);
    SX_PUT_REG_FIELD(inbox, nv_switch_conf_reg->type_class_index, NV_SWITCH_CONF_TYPE_CLASS_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, nv_switch_conf_reg->crc16, NV_SWITCH_CONF_CRC16_OFFSET);
    SX_PUT_REG_FIELD(inbox, das, NV_SWITCH_CONF_DAS_OFFSET);
    SX_PUT_REG_FIELD(inbox, nv_switch_conf_reg->nv_switch_conf.is_nvlink, NV_SWITCH_CONF_IS_NVLINK_OFFSET);
    SX_PUT_REG_FIELD(inbox, nv_switch_conf_reg->nv_switch_conf.split_mode, NV_SWITCH_CONF_SPLIT_MODE_OFFSET);

    return 0;
}

static int __NV_SWITCH_CONF_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mnvda_nv_switch_conf_reg *nv_switch_conf_reg = (struct ku_mnvda_nv_switch_conf_reg*)ku_reg;
    u8                                  valid;
    u8                                  das;

    SX_GET_REG_FIELD(valid, outbox, NV_SWITCH_CONF_VALID_HEADER_TYPE_OFFSET);
    nv_switch_conf_reg->valid = valid >> 6;
    SX_GET_REG_FIELD(nv_switch_conf_reg->length, outbox, NV_SWITCH_CONF_LENGTH_OFFSET);
    SX_GET_REG_FIELD(nv_switch_conf_reg->type_class_index, outbox, NV_SWITCH_CONF_TYPE_CLASS_INDEX_OFFSET);
    SX_GET_REG_FIELD(nv_switch_conf_reg->crc16, outbox, NV_SWITCH_CONF_CRC16_OFFSET);
    SX_GET_REG_FIELD(das, outbox, NV_SWITCH_CONF_DAS_OFFSET);
    nv_switch_conf_reg->nv_switch_conf.das = das >> 4;
    SX_GET_REG_FIELD(nv_switch_conf_reg->nv_switch_conf.is_nvlink, outbox, NV_SWITCH_CONF_IS_NVLINK_OFFSET);
    SX_GET_REG_FIELD(nv_switch_conf_reg->nv_switch_conf.split_mode, outbox, NV_SWITCH_CONF_SPLIT_MODE_OFFSET);

    return 0;
}

int sx_ACCESS_REG_MNVDA_NV_SWITCH_CONF(struct sx_dev *dev, struct ku_access_mnvda_nv_switch_conf_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __NV_SWITCH_CONF_encode,
                                  __NV_SWITCH_CONF_decode,
                                  NV_SWITCH_CONF_REG_LEN,
                                  &reg_data->mnvda_nv_switch_conf_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MNVDA_NV_SWITCH_CONF);

/************************************************
 * RAW_BUFF
 ***********************************************/

int sx_ACCESS_REG_RAW_BUFF(struct sx_dev *dev, struct ku_access_reg_raw_buff *raw_data)
{
    struct sx_cmd_mailbox *in_mailbox;
    struct sx_cmd_mailbox *out_mailbox;
    u32                   *inbox;
    u32                   *outbox;
    int                    err;

    if (SX_MAILBOX_SIZE < raw_data->raw_buff.size) {
        sx_warn(dev, "Cannot send the raw register access request "
                "since the mailbox size is too small\n");
        return -ENOMEM;
    }

    in_mailbox = sx_alloc_cmd_mailbox(dev, raw_data->dev_id);
    if (IS_ERR(in_mailbox)) {
        return PTR_ERR(in_mailbox);
    }

    out_mailbox = sx_alloc_cmd_mailbox(dev, raw_data->dev_id);
    if (IS_ERR(out_mailbox)) {
        err = PTR_ERR(out_mailbox);
        goto out_free;
    }

    inbox = in_mailbox->buf;
    memset(inbox, 0, SX_MAILBOX_SIZE);
    outbox = out_mailbox->buf;

    err = copy_from_user(inbox, raw_data->raw_buff.buff,
                         raw_data->raw_buff.size);
    if (err) {
        goto out;
    }

    err = sx_cmd_box(dev, raw_data->dev_id, in_mailbox, out_mailbox, 0, 0,
                     SX_CMD_ACCESS_REG, SX_CMD_TIME_CLASS_A,
                     raw_data->raw_buff.size);
    if (err) {
        goto out;
    }

    err = copy_to_user(raw_data->raw_buff.buff, outbox,
                       raw_data->raw_buff.size);

out:
    sx_free_cmd_mailbox(dev, out_mailbox);
out_free:
    sx_free_cmd_mailbox(dev, in_mailbox);
    return err;
}
