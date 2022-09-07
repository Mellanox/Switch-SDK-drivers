/*
 * Copyright (C) 2008-2021 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

/************************************************
 * Includes
 ***********************************************/
#include <linux/version.h>
#include <linux/vmalloc.h>
#include <linux/circ_buf.h>
#include <linux/spinlock.h>

#include "sx.h"
#include "sx_af_dbg_info.h"

/************************************************
 * Defines
 ***********************************************/
#define CBUF_SIZE_2MB (2 * 1024 * 1024) /*< should be power of 2 */

/************************************************
 * Type declarations
 ***********************************************/
typedef struct af_dbg_db {
    struct circ_buf cbuf;
    int             size;
    int             max_records;
    u64             drops[CBUF_RECORD_TYPE_NUM_E];
    u64             pushed[CBUF_RECORD_TYPE_NUM_E];
} af_dbg_db_t;

/************************************************
 * Globals
 ***********************************************/
extern int sx_af_counters_dbg_info_print_in_hex;

static DEFINE_SPINLOCK(g_af_dbg_db_lock);
static af_dbg_db_t g_af_dbg_db;
static bool        g_af_dbg_inited = false;

#define SX_GENERATE_STRING(ENUM, STR) STR,
static const char * const cbuf_record_type_e_str_s[] = {
    FOREACH_CBUF_RECORD_TYPE(SX_GENERATE_STRING)
};

/************************************************
 * Functions
 ***********************************************/
static void __sx_af_dbg_info_ts_dump(struct seq_file *m, void *v, void *context, ktime_t *ktime_p);
static const char * __sx_af_dbg_info_cbuf_record_type_str(cbuf_record_type_e type);
static inline int __sx_af_dbg_info_db_init(af_dbg_db_t *db_p, unsigned int size_in_bytes);
static inline void __sx_af_dbg_info_db_deinit(af_dbg_db_t *db_p);
static inline void __sx_af_dbg_info_db_reset(af_dbg_db_t *db_p);
static void __sx_af_dbg_info_drop(void);
static void __sx_af_dbg_info_push(cbuf_record_t *record_p);
static int __sx_af_dbg_info_db_mem_preallocate(af_dbg_db_t **db_p);
static int __sx_af_dbg_info_db_clone(af_dbg_db_t *dst_db_p, af_dbg_db_t const *src_db_p);
static void __sx_af_dbg_info_db_mem_free(af_dbg_db_t **db_p);
static int __sx_af_dbg_info_mafbi_record_dump(struct seq_file *m, void *v, void *context, cbuf_record_t *record_p);
static int __sx_af_dbg_info_mafti_record_dump(struct seq_file *m, void *v, void *context, cbuf_record_t *record_p);
static int __sx_af_dbg_info_mocs_record_dump(struct seq_file *m, void *v, void *context, cbuf_record_t *record_p);
static int __sx_af_dbg_info_record_dump(struct seq_file *m, void *v, void *context, cbuf_record_t *record_p);
static int __sx_af_dbg_info_records_dump(struct seq_file *m, void *v, void *context, af_dbg_db_t *db_p);
static int __sx_af_dbg_info_dump(struct seq_file *m, void *v, void *context, af_dbg_db_t *db_p);

static void __sx_af_dbg_info_ts_dump(struct seq_file *m, void *v, void *context, ktime_t *ktime_p)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    #define TV_SEC_FMT "%lld"
    struct timespec64 ts = ktime_to_timespec64(*ktime_p);
#else
    #define TV_SEC_FMT "%ld"
    struct timespec ts = ktime_to_timespec(*ktime_p);
#endif

    seq_printf(m, "\t\tTimestamp: "TV_SEC_FMT " s, %ld ms (%ld ns) \n",
               ts.tv_sec, ts.tv_nsec / 1000000, ts.tv_nsec);
}

static const char * __sx_af_dbg_info_cbuf_record_type_str(cbuf_record_type_e type)
{
    return (type < CBUF_RECORD_TYPE_NUM_E) ? cbuf_record_type_e_str_s[type] : "Unknown";
}

static inline int __sx_af_dbg_info_db_init(af_dbg_db_t *db_p, unsigned int size_in_bytes)
{
    int err = 0;

    memset(db_p, 0, sizeof(af_dbg_db_t));
    db_p->size = size_in_bytes;
    db_p->max_records = size_in_bytes / sizeof(cbuf_record_t);
    db_p->cbuf.head = 0;
    db_p->cbuf.tail = 0;
    db_p->cbuf.buf = vmalloc(size_in_bytes);
    if (db_p->cbuf.buf == NULL) {
        err = -ENOMEM;
        printk(KERN_ERR PFX "%s: failed to allocate memory for Accumulated counters debug buffer, err [%d]\n",
               __func__, err);
        goto out;
    }
    memset(db_p->cbuf.buf, 0, size_in_bytes);

out:
    return err;
}

static inline void __sx_af_dbg_info_db_deinit(af_dbg_db_t *db_p)
{
    if (g_af_dbg_db.cbuf.buf != NULL) {
        vfree(db_p->cbuf.buf);
        db_p->cbuf.buf = NULL;
    }
    db_p->cbuf.tail = 0;
    db_p->cbuf.head = 0;
    db_p->max_records = 0;
    db_p->size = 0;
}

int sx_af_dbg_info_init(void)
{
    int         err = 0;
    static bool g_af_dbg_init_in_progress = false;

    spin_lock(&g_af_dbg_db_lock);

    if (g_af_dbg_inited) {
        spin_unlock(&g_af_dbg_db_lock);
        return -EALREADY;
    }

    if (g_af_dbg_init_in_progress) {
        spin_unlock(&g_af_dbg_db_lock);
        return -EALREADY;
    } else {
        g_af_dbg_init_in_progress = true;
    }

    spin_unlock(&g_af_dbg_db_lock);

    err = __sx_af_dbg_info_db_init(&g_af_dbg_db, CBUF_SIZE_2MB);
    if (err) {
        spin_lock(&g_af_dbg_db_lock);
        g_af_dbg_inited = false;
        g_af_dbg_init_in_progress = false;
        spin_unlock(&g_af_dbg_db_lock);
        goto out;
    }

    mb();

    spin_lock(&g_af_dbg_db_lock);
    g_af_dbg_inited = true;
    g_af_dbg_init_in_progress = false;
    spin_unlock(&g_af_dbg_db_lock);

out:
    return 0;
}

void sx_af_dbg_info_deinit(void)
{
    static bool g_af_dbg_deinit_in_progress = false;

    spin_lock(&g_af_dbg_db_lock);

    if (!g_af_dbg_inited) {
        spin_unlock(&g_af_dbg_db_lock);
        return;
    }

    if (g_af_dbg_deinit_in_progress) {
        spin_unlock(&g_af_dbg_db_lock);
        return;
    } else {
        g_af_dbg_deinit_in_progress = true;
    }

    spin_unlock(&g_af_dbg_db_lock);

    __sx_af_dbg_info_db_deinit(&g_af_dbg_db);

    spin_lock(&g_af_dbg_db_lock);
    g_af_dbg_inited = false;
    g_af_dbg_deinit_in_progress = false;
    spin_unlock(&g_af_dbg_db_lock);
}

static inline void __sx_af_dbg_info_db_reset(af_dbg_db_t *db_p)
{
    memset(db_p->cbuf.buf, 0, db_p->size);
    db_p->cbuf.tail = 0;
    db_p->cbuf.head = 0;
    db_p->max_records = 0;
    db_p->size = 0;
}

int sx_af_dbg_info_clear(void)
{
    int err = 0;

    spin_lock(&g_af_dbg_db_lock);

    if (!g_af_dbg_inited) {
        err = -EINVAL;
        goto out;
    }

    printk(KERN_NOTICE PFX "Clearing Accumulated counters' debug DB\n");
    __sx_af_dbg_info_db_reset(&g_af_dbg_db);

out:
    spin_unlock(&g_af_dbg_db_lock);
    return err;
}

static void __sx_af_dbg_info_drop(void)
{
    int            count = 0;
    int            cnt_to_end = 0;
    int            leftover_size = 0;
    cbuf_record_t *record_p = NULL;
    cbuf_record_t  record_cpy;

    count = CIRC_CNT(g_af_dbg_db.cbuf.head, g_af_dbg_db.cbuf.tail, g_af_dbg_db.size);
    if (count == 0) {
        /* nothing to drop, buffer is empty */
        return;
    }

    if (count < sizeof(cbuf_record_t)) {
        if (printk_ratelimit()) {
            printk(
                KERN_ERR PFX "Cannot drop a record, buffer is filled with something [%d] that is smaller than one record [%lu]\n",
                count,
                sizeof(cbuf_record_t));
        }
        return;
    }

    cnt_to_end = CIRC_CNT_TO_END(g_af_dbg_db.cbuf.head, g_af_dbg_db.cbuf.tail, g_af_dbg_db.size);

    if (cnt_to_end >= sizeof(cbuf_record_t)) {
        record_p = (cbuf_record_t *)(g_af_dbg_db.cbuf.buf + g_af_dbg_db.cbuf.tail);
        g_af_dbg_db.cbuf.tail = (g_af_dbg_db.cbuf.tail + sizeof(cbuf_record_t)) & (g_af_dbg_db.size - 1);
    } else {
        leftover_size = sizeof(cbuf_record_t) - cnt_to_end;

        memset(&record_cpy, 0, sizeof(cbuf_record_t));

        memcpy(&record_cpy, (g_af_dbg_db.cbuf.buf + g_af_dbg_db.cbuf.tail), cnt_to_end);
        g_af_dbg_db.cbuf.tail = (g_af_dbg_db.cbuf.tail + cnt_to_end) & (g_af_dbg_db.size - 1);

        memcpy((((char *)&record_cpy) + cnt_to_end), (g_af_dbg_db.cbuf.buf + g_af_dbg_db.cbuf.tail), leftover_size);
        g_af_dbg_db.cbuf.tail = (g_af_dbg_db.cbuf.tail + leftover_size) & (g_af_dbg_db.size - 1);

        record_p = &record_cpy;
    }

    g_af_dbg_db.drops[record_p->type]++;
}

static void __sx_af_dbg_info_push(cbuf_record_t *record_p)
{
    int   end = 0;
    int   leftover_size = 0;
    void *item = g_af_dbg_db.cbuf.buf + g_af_dbg_db.cbuf.head;

    g_af_dbg_db.pushed[record_p->type]++;

    end = CIRC_SPACE_TO_END(g_af_dbg_db.cbuf.head, g_af_dbg_db.cbuf.tail, g_af_dbg_db.size);

    if (end >= sizeof(cbuf_record_t)) {
        memcpy(item, record_p, sizeof(cbuf_record_t));
        g_af_dbg_db.cbuf.head = (g_af_dbg_db.cbuf.head + sizeof(cbuf_record_t)) & (g_af_dbg_db.size - 1);
    } else {
        end = CIRC_SPACE_TO_END(g_af_dbg_db.cbuf.head, g_af_dbg_db.cbuf.tail, g_af_dbg_db.size);

        memcpy(item, record_p, end);
        g_af_dbg_db.cbuf.head = (g_af_dbg_db.cbuf.head + end) & (g_af_dbg_db.size - 1);

        leftover_size = sizeof(cbuf_record_t) - end;
        item = g_af_dbg_db.cbuf.buf + g_af_dbg_db.cbuf.head;

        memcpy(item, (((char*)record_p) + end), leftover_size);
        g_af_dbg_db.cbuf.head = (g_af_dbg_db.cbuf.head + leftover_size) & (g_af_dbg_db.size - 1);
    }
}

int sx_af_dbg_info_push(cbuf_record_t *record_p)
{
    int err = 0;

    spin_lock(&g_af_dbg_db_lock);

    if (!g_af_dbg_inited) {
        spin_unlock(&g_af_dbg_db_lock);
        return -EINVAL;
    }

    if (CIRC_SPACE(g_af_dbg_db.cbuf.head, g_af_dbg_db.cbuf.tail, g_af_dbg_db.size) < sizeof(cbuf_record_t)) {
        __sx_af_dbg_info_drop();
    }

    mb();

    if (CIRC_SPACE(g_af_dbg_db.cbuf.head, g_af_dbg_db.cbuf.tail, g_af_dbg_db.size) >= sizeof(cbuf_record_t)) {
        __sx_af_dbg_info_push(record_p);
    } else {
        if (printk_ratelimit()) {
            printk(KERN_ERR PFX "Cannot save a record, the buffer is full.\n");
        }
        g_af_dbg_db.drops[record_p->type]++;
    }

    spin_unlock(&g_af_dbg_db_lock);

    return err;
}

static int __sx_af_dbg_info_db_mem_preallocate(af_dbg_db_t **db_p)
{
    int err = 0;

    *db_p = vmalloc(sizeof(af_dbg_db_t));
    if (*db_p == NULL) {
        err = -ENOMEM;
        printk(KERN_ERR PFX "%s: failed to allocate memory for a copy of Accumulated counters debug DB, err [%d]\n",
               __func__, err);
        goto out;
    }

    (*db_p)->cbuf.buf = vmalloc(CBUF_SIZE_2MB);
    if ((*db_p)->cbuf.buf == NULL) {
        err = -ENOMEM;
        printk(
            KERN_ERR PFX "%s: failed to allocate memory for a copy of Accumulated counters debug buffer, err [%d]\n",
            __func__,
            err);
        goto out;
    }
    (*db_p)->size = CBUF_SIZE_2MB;

out:
    if (err) {
        if (*db_p) {
            vfree(*db_p);
            *db_p = NULL;
        }
    }

    return err;
}

static int __sx_af_dbg_info_db_clone(af_dbg_db_t *dst_db_p, af_dbg_db_t const *src_db_p)
{
    int err = 0;
    int idx = 0;

    if (dst_db_p->size != src_db_p->size) {
        err = -EINVAL;
        goto out;
    }

    dst_db_p->max_records = src_db_p->max_records;

    dst_db_p->cbuf.head = src_db_p->cbuf.head;
    dst_db_p->cbuf.tail = src_db_p->cbuf.tail;
    memcpy(dst_db_p->cbuf.buf, src_db_p->cbuf.buf, dst_db_p->size);

    for (idx = 0; idx < CBUF_RECORD_TYPE_NUM_E; idx++) {
        dst_db_p->drops[idx] = src_db_p->drops[idx];
        dst_db_p->pushed[idx] = src_db_p->pushed[idx];
    }

out:
    return err;
}

static void __sx_af_dbg_info_db_mem_free(af_dbg_db_t **db_p)
{
    vfree((*db_p)->cbuf.buf);
    vfree(*db_p);
    *db_p = NULL;
}

static int __sx_af_dbg_info_mafbi_record_dump(struct seq_file *m, void *v, void *context, cbuf_record_t *record_p)
{
    u8             num_rec = 0;
    unsigned short index = 0;
    u8             type = 0;
    u32           *dword_p = 0;

    type = mlxsw_reg_mafbi_type_get(record_p->data.mafbi_reg.reg);
    seq_printf(m, "\t\tType: %u \n", type);

    if (type != SXD_MAFBI_TYPE_ENTRY_TYPE0_E) {
        goto out;
    }

    num_rec = mlxsw_reg_mafbi_num_rec_get(record_p->data.mafbi_reg.reg);
    seq_printf(m, "\t\tNumber of records: %u \n", num_rec);
    seq_printf(m, "\t\t\t record_idx \t counter_idx \t bytes \t packets \n");
    for (index = 0; index < num_rec; index++) {
        seq_printf(m, "\t\t\t %u \t\t %u \t\t %u \t %u \n", index,
                   mlxsw_reg_mafbi_entry_mafbi_entry_type0_counter_index_get(record_p->data.mafbi_reg.reg, index),
                   mlxsw_reg_mafbi_entry_mafbi_entry_type0_bytes_inc_get(record_p->data.mafbi_reg.reg, index),
                   mlxsw_reg_mafbi_entry_mafbi_entry_type0_packets_inc_get(record_p->data.mafbi_reg.reg, index));
    }

    if (sx_af_counters_dbg_info_print_in_hex) {
        seq_printf(m, "\t\tHex: \n");
        dword_p = (u32 *)record_p->data.mafbi_reg.reg;
        seq_printf(m, "\t\t\t offset \t dword 0 \t dword 1 \t dword 2 \t dword 3 \n");
        for (index = 0; index < MLXSW_MAFBI_LEN / 16; index++) {
            seq_printf(m, "%04x: \t\t\t %08x \t %08x \t %08x \t %08x \n", index, *(dword_p + (4 * index)),
                       *(dword_p + (4 * index) + 1), *(dword_p + (4 * index) + 2), *(dword_p + (4 * index) + 3));
        }
    }

out:
    return 0;
}

static int __sx_af_dbg_info_mafti_record_dump(struct seq_file *m, void *v, void *context, cbuf_record_t *record_p)
{
    u8             num_rec = 0;
    unsigned short index = 0;
    u32           *dword_p = 0;

    num_rec = mlxsw_reg_mafti_num_rec_get(record_p->data.mafti_reg.reg);
    seq_printf(m, "\t\tNumber of records: %u \n", num_rec);
    seq_printf(m, "\t\t\t record_idx \t counter_idx \t bytes \t packets \n");
    for (index = 0; index < num_rec; index++) {
        seq_printf(m, "\t\t\t %u \t\t %u \t\t %u \t %u \n", index,
                   mlxsw_reg_mafti_counter_index_get(record_p->data.mafti_reg.reg, index),
                   mlxsw_reg_mafti_bytes_inc_get(record_p->data.mafti_reg.reg, index),
                   mlxsw_reg_mafti_packets_inc_get(record_p->data.mafti_reg.reg, index));
    }

    if (sx_af_counters_dbg_info_print_in_hex) {
        seq_printf(m, "\t\tHex: \n");
        dword_p = (u32 *)record_p->data.mafbi_reg.reg;
        seq_printf(m, "\t\t\t offset \t dword 0 \t dword 1 \t dword 2 \t dword 3 \n");
        for (index = 0; index < MLXSW_MAFTI_LEN / 16; index++) {
            seq_printf(m, "\t\t\t %04x: \t\t %08x \t %08x \t %08x \t %08x \n", index, *(dword_p + (4 * index)),
                       *(dword_p + (4 * index) + 1), *(dword_p + (4 * index) + 2), *(dword_p + (4 * index) + 3));
        }
    }

    return 0;
}

static int __sx_af_dbg_info_mocs_record_dump(struct seq_file *m, void *v, void *context, cbuf_record_t *record_p)
{
    unsigned short index = 0;
    u32            dword = 0;

    seq_printf(m, "\t\tHex: \n");
    for (index = 0; index < MLXSW_MOCS_LEN; index = index + 4) {
        dword = *((u32 *)(record_p->data.mocs_reg.reg + index));
        seq_printf(m, "\t\t%04x: %08x \n", index, dword);
    }

    return 0;
}

static int __sx_af_dbg_info_record_dump(struct seq_file *m, void *v, void *context, cbuf_record_t *record_p)
{
    const char *type_str_p = NULL;

    __sx_af_dbg_info_ts_dump(m, v, context, &record_p->ts);

    type_str_p = __sx_af_dbg_info_cbuf_record_type_str(record_p->type);
    seq_printf(m, "\t\tType: %s\n", type_str_p);

    switch (record_p->type) {
    case CBUF_RECORD_TYPE_MAFBI_E:
        __sx_af_dbg_info_mafbi_record_dump(m, v, context, record_p);
        break;

    case CBUF_RECORD_TYPE_MAFTI_E:
        __sx_af_dbg_info_mafti_record_dump(m, v, context, record_p);
        break;

    case CBUF_RECORD_TYPE_MOCS_E:
        __sx_af_dbg_info_mocs_record_dump(m, v, context, record_p);
        break;

    default:
        seq_printf(m, "\t\tUnsupported record type: %d\n",
                   record_p->type);
        break;
    }

    return 0;
}

static int __sx_af_dbg_info_records_dump(struct seq_file *m, void *v, void *context, af_dbg_db_t *db_p)
{
    int            head = g_af_dbg_db.cbuf.head;
    int            tail = g_af_dbg_db.cbuf.tail;
    int            size = g_af_dbg_db.size;
    int            count = 0;
    int            record_idx = 0;
    int            cnt_to_end = 0;
    int            leftover_size = 0;
    cbuf_record_t *record_p = NULL;
    cbuf_record_t  record_cpy;

    do {
        count = CIRC_CNT(head, tail, size);
        if (count == 0) {
            /* buffer is empty */
            break;
        }

        if (count < sizeof(cbuf_record_t)) {
            if (printk_ratelimit()) {
                printk(
                    KERN_ERR PFX "Cannot dump a debug record[%d], the buffer is filled with something [%d] that is smaller than one record [%lu]\n",
                    record_idx,
                    count,
                    sizeof(cbuf_record_t));
            }
            break;
        }

        cnt_to_end = CIRC_CNT_TO_END(head, tail, size);

        if (cnt_to_end >= sizeof(cbuf_record_t)) {
            record_p = (cbuf_record_t *)(g_af_dbg_db.cbuf.buf + tail);
            tail = (tail + sizeof(cbuf_record_t)) & (size - 1);
        } else {
            leftover_size = sizeof(cbuf_record_t) - cnt_to_end;
            memset(&record_cpy, 0, sizeof(cbuf_record_t));

            memcpy(&record_cpy, (g_af_dbg_db.cbuf.buf + tail), cnt_to_end);
            tail = (tail + cnt_to_end) & (size - 1);

            memcpy((((char *)&record_cpy) + cnt_to_end), (g_af_dbg_db.cbuf.buf + tail), leftover_size);
            tail = (tail + leftover_size) & (size - 1);

            record_p = &record_cpy;
        }

        seq_printf(m, "\tDB record #%d:\n", record_idx++);
        __sx_af_dbg_info_record_dump(m, v, context, record_p);
    } while (count);

    return 0;
}

static int __sx_af_dbg_info_dump(struct seq_file *m, void *v, void *context, af_dbg_db_t *db_p)
{
    int         db_records = 0;
    int         idx = 0;
    const char *type_str_p = NULL;

    seq_printf(m, "Accumulated counters' debug DB:\n");
    seq_printf(m, "\tBuffer DB size: %d\n", db_p->size);

    db_records = CIRC_CNT(db_p->cbuf.head, db_p->cbuf.tail, db_p->size) / sizeof(cbuf_record_t);
    seq_printf(m, "\tBuffer DB records: %d\n", db_records);
    seq_printf(m, "\tBuffer DB max records: %d\n", db_p->max_records);

    for (idx = 0; idx < CBUF_RECORD_TYPE_NUM_E; idx++) {
        type_str_p = __sx_af_dbg_info_cbuf_record_type_str(idx);
        seq_printf(m, "\tNumber of %s drops: %llu\n", type_str_p, db_p->drops[idx]);
    }

    for (idx = 0; idx < CBUF_RECORD_TYPE_NUM_E; idx++) {
        type_str_p = __sx_af_dbg_info_cbuf_record_type_str(idx);
        seq_printf(m, "\tTotal number of %s records pushed: %llu\n", type_str_p, db_p->pushed[idx]);
    }

    seq_printf(m, "\tDebug DB records:\n");
    __sx_af_dbg_info_records_dump(m, v, context, db_p);

    return 0;
}

int sx_af_dbg_info_dump(struct seq_file *m, void *v, void *context)
{
    int          err = 0;
    af_dbg_db_t *db_clone_p = NULL;

    err = __sx_af_dbg_info_db_mem_preallocate(&db_clone_p);
    if (err) {
        return err;
    }

    spin_lock(&g_af_dbg_db_lock);
    if (!g_af_dbg_inited) {
        spin_unlock(&g_af_dbg_db_lock);
        __sx_af_dbg_info_db_mem_free(&db_clone_p);
        return -EINVAL;
    }

    err = __sx_af_dbg_info_db_clone(db_clone_p, &g_af_dbg_db);
    spin_unlock(&g_af_dbg_db_lock);

    if (err) {
        goto out;
    }

    err = __sx_af_dbg_info_dump(m, v, context, db_clone_p);

out:
    __sx_af_dbg_info_db_mem_free(&db_clone_p);
    return err;
}
