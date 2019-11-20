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

#if !defined(__SX_CORE_COUNTER_H__)
#define __SX_CORE_COUNTER_H__

#define MAX_COUNTER_CATEGORY_NAME_LEN 36
#define MAX_COUNTER_NAME_LEN          48

#define COUNTER_INC(counter) do { sx_core_counter_increment(counter); } while (0)

struct sx_core_counter_category {
    struct list_head list_categories;
    struct list_head list_counters;
    char             name[MAX_COUNTER_CATEGORY_NAME_LEN + 1];
    u16              num_of_counters;
};
enum sx_core_counter_severity {
    COUNTER_SEV_NONE,
    COUNTER_SEV_INFO,
    COUNTER_SEV_NOTICE,
    COUNTER_SEV_ERROR,
};
struct sx_core_counter {
    struct sx_core_counter_category* counter_category;
    struct list_head                 list_counters;
    char                             name[MAX_COUNTER_NAME_LEN + 1];
    enum sx_core_counter_severity    severity;
    atomic64_t                       since_startup;
    u64                              last_time;
    u64                              clear_count;
    u64                              show_count;
};

int sx_core_counters_init(void);
void sx_core_counters_deinit(void);

int sx_core_counter_category_init(struct sx_core_counter_category *counter_category,
                                  const char                      *name);
int sx_core_counter_category_deinit(struct sx_core_counter_category *counter_category);

int sx_core_counter_init(struct sx_core_counter_category *counter_category,
                         struct sx_core_counter          *counter,
                         const char                      *name,
                         enum sx_core_counter_severity    severity);
int sx_core_counter_deinit(struct sx_core_counter *counter);

void sx_core_counter_increment(struct sx_core_counter *counter);

#endif /* __SX_CORE_COUNTER_H__ */
