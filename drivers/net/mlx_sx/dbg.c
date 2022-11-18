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

#include <linux/seq_file.h>

#include "sx.h"
#include "sx_dbg_dump_proc.h"
#include "alloc.h"
#include "mmap.h"
#include "ber_monitor.h"
#include "health_check.h"
#include "sx_af_counters.h"
#include "bulk_cntr_db.h"
#include "dev_db.h"
#include "sx_clock.h"
#include "ptp.h"
#include "synce.h"
#include "qos_emad.h"

int sx_dbg_host_ifc_init(void);
int sx_dbg_host_ifc_deinit(void);
int sx_dbg_db_init(void);
int sx_dbg_db_deinit(void);

void sx_dbg_get_time(struct sx_timeval *sxtv)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    ktime_get_real_ts64(&sxtv->t);
#else
    do_gettimeofday(&sxtv->t);
#endif

    sxtv->t.tv_sec -= sys_tz.tz_minuteswest * 60;
    sxtv->j = jiffies;
}

void sx_dbg_jiffies_to_time(const struct sx_timeval *now, unsigned long jiffies_ts, struct sx_tm *sxtm)
{
    struct sx_timeval _now, past;
    u64               diff_usec, diff_msec;

    if (!now) { /* user did not supply current time, we'll get it alone */
        sx_dbg_get_time(&_now);
        now = &_now;
    }

    diff_msec = jiffies_to_msecs(now->j - jiffies_ts);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    diff_usec = (now->t.tv_sec * 1000000 + now->t.tv_nsec / 1000) - diff_msec * 1000;
    past.t.tv_sec = diff_usec / 1000000;
    past.t.tv_nsec = (diff_usec % 1000000) * 1000;
    time64_to_tm(past.t.tv_sec, 0, &sxtm->tm);
    sxtm->msec = (u32)(past.t.tv_nsec / 1000000);
#else
    diff_usec = (now->t.tv_sec * 1000000 + now->t.tv_usec) - diff_msec * 1000;
    past.t.tv_sec = diff_usec / 1000000;
    past.t.tv_usec = diff_usec % 1000000;
    time_to_tm(past.t.tv_sec, 0, &sxtm->tm);
    sxtm->msec = (u32)(past.t.tv_usec / 1000);
#endif
}

void sx_dbg_jiffies_to_time_str(const struct sx_timeval *now, unsigned long jiffies_ts, char *buff, u32 bufflen)
{
    struct sx_tm sxtm;

    sx_dbg_jiffies_to_time(now, jiffies_ts, &sxtm);

    snprintf(buff, bufflen, "%04d-%02d-%02d %02d:%02d:%02d.%03u",
             (int)(1900 + sxtm.tm.tm_year),
             sxtm.tm.tm_mon + 1,
             sxtm.tm.tm_mday,
             sxtm.tm.tm_hour,
             sxtm.tm.tm_min,
             sxtm.tm.tm_sec,
             sxtm.msec);
}

static bool __dev_iterator_cq_dump(struct sx_dev *dev, void *context)
{
    struct sx_dev_db_iterator_seq_file_context *dec = (struct sx_dev_db_iterator_seq_file_context*)context;
    u8                                          cqn = 0;
    unsigned long                               flags;
    struct sx_cq_table                         *cq_table;
    long                                        now = jiffies;
    int                                         last_time_armed, last_time_event;
    struct cpu_traffic_priority                *cpu_traffic_prio;
    struct sx_priv                             *priv;
    u64                                         cons_index, diff;
    char                                        header[SX_DBG_DUMP_HEADER_MAX_LEN];

    priv = sx_priv(dev);
    if (!priv) {
        goto out;
    }

    cq_table = &priv->cq_table;
    if (!cq_table) {
        goto out;
    }

    cpu_traffic_prio = &cq_table->cpu_traffic_prio;
    if (!cpu_traffic_prio) {
        goto out;
    }

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "CQ dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(dec->m, header);

    if (atomic_read(&cpu_traffic_prio->high_prio_cq_in_load) == 1) {
        seq_printf(dec->m, "*** CPU is under storm traffic! ***\n");
    }

    if (priv->pause_cqn >= 0) {
        seq_printf(dec->m, "CQN %d is paused!\n", priv->pause_cqn);
    }

    sx_dbg_dump_print_table_header(dec->m,
                                   "%-18s | %-4s | %-18s | %-18s | %-5s | %-9s | %-7s | %-10s | %-11s",
                                   "CQ #",
                                   "prio",
                                   "cons_idx",
                                   "diff",
                                   "nent",
                                   "buff_size",
                                   "CQE-ver",
                                   "arm (sec) ",
                                   "event (sec)");

    spin_lock_irqsave(&cq_table->lock, flags);
    if (cq_table->cq == NULL) {
        goto unlock;
    }
    for (cqn = 0; cqn < priv->dev_cap.max_num_cqs; cqn++) {
        if (cqn == NUMBER_OF_SDQS) {
            sx_dbg_dump_print_separate_line(dec->m);
        }

        if (cq_table->cq[cqn] != NULL) {
            last_time_armed = (priv->cq_last_time_armed[cqn] != 0) ?
                              (jiffies_to_msecs(now - priv->cq_last_time_armed[cqn]) / 1000) : 0;

            last_time_event = (priv->cq_last_time_event[cqn] != 0) ?
                              (jiffies_to_msecs(now - priv->cq_last_time_event[cqn]) / 1000) : 0;

            cons_index = cq_table->cq[cqn]->cons_index_dbg;
            diff = cons_index - cq_table->cq[cqn]->cons_index_dbg_snapshot;
            cq_table->cq[cqn]->cons_index_dbg_snapshot = cons_index;

            seq_printf(dec->m,
                       "CQ %02u (%s %02u) %3s | %-4s | %-18llu | %-18llu | %-5u | %-9u | %-7u | %-10u | %-10u\n",
                       cqn,
                       ((cqn < NUMBER_OF_SDQS) ? "SDQ" : "RDQ"),
                       ((cqn < NUMBER_OF_SDQS) ? cqn : cqn - NUMBER_OF_SDQS),
                       (sx_bitmap_test(&priv->monitor_cq_bitmap, cqn) ? "[M]" : ""),
                       (sx_bitmap_test(&cpu_traffic_prio->high_prio_cq_bitmap, cqn) ? "high" : "low"),
                       cons_index,
                       diff,
                       cq_table->cq[cqn]->nent,
                       ((cqn <
                         NUMBER_OF_SDQS) ? 0 : priv->profile.pci_profile.rdq_properties[cqn -
                                                                                        NUMBER_OF_SDQS].entry_size),
                       cq_table->cq[cqn]->cqe_version,
                       jiffies_to_msecs(now - priv->cq_last_time_armed[cqn]) / 1000,
                       jiffies_to_msecs(now - priv->cq_last_time_event[cqn]) / 1000);
        }
    }

unlock:
    spin_unlock_irqrestore(&cq_table->lock, flags);
    sx_dbg_dump_print_empty_line(dec->m);

out:
    return true;
}

static int __cq_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_dev_db_iterator_seq_file_context dec = {
        .m = m,
        .v = v,
        .context = context
    };

    sx_dev_db_iterate(__dev_iterator_cq_dump, &dec);
    return 0;
}

static int __ber_monitor_dump(struct seq_file *m, void *v, void *context)
{
    sx_core_ber_monitor_dump(m, v, context);
    return 0;
}

static bool __dev_iterator_tele_thrs_dump(struct sx_dev *dev, void *context)
{
    struct sx_dev_db_iterator_seq_file_context *dec = (struct sx_dev_db_iterator_seq_file_context*)context;
    u16                                         i = 0;
    unsigned long                               flags;
    char                                        header[SX_DBG_DUMP_HEADER_MAX_LEN];

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "TELE threshold dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(dec->m, header);

    sx_dbg_dump_print_table_header(dec->m, "%-11s| %-11s| %s", "local_port", "state", "tc_pg_vec");
    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    for (i = 0; i < MAX_PHYPORT_NUM + 1; i++) {
        if (sx_priv(dev)->tele_thrs_state[i][TELE_DIR_ING_EGRESS_E]) {
            seq_printf(dec->m, "%-11u| %-11u| [tc] %llx\n",
                       i,
                       sx_priv(dev)->tele_thrs_state[i][TELE_DIR_ING_EGRESS_E],
                       sx_priv(dev)->tele_thrs_tc_vec[i][TELE_DIR_ING_EGRESS_E]);
        }
        if (sx_priv(dev)->tele_thrs_state[i][TELE_DIR_ING_INGRESS_E]) {
            seq_printf(dec->m, "%-11u| %-11u| [pg] %llx\n",
                       i,
                       sx_priv(dev)->tele_thrs_state[i][TELE_DIR_ING_INGRESS_E],
                       sx_priv(dev)->tele_thrs_tc_vec[i][TELE_DIR_ING_INGRESS_E]);
        }
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    sx_dbg_dump_print_empty_line(dec->m);
    return true;
}

static int __tele_thrs_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_dev_db_iterator_seq_file_context dec = {
        .m = m,
        .v = v,
        .context = context
    };

    sx_dev_db_iterate(__dev_iterator_tele_thrs_dump, &dec);
    return 0;
}

static void __monitor_rdq_dump_one(struct seq_file *m, struct sx_dev *dev, int rdq_n)
{
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_dq_table *rdq_table = &priv->rdq_table;
    struct sx_dq       *rdq;

    if (rdq_table == NULL) {
        seq_printf(m, "rdq table is empty\n");
        return;
    }

    if (rdq_n > (priv->dev_cap.max_num_rdqs - 1)) {
        seq_printf(m, "rdq_n %d is out of range [0..%d]\n",
                   rdq_n, priv->dev_cap.max_num_rdqs);
        return;
    }


    if (!rdq_table->dq[rdq_n]) {
        return;
    }

    rdq = rdq_table->dq[rdq_n];

    if (!rdq->is_monitor) {
        return;
    }

    seq_printf(m, "rdq %d data:  is_mon:%d, rx_cnt:%u, rx_start:%u, cpu_tc:%d \n",
               rdq_n,
               rdq->is_monitor,                  /* rdq is cyclic monitor rdq. non valid for sdq */
               rdq->mon_rx_count,
               rdq->mon_rx_start,
               rdq->cpu_tclass);
}

static bool __dev_iterator_monitor_rdq_dump(struct sx_dev *dev, void *context)
{
    struct sx_dev_db_iterator_seq_file_context *dec = (struct sx_dev_db_iterator_seq_file_context*)context;
    int                                         rdq_n;
    struct sx_priv                             *priv = NULL;
    struct sx_dq_table                         *rdq_table = NULL;
    char                                        header[SX_DBG_DUMP_HEADER_MAX_LEN];

    priv = sx_priv(dev);

    if (!priv->rdq_table.dq) {
        return 0;
    }

    rdq_table = &priv->rdq_table;
    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "Monitor RDQ dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(dec->m, header);

    for (rdq_n = 0; rdq_n < priv->dev_cap.max_num_rdqs; rdq_n++) {
        __monitor_rdq_dump_one(dec->m, dev, rdq_n);
    }

    sx_dbg_dump_print_empty_line(dec->m);
    return true;
}

static int __monitor_rdq_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_dev_db_iterator_seq_file_context dec = {
        .m = m,
        .v = v,
        .context = context
    };

    sx_dev_db_iterate(__dev_iterator_monitor_rdq_dump, &dec);
    return 0;
}

static bool __dev_iterator_sdq_dump(struct sx_dev *dev, void *context)
{
    struct sx_dev_db_iterator_seq_file_context *dec = (struct sx_dev_db_iterator_seq_file_context*)context;
    u16                                         sdqn = 0;
    unsigned long                               now = jiffies;
    struct sx_dq                               *sdq = NULL;
    struct sx_priv                             *priv = NULL;
    char                                        max_comp_ts[20];
    char                                        last_full[20];
    char                                        last_comp[20];
    char                                        header[SX_DBG_DUMP_HEADER_MAX_LEN];

    priv = sx_priv(dev);

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "SDQ dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(dec->m, header);

    if (!priv->sdq_table.dq) {
        return 0;
    }

    seq_printf(dec->m,
               "%-5s   %-12s   %-8s   %-8s   %-42s   %-21s   %-27s\n"
               "%-5s   %-12s   %-8s   %-8s   %-12s   %-12s   %-12s   %-6s   %-12s   %-12s   %-12s\n"
               "---------------------------------------------------------------------------------"
               "---------------------------------------------------\n",
               "SDQ#", "Sent", "SW Queue", "SW Queue", "Completion Count", "Max Diff", "Last",
               "    ", "    ", "Level   ", "Drops   ", "OK", "Late", "None", "Msec", "TS (sec ago)", "Full", "Comp");

    for (sdqn = 0; sdqn < priv->dev_cap.max_num_sdqs; sdqn++) {
        sdq = priv->sdq_table.dq[sdqn];

        if (sdq) {
            spin_lock_bh(&sdq->lock);

            if (sdq->last_full_queue != 0) {
                snprintf(last_full, sizeof(last_full), "%u", jiffies_to_msecs(now - sdq->last_full_queue) / 1000);
            } else {
                snprintf(last_full, sizeof(last_full), "N/A");
            }

            if (sdq->last_completion != 0) {
                snprintf(last_comp, sizeof(last_comp), "%u", jiffies_to_msecs(now - sdq->last_completion) / 1000);
            } else {
                snprintf(last_comp, sizeof(last_comp), "N/A");
            }

            if (sdq->max_comp_ts != 0) {
                snprintf(max_comp_ts, sizeof(max_comp_ts), "%u", jiffies_to_msecs(now - sdq->max_comp_ts) / 1000);
            } else {
                snprintf(max_comp_ts, sizeof(max_comp_ts), "N/A");
            }

            seq_printf(dec->m,
                       "%-5u   %-12llu   %-8u   %-8llu   %-12llu   %-12llu   %-12llu   %-6u   %-12s   %-12s   %-12s\n",
                       sdqn,
                       sdq->pkts_sent_to_sdq,
                       sdq->pkts_in_sw_queue,
                       sdq->pkts_sw_queue_drops,
                       sdq->pkts_recv_completion,
                       sdq->pkts_late_completion,
                       sdq->pkts_no_recv_completion,
                       jiffies_to_msecs(sdq->max_comp_time),
                       max_comp_ts,
                       last_full,
                       last_comp);

            spin_unlock_bh(&sdq->lock);
        }
    }

    sx_dbg_dump_print_empty_line(dec->m);
    return true;
}

static int __sdq_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_dev_db_iterator_seq_file_context dec = {
        .m = m,
        .v = v,
        .context = context
    };

    sx_dev_db_iterate(__dev_iterator_sdq_dump, &dec);
    return 0;
}

static int __sdq_max_diff_clear(int argc, const char *argv[], void *context)
{
    struct sx_dev  *dev;
    struct sx_priv *priv;
    int             rc;
    int             dev_id;
    int             sdqn;


    if (argc != 3) {
        return -EINVAL;
    }

    rc = kstrtoint(argv[1], 10, &dev_id);
    if (rc) {
        return -EINVAL;
    }

    rc = kstrtoint(argv[2], 10, &sdqn);
    if (rc) {
        return -EINVAL;
    }

    dev = sx_dev_db_get_dev_by_id(dev_id);
    if (!dev || (sdqn < 0) || (sdqn >= NUMBER_OF_SDQS)) {
        return -EINVAL;
    }

    priv = sx_priv(dev);

    if (priv->sdq_table.dq && priv->sdq_table.dq[sdqn]) {
        priv->sdq_table.dq[sdqn]->max_comp_time = 0;
        priv->sdq_table.dq[sdqn]->max_comp_ts = 0;
    }

    return 0;
}


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
static bool __dev_iterator_rdq_to_filter_ebpf_prog_dump(struct sx_dev *dev, void *context)
{
    struct sx_dev_db_iterator_seq_file_context *dec = (struct sx_dev_db_iterator_seq_file_context*)context;
    u16                                         i = 0;
    u16                                         rdq = 0;
    struct sx_priv                             *priv = NULL;
    unsigned long                               flags;
    char                                        header[SX_DBG_DUMP_HEADER_MAX_LEN];

    priv = sx_priv(dev);

    snprintf(header,
             SX_DBG_DUMP_HEADER_MAX_LEN,
             "RDQ to filter eBPF program mapping dump - device_id %u",
             dev->device_id);

    sx_dbg_dump_print_header(dec->m, header);
    sx_dbg_dump_print_table_header(dec->m, "%-7s| %-7s| %-20s", "#", "RDQ", "Filter eBPF program");

    spin_lock_irqsave(&sx_priv(dev)->rdq_table.lock, flags);

    i = 0;
    for (rdq = 0; rdq < (NUMBER_OF_RDQS); rdq++) {
        if (priv->filter_ebpf_progs[rdq] != NULL) {
            i++;
            seq_printf(dec->m, "%-7u| %-7u| %-20p\n",
                       i,
                       rdq,
                       priv->filter_ebpf_progs[rdq]);
        }
    }

    spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);

    sx_dbg_dump_print_empty_line(dec->m);
    return 0;
}

static int __rdq_to_filter_ebpf_prog_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_dev_db_iterator_seq_file_context dec = {
        .m = m,
        .v = v,
        .context = context
    };

    sx_dev_db_iterate(__dev_iterator_rdq_to_filter_ebpf_prog_dump, &dec);
    return 0;
}

#endif /* if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0)) */

static bool __dev_iterator_fw_and_board_info_dump(struct sx_dev *dev, void *context)
{
    struct sx_dev_db_iterator_seq_file_context *dec = (struct sx_dev_db_iterator_seq_file_context*)context;
    struct sx_priv                             *priv;
    struct sx_fw                               *fw;
    char                                        header[SX_DBG_DUMP_HEADER_MAX_LEN];

    priv = sx_priv(dev);
    fw = &priv->fw;

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "FW and BoardInfo dump - device_id %u", dev->device_id);
    sx_dbg_dump_print_header(dec->m, header);

    seq_printf(dec->m, "PSID                : %s\n", priv->board_id);
    seq_printf(dec->m, "FW release version  : %d.%d.%04d\n",
               (int)(fw->fw_ver >> 32),
               (int)((fw->fw_ver >> 16) & 0xffff),
               (int)(fw->fw_ver & 0xffff));
    seq_printf(dec->m, "FW release date     : %02x/%02x/%04x %02x:%02x\n",
               fw->fw_day,
               fw->fw_month,
               fw->fw_year,
               fw->fw_hour,
               fw->fw_minutes);

    seq_printf(dec->m, "clear_interrupt_base: 0x%llx\n", fw->clr_int_base);
    seq_printf(dec->m, "catas_offset        : 0x%llx\n", fw->catas_offset);
    seq_printf(dec->m, "catas_size          : 0x%x\n", fw->catas_size);
    seq_printf(dec->m, "debug_trace         : %u\n", fw->debug_trace);
    seq_printf(dec->m, "smkey               : %u\n", fw->smkey);
    seq_printf(dec->m, "doorbell_page_offset: 0x%llx\n", fw->doorbell_page_offset);
    seq_printf(dec->m, "frc_offset          : 0x%llx\n", fw->frc_offset);
    seq_printf(dec->m, "utc_sec_offset      : 0x%llx\n", fw->utc_sec_offset);
    seq_printf(dec->m, "utc_nsec_offset     : 0x%llx\n", fw->utc_nsec_offset);
    seq_printf(dec->m, "core_clock          : %u\n", fw->core_clock);
    seq_printf(dec->m, "fw_pages            : %u\n", fw->fw_pages);
    seq_printf(dec->m, "local_out_mb_offset : 0x%x\n", fw->local_out_mb_offset);
    seq_printf(dec->m, "local_out_mb_size   : %u\n", fw->local_out_mb_size);
    seq_printf(dec->m, "local_in_mb_offset  : 0x%x\n", fw->local_in_mb_offset);
    seq_printf(dec->m, "local_in_mb_size    : %u\n", fw->local_in_mb_size);

    sx_dbg_dump_print_empty_line(dec->m);
    return true;
}

static int __fw_and_board_info_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_dev_db_iterator_seq_file_context dec = {
        .m = m,
        .v = v,
        .context = context
    };

    sx_dev_db_iterate(__dev_iterator_fw_and_board_info_dump, &dec);
    return 0;
}

int __init sx_dbg_init(void)
{
    sx_dbg_dump_write_handler_register("sdq_max_diff_clear",
                                       "<dev_id> <sdq_num>",
                                       "Clear max diff between transmitted packet time and completion time",
                                       __sdq_max_diff_clear,
                                       NULL);
    sx_dbg_dump_write_handler_register("qos_counters_clear",
                                       "no parameters",
                                       "Clear EMAD Quality of Service counters",
                                       sx_qos_emad_counter_clear,
                                       NULL);
    sx_dbg_dump_read_handler_register("cq_dump", __cq_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("ber_monitor_dump", __ber_monitor_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("tele_thrs_dump", __tele_thrs_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("ptp_dump", sx_dbg_ptp_dump_proc_show, NULL, NULL);
    sx_dbg_dump_read_handler_register("clock_dump", sx_dbg_clock_dump_proc_show, NULL, NULL);
    sx_dbg_dump_read_handler_register("clock_and_ptp_log_dump", sx_dbg_clock_and_ptp_log_dump_proc_show, NULL, NULL);
    sx_dbg_dump_read_handler_register("monitor_rdq_dump", __monitor_rdq_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("sdq_dump", __sdq_dump, NULL, NULL);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
    sx_dbg_dump_read_handler_register("rdq_to_filter_ebpf_prog_dump", __rdq_to_filter_ebpf_prog_dump, NULL, NULL);
#endif
    sx_dbg_dump_read_handler_register("fw_and_board_info_dump", __fw_and_board_info_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("mmap_dump", sx_mmap_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("bulk_cntr_dump", bulk_cntr_db_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("accuflow_dump", sx_af_counters_dump, sx_af_counters_dump_size, NULL);
    sx_dbg_dump_read_handler_register("dev_db_dump", sx_dev_db_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("health_check_dump", sx_health_check_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("synce_dump", sx_core_synce_dump, NULL, NULL);
    sx_dbg_dump_read_handler_register("qos_emad_dump", sx_qos_emad_dump, NULL, NULL);

    sx_dbg_host_ifc_init();
    sx_dbg_db_init();
    sx_core_counters_init();
    return 0;
}

void sx_dbg_deinit(void)
{
    sx_core_counters_deinit();
    sx_dbg_db_deinit();
    sx_dbg_host_ifc_deinit();

    sx_dbg_dump_read_handler_unregister("cq_dump");
    sx_dbg_dump_read_handler_unregister("ber_monitor_dump");
    sx_dbg_dump_read_handler_unregister("tele_thrs_dump");
    sx_dbg_dump_read_handler_unregister("ptp_dump");
    sx_dbg_dump_read_handler_unregister("clock_dump");
    sx_dbg_dump_read_handler_unregister("clock_and_ptp_log_dump");
    sx_dbg_dump_read_handler_unregister("monitor_rdq_dump");
    sx_dbg_dump_read_handler_unregister("sdq_dump");
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
    sx_dbg_dump_read_handler_unregister("rdq_to_filter_ebpf_prog_dump");
#endif
    sx_dbg_dump_read_handler_unregister("fw_and_board_info_dump");
    sx_dbg_dump_read_handler_unregister("mmap_dump");
    sx_dbg_dump_read_handler_unregister("bulk_cntr_dump");
    sx_dbg_dump_read_handler_unregister("accuflow_dump");
    sx_dbg_dump_read_handler_unregister("dev_db_dump");
    sx_dbg_dump_read_handler_unregister("health_check_dump");
    sx_dbg_dump_read_handler_unregister("synce_dump");
}
