/*
 * Copyright © 2021-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#define VALIDATE_ROLLBACK(snp_res) \
    do {                           \
        if (snp_res == 0) {        \
            return 0;              \
        }                          \
    } while (0)

/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

static LIST_HEAD(__slrip_list_head);
static LIST_HEAD(__slrg_list_head);
static LIST_HEAD(__slrp_list_head);

/************************************************
 *  Local function declarations
 ***********************************************/

static int __slrip_reg_data_to_buffer_print(char buffer[], size_t buffer_length,
                                            struct ku_access_slrip_reg * reg_data);
static ssize_t __slrip_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);

static int __slrg_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_slrg_reg * reg_data);
static ssize_t __slrg_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);

static int __slrp_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_slrp_reg * reg_data);
static ssize_t __slrp_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);

/************************************************
 * Functions                                    *
 ***********************************************/

ssize_t __slrip_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    sxd_params_t               sxd_params;
    struct ku_access_slrip_reg reg_data;
    const slrip_data_t        *data = (slrip_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SLRIP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_slrip_reg));

    sxd_params.reg_id = MLXSW_SLRIP_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_SLRIP_ID, 1);
    reg_data.dev_id = data->dev_data->dev->device_id;

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.slrip_reg.local_port,
                                        reg_data.slrip_reg.lp_msb,
                                        data->local_port);
    reg_data.slrip_reg.pnat = data->pnat;
    reg_data.slrip_reg.lane = data->lane;
    reg_data.slrip_reg.port_type = data->port_type;
    if (data->ib_sel) {
        reg_data.slrip_reg.page_data.slrip_16nm.ib_sel = data->ib_sel;
        reg_data.slrip_reg.version = 3; /* 16nm */
    } else {
        reg_data.slrip_reg.version = 4; /* 7nm */
    }

    err = sx_spice_sxd_access(data->dev_data, &sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __slrip_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

/* file operations */

static const struct file_operations slrip_fops = {
    .read = __slrip_read
};

int __slrip_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_slrip_reg * reg_data)
{
    int      buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->slrip_reg.status);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->slrip_reg.version);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->slrip_reg.local_port, reg_data->slrip_reg.lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->slrip_reg.pnat);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->slrip_reg.lane);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->slrip_reg.port_type);
    buffer += snp_res;
    buffer_size += snp_res;

    switch (reg_data->slrip_reg.version) {
    case 3: /* 16nm */
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ib_sel: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ib_sel);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap1: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap2: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap3: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap4: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap5: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap6: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap7: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap8: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "sel_enc0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.sel_enc0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap_en: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.ffe_tap_en);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "sel_enc1: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.sel_enc1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "sel_enc2: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.sel_enc2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mixer_offset0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.mixer_offset0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mixer_offset1: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.mixer_offset1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "saved0_sel_enc0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.saved0_sel_enc0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "saved0_mixer_offset0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.saved0_mixer_offset0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "saved1_sel_enc0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.saved1_sel_enc0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "saved1_mixer_offset0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_16nm.saved1_mixer_offset0);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case 4: /* 7nm */
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "feq_train_mode: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.feq_train_mode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "term_lpf_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.term_lpf_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vref_val_mode_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.vref_val_mode_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vga_gain_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.vga_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "hf_gain_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.hf_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mf_pole_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.mf_pole_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mf_gain_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.mf_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lf_pole_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.lf_pole_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lf_gain_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.lf_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dc_gain_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dc_gain_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "term_attn_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.term_attn_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f1_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.f1_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f2_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.f2_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f3_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.f3_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f4_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.f4_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f5_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.f5_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f6_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.f6_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f7_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.f7_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "f8_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.f8_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fm1_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.fm1_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fm2_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.fm2_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fm3_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.fm3_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "eth_override_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.eth_override_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mf_pole: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.mf_pole);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mf_gain: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.mf_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lf_pole: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.lf_pole);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lf_gain: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.lf_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "term_attn_ctrl: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.term_attn_ctrl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "hf_gain: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.hf_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dc_gain: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dc_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "adc_vref_val: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.adc_vref_val);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vga_gain: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.vga_gain);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_fm1: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_fm1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_fm2: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_fm2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_fm3: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_fm3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f4: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_f4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f3: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_f3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f2: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_f2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f1: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_f1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f8: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_f8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f7: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_f7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f6: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_f6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_f5: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.ffe_f5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel3: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef3: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel2: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef2: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel1: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef1: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel7: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef7: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel6: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef6: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel5: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef5: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel4: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef4: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_dsel8: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_dsel8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dffe_coef8: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.dffe_coef8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th1: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th0: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th3: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th2: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th5: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th4: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th7: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th6: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th9: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th9);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th8: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th8);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th11: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th11);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th10: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th10);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th13: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th13);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th12: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th12);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th15: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th15);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th14: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th14);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th17: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th17);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th16: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th16);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th19: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th19);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th18: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th18);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th21: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th21);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "th20: 0x%x\n",
                           reg_data->slrip_reg.page_data.slrip_7nm.th20);
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


ssize_t __slrg_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_slrg_reg reg_data;
    const slrg_data_t        *data = (slrg_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SLRG SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_slrg_reg));

    sxd_params.reg_id = MLXSW_SLRG_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_SLRG_ID, 1);
    reg_data.dev_id = data->dev_data->dev->device_id;

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.slrg_reg.local_port,
                                        reg_data.slrg_reg.lp_msb,
                                        data->local_port);
    reg_data.slrg_reg.pnat = data->pnat;
    reg_data.slrg_reg.lane = data->lane;
    reg_data.slrg_reg.port_type = data->port_type;
    reg_data.slrg_reg.test_mode = data->test_mode;

    err = sx_spice_sxd_access(data->dev_data, &sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __slrg_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

/* file operations */

static const struct file_operations slrg_fops = {
    .read = __slrg_read
};

int __slrg_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_slrg_reg * reg_data)
{
    int      buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->slrg_reg.status);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->slrg_reg.version);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->slrg_reg.local_port, reg_data->slrg_reg.lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->slrg_reg.pnat);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->slrg_reg.lane);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->slrg_reg.port_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "test_mode: 0x%x\n", reg_data->slrg_reg.test_mode);
    buffer += snp_res;
    buffer_size += snp_res;
    switch (reg_data->slrg_reg.version) {
    case 0:
    case 1:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade_lane_speed: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.grade_lane_speed);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade_version: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.grade_version);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_units: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.offset_units);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_units: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.phase_units);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_grade_type: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.height_grade_type);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_grade: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.height_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_dz: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.height_dz);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_dv: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.height_dv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_sigma: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.height_sigma);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_pos: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.height_eo_pos);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_neg: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.height_eo_neg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_grade_type: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.phase_grade_type);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_grade: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.phase_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_pos: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.phase_eo_pos);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_neg: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.phase_eo_neg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_set_tested: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.ffe_set_tested);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "test_errors_per_lane: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_40nm_28nm.test_errors_per_lane);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case 3:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade_lane_speed: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.grade_lane_speed);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade_version: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.grade_version);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "grade: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_pos_up: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.height_eo_pos_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_neg_up: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.height_eo_neg_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_pos_up: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.phase_eo_pos_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_neg_up: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.phase_eo_neg_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_pos_mid: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.height_eo_pos_mid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_neg_mid: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.height_eo_neg_mid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_pos_mid: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.phase_eo_pos_mid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_neg_mid: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.phase_eo_neg_mid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_pos_low: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.height_eo_pos_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "height_eo_neg_low: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.height_eo_neg_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_pos_low: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.phase_eo_pos_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phase_eo_neg_low: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.phase_eo_neg_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_eye_grade: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.mid_eye_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "up_eye_grade: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.up_eye_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dn_eye_grade: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_16nm.dn_eye_grade);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case 4:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fom_measurment: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm.fom_measurment);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fom_mode: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm.fom_mode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "initial_fom: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm.initial_fom);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "last_fom: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm.last_fom);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_eye: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm.upper_eye);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_eye: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm.mid_eye);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_eye: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm.lower_eye);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "status: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.status);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "iterations: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.iterations);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_max: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.upper_max);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_max: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.mid_max);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_max: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.lower_max);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "comp_max: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.comp_max);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_min: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.upper_min);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_min: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.mid_min);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_min: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.lower_min);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "comp_min: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.comp_min);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_std: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.upper_std);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_std: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.mid_std);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_std: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.lower_std);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "comp_std: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.comp_std);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "upper_avg: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.upper_avg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mid_avg: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.mid_avg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "lower_avg: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.lower_avg);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "comp_avg: 0x%x\n",
                           reg_data->slrg_reg.page_data.slrg_7nm_testing.lane_meas_info.comp_avg);
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


static int __slrp_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_slrp_reg * reg_data)
{
    int      buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->slrp_reg.status);
    VALIDATE_ROLLBACK(snp_res);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->slrp_reg.version);
    VALIDATE_ROLLBACK(snp_res);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->slrp_reg.local_port, reg_data->slrp_reg.lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->slrp_reg.pnat);
    VALIDATE_ROLLBACK(snp_res);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->slrp_reg.lane);
    VALIDATE_ROLLBACK(snp_res);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->slrp_reg.port_type);
    VALIDATE_ROLLBACK(snp_res);
    buffer += snp_res;
    buffer_size += snp_res;

    switch (reg_data->slrp_reg.port_type) {
    case 0:
    case 2:
        switch (reg_data->slrp_reg.version) {
        case 0:
        case 1:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ib_sel: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ib_sel);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "dp_sel: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.dp_sel);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "dp90sel: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.dp90sel);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mix90phase: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mix90phase);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap2: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap2);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap3: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap3);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap4: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap4);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap5: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap5);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap6: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap6);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap7: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap7);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap8: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap8);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbias_tap_amp: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixerbias_tap_amp);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap_en: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap_en);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap_offset0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap_offset0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ffe_tap_offset1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ffe_tap_offset1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "slicer_offset0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.slicer_offset0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixer_offset0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixer_offset1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbgn_inp: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixerbgn_inp);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbgn_inn: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixerbgn_inn);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbgn_refp: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixerbgn_refp);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixerbgn_refn: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixerbgn_refn);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_slicer_lctrl_h: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.sel_slicer_lctrl_h);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_slicer_lctrl_l: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.sel_slicer_lctrl_l);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ref_mixer_vreg: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.ref_mixer_vreg);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "slicer_gctrl: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.slicer_gctrl);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "lctrl_input: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.lctrl_input);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_cm1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixer_offset_cm1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "common_mode: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.common_mode);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_cm0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.mixer_offset_cm0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "slicer_offset_cm: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_40nm_28nm.slicer_offset_cm);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case 3:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_up: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.mixer_offset_up);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_down: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.mixer_offset_down);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_enc: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_enc);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "dp_sel: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.dp_sel);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_in_mixer_biasgen_up: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_ref_in_mixer_biasgen_up);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_in_mixer_biasgen_mid: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_ref_in_mixer_biasgen_mid);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_in_mixer_biasgen_down: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_ref_in_mixer_biasgen_down);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_in_mixer_biasgen_eo: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_ref_in_mixer_biasgen_eo);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_out_mixer_biasgen_up: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_ref_out_mixer_biasgen_up);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_out_mixer_biasgen_mid: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_ref_out_mixer_biasgen_mid);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_out_mixer_biasgen_down: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_ref_out_mixer_biasgen_down);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_ref_out_mixer_biasgen_eo: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_ref_out_mixer_biasgen_eo);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_amp_mixer_biasgen_up: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_amp_mixer_biasgen_up);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_amp_mixer_biasgen_mid: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_amp_mixer_biasgen_mid);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_amp_mixer_biasgen_down: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_amp_mixer_biasgen_down);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_amp_mixer_biasgen_eo: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_amp_mixer_biasgen_eo);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "mixer_offset_eye_scan: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.mixer_offset_eye_scan);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "gctrl_bin_bgn0_n: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.gctrl_bin_bgn0_n);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "gctrl_bin_bgn0_p: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.gctrl_bin_bgn0_p);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "gctrl_bin_bgn1_n: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.gctrl_bin_bgn1_n);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "gctrl_bin_bgn1_p: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.gctrl_bin_bgn1_p);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_digital_gctrl: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_digital_gctrl);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias2ctle: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_bias2ctle);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "selgc_ref_op0_alev_ctle: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.selgc_ref_op0_alev_ctle);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "selgc_ref_op1_alev_ctle: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.selgc_ref_op1_alev_ctle);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_bias_en_0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_bias_en_1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_2: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_bias_en_2);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_3: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_bias_en_3);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_4: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_bias_en_4);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_5: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_bias_en_5);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_bias_en_6: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_bias_en_6);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrln_en_0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrln_en_1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_2: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrln_en_2);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_3: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrln_en_3);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_4: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrln_en_4);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_5: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrln_en_5);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrln_en_6: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrln_en_6);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrlp_en_0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrlp_en_1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_2: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrlp_en_2);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_3: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrlp_en_3);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_4: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrlp_en_4);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_5: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrlp_en_5);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "sel_gctrlp_en_6: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.sel_gctrlp_en_6);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "crnt_bgn_offset_p1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.crnt_bgn_offset_p1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "crnt_bgn_offset_n1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.crnt_bgn_offset_n1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "crnt_bgn_offset_p0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.crnt_bgn_offset_p0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "crnt_bgn_offset_n0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_16nm.crnt_bgn_offset_n0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case 4:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_recording_admin: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_recording_admin);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_recording_status: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_recording_status);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_rocording_lanes: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_rocording_lanes);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "edge_vos_ccal_en: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.edge_vos_ccal_en);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_gain_shift_auto: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gain_shift_auto);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ccal_mode: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.ccal_mode);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ctle_override_ctrl: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.ctle_override_ctrl);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "vga_override_ctrl: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.vga_override_ctrl);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_vos_override_ctrl: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos_override_ctrl);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_gain_override_ctrl: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gain_override_ctrl);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos_override_ctrl: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos_override_ctrl);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "cal_error_cnt: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.cal_error_cnt);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ccal_state: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.ccal_state);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ccal_op: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.ccal_op);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res =
                snprintf(buffer,
                         buffer_length - buffer_size,
                         "phos: 0x%x\n",
                         reg_data->slrp_reg.page_data.slrp_7nm.phos);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "vga_vos1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.vga_vos1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "vga_vos0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.vga_vos0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "ctle_vos0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.ctle_vos0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_vos: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[0],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[1],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[2],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[3],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[4],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[5],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[6],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[7],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[8],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[9],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[10],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[11],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[12],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[13],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[14],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[15],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[16],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[17],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[18],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[19],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[20],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[21],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[22],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[23],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[24],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[25],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[26],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[27],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[28],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[29],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[30],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[31],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[32],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[33],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[34],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[35],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[36],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[37],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[38],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[39],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[40],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[41],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[42],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[43],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[44],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[45],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[46],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[47],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[48],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[49],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[50],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[51],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[52],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[53],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[54],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[55],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[56],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[57],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[58],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[59],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[60],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[61],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[62],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_vos[63]);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "adc_gos: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[0],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[1],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[2],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[3],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[4],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[5],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[6],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[7],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[8],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[9],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[10],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[11],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[12],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[13],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[14],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[15],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[16],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[17],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[18],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[19],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[20],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[21],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[22],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[23],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[24],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[25],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[26],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[27],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[28],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[29],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[30],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[31],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[32],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[33],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[34],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[35],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[36],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[37],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[38],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[39],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[40],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[41],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[42],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[43],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[44],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[45],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[46],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[47],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[48],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[49],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[50],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[51],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[52],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[53],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[54],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[55],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[56],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[57],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[58],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[59],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[60],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[61],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[62],
                               reg_data->slrp_reg.page_data.slrp_7nm.adc_gos[63]);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos3: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos3);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos2: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos2);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos1: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos1);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos0: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos0);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos7: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos7);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos6: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos6);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos5: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos5);
            VALIDATE_ROLLBACK(snp_res);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "phos4: 0x%x\n",
                               reg_data->slrp_reg.page_data.slrp_7nm.phos4);
            VALIDATE_ROLLBACK(snp_res);
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
                           reg_data->slrp_reg.page_data.slrp_gearbox.ffe_tap_index);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_sub_channel: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_gearbox.ffe_sub_channel);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "snr_en: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_gearbox.snr_en);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dsp_mode: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_gearbox.dsp_mode);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "afe_trim: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_gearbox.afe_trim);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ctle: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_gearbox.ctle);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "raw_snr_value: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_gearbox.raw_snr_value);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "db_snr_value: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_gearbox.db_snr_value);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ffe_tap_value: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_gearbox.ffe_tap_value);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case 4:
    case 5:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mixer00: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.mixer00);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mixer90: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.mixer90);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "termination: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.termination);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "neg_cap_up: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.neg_cap_up);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "neg_cap_mid: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.neg_cap_mid);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "neg_cap_dn: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.neg_cap_dn);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_polarity_up: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_coarse_polarity_up);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_polarity_mid: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_coarse_polarity_mid);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_polarity_dn: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_coarse_polarity_dn);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_polarity_up: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_fine_polarity_up);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_polarity_mid: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_fine_polarity_mid);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_polarity_dn: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_fine_polarity_dn);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "amp_vga: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.amp_vga);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "amp_vga_last_stage: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.amp_vga_last_stage);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_up: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_coarse_up);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_mid: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_coarse_mid);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_coarse_dn: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_coarse_dn);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_up: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_fine_up);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_mid: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_fine_mid);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "offset_fine_dn: 0x%x\n",
                           reg_data->slrp_reg.page_data.slrp_usr.offset_fine_dn);
        VALIDATE_ROLLBACK(snp_res);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        break;
    }

    return buffer_size;
}

static ssize_t __slrp_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_slrp_reg reg_data;
    const slrp_data_t        *data = (slrp_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SLRP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_slrp_reg));

    sxd_params.reg_id = MLXSW_SLRP_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_SLRP_ID, 1);
    reg_data.dev_id = data->dev_data->dev->device_id;

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.slrp_reg.local_port,
                                        reg_data.slrp_reg.lp_msb,
                                        data->local_port);
    reg_data.slrp_reg.pnat = data->pnat;
    reg_data.slrp_reg.lane = data->lane;
    reg_data.slrp_reg.port_type = data->port_type;


    err = sx_spice_sxd_access(data->dev_data, &sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __slrp_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

static const struct file_operations slrp_fops = {
    .read = __slrp_read
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
