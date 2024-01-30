/*
 * Copyright © 2022-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#ifndef SX_SPICE_UPHY_REG_INFRA_H_
#define SX_SPICE_UPHY_REG_INFRA_H_

#include "sx_spice_wrapper.h"
#include <linux/mlx_sx/map.h>

#define UPHY_COMMON_REG_LEN           0x2
#define PEUCG_PAGE_DATA_REC_MAX_COUNT 47

typedef struct uphy_common_reg {
    char reg[UPHY_COMMON_REG_LEN];
} uphy_common_reg_t;

typedef enum {
    UPHY_REG_TYPE_DLN,
    UPHY_REG_TYPE_CLN
} uphy_reg_type_e;

#define __UPHY_ITEM_NAME(_cname, _iname) \
    uphy_reg_ ## _cname ## _ ## _iname ## _item

static inline u16 __uphy_item_get16(const char *buf, const struct mlxsw_item *item, unsigned short index)
{
    unsigned int offset = __mlxsw_item_offset(item, 0, index, sizeof(u16));
    __be16      *b = (__be16 *)buf;
    u16          tmp;

    tmp = b[offset];
    tmp >>= item->shift;
    tmp &= GEN_MASK(item->size.bits - 1, 0);
    return tmp;
}

static inline u8 __uphy_item_get8(const char *buf, const struct mlxsw_item *item, unsigned short index)
{
    unsigned int offset = __mlxsw_item_offset(item, 0, index, sizeof(u8));
    u8          *b = (u8 *)buf;
    u8           tmp;

    tmp = b[offset];
    tmp >>= item->shift;
    tmp &= GEN_MASK(item->size.bits - 1, 0);
    return tmp;
}

/*
 * _cname: container name (e.g. command name, register name)
 * _iname: item name within the container
 */

#define UPHY_ITEM8(_cname, _iname, _offset, _shift, _sizebits)                           \
    static struct mlxsw_item __UPHY_ITEM_NAME(_cname, _iname) = {                        \
        .offset = _offset,                                                               \
        .shift = _shift,                                                                 \
        .size = {.bits = _sizebits, },                                                   \
        .name = "reg_" #_cname "_" #_iname,                                              \
    };                                                                                   \
    uint8_t                  uphy_reg_ ## _cname ## _ ## _iname ## _get(const char *buf) \
    {                                                                                    \
        return __uphy_item_get8(buf, &__UPHY_ITEM_NAME(_cname, _iname), 0);              \
    }

#define UPHY_ITEM16(_cname, _iname, _offset, _shift, _sizebits)                          \
    static struct mlxsw_item __UPHY_ITEM_NAME(_cname, _iname) = {                        \
        .offset = _offset,                                                               \
        .shift = _shift,                                                                 \
        .size = {.bits = _sizebits, },                                                   \
        .name = "reg_" #_cname "_" #_iname,                                              \
    };                                                                                   \
    uint16_t                 uphy_reg_ ## _cname ## _ ## _iname ## _get(const char *buf) \
    {                                                                                    \
        return __uphy_item_get16(buf, &__UPHY_ITEM_NAME(_cname, _iname), 0);             \
    }

typedef int (*sx_spice_uphy_reg_data_to_buffer_cb_t)(char    **buffer,
                                                     size_t    buffer_length,
                                                     int      *buffer_size,
                                                     uint16_t *reg);

struct sx_spice_uphy_reg_info {
    struct sx_core_map_info               map_info;
    uint16_t                              reg_id;
    sx_spice_uphy_reg_data_to_buffer_cb_t print_cb;
};

int sx_spice_uphy_infra_init(void);
void sx_spice_uphy_infra_deinit(void);
const struct sx_spice_uphy_reg_info* sx_spice_uphy_infra_reg_info_get(uphy_reg_type_e reg_type, uint16_t reg_id);
int sx_spice_uphy_infra_reg_init(uphy_reg_type_e                       reg_type,
                                 uint16_t                              reg_id,
                                 sx_spice_uphy_reg_data_to_buffer_cb_t print_cb);

#endif /* SX_SPICE_UPHY_REG_INFRA_H_ */
