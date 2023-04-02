/*
 * Copyright © 2021-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include "sx_spice_access_reg.h"
#include "sx_spice_tree_auto.h"
#include "sx_spice_access_reg_auto.h"

/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

static LIST_HEAD(__slrip_list_head);
static LIST_HEAD(__slrg_list_head);
static LIST_HEAD(__slrp_list_head);
static LIST_HEAD(__peucg_list_head);
static LIST_HEAD(__ppll_list_head);

/************************************************
 *  Local function declarations
 ***********************************************/

/************************************************
 * Functions                                    *
 ***********************************************/

ssize_t sx_spice_access_reg_slrip_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char               *kbuffer = NULL;
    int                 err = 0;
    ssize_t             size = 0;
    ssize_t             print_data_size = 0;
    struct ku_slrip_reg reg_data;
    const slrip_data_t *data = (slrip_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SLRIP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.lane = data->lane;
    reg_data.port_type = data->port_type;
    if (data->ib_sel) {
        reg_data.page_data.slrip_16nm.ib_sel = data->ib_sel;
        reg_data.version = 3; /* 16nm */
    } else {
        reg_data.version = 4; /* 7nm */
    }

    err = SX_SPICE_EMAD_ACCESS_REG(SLRIP, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_slrip_reg_data_to_buffer_print(kbuffer,
                                                                         sizeof(char) * KERNEL_BUFFER_SIZE,
                                                                         &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

/* file operations */

static const struct file_operations slrip_fops = {
    .read = sx_spice_access_reg_slrip_read
};

int sx_spice_access_reg_slrip_reg_data_to_buffer_print(char                  buffer[],
                                                       size_t                buffer_length,
                                                       struct ku_slrip_reg * reg_data)
{
    int      buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->status);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->version);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->lane);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->port_type);
    buffer += snp_res;
    buffer_size += snp_res;

    switch (reg_data->version) {
    case 3: /* 16nm */
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ib_sel: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ib_sel);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap0: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap1: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap2: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap3: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap4: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap5: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap6: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap7: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap8: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "sel_enc0: 0x%x\n",
                           reg_data->page_data.slrip_16nm.sel_enc0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap_en: 0x%x\n",
                           reg_data->page_data.slrip_16nm.ffe_tap_en);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "sel_enc1: 0x%x\n",
                           reg_data->page_data.slrip_16nm.sel_enc1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "sel_enc2: 0x%x\n",
                           reg_data->page_data.slrip_16nm.sel_enc2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mixer_offset0: 0x%x\n",
                           reg_data->page_data.slrip_16nm.mixer_offset0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mixer_offset1: 0x%x\n",
                           reg_data->page_data.slrip_16nm.mixer_offset1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "saved0_sel_enc0: 0x%x\n",
                           reg_data->page_data.slrip_16nm.saved0_sel_enc0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "saved0_mixer_offset0: 0x%x\n",
                           reg_data->page_data.slrip_16nm.saved0_mixer_offset0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "saved1_sel_enc0: 0x%x\n",
                           reg_data->page_data.slrip_16nm.saved1_sel_enc0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "saved1_mixer_offset0: 0x%x\n",
                           reg_data->page_data.slrip_16nm.saved1_mixer_offset0);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case 4: /* 7nm */
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "feq_train_mode: 0x%x\n",
                           reg_data->page_data.slrip_7nm.feq_train_mode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "term_lpf_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.term_lpf_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vref_val_mode_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.vref_val_mode_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vga_gain_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.vga_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "hf_gain_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.hf_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mf_pole_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.mf_pole_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mf_gain_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.mf_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lf_pole_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.lf_pole_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lf_gain_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.lf_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dc_gain_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dc_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "term_attn_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.term_attn_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f1_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.f1_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f2_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.f2_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f3_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.f3_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f4_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.f4_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f5_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.f5_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f6_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.f6_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f7_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.f7_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f8_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.f8_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fm1_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.fm1_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fm2_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.fm2_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fm3_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.fm3_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "eth_override_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.eth_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mf_pole: 0x%x\n",
                           reg_data->page_data.slrip_7nm.mf_pole);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mf_gain: 0x%x\n",
                           reg_data->page_data.slrip_7nm.mf_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lf_pole: 0x%x\n",
                           reg_data->page_data.slrip_7nm.lf_pole);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lf_gain: 0x%x\n",
                           reg_data->page_data.slrip_7nm.lf_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "term_attn_ctrl: 0x%x\n",
                           reg_data->page_data.slrip_7nm.term_attn_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "hf_gain: 0x%x\n",
                           reg_data->page_data.slrip_7nm.hf_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dc_gain: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dc_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "adc_vref_val: 0x%x\n",
                           reg_data->page_data.slrip_7nm.adc_vref_val);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vga_gain: 0x%x\n",
                           reg_data->page_data.slrip_7nm.vga_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_fm1: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_fm1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_fm2: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_fm2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_fm3: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_fm3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f4: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_f4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f3: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_f3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f2: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_f2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f1: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_f1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f8: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_f8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f7: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_f7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f6: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_f6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f5: 0x%x\n",
                           reg_data->page_data.slrip_7nm.ffe_f5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel3: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef3: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel2: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef2: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel1: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef1: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel0: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef0: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel7: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef7: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel6: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef6: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel5: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef5: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel4: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef4: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel8: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_dsel8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef8: 0x%x\n",
                           reg_data->page_data.slrip_7nm.dffe_coef8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th1: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th0: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th3: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th2: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th5: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th4: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th7: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th6: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th9: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th9);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th8: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th11: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th11);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th10: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th10);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th13: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th13);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th12: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th12);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th15: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th15);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th14: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th14);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th17: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th17);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th16: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th16);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th19: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th19);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th18: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th18);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th21: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th21);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th20: 0x%x\n",
                           reg_data->page_data.slrip_7nm.th20);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        /* Other types not supported yet */
        break;
    }

    return buffer_size;
}

int sx_spice_access_reg_slrip_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    slrip_data_t *slrip = NULL;

    slrip = kzalloc(sizeof(slrip_data_t), GFP_KERNEL);
    if (!slrip) {
        printk(KERN_ERR "Failed to allocate slrip for SPICE\n");
        goto out;
    }

    list_add_tail(&slrip->slrip_list, &__slrip_list_head);

    slrip->dev_data = dev_data;
    slrip->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    slrip->pnat = sx_spice_tree_index_value_get(PNAT);
    slrip->lane = sx_spice_tree_index_value_get(LANE);
    slrip->port_type = sx_spice_tree_index_value_get(PORT_TYPE);
    slrip->ib_sel = sx_spice_tree_index_value_get(IB_SEL);


    debugfs_create_file("SLRIP", 0644, parent, (void *)slrip, &slrip_fops);

    return 0;

out:
    return -ENOMEM;
}

void sx_spice_access_reg_slrip_list_free(void)
{
    slrip_data_t *iter_slrip, *tmp_slrip;

    list_for_each_entry_safe(iter_slrip, tmp_slrip, &__slrip_list_head, slrip_list) {
        list_del(&iter_slrip->slrip_list);
        kfree(iter_slrip);
    }
}


ssize_t sx_spice_access_reg_slrg_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char              *kbuffer = NULL;
    int                err = 0;
    ssize_t            size = 0;
    ssize_t            print_data_size = 0;
    struct ku_slrg_reg reg_data;
    const slrg_data_t *data = (slrg_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SLRG SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.lane = data->lane;
    reg_data.port_type = data->port_type;
    reg_data.test_mode = data->test_mode;

    err = SX_SPICE_EMAD_ACCESS_REG(SLRG, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_slrg_reg_data_to_buffer_print(kbuffer,
                                                                        sizeof(char) * KERNEL_BUFFER_SIZE,
                                                                        &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

/* file operations */

static const struct file_operations slrg_fops = {
    .read = sx_spice_access_reg_slrg_read
};

int sx_spice_access_reg_slrg_reg_data_to_buffer_print(char                 buffer[],
                                                      size_t               buffer_length,
                                                      struct ku_slrg_reg * reg_data)
{
    int      buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->status);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->version);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->lane);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->port_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "test_mode: 0x%x\n", reg_data->test_mode);
    buffer += snp_res;
    buffer_size += snp_res;
    switch (reg_data->version) {
    case 0:
    case 1:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade_lane_speed: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.grade_lane_speed);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade_version: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.grade_version);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_units: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.offset_units);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_units: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.phase_units);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_grade_type: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.height_grade_type);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_grade: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.height_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_dz: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.height_dz);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_dv: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.height_dv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_sigma: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.height_sigma);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_pos: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.height_eo_pos);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_neg: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.height_eo_neg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_grade_type: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.phase_grade_type);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_grade: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.phase_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_pos: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.phase_eo_pos);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_neg: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.phase_eo_neg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_set_tested: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.ffe_set_tested);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "test_errors_per_lane: 0x%x\n",
                           reg_data->page_data.slrg_40nm_28nm.test_errors_per_lane);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case 3:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade_lane_speed: 0x%x\n",
                           reg_data->page_data.slrg_16nm.grade_lane_speed);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade_version: 0x%x\n",
                           reg_data->page_data.slrg_16nm.grade_version);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade: 0x%x\n",
                           reg_data->page_data.slrg_16nm.grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_pos_up: 0x%x\n",
                           reg_data->page_data.slrg_16nm.height_eo_pos_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_neg_up: 0x%x\n",
                           reg_data->page_data.slrg_16nm.height_eo_neg_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_pos_up: 0x%x\n",
                           reg_data->page_data.slrg_16nm.phase_eo_pos_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_neg_up: 0x%x\n",
                           reg_data->page_data.slrg_16nm.phase_eo_neg_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_pos_mid: 0x%x\n",
                           reg_data->page_data.slrg_16nm.height_eo_pos_mid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_neg_mid: 0x%x\n",
                           reg_data->page_data.slrg_16nm.height_eo_neg_mid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_pos_mid: 0x%x\n",
                           reg_data->page_data.slrg_16nm.phase_eo_pos_mid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_neg_mid: 0x%x\n",
                           reg_data->page_data.slrg_16nm.phase_eo_neg_mid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_pos_low: 0x%x\n",
                           reg_data->page_data.slrg_16nm.height_eo_pos_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_neg_low: 0x%x\n",
                           reg_data->page_data.slrg_16nm.height_eo_neg_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_pos_low: 0x%x\n",
                           reg_data->page_data.slrg_16nm.phase_eo_pos_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_neg_low: 0x%x\n",
                           reg_data->page_data.slrg_16nm.phase_eo_neg_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_eye_grade: 0x%x\n",
                           reg_data->page_data.slrg_16nm.mid_eye_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "up_eye_grade: 0x%x\n",
                           reg_data->page_data.slrg_16nm.up_eye_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dn_eye_grade: 0x%x\n",
                           reg_data->page_data.slrg_16nm.dn_eye_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case 4:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fom_measurment: 0x%x\n",
                           reg_data->page_data.slrg_7nm.fom_measurment);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fom_mode: 0x%x\n",
                           reg_data->page_data.slrg_7nm.fom_mode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "initial_fom: 0x%x\n",
                           reg_data->page_data.slrg_7nm.initial_fom);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "last_fom: 0x%x\n",
                           reg_data->page_data.slrg_7nm.last_fom);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_eye: 0x%x\n",
                           reg_data->page_data.slrg_7nm.upper_eye);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_eye: 0x%x\n",
                           reg_data->page_data.slrg_7nm.mid_eye);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_eye: 0x%x\n",
                           reg_data->page_data.slrg_7nm.lower_eye);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "status: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.status);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "iterations: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.iterations);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_max: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.upper_max);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_max: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.mid_max);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_max: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.lower_max);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "comp_max: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.comp_max);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_min: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.upper_min);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_min: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.mid_min);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_min: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.lower_min);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "comp_min: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.comp_min);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_std: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.upper_std);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_std: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.mid_std);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_std: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.lower_std);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "comp_std: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.comp_std);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_avg: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.upper_avg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_avg: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.mid_avg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_avg: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.lower_avg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "comp_avg: 0x%x\n",
                           reg_data->page_data.slrg_7nm_testing.lane_meas_info.comp_avg);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        break;
    }

    return buffer_size;
}

int sx_spice_access_reg_slrg_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    slrg_data_t *slrg = NULL;

    slrg = kzalloc(sizeof(slrg_data_t), GFP_KERNEL);
    if (!slrg) {
        printk(KERN_ERR "Failed to allocate slrg for SPICE\n");
        goto out;
    }

    list_add_tail(&slrg->slrg_list, &__slrg_list_head);

    slrg->dev_data = dev_data;
    slrg->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    slrg->pnat = sx_spice_tree_index_value_get(PNAT);
    slrg->lane = sx_spice_tree_index_value_get(LANE);
    slrg->port_type = sx_spice_tree_index_value_get(PORT_TYPE);
    slrg->test_mode = sx_spice_tree_index_value_get(TEST_MODE);

    debugfs_create_file("SLRG", 0644, parent, (void *)slrg, &slrg_fops);

    return 0;

out:
    return -ENOMEM;
}

void sx_spice_access_reg_slrg_list_free(void)
{
    slrg_data_t *iter_slrg, *tmp_slrg;

    list_for_each_entry_safe(iter_slrg, tmp_slrg, &__slrg_list_head, slrg_list) {
        list_del(&iter_slrg->slrg_list);
        kfree(iter_slrg);
    }
}


int sx_spice_access_reg_slrp_reg_data_to_buffer_print(char                 buffer[],
                                                      size_t               buffer_length,
                                                      struct ku_slrp_reg * reg_data)
{
    int      buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->status);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->version);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->lane);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->port_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    switch (reg_data->port_type) {
    case 0:
    case 2:
        switch (reg_data->version) {
        case 0:
        case 1:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ib_sel: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ib_sel);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "dp_sel: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.dp_sel);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "dp90sel: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.dp90sel);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mix90phase: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mix90phase);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap0: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap1: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap2: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap2);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap3: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap3);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap4: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap4);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap5: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap5);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap6: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap6);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap7: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap7);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap8: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap8);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbias_tap_amp: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixerbias_tap_amp);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap_en: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap_en);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap_offset0: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap_offset0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap_offset1: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ffe_tap_offset1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "slicer_offset0: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.slicer_offset0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset0: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixer_offset0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset1: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixer_offset1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbgn_inp: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixerbgn_inp);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbgn_inn: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixerbgn_inn);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbgn_refp: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixerbgn_refp);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbgn_refn: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixerbgn_refn);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_slicer_lctrl_h: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.sel_slicer_lctrl_h);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_slicer_lctrl_l: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.sel_slicer_lctrl_l);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ref_mixer_vreg: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.ref_mixer_vreg);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "slicer_gctrl: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.slicer_gctrl);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lctrl_input: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.lctrl_input);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_cm1: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixer_offset_cm1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "common_mode: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.common_mode);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_cm0: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.mixer_offset_cm0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "slicer_offset_cm: 0x%x\n",
                               reg_data->page_data.slrp_40nm_28nm.slicer_offset_cm);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case 3:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_up: 0x%x\n",
                               reg_data->page_data.slrp_16nm.mixer_offset_up);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_down: 0x%x\n",
                               reg_data->page_data.slrp_16nm.mixer_offset_down);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_enc: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_enc);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "dp_sel: 0x%x\n",
                               reg_data->page_data.slrp_16nm.dp_sel);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_in_mixer_biasgen_up: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_up);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_in_mixer_biasgen_mid: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_mid);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_in_mixer_biasgen_down: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_down);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_in_mixer_biasgen_eo: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_ref_in_mixer_biasgen_eo);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_out_mixer_biasgen_up: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_up);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_out_mixer_biasgen_mid: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_mid);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_out_mixer_biasgen_down: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_down);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_out_mixer_biasgen_eo: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_ref_out_mixer_biasgen_eo);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_amp_mixer_biasgen_up: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_amp_mixer_biasgen_up);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_amp_mixer_biasgen_mid: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_amp_mixer_biasgen_mid);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_amp_mixer_biasgen_down: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_amp_mixer_biasgen_down);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_amp_mixer_biasgen_eo: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_amp_mixer_biasgen_eo);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_eye_scan: 0x%x\n",
                               reg_data->page_data.slrp_16nm.mixer_offset_eye_scan);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "gctrl_bin_bgn0_n: 0x%x\n",
                               reg_data->page_data.slrp_16nm.gctrl_bin_bgn0_n);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "gctrl_bin_bgn0_p: 0x%x\n",
                               reg_data->page_data.slrp_16nm.gctrl_bin_bgn0_p);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "gctrl_bin_bgn1_n: 0x%x\n",
                               reg_data->page_data.slrp_16nm.gctrl_bin_bgn1_n);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "gctrl_bin_bgn1_p: 0x%x\n",
                               reg_data->page_data.slrp_16nm.gctrl_bin_bgn1_p);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_digital_gctrl: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_digital_gctrl);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias2ctle: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_bias2ctle);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "selgc_ref_op0_alev_ctle: 0x%x\n",
                               reg_data->page_data.slrp_16nm.selgc_ref_op0_alev_ctle);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "selgc_ref_op1_alev_ctle: 0x%x\n",
                               reg_data->page_data.slrp_16nm.selgc_ref_op1_alev_ctle);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_0: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_bias_en_0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_1: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_bias_en_1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_2: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_bias_en_2);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_3: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_bias_en_3);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_4: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_bias_en_4);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_5: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_bias_en_5);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_6: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_bias_en_6);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_0: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrln_en_0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_1: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrln_en_1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_2: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrln_en_2);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_3: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrln_en_3);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_4: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrln_en_4);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_5: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrln_en_5);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_6: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrln_en_6);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_0: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrlp_en_0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_1: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrlp_en_1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_2: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrlp_en_2);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_3: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrlp_en_3);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_4: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrlp_en_4);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_5: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrlp_en_5);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_6: 0x%x\n",
                               reg_data->page_data.slrp_16nm.sel_gctrlp_en_6);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "crnt_bgn_offset_p1: 0x%x\n",
                               reg_data->page_data.slrp_16nm.crnt_bgn_offset_p1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "crnt_bgn_offset_n1: 0x%x\n",
                               reg_data->page_data.slrp_16nm.crnt_bgn_offset_n1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "crnt_bgn_offset_p0: 0x%x\n",
                               reg_data->page_data.slrp_16nm.crnt_bgn_offset_p0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "crnt_bgn_offset_n0: 0x%x\n",
                               reg_data->page_data.slrp_16nm.crnt_bgn_offset_n0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case 4:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_recording_admin: 0x%x\n",
                               reg_data->page_data.slrp_7nm.adc_recording_admin);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_recording_status: 0x%x\n",
                               reg_data->page_data.slrp_7nm.adc_recording_status);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_rocording_lanes: 0x%x\n",
                               reg_data->page_data.slrp_7nm.adc_rocording_lanes);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "edge_vos_ccal_en: 0x%x\n",
                               reg_data->page_data.slrp_7nm.edge_vos_ccal_en);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_gain_shift_auto: 0x%x\n",
                               reg_data->page_data.slrp_7nm.adc_gain_shift_auto);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ccal_mode: 0x%x\n",
                               reg_data->page_data.slrp_7nm.ccal_mode);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ctle_override_ctrl: 0x%x\n",
                               reg_data->page_data.slrp_7nm.ctle_override_ctrl);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "vga_override_ctrl: 0x%x\n",
                               reg_data->page_data.slrp_7nm.vga_override_ctrl);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_vos_override_ctrl: 0x%x\n",
                               reg_data->page_data.slrp_7nm.adc_vos_override_ctrl);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_gain_override_ctrl: 0x%x\n",
                               reg_data->page_data.slrp_7nm.adc_gain_override_ctrl);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos_override_ctrl: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos_override_ctrl);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "cal_error_cnt: 0x%x\n",
                               reg_data->page_data.slrp_7nm.cal_error_cnt);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ccal_state: 0x%x\n",
                               reg_data->page_data.slrp_7nm.ccal_state);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ccal_op: 0x%x\n",
                               reg_data->page_data.slrp_7nm.ccal_op);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res =
                snprintf(buffer,
                         buffer_length - buffer_size,
                         "phos: 0x%x\n",
                         reg_data->page_data.slrp_7nm.phos);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "vga_vos1: 0x%x\n",
                               reg_data->page_data.slrp_7nm.vga_vos1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "vga_vos0: 0x%x\n",
                               reg_data->page_data.slrp_7nm.vga_vos0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ctle_vos0: 0x%x\n",
                               reg_data->page_data.slrp_7nm.ctle_vos0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_vos: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
                               reg_data->page_data.slrp_7nm.adc_vos[0],
                               reg_data->page_data.slrp_7nm.adc_vos[1],
                               reg_data->page_data.slrp_7nm.adc_vos[2],
                               reg_data->page_data.slrp_7nm.adc_vos[3],
                               reg_data->page_data.slrp_7nm.adc_vos[4],
                               reg_data->page_data.slrp_7nm.adc_vos[5],
                               reg_data->page_data.slrp_7nm.adc_vos[6],
                               reg_data->page_data.slrp_7nm.adc_vos[7],
                               reg_data->page_data.slrp_7nm.adc_vos[8],
                               reg_data->page_data.slrp_7nm.adc_vos[9],
                               reg_data->page_data.slrp_7nm.adc_vos[10],
                               reg_data->page_data.slrp_7nm.adc_vos[11],
                               reg_data->page_data.slrp_7nm.adc_vos[12],
                               reg_data->page_data.slrp_7nm.adc_vos[13],
                               reg_data->page_data.slrp_7nm.adc_vos[14],
                               reg_data->page_data.slrp_7nm.adc_vos[15],
                               reg_data->page_data.slrp_7nm.adc_vos[16],
                               reg_data->page_data.slrp_7nm.adc_vos[17],
                               reg_data->page_data.slrp_7nm.adc_vos[18],
                               reg_data->page_data.slrp_7nm.adc_vos[19],
                               reg_data->page_data.slrp_7nm.adc_vos[20],
                               reg_data->page_data.slrp_7nm.adc_vos[21],
                               reg_data->page_data.slrp_7nm.adc_vos[22],
                               reg_data->page_data.slrp_7nm.adc_vos[23],
                               reg_data->page_data.slrp_7nm.adc_vos[24],
                               reg_data->page_data.slrp_7nm.adc_vos[25],
                               reg_data->page_data.slrp_7nm.adc_vos[26],
                               reg_data->page_data.slrp_7nm.adc_vos[27],
                               reg_data->page_data.slrp_7nm.adc_vos[28],
                               reg_data->page_data.slrp_7nm.adc_vos[29],
                               reg_data->page_data.slrp_7nm.adc_vos[30],
                               reg_data->page_data.slrp_7nm.adc_vos[31],
                               reg_data->page_data.slrp_7nm.adc_vos[32],
                               reg_data->page_data.slrp_7nm.adc_vos[33],
                               reg_data->page_data.slrp_7nm.adc_vos[34],
                               reg_data->page_data.slrp_7nm.adc_vos[35],
                               reg_data->page_data.slrp_7nm.adc_vos[36],
                               reg_data->page_data.slrp_7nm.adc_vos[37],
                               reg_data->page_data.slrp_7nm.adc_vos[38],
                               reg_data->page_data.slrp_7nm.adc_vos[39],
                               reg_data->page_data.slrp_7nm.adc_vos[40],
                               reg_data->page_data.slrp_7nm.adc_vos[41],
                               reg_data->page_data.slrp_7nm.adc_vos[42],
                               reg_data->page_data.slrp_7nm.adc_vos[43],
                               reg_data->page_data.slrp_7nm.adc_vos[44],
                               reg_data->page_data.slrp_7nm.adc_vos[45],
                               reg_data->page_data.slrp_7nm.adc_vos[46],
                               reg_data->page_data.slrp_7nm.adc_vos[47],
                               reg_data->page_data.slrp_7nm.adc_vos[48],
                               reg_data->page_data.slrp_7nm.adc_vos[49],
                               reg_data->page_data.slrp_7nm.adc_vos[50],
                               reg_data->page_data.slrp_7nm.adc_vos[51],
                               reg_data->page_data.slrp_7nm.adc_vos[52],
                               reg_data->page_data.slrp_7nm.adc_vos[53],
                               reg_data->page_data.slrp_7nm.adc_vos[54],
                               reg_data->page_data.slrp_7nm.adc_vos[55],
                               reg_data->page_data.slrp_7nm.adc_vos[56],
                               reg_data->page_data.slrp_7nm.adc_vos[57],
                               reg_data->page_data.slrp_7nm.adc_vos[58],
                               reg_data->page_data.slrp_7nm.adc_vos[59],
                               reg_data->page_data.slrp_7nm.adc_vos[60],
                               reg_data->page_data.slrp_7nm.adc_vos[61],
                               reg_data->page_data.slrp_7nm.adc_vos[62],
                               reg_data->page_data.slrp_7nm.adc_vos[63]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_gos: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
                               reg_data->page_data.slrp_7nm.adc_gos[0],
                               reg_data->page_data.slrp_7nm.adc_gos[1],
                               reg_data->page_data.slrp_7nm.adc_gos[2],
                               reg_data->page_data.slrp_7nm.adc_gos[3],
                               reg_data->page_data.slrp_7nm.adc_gos[4],
                               reg_data->page_data.slrp_7nm.adc_gos[5],
                               reg_data->page_data.slrp_7nm.adc_gos[6],
                               reg_data->page_data.slrp_7nm.adc_gos[7],
                               reg_data->page_data.slrp_7nm.adc_gos[8],
                               reg_data->page_data.slrp_7nm.adc_gos[9],
                               reg_data->page_data.slrp_7nm.adc_gos[10],
                               reg_data->page_data.slrp_7nm.adc_gos[11],
                               reg_data->page_data.slrp_7nm.adc_gos[12],
                               reg_data->page_data.slrp_7nm.adc_gos[13],
                               reg_data->page_data.slrp_7nm.adc_gos[14],
                               reg_data->page_data.slrp_7nm.adc_gos[15],
                               reg_data->page_data.slrp_7nm.adc_gos[16],
                               reg_data->page_data.slrp_7nm.adc_gos[17],
                               reg_data->page_data.slrp_7nm.adc_gos[18],
                               reg_data->page_data.slrp_7nm.adc_gos[19],
                               reg_data->page_data.slrp_7nm.adc_gos[20],
                               reg_data->page_data.slrp_7nm.adc_gos[21],
                               reg_data->page_data.slrp_7nm.adc_gos[22],
                               reg_data->page_data.slrp_7nm.adc_gos[23],
                               reg_data->page_data.slrp_7nm.adc_gos[24],
                               reg_data->page_data.slrp_7nm.adc_gos[25],
                               reg_data->page_data.slrp_7nm.adc_gos[26],
                               reg_data->page_data.slrp_7nm.adc_gos[27],
                               reg_data->page_data.slrp_7nm.adc_gos[28],
                               reg_data->page_data.slrp_7nm.adc_gos[29],
                               reg_data->page_data.slrp_7nm.adc_gos[30],
                               reg_data->page_data.slrp_7nm.adc_gos[31],
                               reg_data->page_data.slrp_7nm.adc_gos[32],
                               reg_data->page_data.slrp_7nm.adc_gos[33],
                               reg_data->page_data.slrp_7nm.adc_gos[34],
                               reg_data->page_data.slrp_7nm.adc_gos[35],
                               reg_data->page_data.slrp_7nm.adc_gos[36],
                               reg_data->page_data.slrp_7nm.adc_gos[37],
                               reg_data->page_data.slrp_7nm.adc_gos[38],
                               reg_data->page_data.slrp_7nm.adc_gos[39],
                               reg_data->page_data.slrp_7nm.adc_gos[40],
                               reg_data->page_data.slrp_7nm.adc_gos[41],
                               reg_data->page_data.slrp_7nm.adc_gos[42],
                               reg_data->page_data.slrp_7nm.adc_gos[43],
                               reg_data->page_data.slrp_7nm.adc_gos[44],
                               reg_data->page_data.slrp_7nm.adc_gos[45],
                               reg_data->page_data.slrp_7nm.adc_gos[46],
                               reg_data->page_data.slrp_7nm.adc_gos[47],
                               reg_data->page_data.slrp_7nm.adc_gos[48],
                               reg_data->page_data.slrp_7nm.adc_gos[49],
                               reg_data->page_data.slrp_7nm.adc_gos[50],
                               reg_data->page_data.slrp_7nm.adc_gos[51],
                               reg_data->page_data.slrp_7nm.adc_gos[52],
                               reg_data->page_data.slrp_7nm.adc_gos[53],
                               reg_data->page_data.slrp_7nm.adc_gos[54],
                               reg_data->page_data.slrp_7nm.adc_gos[55],
                               reg_data->page_data.slrp_7nm.adc_gos[56],
                               reg_data->page_data.slrp_7nm.adc_gos[57],
                               reg_data->page_data.slrp_7nm.adc_gos[58],
                               reg_data->page_data.slrp_7nm.adc_gos[59],
                               reg_data->page_data.slrp_7nm.adc_gos[60],
                               reg_data->page_data.slrp_7nm.adc_gos[61],
                               reg_data->page_data.slrp_7nm.adc_gos[62],
                               reg_data->page_data.slrp_7nm.adc_gos[63]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos3: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos3);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos2: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos2);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos1: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos1);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos0: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos0);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos7: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos7);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos6: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos6);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos5: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos5);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos4: 0x%x\n",
                               reg_data->page_data.slrp_7nm.phos4);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        default:
            break;
        }
        break;

    case 1:
    case 3:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap_index: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.ffe_tap_index);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_sub_channel: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.ffe_sub_channel);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "snr_en: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.snr_en);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dsp_mode: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.dsp_mode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "afe_trim: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.afe_trim);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ctle: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.ctle);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "raw_snr_value: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.raw_snr_value);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "db_snr_value: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.db_snr_value);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap_value: 0x%x\n",
                           reg_data->page_data.slrp_gearbox.ffe_tap_value);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case 4:
    case 5:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mixer00: 0x%x\n",
                           reg_data->page_data.slrp_usr.mixer00);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mixer90: 0x%x\n",
                           reg_data->page_data.slrp_usr.mixer90);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "termination: 0x%x\n",
                           reg_data->page_data.slrp_usr.termination);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "neg_cap_up: 0x%x\n",
                           reg_data->page_data.slrp_usr.neg_cap_up);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "neg_cap_mid: 0x%x\n",
                           reg_data->page_data.slrp_usr.neg_cap_mid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "neg_cap_dn: 0x%x\n",
                           reg_data->page_data.slrp_usr.neg_cap_dn);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_polarity_up: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_coarse_polarity_up);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_polarity_mid: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_coarse_polarity_mid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_polarity_dn: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_coarse_polarity_dn);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_polarity_up: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_fine_polarity_up);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_polarity_mid: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_fine_polarity_mid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_polarity_dn: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_fine_polarity_dn);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "amp_vga: 0x%x\n",
                           reg_data->page_data.slrp_usr.amp_vga);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "amp_vga_last_stage: 0x%x\n",
                           reg_data->page_data.slrp_usr.amp_vga_last_stage);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_up: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_coarse_up);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_mid: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_coarse_mid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_dn: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_coarse_dn);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_up: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_fine_up);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_mid: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_fine_mid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_dn: 0x%x\n",
                           reg_data->page_data.slrp_usr.offset_fine_dn);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        break;
    }

    return buffer_size;
}

ssize_t sx_spice_access_reg_slrp_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char              *kbuffer = NULL;
    int                err = 0;
    ssize_t            size = 0;
    ssize_t            print_data_size = 0;
    struct ku_slrp_reg reg_data;
    const slrp_data_t *data = (slrp_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SLRP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.lane = data->lane;
    reg_data.port_type = data->port_type;


    err = SX_SPICE_EMAD_ACCESS_REG(SLRP, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_slrp_reg_data_to_buffer_print(kbuffer,
                                                                        sizeof(char) * KERNEL_BUFFER_SIZE,
                                                                        &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

static const struct file_operations slrp_fops = {
    .read = sx_spice_access_reg_slrp_read
};

int sx_spice_access_reg_slrp_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    slrp_data_t *slrp = NULL;

    slrp = kzalloc(sizeof(slrp_data_t), GFP_KERNEL);
    if (!slrp) {
        printk(KERN_ERR "Failed to allocate slrp for SPICE\n");
        goto out;
    }

    list_add_tail(&slrp->slrp_list, &__slrp_list_head);

    slrp->dev_data = dev_data;
    slrp->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    slrp->pnat = sx_spice_tree_index_value_get(PNAT);
    slrp->lane = sx_spice_tree_index_value_get(LANE);
    slrp->port_type = sx_spice_tree_index_value_get(PORT_TYPE);


    debugfs_create_file("SLRP", 0644, parent, (void *)slrp, &slrp_fops);

    return 0;

out:
    return -ENOMEM;
}

void sx_spice_access_reg_slrp_list_free(void)
{
    slrp_data_t *iter_slrp, *tmp_slrp;

    list_for_each_entry_safe(iter_slrp, tmp_slrp, &__slrp_list_head, slrp_list) {
        list_del(&iter_slrp->slrp_list);
        kfree(iter_slrp);
    }
}

int sx_spice_access_reg_peucg_data_to_buffer_print(char *buffer, size_t buffer_length, struct ku_peucg_reg *reg_data)
{
    int                                  buffer_size = 0, snp_res = 0;
    uint32_t                             index = 0;
    uint16_t                             local_port = 0;
    const struct sx_spice_uphy_reg_info *reg_info = NULL;
    uphy_reg_type_e                      reg_type = reg_data->unit;

    if (KERNEL_BUFFER_SIZE == buffer_length) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "unit: 0x%x\n", reg_data->unit);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->lane);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->status);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "payload_size: 0x%x\n",
                           reg_data->payload_size);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "db: 0x%x\n", reg_data->db);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "enum_init: 0x%x\n", reg_data->enum_init);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "num_of_entries: 0x%x\n",
                           reg_data->num_of_entries);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "db_index: 0x%x\n", reg_data->db_index);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    for (index = 0; index < PEUCG_PAGE_DATA_REC_MAX_COUNT; index++) {
        if (reg_data->page_data[index].address == 0) {
            break;
        }

        reg_info = sx_spice_uphy_infra_reg_info_get(reg_type, reg_data->page_data[index].address);
        if (reg_info == NULL) {
            printk(KERN_ERR "REG 0x%x: Register is not initialized!\n", reg_data->page_data[index].address);
        } else {
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "rxtx: 0x%x\n",
                               reg_data->page_data[index].rxtx);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res =
                snprintf(buffer,
                         buffer_length - buffer_size,
                         "address: 0x%x\n",
                         reg_data->page_data[index].address);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;

            snp_res = reg_info->print_cb(&buffer, buffer_length, &buffer_size,
                                         &reg_data->page_data[index].payload_data);
            if (snp_res == 0) {
                return 0;
            }
        }
    }

    return buffer_size;
}

int __pll_index_get(dev_private_data_t *dev_data, uint8_t local_port, uint8_t lp_msb, uint8_t pnat, uint8_t *pll_index)
{
    int                err = 0;
    struct ku_pmdr_reg reg_data;

    memset(&reg_data, 0, sizeof(struct ku_pmdr_reg));

    reg_data.local_port = local_port;
    reg_data.lp_msb = lp_msb;
    reg_data.pnat = pnat;

    err = SX_SPICE_EMAD_ACCESS_REG(PMDR, dev_data, &reg_data);
    if (err) {
        goto out;
    }

    *pll_index = reg_data.pll_index;

out:
    return err;
}

ssize_t sx_spice_access_reg_peucg_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char               *kbuffer = NULL;
    int                 err = 0;
    ssize_t             size = 0;
    ssize_t             print_data_size = 0;
    struct ku_peucg_reg reg_data;
    const peucg_data_t *data = (peucg_data_t*)filp->f_inode->i_private;
    uint16_t            cln_address_array[] = {1, 79, 80, 81, 96, 97, 118, 144};
    uint16_t            dln_rx_address_array[] = {3, 18, 311, 312, 313, 314, 315,
                                                  406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417,
                                                  418,
                                                  419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430,
                                                  431,
                                                  432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443,
                                                  444,
                                                  445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456,
                                                  457,
                                                  458, 459, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469,
                                                  470,
                                                  471, 472, 473, 474, 475, 480, 481, 482, 483, 487, 488, 489,
                                                  490,
                                                  674, 675, 676, 677, 678, 679, 680, 681, 682, 683, 684, 685,
                                                  686,
                                                  687, 688, 689, 690, 691, 692, 693, 694, 695, 696, 697, 698,
                                                  699,
                                                  700, 701, 702, 703, 704, 705, 706, 707, 708, 709, 710, 711,
                                                  712,
                                                  713, 714, 715, 741, 910, 911, 912, 913, 914, 915};
    uint16_t            dln_tx_address_array[] = {2, 18, 129, 164, 165, 166, 167, 172, 173, 174};
    uint8_t             cln_arr_size = 8;
    uint8_t             dln_rx_arr_size = 134;
    uint8_t             dln_tx_arr_size = 10;
    uint8_t             i = 0, pd_it = 0;
    uint16_t            kernel_buff_size = sizeof(char) * KERNEL_BUFFER_SIZE;
    uint8_t             pll_index;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PEUCG SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.unit = data->unit;
    reg_data.pnat = data->pnat;
    reg_data.lane = data->lane;
    reg_data.enum_init = data->enum_init;
    reg_data.db_index = data->db_index;

    if (data->unit == 0) { /* DLN */
        for (i = 0; i < dln_tx_arr_size; i++, pd_it++) {
            if (pd_it == PEUCG_PAGE_DATA_REC_MAX_COUNT) {
                reg_data.payload_size = pd_it;

                err = SX_SPICE_EMAD_ACCESS_REG(PEUCG, data->dev_data, &reg_data);
                if (err) {
                    print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
                    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
                    goto out;
                }

                print_data_size += sx_spice_access_reg_peucg_data_to_buffer_print(kbuffer + print_data_size,
                                                                                  kernel_buff_size - print_data_size,
                                                                                  &reg_data);

                pd_it = 0;
                memset(reg_data.page_data, 0, sizeof(sxd_peucg_page_data_t) * PEUCG_PAGE_DATA_REC_MAX_COUNT);
            }

            reg_data.page_data[pd_it].address = dln_tx_address_array[i];
            reg_data.page_data[pd_it].rxtx = 0; /* tx - 0 rx - 1 */
        }

        for (i = 0; i < dln_rx_arr_size; i++, pd_it++) {
            if (pd_it == PEUCG_PAGE_DATA_REC_MAX_COUNT) {
                reg_data.payload_size = pd_it;

                err = SX_SPICE_EMAD_ACCESS_REG(PEUCG, data->dev_data, &reg_data);
                if (err) {
                    print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
                    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
                    goto out;
                }

                print_data_size += sx_spice_access_reg_peucg_data_to_buffer_print(kbuffer + print_data_size,
                                                                                  kernel_buff_size - print_data_size,
                                                                                  &reg_data);

                pd_it = 0;
                memset(reg_data.page_data, 0, sizeof(sxd_peucg_page_data_t) * PEUCG_PAGE_DATA_REC_MAX_COUNT);
            }

            reg_data.page_data[pd_it].address = dln_rx_address_array[i];
            reg_data.page_data[pd_it].rxtx = 1; /* tx - 0 rx - 1 */
        }
        reg_data.payload_size = pd_it;

        err = SX_SPICE_EMAD_ACCESS_REG(PEUCG, data->dev_data, &reg_data);
        if (err) {
            print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
            size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
            goto out;
        }

        print_data_size += sx_spice_access_reg_peucg_data_to_buffer_print(kbuffer + print_data_size,
                                                                          kernel_buff_size - print_data_size,
                                                                          &reg_data);
    } else { /* CLN */
        err = __pll_index_get(data->dev_data, reg_data.local_port, reg_data.lp_msb,
                              reg_data.pnat, &pll_index);
        if (err) {
            print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
            size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
            goto out;
        }

        /* If unit is CLN - local port is pll index number */
        reg_data.local_port = pll_index;

        for (i = 0; i < cln_arr_size; i++) {
            reg_data.page_data[i].address = cln_address_array[i];
            reg_data.page_data[i].rxtx = 0; /* tx - 0 rx - 1 */
        }

        reg_data.payload_size = cln_arr_size;

        err = SX_SPICE_EMAD_ACCESS_REG(PEUCG, data->dev_data, &reg_data);
        if (err) {
            print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
            size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
            goto out;
        }

        SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                            reg_data.lp_msb,
                                            data->local_port);

        print_data_size = sx_spice_access_reg_peucg_data_to_buffer_print(kbuffer,
                                                                         sizeof(char) * KERNEL_BUFFER_SIZE,
                                                                         &reg_data);
    }

    if (lbuf < print_data_size) {
        printk(KERN_ERR "User buffer size is insufficient for PEUCG SPICE file generation\n");
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

static const struct file_operations peucg_fops = {
    .read = sx_spice_access_reg_peucg_read
};

int sx_spice_access_reg_peucg_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    peucg_data_t *peucg = NULL;

    peucg = kzalloc(sizeof(peucg_data_t), GFP_KERNEL);
    if (!peucg) {
        printk(KERN_ERR "Failed to allocate peucg for SPICE\n");
        goto out;
    }

    list_add_tail(&peucg->peucg_list, &__peucg_list_head);

    peucg->dev_data = dev_data;
    peucg->unit = sx_spice_tree_index_value_get(UNIT);
    peucg->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    peucg->pnat = sx_spice_tree_index_value_get(PNAT);
    peucg->lane = sx_spice_tree_index_value_get(LANE);
    peucg->enum_init = sx_spice_tree_index_value_get(ENUM_INIT);
    peucg->db_index = sx_spice_tree_index_value_get(DB_INDEX);

    debugfs_create_file("PEUCG", 0644, parent, (void *)peucg, &peucg_fops);

    return 0;

out:
    return -ENOMEM;
}

void sx_spice_access_reg_peucg_list_free(void)
{
    peucg_data_t *iter_peucg, *tmp_peucg;

    list_for_each_entry_safe(iter_peucg, tmp_peucg, &__peucg_list_head, peucg_list) {
        list_del(&iter_peucg->peucg_list);
        kfree(iter_peucg);
    }
}

int sx_spice_access_reg_ppll_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_ppll_reg * reg_data)
{
    int      buffer_size = 0, snp_res = 0;
    uint32_t i = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "num_pll_groups: 0x%x\n", reg_data->num_pll_groups);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_group: 0x%x\n", reg_data->pll_group);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pci_oob_pll: 0x%x\n", reg_data->pci_oob_pll);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "num_plls: 0x%x\n", reg_data->num_plls);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->version);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    switch (reg_data->version) {
    case SXD_PPLL_VERSION_PRODUCTS_28NM_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ae: 0x%x\n", reg_data->page_data.ppll_28nm.ae);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        for (i = 0; i < SXD_PPLL_PLL_STATUS_28NM_NUM; i++) {
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lock_cal: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].lock_cal);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lock_status: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].lock_status);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "algo_f_ctrl: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].algo_f_ctrl);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "analog_algo_num_var: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].analog_algo_num_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "f_ctrl_measure: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].f_ctrl_measure);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "analog_var: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].analog_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "high_var: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].high_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "low_var: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].low_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mid_var: 0x%x\n",
                               reg_data->page_data.ppll_28nm.pll_status_28nm[i].mid_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        break;

    case SXD_PPLL_VERSION_PRODUCTS_16NM_E:
        for (i = 0; i < SXD_PPLL_PLL_STATUS_16NM_NUM; i++) {
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lock_status: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_status);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "pll_pwrup: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].pll_pwrup);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lock_pulse: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_pulse);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lock_lost_counter: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_lost_counter);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ae: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].ae);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lock_clk_val_cause: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].lock_clk_val_cause);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "plllock_clk_val: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].plllock_clk_val);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "clock_valid: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].clock_valid);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "pll_speed: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].pll_speed);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lock: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].lock);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "analog_var: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].analog_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "high_var: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].high_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "low_var: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].low_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mid_var: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].mid_var);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "fctrl_measure: 0x%x\n",
                               reg_data->page_data.ppll_reg_16nm.pll_status_16nm[i].fctrl_measure);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        break;

    case SXD_PPLL_VERSION_PRODUCTS_7NM_E:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "pll_ugl_state: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.pll_ugl_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lokcdet_error_count: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lokcdet_error_count);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lockdet_err_measure_done: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lockdet_err_measure_done);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lockdet_err_state: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lockdet_err_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lockdet_cnt_based_lock: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lockdet_cnt_based_lock);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lockdet_err_cnt_unlocked_sticky: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lockdet_err_cnt_unlocked_sticky);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lockdet_err_cnt_locked_sticky: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lockdet_err_cnt_locked_sticky);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lockdet_err_cnt_active_lock: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lockdet_err_cnt_active_lock);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cal_internal_state: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cal_internal_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cal_main_state: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cal_main_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "pll_lockdet_state: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.pll_lockdet_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "pwr_up_state: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.pwr_up_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cal_abort_sticky: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cal_abort_sticky);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cal_abort: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cal_abort);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cal_valid_sticky: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cal_valid_sticky);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dco_coarse: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.dco_coarse);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cal_done: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cal_done);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cal_en: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cal_en);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dco_coarse_bin: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.dco_coarse_bin);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cal_error_counter: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cal_error_counter);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lma_rcal_code: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lma_rcal_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lma_rcal_tx_p_code: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lma_rcal_tx_p_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lma_rcal_tx_n_code: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.lma_rcal_tx_n_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rcal_done_valid_sticky: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.rcal_done_valid_sticky);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rcal_tx_p_valid_sticky: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.rcal_tx_p_valid_sticky);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rcal_tx_n_valid_sticky: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.rcal_tx_n_valid_sticky);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rcal_fsm_done: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.rcal_fsm_done);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "speedo_valid: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.speedo_valid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cvb_trim_valid: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cvb_trim_valid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "bg_trim_valid: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.bg_trim_valid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "speedo: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.speedo);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cvb_trim: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.cvb_trim);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "bg_trim: 0x%x\n",
                           reg_data->page_data.ppll_reg_7nm.bg_trim);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        /* Other types not supported yet */
        break;
    }

    return buffer_size;
}

ssize_t sx_spice_access_reg_ppll_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char              *kbuffer = NULL;
    int                err = 0;
    ssize_t            size = 0;
    ssize_t            print_data_size = 0;
    struct ku_ppll_reg reg_data;
    const ppll_data_t *data = (ppll_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PPLL SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.pll_group = data->pll_group;

    err = SX_SPICE_EMAD_ACCESS_REG(PPLL, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_ppll_data_to_buffer_print(kbuffer,
                                                                    sizeof(char) * KERNEL_BUFFER_SIZE,
                                                                    &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

static const struct file_operations ppll_fops = {
    .read = sx_spice_access_reg_ppll_read
};

int sx_spice_access_reg_ppll_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    ppll_data_t *ppll = NULL;

    ppll = kzalloc(sizeof(ppll_data_t), GFP_KERNEL);
    if (!ppll) {
        printk(KERN_ERR "Failed to allocate ppll for SPICE\n");
        goto out;
    }

    list_add_tail(&ppll->ppll_list, &__ppll_list_head);

    ppll->dev_data = dev_data;
    ppll->pll_group = sx_spice_tree_index_value_get(PLL_GROUP);

    debugfs_create_file("PPLL", 0644, parent, (void *)ppll, &ppll_fops);

    return 0;

out:
    return -ENOMEM;
}

void sx_spice_access_reg_ppll_list_free(void)
{
    ppll_data_t *iter_ppll, *tmp_ppll;

    list_for_each_entry_safe(iter_ppll, tmp_ppll, &__ppll_list_head, ppll_list) {
        list_del(&iter_ppll->ppll_list);
        kfree(iter_ppll);
    }
}
