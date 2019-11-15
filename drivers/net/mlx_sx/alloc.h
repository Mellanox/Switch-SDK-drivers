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

#ifndef ALLOC_H_
#define ALLOC_H_

/************************************************
 * Includes
 ***********************************************/

#include "sx.h"

/************************************************
 * Function prototypes
 ***********************************************/
u32 sx_bitmap_test(struct sx_bitmap *bitmap, u32 obj);
u32 sx_bitmap_set(struct sx_bitmap *bitmap, u32 obj);
u32 sx_bitmap_alloc(struct sx_bitmap *bitmap);
void sx_bitmap_free(struct sx_bitmap *bitmap, u32 obj);
int sx_buf_alloc(struct sx_dev *dev, int size, int max_direct,
                 struct sx_buf *buf, int init_val);
void sx_fill_page_list(__be64 *dma_addrs, struct sx_buf *buf);
void sx_buf_free(struct sx_dev *dev, int size, struct sx_buf *buf);
void sx_bitmap_free(struct sx_bitmap *bitmap, u32 obj);
int sx_bitmap_init(struct sx_bitmap *bitmap, u32 num);

#endif /* ALLOC_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
