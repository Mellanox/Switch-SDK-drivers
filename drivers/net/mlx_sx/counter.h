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
