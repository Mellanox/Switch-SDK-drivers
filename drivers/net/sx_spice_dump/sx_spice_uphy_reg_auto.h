/*
 * Copyright © 2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#ifndef SX_SPICE_UPHY_REG_AUTO_H_
#define SX_SPICE_UPHY_REG_AUTO_H_

#include "sx_spice_uphy_reg_infra.h"

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 *  Macros
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/
struct uphy_reg_cln_cfg_id_ctrl {
    uint8_t    bkv_minor;
    uint8_t    bkv_major;
    uint8_t    variant;
    uint8_t    protocol;
};

struct uphy_reg_pllc_dco_coarse_stat_id0 {
    uint8_t    cal_abort_sticky;
    uint8_t    cal_abort;
    uint8_t    cal_valid_sticky;
    uint8_t    dco_coarse;
};

struct uphy_reg_pllc_dco_coarse_stat_id1 {
    uint8_t    cal_abort_sticky;
    uint8_t    cal_abort;
    uint8_t    cal_valid_sticky;
    uint8_t    dco_coarse;
};

struct uphy_reg_pllc_dco_coarse_stat_id2 {
    uint8_t    cal_abort_sticky;
    uint8_t    cal_abort;
    uint8_t    cal_valid_sticky;
    uint8_t    dco_coarse;
};

struct uphy_reg_pllc_dlf_accu_stat0 {
    uint16_t    accu1_out;
};

struct uphy_reg_pllc_dlf_accu_stat1 {
    uint16_t    accu2_out;
};

struct uphy_reg_mgmt_bgap_fuse_ctrl {
    uint8_t    speedo_valid;
    uint8_t    cvb_trim_valid;
    uint8_t    bg_trim_valid;
    uint8_t    speedo;
    uint8_t    cvb_trim;
    uint8_t    bg_trim;
};

struct uphy_reg_rcal_stat2 {
    uint8_t    clndln_rcal_val;
    uint8_t    clndln_rcal_tx_p_val;
    uint8_t    clndln_rcal_tx_n_val;
    uint8_t    lmx_rcal_val;
};

struct uphy_reg_dln_cfg_tx_id_ctrl {
    uint8_t    bkv_minor;
    uint8_t    bkv_major;
    uint8_t    variant;
    uint8_t    protocol;
};

struct uphy_reg_dln_cfg_rx_id_ctrl {
    uint8_t    bkv_minor;
    uint8_t    bkv_major;
    uint8_t    variant;
    uint8_t    protocol;
};

struct uphy_reg_dln_master_ctrl {
    uint8_t    fast_sim;
    uint8_t    bist_sync_rd_mode;
    uint8_t    ae_sync_rd_mode;
    uint8_t    rx_sync_rd_mode;
    uint8_t    txcal_adc_sync_rd_mode;
    uint8_t    txpll_fll_sync_rd_mode;
    uint8_t    mgmt_sync_rd_mode;
};

struct uphy_reg_dln_clk_ctrl {
    uint8_t    pdes_clk_mux_async_mode;
    uint8_t    pdes_clk_mux_clk_sel_ovrd;
    uint8_t    pdes_clk_mux_clk_sel;
    uint8_t    fed_tx_clk_mux_async_mode;
    uint8_t    pll_clk_en_ovrd;
    uint8_t    mgmt_clk_en_ovrd;
};

struct uphy_reg_dln_irq_ovrd {
    uint8_t    nop_rs_unf_error_ovrd;
    uint8_t    nop_rs_ovf_error_ovrd;
    uint8_t    nop_ds_unf_error_ovrd;
    uint8_t    nop_ds_ovf_error_ovrd;
    uint8_t    peq_adc_overload_ovrd;
    uint8_t    feq_adc_overload_ovrd;
    uint8_t    cdr_error_ovrd;
    uint8_t    imem_chksm_error_ovrd;
};

struct uphy_reg_dln_irq_clear {
    uint8_t    nop_rsunf_error_clear;
    uint8_t    nop_rsovf_error_clear;
    uint8_t    nop_dsunf_error_clear;
    uint8_t    nop_dsovf_error_clear;
    uint8_t    peq_adc_overload_clear;
    uint8_t    feq_adc_overload_clear;
    uint8_t    cdr_error_clear;
    uint8_t    imem_chksm_error_clear;
};

struct uphy_reg_dln_irq_mask {
    uint8_t    nop_rsunf_error_mask;
    uint8_t    nop_rsovf_error_mask;
    uint8_t    nop_dsunf_error_mask;
    uint8_t    nop_dsovf_error_mask;
    uint8_t    peq_adc_overload_mask;
    uint8_t    feq_adc_overload_mask;
    uint8_t    cdr_error_mask;
    uint8_t    imem_chksm_error_mask;
};

struct uphy_reg_dln_irq_stat {
    uint8_t    nop_rsunf_error;
    uint8_t    nop_rsovf_error;
    uint8_t    nop_dsunf_error;
    uint8_t    nop_dsovf_error;
    uint8_t    peq_adc_overload;
    uint8_t    feq_adc_overload;
    uint8_t    cdr_error;
    uint8_t    imem_chksm_error;
};

struct uphy_reg_mgmt_dln_misc_ctrl {
    uint8_t    misc_out;
    uint8_t    pwr_valid_ovrd;
    uint8_t    hvdddet_ctrl;
};

struct uphy_reg_mgmt_dln_fuse_ctrl {
    uint8_t    speedo;
};

struct uphy_reg_mgmt_dln_misc_stat {
    uint8_t    pdes_clk_mux_switch_status;
    uint8_t    tx_fifo_clk_mux_switch_status;
    uint8_t    misc_ctrl;
};

struct uphy_reg_mgmt_dln_cln_stat {
    uint8_t    pll_clk_en_req;
    uint8_t    mgmt_clk_en_req;
    uint8_t    pll_b_clk_valid;
    uint8_t    pll_a_clk_valid;
    uint8_t    bg_valid;
};

struct uphy_reg_mgmt_dln_cln_rcal_stat {
    uint8_t    rcal_tx_p_val;
    uint8_t    rcal_tx_n_val;
    uint8_t    rcal_val;
};

struct uphy_reg_mgmt_dln_intf_stat {
    uint8_t    rx_rate_id;
    uint8_t    tx_rate_id;
    uint8_t    rx_pstate;
    uint8_t    tx_pstate;
};

struct uphy_reg_mgmt_dln_pss_stat {
    uint8_t    rx_pll_clk_valid_error_flag;
    uint8_t    rx_pss_state;
    uint8_t    tx_pll_clk_valid_error_flag;
    uint8_t    tx_pss_state;
};

struct uphy_reg_mgmt_rcal_ctrl {
    uint8_t    rx_rcal_ovrd;
    uint8_t    tx_rcal_ovrd;
    uint8_t    rx_rcal_val;
    uint8_t    tx_rcal_p_val;
    uint8_t    tx_rcal_n_val;
};

struct uphy_reg_mgmt_rcal_stat {
    uint8_t    rx_term_rcal_val;
    uint8_t    rx_rcal_val;
    uint8_t    tx_cal_p_val;
    uint8_t    tx_cal_n_val;
};

struct uphy_reg_mgmt_tx_aeintf_stat {
    uint8_t    tx_cal_idle;
    uint8_t    tx_dco_cal_idle;
    uint8_t    tx_pss_ready;
};

struct uphy_reg_mgmt_tx_aeintf_dcocal_stat {
    uint8_t    state;
    uint8_t    idle;
    uint8_t    abort_req;
    uint8_t    abort_en;
    uint8_t    done;
    uint8_t    ack;
    uint8_t    req;
    uint8_t    en;
};

struct uphy_reg_mgmt_tx_aeintf_txcal_stat {
    uint8_t    state;
    uint8_t    idle;
    uint8_t    abort_req;
    uint8_t    abort_en;
    uint8_t    done;
    uint8_t    ack;
    uint8_t    req;
    uint8_t    en;
};

struct uphy_reg_mgmt_rx_aeintf_stat {
    uint8_t    margin_idle;
    uint8_t    eom_idle;
    uint8_t    eq_idle;
    uint8_t    cal_idle;
    uint8_t    rxinit_idle;
    uint8_t    rx_cdr_en;
    uint8_t    rx_data_en;
    uint8_t    rx_pss_ready;
};

struct uphy_reg_mgmt_rx_aeintf_rxinit_stat {
    uint8_t    state;
    uint8_t    idle;
    uint8_t    abort_req;
    uint8_t    abort_en;
    uint8_t    done;
    uint8_t    ack;
    uint8_t    req;
    uint8_t    en;
};

struct uphy_reg_mgmt_rx_aeintf_cal_stat {
    uint8_t    state;
    uint8_t    idle;
    uint8_t    abort_req;
    uint8_t    abort_en;
    uint8_t    done;
    uint8_t    ack;
    uint8_t    req;
    uint8_t    en;
};

struct uphy_reg_mgmt_rx_aeintf_eq_stat {
    uint8_t    state;
    uint8_t    idle;
    uint8_t    abort_req;
    uint8_t    abort_en;
    uint8_t    done;
    uint8_t    ack;
    uint8_t    req;
    uint8_t    en;
};

struct uphy_reg_mgmt_rx_aeintf_eom_stat {
    uint8_t    state;
    uint8_t    idle;
    uint8_t    abort_req;
    uint8_t    abort_en;
    uint8_t    done;
    uint8_t    ack;
    uint8_t    req;
    uint8_t    en;
};

struct uphy_reg_mgmt_rx_aeintf_margin_stat {
    uint8_t    state;
    uint8_t    idle;
    uint8_t    abort_req;
    uint8_t    abort_en;
    uint8_t    done;
    uint8_t    ack;
    uint8_t    req;
    uint8_t    en;
};

struct uphy_reg_mgmt_tx_ctrl {
    uint8_t    dac_pattern_en;
    uint8_t    dac_pattern_en_ovrd;
    uint8_t    tsync_rstb;
    uint8_t    tsync_rstb_ovrd;
    uint8_t    tdata_ready;
    uint8_t    tdata_ready_ovrd;
    uint8_t    tsync_en;
    uint8_t    tsync_en_ovrd;
    uint8_t    tsync_en_mode;
    uint8_t    xdigclk_en;
    uint8_t    txclkref_en;
    uint8_t    disable_mode;
    uint8_t    term_mode;
    uint8_t    cmh_mode;
};

struct uphy_reg_mgmt_rx_ctrl {
    uint8_t    tsense_ovrd_en;
    uint8_t    tsense_ovrd_val;
    uint8_t    rx_xdigclk_en;
    uint8_t    pdes_data_clamp_mode;
    uint8_t    pdes_clk_switch_mode;
    uint8_t    ac_mode;
};

struct uphy_reg_mgmt_tx_rate_ctrl0_id0 {
    uint8_t    tx_clkbuf_id;
    uint8_t    tx_pll_id;
    uint8_t    tx_clk_id;
    uint8_t    iqdcc_cal_en;
    uint8_t    txpll_bypass_en;
    uint8_t    txpll_bypass_postdiv;
    uint8_t    xdigclk_ctrl;
    uint8_t    txclkref_ctrl;
    uint8_t    tx_rate_pdiv;
    uint8_t    modulation;
};

struct uphy_reg_mgmt_tx_rate_ctrl0_id1 {
    uint8_t    tx_clkbuf_id;
    uint8_t    tx_pll_id;
    uint8_t    tx_clk_id;
    uint8_t    iqdcc_cal_en;
    uint8_t    txpll_bypass_en;
    uint8_t    txpll_bypass_postdiv;
    uint8_t    xdigclk_ctrl;
    uint8_t    txclkref_ctrl;
    uint8_t    tx_rate_pdiv;
    uint8_t    modulation;
};

struct uphy_reg_mgmt_tx_rate_ctrl0_id2 {
    uint8_t    tx_clkbuf_id;
    uint8_t    tx_pll_id;
    uint8_t    tx_clk_id;
    uint8_t    iqdcc_cal_en;
    uint8_t    txpll_bypass_en;
    uint8_t    txpll_bypass_postdiv;
    uint8_t    xdigclk_ctrl;
    uint8_t    txclkref_ctrl;
    uint8_t    tx_rate_pdiv;
    uint8_t    modulation;
};

struct uphy_reg_mgmt_tx_rate_ctrl0_id3 {
    uint8_t    tx_clkbuf_id;
    uint8_t    tx_pll_id;
    uint8_t    tx_clk_id;
    uint8_t    iqdcc_cal_en;
    uint8_t    txpll_bypass_en;
    uint8_t    txpll_bypass_postdiv;
    uint8_t    xdigclk_ctrl;
    uint8_t    txclkref_ctrl;
    uint8_t    tx_rate_pdiv;
    uint8_t    modulation;
};

struct uphy_reg_mgmt_tx_rate_ctrl0_id4 {
    uint8_t    tx_clkbuf_id;
    uint8_t    tx_pll_id;
    uint8_t    tx_clk_id;
    uint8_t    iqdcc_cal_en;
    uint8_t    txpll_bypass_en;
    uint8_t    txpll_bypass_postdiv;
    uint8_t    xdigclk_ctrl;
    uint8_t    txclkref_ctrl;
    uint8_t    tx_rate_pdiv;
    uint8_t    modulation;
};

struct uphy_reg_mgmt_tx_rate_ctrl1_id0 {
    uint8_t    tx_fifo_wptr_ctrl;
    uint8_t    sync_dly_sel;
    uint8_t    tclk_dly;
    uint8_t    dac_predrv_eq_en;
    uint8_t    ser_clk_sel;
    uint8_t    ser_flush_time;
};

struct uphy_reg_mgmt_tx_rate_ctrl1_id1 {
    uint8_t    tx_fifo_wptr_ctrl;
    uint8_t    sync_dly_sel;
    uint8_t    tclk_dly;
    uint8_t    dac_predrv_eq_en;
    uint8_t    ser_clk_sel;
    uint8_t    ser_flush_time;
};

struct uphy_reg_mgmt_tx_rate_ctrl1_id2 {
    uint8_t    tx_fifo_wptr_ctrl;
    uint8_t    sync_dly_sel;
    uint8_t    tclk_dly;
    uint8_t    dac_predrv_eq_en;
    uint8_t    ser_clk_sel;
    uint8_t    ser_flush_time;
};

struct uphy_reg_mgmt_tx_rate_ctrl1_id3 {
    uint8_t    tx_fifo_wptr_ctrl;
    uint8_t    sync_dly_sel;
    uint8_t    tclk_dly;
    uint8_t    dac_predrv_eq_en;
    uint8_t    ser_clk_sel;
    uint8_t    ser_flush_time;
};

struct uphy_reg_mgmt_tx_rate_ctrl1_id4 {
    uint8_t    tx_fifo_wptr_ctrl;
    uint8_t    sync_dly_sel;
    uint8_t    tclk_dly;
    uint8_t    dac_predrv_eq_en;
    uint8_t    ser_clk_sel;
    uint8_t    ser_flush_time;
};

struct uphy_reg_mgmt_rx_rate_ctrl0_id0 {
    uint8_t    adc_res;
    uint8_t    mlsd_mode;
    uint8_t    cdrpd;
    uint8_t    modulation;
    uint8_t    eqtarget;
    uint8_t    rx_rate_pdiv;
    uint8_t    rank2_way;
    uint8_t    rx_nway;
};

struct uphy_reg_mgmt_rx_rate_ctrl0_id1 {
    uint8_t    adc_res;
    uint8_t    mlsd_mode;
    uint8_t    cdrpd;
    uint8_t    modulation;
    uint8_t    eqtarget;
    uint8_t    rx_rate_pdiv;
    uint8_t    rank2_way;
    uint8_t    rx_nway;
};

struct uphy_reg_mgmt_rx_rate_ctrl0_id2 {
    uint8_t    adc_res;
    uint8_t    mlsd_mode;
    uint8_t    cdrpd;
    uint8_t    modulation;
    uint8_t    eqtarget;
    uint8_t    rx_rate_pdiv;
    uint8_t    rank2_way;
    uint8_t    rx_nway;
};

struct uphy_reg_mgmt_rx_rate_ctrl0_id3 {
    uint8_t    adc_res;
    uint8_t    mlsd_mode;
    uint8_t    cdrpd;
    uint8_t    modulation;
    uint8_t    eqtarget;
    uint8_t    rx_rate_pdiv;
    uint8_t    rank2_way;
    uint8_t    rx_nway;
};

struct uphy_reg_mgmt_rx_rate_ctrl0_id4 {
    uint8_t    adc_res;
    uint8_t    mlsd_mode;
    uint8_t    cdrpd;
    uint8_t    modulation;
    uint8_t    eqtarget;
    uint8_t    rx_rate_pdiv;
    uint8_t    rank2_way;
    uint8_t    rx_nway;
};

struct uphy_reg_mgmt_rx_rate_ctrl1_id0 {
    uint8_t    des_xdigclk_en;
    uint8_t    margin_aeintf_en;
    uint8_t    rx_cdr_misc_id;
    uint8_t    rx_cdr_fll_id;
    uint8_t    rx_clk_id;
};

struct uphy_reg_mgmt_rx_rate_ctrl1_id1 {
    uint8_t    des_xdigclk_en;
    uint8_t    margin_aeintf_en;
    uint8_t    rx_cdr_misc_id;
    uint8_t    rx_cdr_fll_id;
    uint8_t    rx_clk_id;
};

struct uphy_reg_mgmt_rx_rate_ctrl1_id2 {
    uint8_t    des_xdigclk_en;
    uint8_t    margin_aeintf_en;
    uint8_t    rx_cdr_misc_id;
    uint8_t    rx_cdr_fll_id;
    uint8_t    rx_clk_id;
};

struct uphy_reg_mgmt_rx_rate_ctrl1_id3 {
    uint8_t    des_xdigclk_en;
    uint8_t    margin_aeintf_en;
    uint8_t    rx_cdr_misc_id;
    uint8_t    rx_cdr_fll_id;
    uint8_t    rx_clk_id;
};

struct uphy_reg_mgmt_rx_rate_ctrl1_id4 {
    uint8_t    des_xdigclk_en;
    uint8_t    margin_aeintf_en;
    uint8_t    rx_cdr_misc_id;
    uint8_t    rx_cdr_fll_id;
    uint8_t    rx_clk_id;
};

struct uphy_reg_tx_enc_ctrl {
    uint8_t    pam4_2b_lut;
};

struct uphy_reg_rx_dec_ctrl {
    uint8_t    pam4_2b_lut;
    uint8_t    pam4_dme_lut;
    uint8_t    pam2_pr1_inv;
    uint8_t    pam2_pr0_inv;
    uint8_t    pam2_dme_inv;
    uint8_t    rx_dec_infer_ckg_en;
};

struct uphy_reg_mgmt_tx_timer_ctrl0 {
    uint8_t    entry120_time;
    uint8_t    entry110_time;
    uint8_t    entry101_time;
    uint8_t    entry100_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl1 {
    uint8_t    entry210_time;
    uint8_t    entry200_time;
    uint8_t    entry140_time;
    uint8_t    entry130_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl2 {
    uint8_t    entry250_time;
    uint8_t    entry240_time;
    uint8_t    entry230_time;
    uint8_t    entry220_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl3 {
    uint8_t    entry310_time;
    uint8_t    entry302_time;
    uint8_t    entry301_time;
    uint8_t    entry300_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl4 {
    uint8_t    entry400_time;
    uint8_t    entry321_time;
    uint8_t    entry320_time;
    uint8_t    entry311_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl5 {
    uint8_t    entry411_time;
    uint8_t    entry410_time;
    uint8_t    entry402_time;
    uint8_t    entry401_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl6 {
    uint8_t    entry500_time;
    uint8_t    entry440_time;
    uint8_t    entry430_time;
    uint8_t    entry420_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl7 {
    uint8_t    exit200_time;
    uint8_t    exit100_time;
    uint8_t    entry520_time;
    uint8_t    entry510_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl8 {
    uint8_t    exit400_time;
    uint8_t    exit310_time;
    uint8_t    exit300_time;
    uint8_t    exit210_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl9 {
    uint8_t    exit600_time;
    uint8_t    exit510_time;
    uint8_t    exit500_time;
    uint8_t    exit410_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl10 {
    uint8_t    exit730_time;
    uint8_t    exit720_time;
    uint8_t    exit710_time;
    uint8_t    exit700_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl11_id0 {
    uint8_t    txpll_nocal_lock_time;
    uint8_t    exit740_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl11_id1 {
    uint8_t    txpll_nocal_lock_time;
    uint8_t    exit740_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl11_id2 {
    uint8_t    txpll_nocal_lock_time;
    uint8_t    exit740_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl11_id3 {
    uint8_t    txpll_nocal_lock_time;
    uint8_t    exit740_time;
};

struct uphy_reg_mgmt_tx_timer_ctrl11_id4 {
    uint8_t    txpll_nocal_lock_time;
    uint8_t    exit740_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl0 {
    uint8_t    entry200_time;
    uint8_t    entry120_time;
    uint8_t    entry110_time;
    uint8_t    entry100_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl1 {
    uint8_t    entry400_time;
    uint8_t    entry300_time;
    uint8_t    entry220_time;
    uint8_t    entry210_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl2 {
    uint8_t    entry600_time;
    uint8_t    entry510_time;
    uint8_t    entry500_time;
    uint8_t    entry410_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl3 {
    uint8_t    entry620_time;
    uint8_t    entry611_time;
    uint8_t    entry610_time;
    uint8_t    entry601_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl4 {
    uint8_t    entry720_time;
    uint8_t    entry710_time;
    uint8_t    entry700_time;
    uint8_t    entry621_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl5 {
    uint8_t    entry900_time;
    uint8_t    entry810_time;
    uint8_t    entry800_time;
    uint8_t    entry730_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl6 {
    uint8_t    exit100_time;
    uint8_t    entry930_time;
    uint8_t    entry920_time;
    uint8_t    entry910_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl7 {
    uint8_t    exit230_time;
    uint8_t    exit220_time;
    uint8_t    exit210_time;
    uint8_t    exit200_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl8 {
    uint8_t    exit320_time;
    uint8_t    exit310_time;
    uint8_t    exit301_time;
    uint8_t    exit300_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl9 {
    uint8_t    exit410_time;
    uint8_t    exit400_time;
    uint8_t    exit330_time;
    uint8_t    exit321_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl10 {
    uint8_t    exit600_time;
    uint8_t    exit500_time;
    uint8_t    exit412_time;
    uint8_t    exit411_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl11 {
    uint8_t    exit810_time;
    uint8_t    exit801_time;
    uint8_t    exit800_time;
    uint8_t    exit700_time;
};

struct uphy_reg_mgmt_rx_timer_ctrl12 {
    uint8_t    exit900_time;
    uint8_t    exit820_time;
};

struct uphy_reg_mgmt_tx_pss_ctrl {
    uint8_t    pss_timer;
    uint8_t    pss_ovrd;
    uint8_t    pss_state;
};

struct uphy_reg_mgmt_rx_pss_ctrl {
    uint8_t    pss_timer;
    uint8_t    pss_ovrd;
    uint8_t    pss_state;
};

struct uphy_reg_mgmt_pss_valid_ctrl {
    uint8_t    rx_dco_vld_mask;
    uint8_t    tx_iqdcc_vld_mask;
    uint8_t    tx_dco_vld_mask;
    uint8_t    tx_p0p3p0_dco_nocal_ctrl;
    uint8_t    tx_p0p2p0_dco_nocal_ctrl;
    uint8_t    rx_clkrcv_ls_en_clk_error_ovrd;
    uint8_t    tx_drv_clk_ls_en_clk_error_ovrd;
    uint8_t    tx_ser_clk_ls_en_clk_error_ovrd;
    uint8_t    tx_clkrcv_ls_en_clk_error_ovrd;
};

struct uphy_reg_mgmt_tx_rvdd_ctrl0 {
    uint8_t    data_rvdd_ctrl;
    uint8_t    hsclk_rvdd_ctrl;
    uint8_t    lsclk_rvdd_ctrl;
};

struct uphy_reg_mgmt_tx_rvdd_ctrl1 {
    uint8_t    data_rvdd_vref_sel;
    uint8_t    hsclk_rvdd_vref_sel;
    uint8_t    lsclk_rvdd_vref_sel;
    uint8_t    data_rvdd_leaker_mode;
    uint8_t    hsclk_rvdd_leaker_mode;
    uint8_t    lsclk_rvdd_leaker_mode;
};

struct uphy_reg_mgmt_tx_rvdd_ctrl2 {
    uint8_t    data_rvdd_diode_clamp_mode;
    uint8_t    hsclk_rvdd_diode_clamp_mode;
    uint8_t    lsclk_rvdd_diode_clamp_mode;
    uint8_t    data_rvdd_rz_ctrl;
    uint8_t    data_rvdd_gm2_ctrl;
    uint8_t    hsclk_rvdd_rz_ctrl;
    uint8_t    hsclk_rvdd_gm2_ctrl;
    uint8_t    lsclk_rvdd_rz_ctrl;
    uint8_t    lsclk_rvdd_gm2_ctrl;
};

struct uphy_reg_mgmt_rx_rvdd_ctrl0 {
    uint8_t    data_rvdd_vref_sel;
    uint8_t    clk_rvdd_vref_sel;
    uint8_t    data_rvdd_leaker_mode;
    uint8_t    clk_rvdd_leaker_mode;
    uint8_t    data_rvdd_ctrl;
    uint8_t    clk_rvdd_ctrl;
};

struct uphy_reg_mgmt_rx_rvdd_ctrl1 {
    uint8_t    data_rvdd_diode_clamp_mode;
    uint8_t    clk_rvdd_diode_clamp_mode;
    uint8_t    data_rvdd_rz_ctrl;
    uint8_t    data_rvdd_gm2_ctrl;
    uint8_t    clk_rvdd_rz_ctrl;
    uint8_t    clk_rvdd_gm2_ctrl;
};

struct uphy_reg_mgmt_tx_clkrcv_ctrl_id0 {
    uint8_t    clkrcv_ac_bypass;
    uint8_t    clkrcv_bias_i_ctrl;
    uint8_t    clkrcv_ls_r_ctrl;
    uint8_t    clkrcv_tia_r_ctrl;
    uint8_t    clkrcv_i_ctrl;
};

struct uphy_reg_mgmt_tx_clkrcv_ctrl_id1 {
    uint8_t    clkrcv_ac_bypass;
    uint8_t    clkrcv_bias_i_ctrl;
    uint8_t    clkrcv_ls_r_ctrl;
    uint8_t    clkrcv_tia_r_ctrl;
    uint8_t    clkrcv_i_ctrl;
};

struct uphy_reg_mgmt_rx_clkrcv_ctrl_id0 {
    uint8_t    clkrcv_ac_bypass;
    uint8_t    clkrcv_bias_i_ctrl;
    uint8_t    clkrcv_ls_r_ctrl;
    uint8_t    clkrcv_tia_r_ctrl;
    uint8_t    clkrcv_i_ctrl;
};

struct uphy_reg_mgmt_rx_clkrcv_ctrl_id1 {
    uint8_t    clkrcv_ac_bypass;
    uint8_t    clkrcv_bias_i_ctrl;
    uint8_t    clkrcv_ls_r_ctrl;
    uint8_t    clkrcv_tia_r_ctrl;
    uint8_t    clkrcv_i_ctrl;
};

struct uphy_reg_mgmt_tx_fifo_ctrl {
    uint8_t    fifo_chk_en;
    uint8_t    fifo_skip_wptr;
    uint8_t    fifo_err_hold;
    uint8_t    fifo_err_clr;
};

struct uphy_reg_mgmt_tx_cal_drv_ctrl {
    uint8_t    z_pcal_offset;
    uint8_t    z_ncal_offset;
    uint8_t    z_pcal;
    uint8_t    z_ncal;
};

struct uphy_reg_mgmt_tx_bias_ctrl {
    uint8_t    cgm_ready_ovrd;
    uint8_t    bg_ready_ovrd;
    uint8_t    bias_ready_ovrd;
    uint8_t    cgm_start_mode;
    uint8_t    ptat_slope_en;
    uint8_t    ptat_slope_ctrl;
    uint8_t    bg_i_ctrl;
    uint8_t    ptat_i_ctrl;
};

struct uphy_reg_mgmt_tx_misc_ctrl {
    uint16_t    misc_ctrl;
};

struct uphy_reg_mgmt_tx_stat {
    uint8_t    fifo_latency;
    uint8_t    fifo_err;
    uint8_t    rdet_status;
};

struct uphy_reg_mgmt_txpll_ctrl_id0 {
    uint8_t    postdiv;
    uint8_t    ndiv;
    uint8_t    mdiv;
};

struct uphy_reg_mgmt_txpll_ctrl_id1 {
    uint8_t    postdiv;
    uint8_t    ndiv;
    uint8_t    mdiv;
};

struct uphy_reg_mgmt_txpll_dco_ctrl_id0 {
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_mgmt_txpll_dco_ctrl_id1 {
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_mgmt_txpll_filter_ctrl0_id0 {
    uint8_t    pfd_ctrl;
    uint8_t    refsel;
    uint8_t    cp_ctrl;
    uint8_t    lpf_c_ctrl;
    uint8_t    lpf_r_ctrl;
};

struct uphy_reg_mgmt_txpll_filter_ctrl0_id1 {
    uint8_t    pfd_ctrl;
    uint8_t    refsel;
    uint8_t    cp_ctrl;
    uint8_t    lpf_c_ctrl;
    uint8_t    lpf_r_ctrl;
};

struct uphy_reg_mgmt_txpll_filter_ctrl1_id0 {
    uint8_t    preset_ctrl;
    uint8_t    slowloop_fastprecharge_sel;
    uint8_t    slowloop_c_ctrl;
    uint8_t    slowloop_r_ctrl;
};

struct uphy_reg_mgmt_txpll_filter_ctrl1_id1 {
    uint8_t    preset_ctrl;
    uint8_t    slowloop_fastprecharge_sel;
    uint8_t    slowloop_c_ctrl;
    uint8_t    slowloop_r_ctrl;
};

struct uphy_reg_mgmt_txpll_ro_ctrl0_id0 {
    uint8_t    ro_drv_xcouple_ctrl;
    uint8_t    ro_drv_ctrl;
};

struct uphy_reg_mgmt_txpll_ro_ctrl0_id1 {
    uint8_t    ro_drv_xcouple_ctrl;
    uint8_t    ro_drv_ctrl;
};

struct uphy_reg_mgmt_txpll_ro_ctrl1_id0 {
    uint8_t    ro_c_ctrl;
    uint8_t    ro_i_ctrl;
    uint8_t    ro_currentsrc_ctrl;
    uint8_t    ro_psrc_diode_ctrl;
};

struct uphy_reg_mgmt_txpll_ro_ctrl1_id1 {
    uint8_t    ro_c_ctrl;
    uint8_t    ro_i_ctrl;
    uint8_t    ro_currentsrc_ctrl;
    uint8_t    ro_psrc_diode_ctrl;
};

struct uphy_reg_mgmt_txpll_ro_ctrl2_id0 {
    uint8_t    clkgate_mode;
    uint8_t    ro_start_mode;
    uint8_t    slowloop_kvco_ctrl;
    uint8_t    ro_kvco_ctrl;
};

struct uphy_reg_mgmt_txpll_ro_ctrl2_id1 {
    uint8_t    clkgate_mode;
    uint8_t    ro_start_mode;
    uint8_t    slowloop_kvco_ctrl;
    uint8_t    ro_kvco_ctrl;
};

struct uphy_reg_mgmt_txpll_bias_ctrl_id0 {
    uint8_t    bias_mode;
    uint8_t    bias_temp_offset_ctrl;
    uint8_t    bias_temp_slope_ctrl;
    uint8_t    bias_ptat_i_ctrl;
    uint8_t    bias_ctat_i_ctrl;
};

struct uphy_reg_mgmt_txpll_bias_ctrl_id1 {
    uint8_t    bias_mode;
    uint8_t    bias_temp_offset_ctrl;
    uint8_t    bias_temp_slope_ctrl;
    uint8_t    bias_ptat_i_ctrl;
    uint8_t    bias_ctat_i_ctrl;
};

struct uphy_reg_mgmt_txpll_cal_ctrl_id0 {
    uint8_t    txpll_fll_clk_en_ovrd;
    uint8_t    dco_fine_mode;
    uint8_t    dco_coarse_mode;
};

struct uphy_reg_mgmt_txpll_cal_ctrl_id1 {
    uint8_t    txpll_fll_clk_en_ovrd;
    uint8_t    dco_fine_mode;
    uint8_t    dco_coarse_mode;
};

struct uphy_reg_mgmt_txpll_cal_coarse_ctrl0_id0 {
    uint8_t    fll_hi_gain;
    uint8_t    fll_lo_gain;
    uint8_t    fravg_window;
};

struct uphy_reg_mgmt_txpll_cal_coarse_ctrl0_id1 {
    uint8_t    fll_hi_gain;
    uint8_t    fll_lo_gain;
    uint8_t    fravg_window;
};

struct uphy_reg_mgmt_txpll_cal_coarse_ctrl1_id0 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_mgmt_txpll_cal_coarse_ctrl1_id1 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_mgmt_txpll_cal_coarse_ctrl2_id0 {
    uint8_t    timeout_time;
    uint8_t    higear_time;
    uint8_t    logear_time;
};

struct uphy_reg_mgmt_txpll_cal_coarse_ctrl2_id1 {
    uint8_t    timeout_time;
    uint8_t    higear_time;
    uint8_t    logear_time;
};

struct uphy_reg_mgmt_txpll_cal_fine_ctrl0_id0 {
    uint8_t    fll_hi_gain;
    uint8_t    fll_lo_gain;
    uint8_t    fravg_window;
};

struct uphy_reg_mgmt_txpll_cal_fine_ctrl0_id1 {
    uint8_t    fll_hi_gain;
    uint8_t    fll_lo_gain;
    uint8_t    fravg_window;
};

struct uphy_reg_mgmt_txpll_cal_fine_ctrl1_id0 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_mgmt_txpll_cal_fine_ctrl1_id1 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_mgmt_txpll_cal_fine_ctrl2_id0 {
    uint8_t    timeout_time;
    uint8_t    higear_time;
    uint8_t    logear_time;
};

struct uphy_reg_mgmt_txpll_cal_fine_ctrl2_id1 {
    uint8_t    timeout_time;
    uint8_t    higear_time;
    uint8_t    logear_time;
};

struct uphy_reg_mgmt_txpll_cal_state_ctrl {
    uint8_t    cal_state_ovrd;
    uint8_t    cal_state;
};

struct uphy_reg_mgmt_txpll_cal_stat {
    uint8_t    rcal_val_changed;
    uint8_t    dco_fine_cal_valid;
    uint8_t    dco_coarse_cal_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_mgmt_txpll_cal_fravg_stat {
    uint16_t    fravg;
};

struct uphy_reg_mgmt_txpll_cal_state_stat {
    uint8_t    cal_fll_locked;
    uint8_t    cal_state;
};

struct uphy_reg_mgmt_txpll_cal_ctx_stat_id0 {
    uint8_t    dco_fine_cal_valid;
    uint8_t    dco_coarse_cal_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_mgmt_txpll_cal_ctx_stat_id1 {
    uint8_t    dco_fine_cal_valid;
    uint8_t    dco_coarse_cal_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_mgmt_tx_clkbuf_iqc_ctrl_id0 {
    uint8_t    iqc_iclk_dly;
    uint8_t    iqc_qclk_dly;
};

struct uphy_reg_mgmt_tx_clkbuf_iqc_ctrl_id1 {
    uint8_t    iqc_iclk_dly;
    uint8_t    iqc_qclk_dly;
};

struct uphy_reg_mgmt_tx_clkbuf_dly_ctrl {
    uint8_t    clkbuf_qclk_dly_ctrl;
    uint8_t    clkbuf_qclkb_dly_ctrl;
    uint8_t    clkbuf_iclk_dly_ctrl;
    uint8_t    clkbuf_iclkb_dly_ctrl;
};

struct uphy_reg_mgmt_tx_clkbuf_dcc_i_ctrl_id0 {
    uint8_t    dcc_iclk_vref_ctrl;
    uint8_t    dcc_iclkb_vref_ctrl;
};

struct uphy_reg_mgmt_tx_clkbuf_dcc_i_ctrl_id1 {
    uint8_t    dcc_iclk_vref_ctrl;
    uint8_t    dcc_iclkb_vref_ctrl;
};

struct uphy_reg_mgmt_tx_clkbuf_dcc_q_ctrl_id0 {
    uint8_t    dcc_qclk_vref_ctrl;
    uint8_t    dcc_qclkb_vref_ctrl;
};

struct uphy_reg_mgmt_tx_clkbuf_dcc_q_ctrl_id1 {
    uint8_t    dcc_qclk_vref_ctrl;
    uint8_t    dcc_qclkb_vref_ctrl;
};

struct uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0 {
    uint8_t    bypass_ac;
    uint8_t    dcc_loop_en;
    uint8_t    qilo_ctrl;
    uint8_t    serclk_dly_ctrl;
    uint8_t    dcc_chpclk_div;
    uint8_t    dcc_vref_range;
    uint8_t    adc_buf_gain_attn;
    uint8_t    adc_clk_div_mode;
    uint8_t    adc_vref_range;
};

struct uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1 {
    uint8_t    bypass_ac;
    uint8_t    dcc_loop_en;
    uint8_t    qilo_ctrl;
    uint8_t    serclk_dly_ctrl;
    uint8_t    dcc_chpclk_div;
    uint8_t    dcc_vref_range;
    uint8_t    adc_buf_gain_attn;
    uint8_t    adc_clk_div_mode;
    uint8_t    adc_vref_range;
};

struct uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2 {
    uint8_t    bypass_ac;
    uint8_t    dcc_loop_en;
    uint8_t    qilo_ctrl;
    uint8_t    serclk_dly_ctrl;
    uint8_t    dcc_chpclk_div;
    uint8_t    dcc_vref_range;
    uint8_t    adc_buf_gain_attn;
    uint8_t    adc_clk_div_mode;
    uint8_t    adc_vref_range;
};

struct uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3 {
    uint8_t    bypass_ac;
    uint8_t    dcc_loop_en;
    uint8_t    qilo_ctrl;
    uint8_t    serclk_dly_ctrl;
    uint8_t    dcc_chpclk_div;
    uint8_t    dcc_vref_range;
    uint8_t    adc_buf_gain_attn;
    uint8_t    adc_clk_div_mode;
    uint8_t    adc_vref_range;
};

struct uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4 {
    uint8_t    bypass_ac;
    uint8_t    dcc_loop_en;
    uint8_t    qilo_ctrl;
    uint8_t    serclk_dly_ctrl;
    uint8_t    dcc_chpclk_div;
    uint8_t    dcc_vref_range;
    uint8_t    adc_buf_gain_attn;
    uint8_t    adc_clk_div_mode;
    uint8_t    adc_vref_range;
};

struct uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl {
    uint8_t    dac_pattern;
    uint8_t    dac_pattern_ovrd;
    uint8_t    adc_vsense_sel_ovrd;
    uint8_t    adc_vsense_sel;
    uint8_t    tx_vsense_en_ovrd;
    uint8_t    tx_vsense_en;
    uint8_t    cal_drv_en_ovrd;
    uint8_t    cal_drv_en;
    uint8_t    cal_adc_en_ovrd;
    uint8_t    cal_adc_en;
    uint8_t    txclk_en_ovrd;
    uint8_t    txclk_en;
};

struct uphy_reg_mgmt_tx_iqdcc_ctrl_id0 {
    uint8_t    iqdcc_cal_valid_mask;
    uint8_t    iqdcc_cal_mode;
    uint8_t    qdcd_mode;
    uint8_t    idcd_mode;
    uint8_t    iqc_mode;
};

struct uphy_reg_mgmt_tx_iqdcc_ctrl_id1 {
    uint8_t    iqdcc_cal_valid_mask;
    uint8_t    iqdcc_cal_mode;
    uint8_t    qdcd_mode;
    uint8_t    idcd_mode;
    uint8_t    iqc_mode;
};

struct uphy_reg_mgmt_tx_iqdcc_iter_ctrl {
    uint8_t    iqc_iter;
    uint8_t    tx_idcd_iter;
    uint8_t    tx_qdcd_iter;
};

struct uphy_reg_mgmt_tx_iqdcc_timer_ctrl0 {
    uint8_t    adc_en_wait;
    uint8_t    qdcd_settle_wait;
    uint8_t    idcd_settle_wait;
    uint8_t    iqc_settle_wait;
};

struct uphy_reg_mgmt_tx_iqdcc_timer_ctrl1 {
    uint8_t    glbl_iter;
    uint8_t    adc_reset_wait;
    uint8_t    txclk_en_wait;
};

struct uphy_reg_mgmt_tx_iqdcc_adc_res_ctrl {
    uint8_t    qdcd_adc_res;
    uint8_t    idcd_adc_res;
    uint8_t    iqc_adc_res;
    uint8_t    ofst_adc_res;
};

struct uphy_reg_mgmt_tx_iqdcc_iqc_ctrl0 {
    uint8_t    iqc_grad_inv;
    uint8_t    iqc_ofst_gain;
    uint8_t    xor_iqc_gain;
    uint8_t    tx_iqc_gain;
    uint8_t    iqc_gmac_load_val;
};

struct uphy_reg_mgmt_tx_iqdcc_iqc_ctrl1 {
    uint8_t    iqc_gmac_delta_en;
    uint8_t    iqc_gmac_delta_max;
    uint8_t    iqc_gmac_delta_min;
};

struct uphy_reg_mgmt_tx_iqdcc_iqc_ctrl2 {
    uint8_t    iqc_diff_ofst;
};

struct uphy_reg_mgmt_tx_iqdcc_idcd_ctrl0 {
    uint8_t    idcd_grad_inv;
    uint8_t    idcd_ofst_gain;
    uint8_t    tx_idcd_gain;
    uint8_t    idcd_gmac_load_val;
};

struct uphy_reg_mgmt_tx_iqdcc_idcd_ctrl1 {
    uint8_t    idcd_gmac_delta_en;
    uint8_t    idcd_gmac_delta_max;
    uint8_t    idcd_gmac_delta_min;
};

struct uphy_reg_mgmt_tx_iqdcc_idcd_ctrl2 {
    uint8_t    idcd_diff_ofst;
    uint8_t    dcc_iclkb_ofst;
    uint8_t    dcc_iclk_ofst;
};

struct uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl0 {
    uint8_t    qdcd_grad_inv;
    uint8_t    qdcd_ofst_gain;
    uint8_t    tx_qdcd_gain;
    uint8_t    qdcd_gmac_load_val;
};

struct uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl1 {
    uint8_t    qdcd_gmac_delta_en;
    uint8_t    qdcd_gmac_delta_max;
    uint8_t    qdcd_gmac_delta_min;
};

struct uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl2 {
    uint8_t    qdcd_diff_ofst;
    uint8_t    dcc_qclkb_ofst;
    uint8_t    dcc_qclk_ofst;
};

struct uphy_reg_mgmt_tx_iqdcc_state_ctrl {
    uint8_t    iqdcc_cal_state_ovrd;
    uint8_t    iqdcc_cal_state;
};

struct uphy_reg_mgmt_tx_iqdcc_adc_state_ctrl {
    uint8_t    cal_adc_reset_ovrd;
    uint8_t    cal_adc_reset;
    uint8_t    iqdcc_adc_state_ovrd;
    uint8_t    iqdcc_adc_state;
};

struct uphy_reg_mgmt_tx_clkbuf_iqc_stat {
    uint8_t    iqc_qclk_dly;
    uint8_t    iqc_iclk_dly;
};

struct uphy_reg_mgmt_tx_clkbuf_dcc_i_stat {
    uint8_t    dcc_iclk_vref_ctrl;
    uint8_t    dcc_iclkb_vref_ctrl;
};

struct uphy_reg_mgmt_tx_clkbuf_dcc_q_stat {
    uint8_t    dcc_qclk_vref_ctrl;
    uint8_t    dcc_qclkb_vref_ctrl;
};

struct uphy_reg_mgmt_tx_iqdcc_state_stat {
    uint8_t    iqdcc_qdcd_cal_valid;
    uint8_t    iqdcc_idcd_cal_valid;
    uint8_t    iqdcc_iqc_cal_valid;
    uint8_t    iqdcc_cal_valid;
    uint8_t    iqdcc_cal_state;
};

struct uphy_reg_mgmt_tx_iqdcc_adc_state_stat {
    uint8_t    iqdcc_adc_state;
};

struct uphy_reg_mgmt_txeqterm_ctrl0 {
    uint8_t    p1_max;
    uint8_t    m3_max;
    uint8_t    tx_fir_scale_ctrl;
    uint8_t    tx_fir_m0;
};

struct uphy_reg_mgmt_txeqterm_ctrl1 {
    uint8_t    main_tp_en;
    uint8_t    m1_max;
    uint8_t    m2_max;
    uint8_t    cmh_iout_ctrl;
    uint8_t    cmh_vcm_ctrl_ovrd;
    uint8_t    cmh_vcm_ctrl;
};

struct uphy_reg_mgmt_txeqterm_ctrl2 {
    uint8_t    tx_amp_val;
    uint8_t    tx_amp_ovrd;
};

struct uphy_reg_mgmt_txeqterm_stat0 {
    uint8_t    fir_pre1;
    uint8_t    fir_post1;
    uint8_t    drv_amp;
};

struct uphy_reg_mgmt_txeqterm_stat1 {
    uint8_t    fir_pre2;
    uint8_t    fir_pre3;
};

struct uphy_reg_mgmt_txeqterm_stat2 {
    uint8_t    reverved1;
    uint8_t    fir_c0;
    uint8_t    reverved0;
    uint8_t    fir_m;
};

struct uphy_reg_mgmt_txeqlut_ctrl {
    uint8_t    txfir_1tap_en;
    uint8_t    txfir_3tap_en;
    uint8_t    txfir_5tap_en;
};

struct uphy_reg_mgmt_txeqlut_ctrl0 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl1 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl2 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl3 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl4 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl5 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl6 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl7 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl8 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl9 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl10 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl11 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl12 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl13 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl14 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl15 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl16 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl17 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl18 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl19 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl20 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl21 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl22 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl23 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl24 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl25 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl26 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl27 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl28 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl29 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl30 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_txeqlut_ctrl31 {
    uint8_t    lut1;
    uint8_t    lut0;
};

struct uphy_reg_mgmt_rx_term_ctrl0 {
    uint8_t    term_vddod_mode_nonp0;
    uint8_t    p3_rxterm_cmfb_en;
    uint8_t    term_cm_mode_nonp0;
    uint8_t    term_vddod_mode_p0;
    uint8_t    term_cm_mode_p0;
};

struct uphy_reg_mgmt_rx_term_ctrl1 {
    uint8_t    term_ota_bw_ctrl;
    uint8_t    term_vcm_ctrl;
};

struct uphy_reg_mgmt_rx_tah_ctrl_id0 {
    uint8_t    tah_i_ctrl;
};

struct uphy_reg_mgmt_rx_tah_ctrl_id1 {
    uint8_t    tah_i_ctrl;
};

struct uphy_reg_mgmt_rx_tah_ctrl_id2 {
    uint8_t    tah_i_ctrl;
};

struct uphy_reg_mgmt_rx_tah_ctrl_id3 {
    uint8_t    tah_i_ctrl;
};

struct uphy_reg_mgmt_rx_tah_ctrl_id4 {
    uint8_t    tah_i_ctrl;
};

struct uphy_reg_mgmt_rx_adc_ctrl {
    uint8_t    ae_rphase_inv;
    uint8_t    adc_clkboost_en;
    uint8_t    reg_byp_ovrd;
    uint8_t    reg_byp_en;
    uint8_t    adc_en_ovrd;
    uint8_t    adc_en;
};

struct uphy_reg_mgmt_rx_bias_ctrl {
    uint8_t    cgm_start_time;
    uint8_t    cgm_ready_ovrd;
    uint8_t    bg_ready_ovrd;
    uint8_t    bias_ready_ovrd;
    uint8_t    cgm_start_mode;
    uint8_t    ptat_slope_en;
    uint8_t    ptat_slope_ctrl;
    uint8_t    bg_i_ctrl;
    uint8_t    ptat_i_ctrl;
};

struct uphy_reg_mgmt_rx_bias_ctrl1 {
    uint8_t    rx_bias_lut_mode;
};

struct uphy_reg_mgmt_rx_misc_ctrl_id0 {
    uint16_t    misc_ctrl;
};

struct uphy_reg_mgmt_rx_misc_ctrl_id1 {
    uint16_t    misc_ctrl;
};

struct uphy_reg_mgmt_rx_misc_ctrl_id2 {
    uint16_t    misc_ctrl;
};

struct uphy_reg_ae_cdr_ctrl_id0 {
    uint8_t    cdr_ctx;
    uint8_t    faa_mode;
    uint8_t    frdot_mode;
    uint8_t    frest_mode;
    uint8_t    dco_fine_mode;
    uint8_t    dco_coarse_mode;
};

struct uphy_reg_ae_cdr_ctrl_id1 {
    uint8_t    cdr_ctx;
    uint8_t    faa_mode;
    uint8_t    frdot_mode;
    uint8_t    frest_mode;
    uint8_t    dco_fine_mode;
    uint8_t    dco_coarse_mode;
};

struct uphy_reg_ae_cdr_ctrl_id2 {
    uint8_t    cdr_ctx;
    uint8_t    faa_mode;
    uint8_t    frdot_mode;
    uint8_t    frest_mode;
    uint8_t    dco_fine_mode;
    uint8_t    dco_coarse_mode;
};

struct uphy_reg_ae_cdr_ctrl_id3 {
    uint8_t    cdr_ctx;
    uint8_t    faa_mode;
    uint8_t    frdot_mode;
    uint8_t    frest_mode;
    uint8_t    dco_fine_mode;
    uint8_t    dco_coarse_mode;
};

struct uphy_reg_ae_cdr_ctrl_id4 {
    uint8_t    cdr_ctx;
    uint8_t    faa_mode;
    uint8_t    frdot_mode;
    uint8_t    frest_mode;
    uint8_t    dco_fine_mode;
    uint8_t    dco_coarse_mode;
};

struct uphy_reg_ae_cdr_dco_ctrl0_id0 {
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctrl0_id1 {
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctrl0_id2 {
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctrl0_id3 {
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctrl0_id4 {
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctrl1_id0 {
    uint8_t    fll_refclk_ctrl;
    uint8_t    dco_i_diode_ctrl;
    uint8_t    dco_i_ctrl;
    uint8_t    dco_drv_ctrl;
    uint8_t    dco_core_mode;
    uint8_t    dco_c_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl1_id1 {
    uint8_t    fll_refclk_ctrl;
    uint8_t    dco_i_diode_ctrl;
    uint8_t    dco_i_ctrl;
    uint8_t    dco_drv_ctrl;
    uint8_t    dco_core_mode;
    uint8_t    dco_c_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl1_id2 {
    uint8_t    fll_refclk_ctrl;
    uint8_t    dco_i_diode_ctrl;
    uint8_t    dco_i_ctrl;
    uint8_t    dco_drv_ctrl;
    uint8_t    dco_core_mode;
    uint8_t    dco_c_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl1_id3 {
    uint8_t    fll_refclk_ctrl;
    uint8_t    dco_i_diode_ctrl;
    uint8_t    dco_i_ctrl;
    uint8_t    dco_drv_ctrl;
    uint8_t    dco_core_mode;
    uint8_t    dco_c_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl1_id4 {
    uint8_t    fll_refclk_ctrl;
    uint8_t    dco_i_diode_ctrl;
    uint8_t    dco_i_ctrl;
    uint8_t    dco_drv_ctrl;
    uint8_t    dco_core_mode;
    uint8_t    dco_c_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl2 {
    uint8_t    bck_trk_pat_sel;
    uint8_t    bck_acq_pat_sel;
    uint8_t    dco_freq_dac_vref_precharge_en_ovrd;
    uint8_t    dco_phase_dac_precharge_en_ovrd;
    uint8_t    dco_precharge_en_ovrd;
    uint8_t    dco_ls_en_ovrd;
    uint8_t    dco_ls_en;
};

struct uphy_reg_ae_cdr_dco_ctrl3_id0 {
    uint8_t    dco_phase_gain_range;
    uint8_t    dco_r_ctrl;
    uint8_t    dco_r_short_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl3_id1 {
    uint8_t    dco_phase_gain_range;
    uint8_t    dco_r_ctrl;
    uint8_t    dco_r_short_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl3_id2 {
    uint8_t    dco_phase_gain_range;
    uint8_t    dco_r_ctrl;
    uint8_t    dco_r_short_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl3_id3 {
    uint8_t    dco_phase_gain_range;
    uint8_t    dco_r_ctrl;
    uint8_t    dco_r_short_ctrl;
};

struct uphy_reg_ae_cdr_dco_ctrl3_id4 {
    uint8_t    dco_phase_gain_range;
    uint8_t    dco_r_ctrl;
    uint8_t    dco_r_short_ctrl;
};

struct uphy_reg_ae_cdr_frest_ctrl {
    uint16_t    cdr_frest;
};

struct uphy_reg_ae_cdr_frdot_ctrl {
    uint16_t    cdr_frdot;
};

struct uphy_reg_ae_cdr_state_ctrl {
    uint8_t    cdr_state_ovrd;
    uint8_t    cdr_aeintf_state_ovrd;
    uint8_t    cdr_op_ovrd;
    uint8_t    cdr_state;
    uint8_t    cdr_aeintf_state;
    uint8_t    cdr_op;
};

struct uphy_reg_ae_cdr_fll_div_ctrl_id0 {
    uint8_t    fll_clk_ctrl;
};

struct uphy_reg_ae_cdr_fll_div_ctrl_id1 {
    uint8_t    fll_clk_ctrl;
};

struct uphy_reg_ae_cdr_fll_div_ctrl_id2 {
    uint8_t    fll_clk_ctrl;
};

struct uphy_reg_ae_cdr_fll_div_ctrl_id3 {
    uint8_t    fll_clk_ctrl;
};

struct uphy_reg_ae_cdr_fll_div_ctrl_id4 {
    uint8_t    fll_clk_ctrl;
};

struct uphy_reg_ae_cdr_fll_dco_coarse_ctrl0_id0 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_dco_coarse_ctrl0_id1 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_dco_coarse_ctrl1_id0 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_fll_dco_coarse_ctrl1_id1 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_fll_dco_fine_ctrl0_id0 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_dco_fine_ctrl0_id1 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_dco_fine_ctrl1_id0 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_fll_dco_fine_ctrl1_id1 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl0_id0 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl0_id1 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl0_id2 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl0_id3 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl0_id4 {
    uint8_t    fravg_time;
    uint8_t    fravg_window;
    uint8_t    fll_gain;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl1_id0 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl1_id1 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl1_id2 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl1_id3 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_fll_frest_ctrl1_id4 {
    uint16_t    fll_lock_th;
};

struct uphy_reg_ae_cdr_pll_gain_ctrl0_id0 {
    uint8_t    pll_dsm3_gain;
    uint8_t    pll_freq3_gain;
    uint8_t    pll_freq2_gain_trk;
    uint8_t    pll_freq2_gain_acq;
};

struct uphy_reg_ae_cdr_pll_gain_ctrl0_id1 {
    uint8_t    pll_dsm3_gain;
    uint8_t    pll_freq3_gain;
    uint8_t    pll_freq2_gain_trk;
    uint8_t    pll_freq2_gain_acq;
};

struct uphy_reg_ae_cdr_pll_gain_ctrl0_id2 {
    uint8_t    pll_dsm3_gain;
    uint8_t    pll_freq3_gain;
    uint8_t    pll_freq2_gain_trk;
    uint8_t    pll_freq2_gain_acq;
};

struct uphy_reg_ae_cdr_pll_gain_ctrl0_id3 {
    uint8_t    pll_dsm3_gain;
    uint8_t    pll_freq3_gain;
    uint8_t    pll_freq2_gain_trk;
    uint8_t    pll_freq2_gain_acq;
};

struct uphy_reg_ae_cdr_pll_gain_ctrl0_id4 {
    uint8_t    pll_dsm3_gain;
    uint8_t    pll_freq3_gain;
    uint8_t    pll_freq2_gain_trk;
    uint8_t    pll_freq2_gain_acq;
};

struct uphy_reg_ae_cdr_pll_gain_ctrl1 {
    uint8_t    pll_freq2_gain_bck_trk;
    uint8_t    pll_freq2_gain_bck_acq;
};

struct uphy_reg_ae_cdr_seq_ctrl_id0 {
    uint8_t    ccal_phos_seq_expiry_mode;
    uint8_t    slicers_seq_expiry_mode;
    uint8_t    cdr_ccal_phos_expiry_time;
    uint8_t    cdr_slicers_trk_time;
    uint8_t    cdr_pll_acq_time;
    uint8_t    cdr_ccal_start_time;
};

struct uphy_reg_ae_cdr_seq_ctrl_id1 {
    uint8_t    ccal_phos_seq_expiry_mode;
    uint8_t    slicers_seq_expiry_mode;
    uint8_t    cdr_ccal_phos_expiry_time;
    uint8_t    cdr_slicers_trk_time;
    uint8_t    cdr_pll_acq_time;
    uint8_t    cdr_ccal_start_time;
};

struct uphy_reg_ae_cdr_seq_ctrl_id2 {
    uint8_t    ccal_phos_seq_expiry_mode;
    uint8_t    slicers_seq_expiry_mode;
    uint8_t    cdr_ccal_phos_expiry_time;
    uint8_t    cdr_slicers_trk_time;
    uint8_t    cdr_pll_acq_time;
    uint8_t    cdr_ccal_start_time;
};

struct uphy_reg_ae_cdr_seq_ctrl_id3 {
    uint8_t    ccal_phos_seq_expiry_mode;
    uint8_t    slicers_seq_expiry_mode;
    uint8_t    cdr_ccal_phos_expiry_time;
    uint8_t    cdr_slicers_trk_time;
    uint8_t    cdr_pll_acq_time;
    uint8_t    cdr_ccal_start_time;
};

struct uphy_reg_ae_cdr_seq_ctrl_id4 {
    uint8_t    ccal_phos_seq_expiry_mode;
    uint8_t    slicers_seq_expiry_mode;
    uint8_t    cdr_ccal_phos_expiry_time;
    uint8_t    cdr_slicers_trk_time;
    uint8_t    cdr_pll_acq_time;
    uint8_t    cdr_ccal_start_time;
};

struct uphy_reg_ae_feq_train_seq_ctrl_id0 {
    uint8_t    feq_slicers_addl_trk_time;
    uint8_t    feq_ccal_phos_expiry_time;
    uint8_t    feq_ffe_slicers_trk_time;
    uint8_t    cdr_spin_time;
};

struct uphy_reg_ae_feq_train_seq_ctrl_id1 {
    uint8_t    feq_slicers_addl_trk_time;
    uint8_t    feq_ccal_phos_expiry_time;
    uint8_t    feq_ffe_slicers_trk_time;
    uint8_t    cdr_spin_time;
};

struct uphy_reg_ae_peq_train_seq_ctrl_id0 {
    uint8_t    peq_ffe_eth_time;
};

struct uphy_reg_ae_peq_train_seq_ctrl_id1 {
    uint8_t    peq_ffe_eth_time;
};

struct uphy_reg_ae_cdr_pll_lock_th_ctrl_id0 {
    uint16_t    pll_unlock_th;
};

struct uphy_reg_ae_cdr_pll_lock_th_ctrl_id1 {
    uint16_t    pll_unlock_th;
};

struct uphy_reg_ae_cdr_pll_lock_th_ctrl_id2 {
    uint16_t    pll_unlock_th;
};

struct uphy_reg_ae_cdr_pll_lock_th_ctrl_id3 {
    uint16_t    pll_unlock_th;
};

struct uphy_reg_ae_cdr_pll_lock_th_ctrl_id4 {
    uint16_t    pll_unlock_th;
};

struct uphy_reg_ae_cdr_dco_gain_ctrl0_id0 {
    uint8_t    phase_gain_range;
    uint8_t    freq_gain;
    uint8_t    acq_csdet_grad_dup_off;
    uint8_t    phase_gain_trk;
    uint8_t    phase_gain_acq;
};

struct uphy_reg_ae_cdr_dco_gain_ctrl0_id1 {
    uint8_t    phase_gain_range;
    uint8_t    freq_gain;
    uint8_t    acq_csdet_grad_dup_off;
    uint8_t    phase_gain_trk;
    uint8_t    phase_gain_acq;
};

struct uphy_reg_ae_cdr_dco_gain_ctrl0_id2 {
    uint8_t    phase_gain_range;
    uint8_t    freq_gain;
    uint8_t    acq_csdet_grad_dup_off;
    uint8_t    phase_gain_trk;
    uint8_t    phase_gain_acq;
};

struct uphy_reg_ae_cdr_dco_gain_ctrl0_id3 {
    uint8_t    phase_gain_range;
    uint8_t    freq_gain;
    uint8_t    acq_csdet_grad_dup_off;
    uint8_t    phase_gain_trk;
    uint8_t    phase_gain_acq;
};

struct uphy_reg_ae_cdr_dco_gain_ctrl0_id4 {
    uint8_t    phase_gain_range;
    uint8_t    freq_gain;
    uint8_t    acq_csdet_grad_dup_off;
    uint8_t    phase_gain_trk;
    uint8_t    phase_gain_acq;
};

struct uphy_reg_ae_cdr_dco_gain_ctrl1 {
    uint8_t    phase_gain_bck_trk;
    uint8_t    phase_gain_bck_acq;
};

struct uphy_reg_ae_cdr_dco_ph_freq_ctrl_id0 {
    uint8_t    pll_grad_inv;
    uint8_t    freq_dac_loop_en;
    uint8_t    freq_dac_vref_sel;
    uint8_t    freq_dac_i_ctrl;
    uint8_t    freq_dsm_r_ctrl;
    uint8_t    phase_dac_stack_ctrl;
};

struct uphy_reg_ae_cdr_dco_ph_freq_ctrl_id1 {
    uint8_t    pll_grad_inv;
    uint8_t    freq_dac_loop_en;
    uint8_t    freq_dac_vref_sel;
    uint8_t    freq_dac_i_ctrl;
    uint8_t    freq_dsm_r_ctrl;
    uint8_t    phase_dac_stack_ctrl;
};

struct uphy_reg_ae_cdr_dco_ph_freq_ctrl_id2 {
    uint8_t    pll_grad_inv;
    uint8_t    freq_dac_loop_en;
    uint8_t    freq_dac_vref_sel;
    uint8_t    freq_dac_i_ctrl;
    uint8_t    freq_dsm_r_ctrl;
    uint8_t    phase_dac_stack_ctrl;
};

struct uphy_reg_ae_cdr_dco_ph_freq_ctrl_id3 {
    uint8_t    pll_grad_inv;
    uint8_t    freq_dac_loop_en;
    uint8_t    freq_dac_vref_sel;
    uint8_t    freq_dac_i_ctrl;
    uint8_t    freq_dsm_r_ctrl;
    uint8_t    phase_dac_stack_ctrl;
};

struct uphy_reg_ae_cdr_dco_ph_freq_ctrl_id4 {
    uint8_t    pll_grad_inv;
    uint8_t    freq_dac_loop_en;
    uint8_t    freq_dac_vref_sel;
    uint8_t    freq_dac_i_ctrl;
    uint8_t    freq_dsm_r_ctrl;
    uint8_t    phase_dac_stack_ctrl;
};

struct uphy_reg_ae_cdr_dco_bias_ctrl_id0 {
    uint8_t    bias_filter_r_ctrl;
    uint8_t    bias_temp_offset_ctrl;
    uint8_t    bias_mode;
    uint8_t    bias_temp_slope_ctrl;
    uint8_t    bias_ptat_i_ctrl;
    uint8_t    bias_ctat_i_ctrl;
};

struct uphy_reg_ae_cdr_dco_bias_ctrl_id1 {
    uint8_t    bias_filter_r_ctrl;
    uint8_t    bias_temp_offset_ctrl;
    uint8_t    bias_mode;
    uint8_t    bias_temp_slope_ctrl;
    uint8_t    bias_ptat_i_ctrl;
    uint8_t    bias_ctat_i_ctrl;
};

struct uphy_reg_ae_cdr_dco_bias_ctrl_id2 {
    uint8_t    bias_filter_r_ctrl;
    uint8_t    bias_temp_offset_ctrl;
    uint8_t    bias_mode;
    uint8_t    bias_temp_slope_ctrl;
    uint8_t    bias_ptat_i_ctrl;
    uint8_t    bias_ctat_i_ctrl;
};

struct uphy_reg_ae_cdr_dco_bias_ctrl_id3 {
    uint8_t    bias_filter_r_ctrl;
    uint8_t    bias_temp_offset_ctrl;
    uint8_t    bias_mode;
    uint8_t    bias_temp_slope_ctrl;
    uint8_t    bias_ptat_i_ctrl;
    uint8_t    bias_ctat_i_ctrl;
};

struct uphy_reg_ae_cdr_dco_bias_ctrl_id4 {
    uint8_t    bias_filter_r_ctrl;
    uint8_t    bias_temp_offset_ctrl;
    uint8_t    bias_mode;
    uint8_t    bias_temp_slope_ctrl;
    uint8_t    bias_ptat_i_ctrl;
    uint8_t    bias_ctat_i_ctrl;
};

struct uphy_reg_ae_cdr_dco_timer_ctrl_id0 {
    uint8_t    dco_coarse_tune_timeout;
    uint8_t    dco_postcharge_time;
};

struct uphy_reg_ae_cdr_dco_timer_ctrl_id1 {
    uint8_t    dco_coarse_tune_timeout;
    uint8_t    dco_postcharge_time;
};

struct uphy_reg_ae_cdr_dco_timer_ctrl_id2 {
    uint8_t    dco_coarse_tune_timeout;
    uint8_t    dco_postcharge_time;
};

struct uphy_reg_ae_cdr_dco_timer_ctrl_id3 {
    uint8_t    dco_coarse_tune_timeout;
    uint8_t    dco_postcharge_time;
};

struct uphy_reg_ae_cdr_dco_timer_ctrl_id4 {
    uint8_t    dco_coarse_tune_timeout;
    uint8_t    dco_postcharge_time;
};

struct uphy_reg_ae_cdr_csdet_ctrl {
    uint8_t    acq_csdet_frdot_off;
    uint8_t    pam4_pr1_seq_err_patsel;
    uint8_t    csdet_gain;
    uint8_t    csdet_err_thres_trk;
    uint8_t    csdet_err_thres_acq;
};

struct uphy_reg_ae_cdr_spin_ctrl {
    uint16_t    spin_freq;
};

struct uphy_reg_ae_cdr_dco_stat {
    uint8_t    cdr_initialized;
    uint8_t    dco_fine_tune_valid;
    uint8_t    dco_coarse_tune_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_frest_stat {
    uint16_t    frest;
};

struct uphy_reg_ae_cdr_frdot_stat {
    uint16_t    frdot;
};

struct uphy_reg_ae_cdr_fravg_stat {
    uint16_t    fravg;
};

struct uphy_reg_ae_cdr_stat {
    uint8_t    cdr_error_cnt;
    uint8_t    cdr_error;
    uint8_t    cdr_pll_unlocked;
    uint8_t    cdr_fll_locked;
    uint8_t    cdr_seq_abort_en;
    uint8_t    cdr_seq_en;
    uint8_t    cdr_pll_en;
    uint8_t    cdr_fll_en;
};

struct uphy_reg_ae_cdr_state_stat {
    uint8_t    cdr_ctx;
    uint8_t    cdr_state;
    uint8_t    cdr_aeintf_state;
    uint8_t    cdr_op;
};

struct uphy_reg_ae_cdr_dco_ctx_stat_id0 {
    uint8_t    cdr_initialized;
    uint8_t    dco_fine_tune_valid;
    uint8_t    dco_coarse_tune_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctx_stat_id1 {
    uint8_t    cdr_initialized;
    uint8_t    dco_fine_tune_valid;
    uint8_t    dco_coarse_tune_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctx_stat_id2 {
    uint8_t    cdr_initialized;
    uint8_t    dco_fine_tune_valid;
    uint8_t    dco_coarse_tune_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctx_stat_id3 {
    uint8_t    cdr_initialized;
    uint8_t    dco_fine_tune_valid;
    uint8_t    dco_coarse_tune_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_cdr_dco_ctx_stat_id4 {
    uint8_t    cdr_initialized;
    uint8_t    dco_fine_tune_valid;
    uint8_t    dco_coarse_tune_valid;
    uint8_t    dco_fine;
    uint8_t    dco_coarse;
};

struct uphy_reg_ae_ctle_vos_ctrl {
    uint8_t    ctle_vos;
};

struct uphy_reg_ae_vga_vos_ctrl {
    uint8_t    vga_vos_gen_vcal;
    uint8_t    vga_vos;
};

struct uphy_reg_ae_adc_cal_ctrl0 {
    uint8_t    adc_vos_wds;
    uint8_t    adc_vos_ren;
};

struct uphy_reg_ae_adc_cal_ctrl1 {
    uint8_t    adc_gain_wds;
    uint8_t    adc_gain_ren;
};

struct uphy_reg_ae_adc_cal_ctrl2 {
    uint8_t    adc_cal_addr;
    uint8_t    adc_cal_addr_ovrd;
    uint8_t    adc_gain_wds_ovrd;
    uint8_t    adc_vos_wds_ovrd;
};

struct uphy_reg_ae_adc_cal_val_ctrl {
    uint8_t    adc_gain_val;
    uint8_t    adc_vos_val;
};

struct uphy_reg_ae_adc_cal_clk_ctrl_id0 {
    uint8_t    adc_vosdac_clk_opt;
};

struct uphy_reg_ae_adc_cal_clk_ctrl_id1 {
    uint8_t    adc_vosdac_clk_opt;
};

struct uphy_reg_ae_adc_cal_clk_ctrl_id2 {
    uint8_t    adc_vosdac_clk_opt;
};

struct uphy_reg_ae_adc_cal_clk_ctrl_id3 {
    uint8_t    adc_vosdac_clk_opt;
};

struct uphy_reg_ae_adc_cal_clk_ctrl_id4 {
    uint8_t    adc_vosdac_clk_opt;
};

struct uphy_reg_ae_phos_ctrl {
    uint8_t    phos_ren_ovrd;
    uint8_t    phos_wds_ovrd;
    uint8_t    phos_addr_ovrd;
    uint8_t    phos_addr;
    uint8_t    phos;
};

struct uphy_reg_ae_cal_vos_ctrl0_id0 {
    uint8_t    edge_vos_ccal_en;
    uint8_t    adc_gain_shift_auto;
    uint8_t    ccal_mode;
    uint8_t    scal_phos_auto;
};

struct uphy_reg_ae_cal_vos_ctrl0_id1 {
    uint8_t    edge_vos_ccal_en;
    uint8_t    adc_gain_shift_auto;
    uint8_t    ccal_mode;
    uint8_t    scal_phos_auto;
};

struct uphy_reg_ae_cal_vos_ctrl0_id2 {
    uint8_t    edge_vos_ccal_en;
    uint8_t    adc_gain_shift_auto;
    uint8_t    ccal_mode;
    uint8_t    scal_phos_auto;
};

struct uphy_reg_ae_cal_vos_ctrl0_id3 {
    uint8_t    edge_vos_ccal_en;
    uint8_t    adc_gain_shift_auto;
    uint8_t    ccal_mode;
    uint8_t    scal_phos_auto;
};

struct uphy_reg_ae_cal_vos_ctrl0_id4 {
    uint8_t    edge_vos_ccal_en;
    uint8_t    adc_gain_shift_auto;
    uint8_t    ccal_mode;
    uint8_t    scal_phos_auto;
};

struct uphy_reg_ae_cal_vos_ctrl1 {
    uint8_t    ccal_decimated_by4_en;
    uint8_t    adc_gain_grad_inv;
    uint8_t    adc_vos_grad_inv;
    uint8_t    vga_vos_grad_inv;
    uint8_t    ctle_vos_grad_inv;
};

struct uphy_reg_ae_cal_vos_fcal_ctrl {
    uint8_t    term_phcal_en;
    uint8_t    term_phcal_en_ovrd;
    uint8_t    clkrcv_phcal_en;
    uint8_t    clkrcv_phcal_en_ovrd;
    uint8_t    vga_gen_vcal;
    uint8_t    vga_gen_vcal_ovrd;
    uint8_t    tah_squelch;
    uint8_t    vga_squelch;
    uint8_t    ctle_squelch;
    uint8_t    term_squelch;
    uint8_t    tah_squelch_ovrd;
    uint8_t    vga_squelch_ovrd;
    uint8_t    ctle_squelch_ovrd;
    uint8_t    term_squelch_ovrd;
};

struct uphy_reg_ae_cal_ctle_vos_ctrl0_id0 {
    uint8_t    blw_mode;
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_ctle_vos_ctrl0_id1 {
    uint8_t    blw_mode;
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_ctle_vos_ctrl0_id2 {
    uint8_t    blw_mode;
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_ctle_vos_ctrl0_id3 {
    uint8_t    blw_mode;
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_ctle_vos_ctrl0_id4 {
    uint8_t    blw_mode;
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl0 {
    uint8_t    ctle_vos_ccal_step;
    uint8_t    ctle_vos_ical_step;
    uint8_t    ctle_vos_fine_step;
    uint8_t    ctle_vos_coarse_step;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl1 {
    uint8_t    ctle_vos_ical_acc;
    uint8_t    ctle_vos_fcal_acc;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id0 {
    uint8_t    ctle_vos_ical_gain;
    uint8_t    ctle_vos_fine_gain;
    uint8_t    ctle_vos_coarse_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id1 {
    uint8_t    ctle_vos_ical_gain;
    uint8_t    ctle_vos_fine_gain;
    uint8_t    ctle_vos_coarse_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id2 {
    uint8_t    ctle_vos_ical_gain;
    uint8_t    ctle_vos_fine_gain;
    uint8_t    ctle_vos_coarse_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id3 {
    uint8_t    ctle_vos_ical_gain;
    uint8_t    ctle_vos_fine_gain;
    uint8_t    ctle_vos_coarse_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id4 {
    uint8_t    ctle_vos_ical_gain;
    uint8_t    ctle_vos_fine_gain;
    uint8_t    ctle_vos_coarse_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id0 {
    uint8_t    ctle_vos_ccal_trk_gain;
    uint8_t    ctle_vos_ccal_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id1 {
    uint8_t    ctle_vos_ccal_trk_gain;
    uint8_t    ctle_vos_ccal_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id2 {
    uint8_t    ctle_vos_ccal_trk_gain;
    uint8_t    ctle_vos_ccal_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id3 {
    uint8_t    ctle_vos_ccal_trk_gain;
    uint8_t    ctle_vos_ccal_gain;
};

struct uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id4 {
    uint8_t    ctle_vos_ccal_trk_gain;
    uint8_t    ctle_vos_ccal_gain;
};

struct uphy_reg_ae_cal_vga_vos_ctrl0_id0 {
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_vga_vos_ctrl0_id1 {
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_vga_vos_ctrl0_id2 {
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_vga_vos_ctrl0_id3 {
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_vga_vos_ctrl0_id4 {
    uint8_t    vos_range;
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_vga_vos_ctrl1_id0 {
    uint8_t    vos_gain_th;
    uint8_t    vga_gain_vos1;
    uint8_t    vga_gain_vos0;
};

struct uphy_reg_ae_cal_vga_vos_ctrl1_id1 {
    uint8_t    vos_gain_th;
    uint8_t    vga_gain_vos1;
    uint8_t    vga_gain_vos0;
};

struct uphy_reg_ae_cal_vga_vos_ctrl1_id2 {
    uint8_t    vos_gain_th;
    uint8_t    vga_gain_vos1;
    uint8_t    vga_gain_vos0;
};

struct uphy_reg_ae_cal_vga_vos_ctrl1_id3 {
    uint8_t    vos_gain_th;
    uint8_t    vga_gain_vos1;
    uint8_t    vga_gain_vos0;
};

struct uphy_reg_ae_cal_vga_vos_ctrl1_id4 {
    uint8_t    vos_gain_th;
    uint8_t    vga_gain_vos1;
    uint8_t    vga_gain_vos0;
};

struct uphy_reg_ae_cal_vga_vos_gmac_ctrl0 {
    uint8_t    vga_vos_ical_step;
    uint8_t    vga_vos_fine_step;
    uint8_t    vga_vos_coarse_step;
};

struct uphy_reg_ae_cal_vga_vos_gmac_ctrl1 {
    uint8_t    vga_vos_ical_acc;
    uint8_t    vga_vos_fcal_acc;
};

struct uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id0 {
    uint8_t    vga_vos_ical_gain;
    uint8_t    vga_vos_fine_gain;
    uint8_t    vga_vos_coarse_gain;
};

struct uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id1 {
    uint8_t    vga_vos_ical_gain;
    uint8_t    vga_vos_fine_gain;
    uint8_t    vga_vos_coarse_gain;
};

struct uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id2 {
    uint8_t    vga_vos_ical_gain;
    uint8_t    vga_vos_fine_gain;
    uint8_t    vga_vos_coarse_gain;
};

struct uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id3 {
    uint8_t    vga_vos_ical_gain;
    uint8_t    vga_vos_fine_gain;
    uint8_t    vga_vos_coarse_gain;
};

struct uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id4 {
    uint8_t    vga_vos_ical_gain;
    uint8_t    vga_vos_fine_gain;
    uint8_t    vga_vos_coarse_gain;
};

struct uphy_reg_ae_cal_adc_vos_ctrl_id0 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_vos_ctrl_id1 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_vos_ctrl_id2 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_vos_ctrl_id3 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_vos_ctrl_id4 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_vos_gmac_ctrl0 {
    uint8_t    adc_vos_ccal_step;
    uint8_t    adc_vos_ical_step;
    uint8_t    adc_vos_sprfine_step;
    uint8_t    adc_vos_fine_step;
    uint8_t    adc_vos_coarse_step;
};

struct uphy_reg_ae_cal_adc_vos_gmac_ctrl1 {
    uint8_t    adc_vos_ical_iter;
    uint8_t    adc_vos_sprfine_iter;
    uint8_t    adc_vos_fine_iter;
    uint8_t    adc_vos_coarse_iter;
};

struct uphy_reg_ae_cal_adc_vos_gmac_ctrl2 {
    uint8_t    adc_vos_ccal_acc;
    uint8_t    adc_vos_ical_acc;
    uint8_t    adc_vos_fcal_acc;
};

struct uphy_reg_ae_cal_adc_vos_gmac_ctrl3 {
    uint8_t    adc_vos_ical_gain;
    uint8_t    adc_vos_sprfine_gain;
    uint8_t    adc_vos_fine_gain;
    uint8_t    adc_vos_coarse_gain;
};

struct uphy_reg_ae_cal_adc_vos_gmac_ctrl4 {
    uint8_t    edge_vos_ccal_gain;
    uint8_t    adc_vos_ccal_gain;
};

struct uphy_reg_ae_cal_adc_gain_ctrl_id0 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_gain_ctrl_id1 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_gain_ctrl_id2 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_gain_ctrl_id3 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_gain_ctrl_id4 {
    uint8_t    vos_ctxid;
    uint8_t    vos_ctx;
    uint8_t    vos_mode;
};

struct uphy_reg_ae_cal_adc_gain_gmac_ctrl0 {
    uint8_t    adc_gain_sprfine_iter;
    uint8_t    adc_gain_fine_iter;
    uint8_t    adc_gain_coarse_iter;
    uint8_t    adc_gain_sprfine_step;
    uint8_t    adc_gain_fine_step;
    uint8_t    adc_gain_coarse_step;
};

struct uphy_reg_ae_cal_adc_gain_gmac_ctrl1 {
    uint8_t    adc_gain_ccal_step;
    uint8_t    adc_gain_ccal_win_cnt;
    uint8_t    adc_gain_ccal_acc;
    uint8_t    adc_gain_fcal_acc;
};

struct uphy_reg_ae_cal_adc_gain_gmac_ctrl2 {
    uint8_t    adc_gain_ccal_gain;
    uint8_t    adc_gain_sprfine_gain;
    uint8_t    adc_gain_fine_gain;
    uint8_t    adc_gain_coarse_gain;
};

struct uphy_reg_ae_cal_phos_ctrl0_id0 {
    uint8_t    hold_time;
    uint8_t    setup_time;
    uint8_t    strobe_width;
    uint8_t    ccal_phos_iter_time;
    uint8_t    ccal_phos_mode;
};

struct uphy_reg_ae_cal_phos_ctrl0_id1 {
    uint8_t    hold_time;
    uint8_t    setup_time;
    uint8_t    strobe_width;
    uint8_t    ccal_phos_iter_time;
    uint8_t    ccal_phos_mode;
};

struct uphy_reg_ae_cal_phos_ctrl0_id2 {
    uint8_t    hold_time;
    uint8_t    setup_time;
    uint8_t    strobe_width;
    uint8_t    ccal_phos_iter_time;
    uint8_t    ccal_phos_mode;
};

struct uphy_reg_ae_cal_phos_ctrl0_id3 {
    uint8_t    hold_time;
    uint8_t    setup_time;
    uint8_t    strobe_width;
    uint8_t    ccal_phos_iter_time;
    uint8_t    ccal_phos_mode;
};

struct uphy_reg_ae_cal_phos_ctrl0_id4 {
    uint8_t    hold_time;
    uint8_t    setup_time;
    uint8_t    strobe_width;
    uint8_t    ccal_phos_iter_time;
    uint8_t    ccal_phos_mode;
};

struct uphy_reg_ae_cal_phos_ctrl1 {
    uint8_t    ccal_phos_delta;
    uint8_t    ccal_phos_gain;
    uint8_t    phos_grad_inv;
};

struct uphy_reg_ae_scal_phos_ctrl0 {
    uint8_t    scal_phos_gain;
    uint8_t    scal_phos_grad_slp_sel;
    uint16_t    scal_phos_h0;
};

struct uphy_reg_ae_scal_phos_ctrl1 {
    uint8_t    scal_phos_iter_time;
    uint8_t    scal_phos_time;
    uint8_t    scal_phos_pll_lock_time;
    uint8_t    scal_phos_fll_slicers_time;
};

struct uphy_reg_ae_scal_phos_ctrl2 {
    uint8_t    scal_phos_csdet_off;
    uint8_t    pll_freq2_gain_scal;
    uint8_t    phase_gain_scal;
    uint8_t    scal_phos_valid_ovrd;
    uint8_t    scal_phos_valid;
    uint8_t    scal_phos_delta;
};

struct uphy_reg_ae_cal_vos_ccal_state_ctrl {
    uint8_t    ccal_state_ovrd;
    uint8_t    ccal_op_ovrd;
    uint8_t    ccal_state;
    uint8_t    ccal_op;
};

struct uphy_reg_ae_cal_phos_state_ctrl {
    uint8_t    op_ovrd;
    uint8_t    state_ovrd;
    uint8_t    aeintf_state_ovrd;
    uint8_t    phos_op;
    uint8_t    phos_state;
    uint8_t    phos_aeintf_state;
};

struct uphy_reg_ae_cal_vos_valid_ctrl0 {
    uint8_t    vga_vos_valid_ovrd;
    uint8_t    vga_vos_valid;
    uint8_t    ctle_vos_valid_ovrd;
    uint8_t    ctle_vos_valid;
};

struct uphy_reg_ae_cal_vos_valid_ctrl1 {
    uint8_t    adc_vos_valid_ovrd;
    uint8_t    adc_vos_valid;
    uint8_t    adc_gain_valid_ovrd;
    uint8_t    adc_gain_valid;
};

struct uphy_reg_ae_ctle_vos_ctx0_stat0 {
    uint8_t    ctle_vos0;
};

struct uphy_reg_ae_ctle_vos_ctx1_stat0 {
    uint8_t    ctle_vos0;
};

struct uphy_reg_ae_ctle_vos_ctx2_stat0 {
    uint8_t    ctle_vos0;
};

struct uphy_reg_ae_vga_vos_ctx0_stat {
    uint8_t    vga_vos1;
    uint8_t    vga_vos0;
};

struct uphy_reg_ae_vga_vos_ctx1_stat {
    uint8_t    vga_vos1;
    uint8_t    vga_vos0;
};

struct uphy_reg_ae_vga_vos_ctx2_stat {
    uint8_t    vga_vos1;
    uint8_t    vga_vos0;
};

struct uphy_reg_ae_adc0_cal_stat0 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc0_cal_stat1 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc0_cal_stat2 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc0_cal_stat3 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc0_cal_stat4 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc0_cal_stat5 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc0_cal_stat6 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc0_cal_stat7 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc1_cal_stat0 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc1_cal_stat1 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc1_cal_stat2 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc1_cal_stat3 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc1_cal_stat4 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc1_cal_stat5 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc1_cal_stat6 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc1_cal_stat7 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc2_cal_stat0 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc2_cal_stat1 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc2_cal_stat2 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc2_cal_stat3 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc2_cal_stat4 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc2_cal_stat5 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc2_cal_stat6 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc2_cal_stat7 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc3_cal_stat0 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc3_cal_stat1 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc3_cal_stat2 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc3_cal_stat3 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc3_cal_stat4 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc3_cal_stat5 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc3_cal_stat6 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc3_cal_stat7 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc4_cal_stat0 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc4_cal_stat1 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc4_cal_stat2 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc4_cal_stat3 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc4_cal_stat4 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc4_cal_stat5 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc4_cal_stat6 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc4_cal_stat7 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc5_cal_stat0 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc5_cal_stat1 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc5_cal_stat2 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc5_cal_stat3 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc5_cal_stat4 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc5_cal_stat5 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc5_cal_stat6 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc5_cal_stat7 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc6_cal_stat0 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc6_cal_stat1 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc6_cal_stat2 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc6_cal_stat3 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc6_cal_stat4 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc6_cal_stat5 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc6_cal_stat6 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc6_cal_stat7 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc7_cal_stat0 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc7_cal_stat1 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc7_cal_stat2 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc7_cal_stat3 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc7_cal_stat4 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc7_cal_stat5 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc7_cal_stat6 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc7_cal_stat7 {
    uint8_t    adc_gos;
    uint8_t    adc_vos;
};

struct uphy_reg_ae_adc_cal_rd_stat0 {
    uint8_t    adc1_cal_val;
    uint8_t    adc0_cal_val;
};

struct uphy_reg_ae_adc_cal_rd_stat1 {
    uint8_t    adc3_cal_val;
    uint8_t    adc2_cal_val;
};

struct uphy_reg_ae_adc_cal_rd_stat2 {
    uint8_t    adc5_cal_val;
    uint8_t    adc4_cal_val;
};

struct uphy_reg_ae_adc_cal_rd_stat3 {
    uint8_t    adc7_cal_val;
    uint8_t    adc6_cal_val;
};

struct uphy_reg_ae_phos_stat0 {
    uint8_t    phos1;
    uint8_t    phos0;
};

struct uphy_reg_ae_phos_stat1 {
    uint8_t    phos3;
    uint8_t    phos2;
};

struct uphy_reg_ae_phos_stat2 {
    uint8_t    phos5;
    uint8_t    phos4;
};

struct uphy_reg_ae_phos_stat3 {
    uint8_t    phos7;
    uint8_t    phos6;
};

struct uphy_reg_ae_phos_rd_stat {
    uint8_t    phos;
};

struct uphy_reg_ae_cal_vos_ccal_state_stat {
    uint8_t    cal_error_cnt;
    uint8_t    ccal_state;
    uint8_t    ccal_op;
};

struct uphy_reg_ae_cal_phos_state_stat {
    uint8_t    phos_op;
    uint8_t    phos_state;
    uint8_t    phos_aeintf_state;
};

struct uphy_reg_ae_cal_vos_valid_stat0 {
    uint8_t    ctle_vos_ctx1_initialized;
    uint8_t    ctle_vos_ctx1_valid;
    uint8_t    ctle_vos_ctx0_initialized;
    uint8_t    ctle_vos_ctx0_valid;
};

struct uphy_reg_ae_cal_vos_valid_stat1 {
    uint8_t    ctle_vos_ctx2_initialized;
    uint8_t    ctle_vos_ctx2_valid;
    uint8_t    vga_vos_ctx0_initialized;
    uint8_t    vga_vos_ctx0_valid;
};

struct uphy_reg_ae_cal_vos_valid_stat2 {
    uint8_t    vga_vos_ctx2_initialized;
    uint8_t    vga_vos_ctx2_valid;
    uint8_t    vga_vos_ctx1_initialized;
    uint8_t    vga_vos_ctx1_valid;
};

struct uphy_reg_ae_cal_vos_valid_stat3 {
    uint8_t    adc_vos_initialized;
    uint8_t    adc_vos_valid;
    uint8_t    adc_gain_initialized;
    uint8_t    adc_gain_valid;
};

struct uphy_reg_ae_term_attn_ctrl_id0 {
    uint8_t    term_i_ctrl;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_term_attn_ctrl_id1 {
    uint8_t    term_i_ctrl;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_term_attn_ctrl_id2 {
    uint8_t    term_i_ctrl;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_term_attn_ctrl_id3 {
    uint8_t    term_i_ctrl;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_term_attn_ctrl_id4 {
    uint8_t    term_i_ctrl;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_ctle_ctrl0_id0 {
    uint8_t    hf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_ctrl0_id1 {
    uint8_t    hf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_ctrl0_id2 {
    uint8_t    hf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_ctrl0_id3 {
    uint8_t    hf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_ctrl0_id4 {
    uint8_t    hf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_ctrl1_id0 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_ctle_ctrl1_id1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_ctle_ctrl1_id2 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_ctle_ctrl1_id3 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_ctle_ctrl1_id4 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_ctle_ctrl2_id0 {
    uint8_t    ctle_rvdd_ctrl;
    uint8_t    ctle_tia_res_ctrl;
    uint8_t    ctle_tia_i_ctrl;
    uint8_t    ctle_tas_i_ctrl;
    uint8_t    ctle_i_ctrl;
};

struct uphy_reg_ae_ctle_ctrl2_id1 {
    uint8_t    ctle_rvdd_ctrl;
    uint8_t    ctle_tia_res_ctrl;
    uint8_t    ctle_tia_i_ctrl;
    uint8_t    ctle_tas_i_ctrl;
    uint8_t    ctle_i_ctrl;
};

struct uphy_reg_ae_ctle_ctrl2_id2 {
    uint8_t    ctle_rvdd_ctrl;
    uint8_t    ctle_tia_res_ctrl;
    uint8_t    ctle_tia_i_ctrl;
    uint8_t    ctle_tas_i_ctrl;
    uint8_t    ctle_i_ctrl;
};

struct uphy_reg_ae_ctle_ctrl2_id3 {
    uint8_t    ctle_rvdd_ctrl;
    uint8_t    ctle_tia_res_ctrl;
    uint8_t    ctle_tia_i_ctrl;
    uint8_t    ctle_tas_i_ctrl;
    uint8_t    ctle_i_ctrl;
};

struct uphy_reg_ae_ctle_ctrl2_id4 {
    uint8_t    ctle_rvdd_ctrl;
    uint8_t    ctle_tia_res_ctrl;
    uint8_t    ctle_tia_i_ctrl;
    uint8_t    ctle_tas_i_ctrl;
    uint8_t    ctle_i_ctrl;
};

struct uphy_reg_ae_vga_ctrl0_id0 {
    uint8_t    vga_vcm_ctrl;
    uint8_t    vga_time;
    uint8_t    vga_gain;
};

struct uphy_reg_ae_vga_ctrl0_id1 {
    uint8_t    vga_vcm_ctrl;
    uint8_t    vga_time;
    uint8_t    vga_gain;
};

struct uphy_reg_ae_vga_ctrl0_id2 {
    uint8_t    vga_vcm_ctrl;
    uint8_t    vga_time;
    uint8_t    vga_gain;
};

struct uphy_reg_ae_vga_ctrl0_id3 {
    uint8_t    vga_vcm_ctrl;
    uint8_t    vga_time;
    uint8_t    vga_gain;
};

struct uphy_reg_ae_vga_ctrl0_id4 {
    uint8_t    vga_vcm_ctrl;
    uint8_t    vga_time;
    uint8_t    vga_gain;
};

struct uphy_reg_ae_vga_ctrl1_id0 {
    uint8_t    vga_tia_r_ctrl;
    uint8_t    vga_tia_i_ctrl;
    uint8_t    vga_tas_i_ctrl;
    uint8_t    vga_ssf_i_ctrl;
};

struct uphy_reg_ae_vga_ctrl1_id1 {
    uint8_t    vga_tia_r_ctrl;
    uint8_t    vga_tia_i_ctrl;
    uint8_t    vga_tas_i_ctrl;
    uint8_t    vga_ssf_i_ctrl;
};

struct uphy_reg_ae_vga_ctrl1_id2 {
    uint8_t    vga_tia_r_ctrl;
    uint8_t    vga_tia_i_ctrl;
    uint8_t    vga_tas_i_ctrl;
    uint8_t    vga_ssf_i_ctrl;
};

struct uphy_reg_ae_vga_ctrl1_id3 {
    uint8_t    vga_tia_r_ctrl;
    uint8_t    vga_tia_i_ctrl;
    uint8_t    vga_tas_i_ctrl;
    uint8_t    vga_ssf_i_ctrl;
};

struct uphy_reg_ae_vga_ctrl1_id4 {
    uint8_t    vga_tia_r_ctrl;
    uint8_t    vga_tia_i_ctrl;
    uint8_t    vga_tas_i_ctrl;
    uint8_t    vga_ssf_i_ctrl;
};

struct uphy_reg_ae_adc_vref_ctrl0_id0 {
    uint8_t    adc_vref_range;
    uint8_t    adc_vref_i_ctrl;
    uint8_t    adc_i_ctrl;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_adc_vref_ctrl0_id1 {
    uint8_t    adc_vref_range;
    uint8_t    adc_vref_i_ctrl;
    uint8_t    adc_i_ctrl;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_adc_vref_ctrl0_id2 {
    uint8_t    adc_vref_range;
    uint8_t    adc_vref_i_ctrl;
    uint8_t    adc_i_ctrl;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_adc_vref_ctrl0_id3 {
    uint8_t    adc_vref_range;
    uint8_t    adc_vref_i_ctrl;
    uint8_t    adc_i_ctrl;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_adc_vref_ctrl0_id4 {
    uint8_t    adc_vref_range;
    uint8_t    adc_vref_i_ctrl;
    uint8_t    adc_i_ctrl;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_adc_vref_ctrl1_id0 {
    uint8_t    closeloop_en;
    uint8_t    adc_vref_wds_ovrd;
    uint8_t    adc_vref_wds;
};

struct uphy_reg_ae_adc_vref_ctrl1_id1 {
    uint8_t    closeloop_en;
    uint8_t    adc_vref_wds_ovrd;
    uint8_t    adc_vref_wds;
};

struct uphy_reg_ae_adc_vref_ctrl1_id2 {
    uint8_t    closeloop_en;
    uint8_t    adc_vref_wds_ovrd;
    uint8_t    adc_vref_wds;
};

struct uphy_reg_ae_adc_vref_ctrl1_id3 {
    uint8_t    closeloop_en;
    uint8_t    adc_vref_wds_ovrd;
    uint8_t    adc_vref_wds;
};

struct uphy_reg_ae_adc_vref_ctrl1_id4 {
    uint8_t    closeloop_en;
    uint8_t    adc_vref_wds_ovrd;
    uint8_t    adc_vref_wds;
};

struct uphy_reg_ae_cdr_offset_ctrl {
    uint8_t    cdr_offset;
};

struct uphy_reg_ae_ffe_ctrl0_id0 {
    uint8_t    ffe_fm2;
    uint8_t    ffe_fm3;
};

struct uphy_reg_ae_ffe_ctrl0_id1 {
    uint8_t    ffe_fm2;
    uint8_t    ffe_fm3;
};

struct uphy_reg_ae_ffe_ctrl1_id0 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_ffe_ctrl1_id1 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_ffe_ctrl2_id0 {
    uint8_t    ffe_f3;
    uint8_t    ffe_f2;
};

struct uphy_reg_ae_ffe_ctrl2_id1 {
    uint8_t    ffe_f3;
    uint8_t    ffe_f2;
};

struct uphy_reg_ae_ffe_ctrl3_id0 {
    uint8_t    ffe_f5;
    uint8_t    ffe_f4;
};

struct uphy_reg_ae_ffe_ctrl3_id1 {
    uint8_t    ffe_f5;
    uint8_t    ffe_f4;
};

struct uphy_reg_ae_ffe_ctrl4_id0 {
    uint8_t    ffe_f7;
    uint8_t    ffe_f6;
};

struct uphy_reg_ae_ffe_ctrl4_id1 {
    uint8_t    ffe_f7;
    uint8_t    ffe_f6;
};

struct uphy_reg_ae_ffe_ctrl5_id0 {
    uint8_t    ffe_f8;
};

struct uphy_reg_ae_ffe_ctrl5_id1 {
    uint8_t    ffe_f8;
};

struct uphy_reg_ae_dffe_ctrl0 {
    uint8_t    dffe_dsel1;
    uint8_t    dffe_coef1;
    uint8_t    dffe_dsel0;
    uint8_t    dffe_coef0;
};

struct uphy_reg_ae_dffe_ctrl1 {
    uint8_t    dffe_dsel3;
    uint8_t    dffe_coef3;
    uint8_t    dffe_dsel2;
    uint8_t    dffe_coef2;
};

struct uphy_reg_ae_dffe_ctrl2 {
    uint8_t    dffe_dsel5;
    uint8_t    dffe_coef5;
    uint8_t    dffe_dsel4;
    uint8_t    dffe_coef4;
};

struct uphy_reg_ae_dffe_ctrl3 {
    uint8_t    dffe_dsel7;
    uint8_t    dffe_coef7;
    uint8_t    dffe_dsel6;
    uint8_t    dffe_coef6;
};

struct uphy_reg_ae_dffe_ctrl4 {
    uint8_t    dffe_dsel8;
    uint8_t    dffe_coef8;
};

struct uphy_reg_ae_slicer_eth_ctrl0_id0 {
    uint16_t    eth0;
};

struct uphy_reg_ae_slicer_eth_ctrl0_id1 {
    uint16_t    eth0;
};

struct uphy_reg_ae_slicer_eth_ctrl0_id2 {
    uint16_t    eth0;
};

struct uphy_reg_ae_slicer_eth_ctrl0_id3 {
    uint16_t    eth0;
};

struct uphy_reg_ae_slicer_eth_ctrl0_id4 {
    uint16_t    eth0;
};

struct uphy_reg_ae_slicer_eth_ctrl1 {
    uint16_t    eth1;
};

struct uphy_reg_ae_slicer_eth_ctrl2_id0 {
    uint16_t    eth2;
};

struct uphy_reg_ae_slicer_eth_ctrl2_id1 {
    uint16_t    eth2;
};

struct uphy_reg_ae_slicer_eth_ctrl2_id2 {
    uint16_t    eth2;
};

struct uphy_reg_ae_slicer_eth_ctrl2_id3 {
    uint16_t    eth2;
};

struct uphy_reg_ae_slicer_eth_ctrl2_id4 {
    uint16_t    eth2;
};

struct uphy_reg_ae_slicer_eth_ctrl3 {
    uint16_t    eth3;
};

struct uphy_reg_ae_slicer_eth_ctrl4 {
    uint16_t    eth4;
};

struct uphy_reg_ae_slicer_eth_ctrl5 {
    uint16_t    eth5;
};

struct uphy_reg_ae_slicer_eth_ctrl6 {
    uint16_t    eth6;
};

struct uphy_reg_ae_slicer_eth_ctrl7 {
    uint16_t    eth7;
};

struct uphy_reg_ae_ctle_preset0_ctrl_id0 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset0_ctrl_id1 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset1_ctrl_id0 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset1_ctrl_id1 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset2_ctrl_id0 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset2_ctrl_id1 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset3_ctrl_id0 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset3_ctrl_id1 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset4_ctrl_id0 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset4_ctrl_id1 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset5_ctrl_id0 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset5_ctrl_id1 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset6_ctrl_id0 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset6_ctrl_id1 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset7_ctrl_id0 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_preset7_ctrl_id1 {
    uint8_t    hf_gain;
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_eq_train_ctrl0_id0 {
    uint8_t    peq_tsense_en;
    uint8_t    vref_peq_en;
    uint8_t    dffe_peq_scout_skip;
    uint8_t    peq_f1_adapt_skip;
    uint8_t    dcg_hfg_fine_srch_en;
    uint8_t    lfg_mfg_fine_srch_en;
    uint8_t    lfg_mfg_crs_srch_en;
    uint8_t    peq_train_mode;
    uint8_t    feq_train_mode;
};

struct uphy_reg_ae_eq_train_ctrl0_id1 {
    uint8_t    peq_tsense_en;
    uint8_t    vref_peq_en;
    uint8_t    dffe_peq_scout_skip;
    uint8_t    peq_f1_adapt_skip;
    uint8_t    dcg_hfg_fine_srch_en;
    uint8_t    lfg_mfg_fine_srch_en;
    uint8_t    lfg_mfg_crs_srch_en;
    uint8_t    peq_train_mode;
    uint8_t    feq_train_mode;
};

struct uphy_reg_ae_eq_train_ctrl0_id2 {
    uint8_t    peq_tsense_en;
    uint8_t    vref_peq_en;
    uint8_t    dffe_peq_scout_skip;
    uint8_t    peq_f1_adapt_skip;
    uint8_t    dcg_hfg_fine_srch_en;
    uint8_t    lfg_mfg_fine_srch_en;
    uint8_t    lfg_mfg_crs_srch_en;
    uint8_t    peq_train_mode;
    uint8_t    feq_train_mode;
};

struct uphy_reg_ae_eq_train_ctrl0_id3 {
    uint8_t    peq_tsense_en;
    uint8_t    vref_peq_en;
    uint8_t    dffe_peq_scout_skip;
    uint8_t    peq_f1_adapt_skip;
    uint8_t    dcg_hfg_fine_srch_en;
    uint8_t    lfg_mfg_fine_srch_en;
    uint8_t    lfg_mfg_crs_srch_en;
    uint8_t    peq_train_mode;
    uint8_t    feq_train_mode;
};

struct uphy_reg_ae_eq_train_ctrl0_id4 {
    uint8_t    peq_tsense_en;
    uint8_t    vref_peq_en;
    uint8_t    dffe_peq_scout_skip;
    uint8_t    peq_f1_adapt_skip;
    uint8_t    dcg_hfg_fine_srch_en;
    uint8_t    lfg_mfg_fine_srch_en;
    uint8_t    lfg_mfg_crs_srch_en;
    uint8_t    peq_train_mode;
    uint8_t    feq_train_mode;
};

struct uphy_reg_ae_eq_train_ctrl1_id0 {
    uint8_t    term_lpf_mode;
    uint8_t    cdr_offset_mode;
    uint8_t    vref_val_mode;
    uint8_t    eq_auto;
    uint8_t    rx_dffe_id;
    uint8_t    rx_ffe_id;
    uint8_t    rx_ctle_id;
    uint8_t    adapt_id;
};

struct uphy_reg_ae_eq_train_ctrl1_id1 {
    uint8_t    term_lpf_mode;
    uint8_t    cdr_offset_mode;
    uint8_t    vref_val_mode;
    uint8_t    eq_auto;
    uint8_t    rx_dffe_id;
    uint8_t    rx_ffe_id;
    uint8_t    rx_ctle_id;
    uint8_t    adapt_id;
};

struct uphy_reg_ae_eq_train_ctrl1_id2 {
    uint8_t    term_lpf_mode;
    uint8_t    cdr_offset_mode;
    uint8_t    vref_val_mode;
    uint8_t    eq_auto;
    uint8_t    rx_dffe_id;
    uint8_t    rx_ffe_id;
    uint8_t    rx_ctle_id;
    uint8_t    adapt_id;
};

struct uphy_reg_ae_eq_train_ctrl1_id3 {
    uint8_t    term_lpf_mode;
    uint8_t    cdr_offset_mode;
    uint8_t    vref_val_mode;
    uint8_t    eq_auto;
    uint8_t    rx_dffe_id;
    uint8_t    rx_ffe_id;
    uint8_t    rx_ctle_id;
    uint8_t    adapt_id;
};

struct uphy_reg_ae_eq_train_ctrl1_id4 {
    uint8_t    term_lpf_mode;
    uint8_t    cdr_offset_mode;
    uint8_t    vref_val_mode;
    uint8_t    eq_auto;
    uint8_t    rx_dffe_id;
    uint8_t    rx_ffe_id;
    uint8_t    rx_ctle_id;
    uint8_t    adapt_id;
};

struct uphy_reg_ae_eq_train_ctrl2_id0 {
    uint8_t    vga_gain_mode;
    uint8_t    hf_gain_mode;
    uint8_t    mf_pole_mode;
    uint8_t    mf_gain_mode;
    uint8_t    lf_pole_mode;
    uint8_t    lf_gain_mode;
    uint8_t    dc_gain_mode;
    uint8_t    term_attn_mode;
};

struct uphy_reg_ae_eq_train_ctrl2_id1 {
    uint8_t    vga_gain_mode;
    uint8_t    hf_gain_mode;
    uint8_t    mf_pole_mode;
    uint8_t    mf_gain_mode;
    uint8_t    lf_pole_mode;
    uint8_t    lf_gain_mode;
    uint8_t    dc_gain_mode;
    uint8_t    term_attn_mode;
};

struct uphy_reg_ae_eq_train_ctrl2_id2 {
    uint8_t    vga_gain_mode;
    uint8_t    hf_gain_mode;
    uint8_t    mf_pole_mode;
    uint8_t    mf_gain_mode;
    uint8_t    lf_pole_mode;
    uint8_t    lf_gain_mode;
    uint8_t    dc_gain_mode;
    uint8_t    term_attn_mode;
};

struct uphy_reg_ae_eq_train_ctrl2_id3 {
    uint8_t    vga_gain_mode;
    uint8_t    hf_gain_mode;
    uint8_t    mf_pole_mode;
    uint8_t    mf_gain_mode;
    uint8_t    lf_pole_mode;
    uint8_t    lf_gain_mode;
    uint8_t    dc_gain_mode;
    uint8_t    term_attn_mode;
};

struct uphy_reg_ae_eq_train_ctrl2_id4 {
    uint8_t    vga_gain_mode;
    uint8_t    hf_gain_mode;
    uint8_t    mf_pole_mode;
    uint8_t    mf_gain_mode;
    uint8_t    lf_pole_mode;
    uint8_t    lf_gain_mode;
    uint8_t    dc_gain_mode;
    uint8_t    term_attn_mode;
};

struct uphy_reg_ae_eq_train_ctrl3_id0 {
    uint8_t    f8_mode;
    uint8_t    f7_mode;
    uint8_t    f6_mode;
    uint8_t    f5_mode;
    uint8_t    f4_mode;
    uint8_t    f3_mode;
    uint8_t    f2_mode;
    uint8_t    f1_mode;
};

struct uphy_reg_ae_eq_train_ctrl3_id1 {
    uint8_t    f8_mode;
    uint8_t    f7_mode;
    uint8_t    f6_mode;
    uint8_t    f5_mode;
    uint8_t    f4_mode;
    uint8_t    f3_mode;
    uint8_t    f2_mode;
    uint8_t    f1_mode;
};

struct uphy_reg_ae_eq_train_ctrl3_id2 {
    uint8_t    f8_mode;
    uint8_t    f7_mode;
    uint8_t    f6_mode;
    uint8_t    f5_mode;
    uint8_t    f4_mode;
    uint8_t    f3_mode;
    uint8_t    f2_mode;
    uint8_t    f1_mode;
};

struct uphy_reg_ae_eq_train_ctrl3_id3 {
    uint8_t    f8_mode;
    uint8_t    f7_mode;
    uint8_t    f6_mode;
    uint8_t    f5_mode;
    uint8_t    f4_mode;
    uint8_t    f3_mode;
    uint8_t    f2_mode;
    uint8_t    f1_mode;
};

struct uphy_reg_ae_eq_train_ctrl3_id4 {
    uint8_t    f8_mode;
    uint8_t    f7_mode;
    uint8_t    f6_mode;
    uint8_t    f5_mode;
    uint8_t    f4_mode;
    uint8_t    f3_mode;
    uint8_t    f2_mode;
    uint8_t    f1_mode;
};

struct uphy_reg_ae_eq_train_ctrl4_id0 {
    uint8_t    h2_on;
    uint8_t    h1_on;
    uint8_t    dffe_mode;
    uint8_t    fm1_mode;
    uint8_t    fm2_mode;
    uint8_t    fm3_mode;
};

struct uphy_reg_ae_eq_train_ctrl4_id1 {
    uint8_t    h2_on;
    uint8_t    h1_on;
    uint8_t    dffe_mode;
    uint8_t    fm1_mode;
    uint8_t    fm2_mode;
    uint8_t    fm3_mode;
};

struct uphy_reg_ae_eq_train_ctrl4_id2 {
    uint8_t    h2_on;
    uint8_t    h1_on;
    uint8_t    dffe_mode;
    uint8_t    fm1_mode;
    uint8_t    fm2_mode;
    uint8_t    fm3_mode;
};

struct uphy_reg_ae_eq_train_ctrl4_id3 {
    uint8_t    h2_on;
    uint8_t    h1_on;
    uint8_t    dffe_mode;
    uint8_t    fm1_mode;
    uint8_t    fm2_mode;
    uint8_t    fm3_mode;
};

struct uphy_reg_ae_eq_train_ctrl4_id4 {
    uint8_t    h2_on;
    uint8_t    h1_on;
    uint8_t    dffe_mode;
    uint8_t    fm1_mode;
    uint8_t    fm2_mode;
    uint8_t    fm3_mode;
};

struct uphy_reg_ae_eq_train_ctrl5_id0 {
    uint8_t    apply_h0_eth_ovrd;
    uint8_t    eth_auto;
};

struct uphy_reg_ae_eq_train_ctrl5_id1 {
    uint8_t    apply_h0_eth_ovrd;
    uint8_t    eth_auto;
};

struct uphy_reg_ae_eq_train_ctrl5_id2 {
    uint8_t    apply_h0_eth_ovrd;
    uint8_t    eth_auto;
};

struct uphy_reg_ae_eq_train_ctrl5_id3 {
    uint8_t    apply_h0_eth_ovrd;
    uint8_t    eth_auto;
};

struct uphy_reg_ae_eq_train_ctrl5_id4 {
    uint8_t    apply_h0_eth_ovrd;
    uint8_t    eth_auto;
};

struct uphy_reg_ae_eq_term_attn_ctrl_id0 {
    uint8_t    lpf_hfg_en;
    uint8_t    attn_time;
    uint8_t    attn_step;
    uint8_t    attn_max;
    uint8_t    attn_min;
};

struct uphy_reg_ae_eq_term_attn_ctrl_id1 {
    uint8_t    lpf_hfg_en;
    uint8_t    attn_time;
    uint8_t    attn_step;
    uint8_t    attn_max;
    uint8_t    attn_min;
};

struct uphy_reg_ae_eq_ctle_ctrl_id0 {
    uint8_t    grid_skp_hfg;
    uint8_t    grid_skp_dcg;
    uint8_t    grid_skp_mfg;
    uint8_t    grid_skp_mfp;
    uint8_t    grid_skp_lfg;
    uint8_t    grid_skp_lfp;
    uint8_t    ctle_preset_max;
};

struct uphy_reg_ae_eq_ctle_ctrl_id1 {
    uint8_t    grid_skp_hfg;
    uint8_t    grid_skp_dcg;
    uint8_t    grid_skp_mfg;
    uint8_t    grid_skp_mfp;
    uint8_t    grid_skp_lfg;
    uint8_t    grid_skp_lfp;
    uint8_t    ctle_preset_max;
};

struct uphy_reg_ae_eq_ctle_dc_gain_ctrl_id0 {
    uint8_t    dc_gain_step;
    uint8_t    dc_gain_max;
    uint8_t    dc_gain_min;
};

struct uphy_reg_ae_eq_ctle_dc_gain_ctrl_id1 {
    uint8_t    dc_gain_step;
    uint8_t    dc_gain_max;
    uint8_t    dc_gain_min;
};

struct uphy_reg_ae_eq_ctle_lf_gain_ctrl_id0 {
    uint8_t    lf_gain_step;
    uint8_t    lf_gain_max;
    uint8_t    lf_gain_min;
};

struct uphy_reg_ae_eq_ctle_lf_gain_ctrl_id1 {
    uint8_t    lf_gain_step;
    uint8_t    lf_gain_max;
    uint8_t    lf_gain_min;
};

struct uphy_reg_ae_eq_ctle_lf_pole_ctrl_id0 {
    uint8_t    lf_pole_step;
    uint8_t    lf_pole_max;
    uint8_t    lf_pole_min;
};

struct uphy_reg_ae_eq_ctle_lf_pole_ctrl_id1 {
    uint8_t    lf_pole_step;
    uint8_t    lf_pole_max;
    uint8_t    lf_pole_min;
};

struct uphy_reg_ae_eq_ctle_mf_gain_ctrl_id0 {
    uint8_t    mf_gain_step;
    uint8_t    mf_gain_max;
    uint8_t    mf_gain_min;
};

struct uphy_reg_ae_eq_ctle_mf_gain_ctrl_id1 {
    uint8_t    mf_gain_step;
    uint8_t    mf_gain_max;
    uint8_t    mf_gain_min;
};

struct uphy_reg_ae_eq_ctle_mf_pole_ctrl_id0 {
    uint8_t    mf_pole_step;
    uint8_t    mf_pole_max;
    uint8_t    mf_pole_min;
};

struct uphy_reg_ae_eq_ctle_mf_pole_ctrl_id1 {
    uint8_t    mf_pole_step;
    uint8_t    mf_pole_max;
    uint8_t    mf_pole_min;
};

struct uphy_reg_ae_eq_ctle_hf_gain_ctrl_id0 {
    uint8_t    hf_gain_step;
    uint8_t    hf_gain_max;
    uint8_t    hf_gain_min;
};

struct uphy_reg_ae_eq_ctle_hf_gain_ctrl_id1 {
    uint8_t    hf_gain_step;
    uint8_t    hf_gain_max;
    uint8_t    hf_gain_min;
};

struct uphy_reg_ae_eq_vga_gain_ctrl_id0 {
    uint8_t    vga_gain_step;
    uint8_t    vga_gain_max;
    uint8_t    vga_gain_min;
};

struct uphy_reg_ae_eq_vga_gain_ctrl_id1 {
    uint8_t    vga_gain_step;
    uint8_t    vga_gain_max;
    uint8_t    vga_gain_min;
};

struct uphy_reg_ae_eq_cdr_offset_ctrl0_id0 {
    uint8_t    cdr_offset_max;
    uint8_t    cdr_offset_min;
};

struct uphy_reg_ae_eq_cdr_offset_ctrl0_id1 {
    uint8_t    cdr_offset_max;
    uint8_t    cdr_offset_min;
};

struct uphy_reg_ae_eq_cdr_offset_ctrl1_id0 {
    uint8_t    cdr_offset_time;
    uint8_t    cdr_offset_step;
};

struct uphy_reg_ae_eq_cdr_offset_ctrl1_id1 {
    uint8_t    cdr_offset_time;
    uint8_t    cdr_offset_step;
};

struct uphy_reg_ae_eq_agc_ctrl0_id0 {
    uint8_t    zmax_targ_hi;
    uint8_t    zmax_targ_lo;
};

struct uphy_reg_ae_eq_agc_ctrl0_id1 {
    uint8_t    zmax_targ_hi;
    uint8_t    zmax_targ_lo;
};

struct uphy_reg_ae_eq_agc_ctrl1_id0 {
    uint8_t    zmax_targ_hi;
    uint8_t    zmax_targ_lo;
};

struct uphy_reg_ae_eq_agc_ctrl1_id1 {
    uint8_t    zmax_targ_hi;
    uint8_t    zmax_targ_lo;
};

struct uphy_reg_ae_eq_agc_ctrl2_id0 {
    uint8_t    feq_vref_iters;
    uint8_t    attn_iters;
    uint8_t    peq_vref_iters;
    uint8_t    vga_iters;
};

struct uphy_reg_ae_eq_agc_ctrl2_id1 {
    uint8_t    feq_vref_iters;
    uint8_t    attn_iters;
    uint8_t    peq_vref_iters;
    uint8_t    vga_iters;
};

struct uphy_reg_ae_eq_adc_vref_val_ctrl0_id0 {
    uint8_t    vref_val_max;
    uint8_t    vref_val_min;
};

struct uphy_reg_ae_eq_adc_vref_val_ctrl0_id1 {
    uint8_t    vref_val_max;
    uint8_t    vref_val_min;
};

struct uphy_reg_ae_eq_adc_vref_val_ctrl1_id0 {
    uint8_t    vref_time;
    uint8_t    peq_adc_vref_step;
    uint8_t    feq_adc_vref_step;
};

struct uphy_reg_ae_eq_adc_vref_val_ctrl1_id1 {
    uint8_t    vref_time;
    uint8_t    peq_adc_vref_step;
    uint8_t    feq_adc_vref_step;
};

struct uphy_reg_ae_eq_ffe_ctrl0_id0 {
    uint8_t    f1_adapt_sel;
    uint16_t    cdr_spin_ffe_mask;
};

struct uphy_reg_ae_eq_ffe_ctrl0_id1 {
    uint8_t    f1_adapt_sel;
    uint16_t    cdr_spin_ffe_mask;
};

struct uphy_reg_ae_eq_ffe_ctrl1_id0 {
    uint8_t    ffe_outer_taps_gain_trk;
    uint8_t    ffe_inner_taps_gain_trk;
    uint8_t    ffe_outer_taps_gain_acq;
    uint8_t    ffe_inner_taps_gain_acq;
};

struct uphy_reg_ae_eq_ffe_ctrl1_id1 {
    uint8_t    ffe_outer_taps_gain_trk;
    uint8_t    ffe_inner_taps_gain_trk;
    uint8_t    ffe_outer_taps_gain_acq;
    uint8_t    ffe_inner_taps_gain_acq;
};

struct uphy_reg_ae_eq_ffe_ctrl2 {
    uint8_t    ffe_grad;
    uint16_t    ffe_grad_inv;
};

struct uphy_reg_ae_eq_ffe_cstr_ctrl {
    uint8_t    ffe_cstr_fom_th;
    uint8_t    ffe_cstr_grid_ovrd;
    uint8_t    ffe_cstr_grid_val;
    uint8_t    feq_adc_cal_off_ovrd_val;
    uint8_t    feq_adc_cal_off_ovrd;
    uint8_t    ffe_cstr_oe_sum_th;
    uint8_t    ffe_cstr_mode_en;
};

struct uphy_reg_ae_eq_dffe_ctrl0 {
    uint8_t    feq_dffe_iters;
    uint8_t    feq_dffe_delay;
    uint8_t    peq_dffe_iters;
    uint8_t    peq_dffe_delay;
};

struct uphy_reg_ae_eq_dffe_ctrl1 {
    uint8_t    max_taps;
    uint8_t    hsum_min;
};

struct uphy_reg_ae_eq_dffe_ctrl2 {
    uint8_t    grad_inv;
    uint8_t    gmac_gain;
};

struct uphy_reg_ae_eq_slicer_ctrl0_id0 {
    uint8_t    future_bit_sel;
    uint8_t    th_delta_scale;
};

struct uphy_reg_ae_eq_slicer_ctrl0_id1 {
    uint8_t    future_bit_sel;
    uint8_t    th_delta_scale;
};

struct uphy_reg_ae_eq_slicer_ctrl1_id0 {
    uint8_t    eth7_6_0_gain_acq;
    uint8_t    eth5_1_gain_acq;
    uint8_t    eth4_2_gain_acq;
    uint8_t    eth3_gain_acq;
};

struct uphy_reg_ae_eq_slicer_ctrl1_id1 {
    uint8_t    eth7_6_0_gain_acq;
    uint8_t    eth5_1_gain_acq;
    uint8_t    eth4_2_gain_acq;
    uint8_t    eth3_gain_acq;
};

struct uphy_reg_ae_eq_slicer_ctrl2_id0 {
    uint8_t    eth7_6_0_gain_trk;
    uint8_t    eth5_1_gain_trk;
    uint8_t    eth4_2_gain_trk;
    uint8_t    eth3_gain_trk;
};

struct uphy_reg_ae_eq_slicer_ctrl2_id1 {
    uint8_t    eth7_6_0_gain_trk;
    uint8_t    eth5_1_gain_trk;
    uint8_t    eth4_2_gain_trk;
    uint8_t    eth3_gain_trk;
};

struct uphy_reg_ae_eq_slicer_ctrl3 {
    uint8_t    eth_grad_inv;
};

struct uphy_reg_ae_eq_dme_ctrl {
    uint8_t    trk_time;
    uint8_t    ieee_safe_mode_en;
};

struct uphy_reg_ae_eq_shc_ctrl0 {
    uint8_t    en_mu_cdr_os;
    uint8_t    en_mu_lfp;
    uint8_t    en_mu_mfp;
    uint8_t    en_mu_lfg;
    uint8_t    en_mu_mfg;
    uint8_t    en_mu_hfg;
    uint8_t    en_mu_dcg;
    uint8_t    shc_mutate_cnt;
    uint8_t    shc_pgrid_srch_en;
};

struct uphy_reg_ae_eq_shc_ctrl1 {
    uint8_t    mfp_ln_ord;
    uint8_t    lfg_ln_ord;
    uint8_t    mfg_ln_ord;
    uint8_t    hfg_ln_ord;
    uint8_t    dcg_ln_ord;
};

struct uphy_reg_ae_eq_shc_ctrl2 {
    uint8_t    cdr_os_ln_ord;
    uint8_t    lfp_ln_ord;
};

struct uphy_reg_ae_eq_shc_dcg_ctrl {
    uint8_t    dcg_rslice;
    uint8_t    dcg_radius;
};

struct uphy_reg_ae_eq_shc_lfg_ctrl {
    uint8_t    lfg_rslice;
    uint8_t    lfg_radius;
};

struct uphy_reg_ae_eq_shc_lfp_ctrl {
    uint8_t    lfp_rslice;
    uint8_t    lfp_radius;
};

struct uphy_reg_ae_eq_shc_mfg_ctrl {
    uint8_t    mfg_rslice;
    uint8_t    mfg_radius;
};

struct uphy_reg_ae_eq_shc_mfp_ctrl {
    uint8_t    mfp_rslice;
    uint8_t    mfp_radius;
};

struct uphy_reg_ae_eq_shc_hfg_ctrl {
    uint8_t    hfg_rslice;
    uint8_t    hfg_radius;
};

struct uphy_reg_ae_eq_shc_cdr_offset_ctrl {
    uint8_t    cdr_os_mu_scale;
    uint8_t    cdr_os_rslice;
    uint8_t    cdr_os_radius;
};

struct uphy_reg_ae_eq_misc_ctrl_id0 {
    uint8_t    spare_ctrl;
};

struct uphy_reg_ae_eq_misc_ctrl_id1 {
    uint8_t    spare_ctrl;
};

struct uphy_reg_ae_eq_slicer_state_ctrl {
    uint8_t    eth_state_ovrd;
    uint8_t    eth_state;
    uint8_t    eth_op_ovrd;
    uint8_t    eth_op;
};

struct uphy_reg_ae_eq_valid_ctrl {
    uint8_t    eq_init_ovrd;
    uint8_t    eq_train_valid_ovrd;
    uint8_t    eq_train_valid;
};

struct uphy_reg_ae_term_attn_stat {
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_ctle_stat0 {
    uint8_t    hf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_stat1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_vga_stat {
    uint8_t    vga_gain;
};

struct uphy_reg_ae_adc_vref_stat {
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_cdr_offset_stat {
    uint8_t    cdr_offset;
};

struct uphy_reg_ae_ffe_stat0 {
    uint8_t    ffe_fm2;
    uint8_t    ffe_fm3;
};

struct uphy_reg_ae_ffe_stat1 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_ffe_stat2 {
    uint8_t    ffe_f3;
    uint8_t    ffe_f2;
};

struct uphy_reg_ae_ffe_stat3 {
    uint8_t    ffe_f5;
    uint8_t    ffe_f4;
};

struct uphy_reg_ae_ffe_stat4 {
    uint8_t    ffe_f7;
    uint8_t    ffe_f6;
};

struct uphy_reg_ae_ffe_stat5 {
    uint8_t    ffe_f8;
};

struct uphy_reg_ae_dffe_stat0 {
    uint8_t    dffe_dsel1;
    uint8_t    dffe_coef1;
    uint8_t    dffe_dsel0;
    uint8_t    dffe_coef0;
};

struct uphy_reg_ae_dffe_stat1 {
    uint8_t    dffe_dsel3;
    uint8_t    dffe_coef3;
    uint8_t    dffe_dsel2;
    uint8_t    dffe_coef2;
};

struct uphy_reg_ae_dffe_stat2 {
    uint8_t    dffe_dsel5;
    uint8_t    dffe_coef5;
    uint8_t    dffe_dsel4;
    uint8_t    dffe_coef4;
};

struct uphy_reg_ae_dffe_stat3 {
    uint8_t    dffe_dsel7;
    uint8_t    dffe_coef7;
    uint8_t    dffe_dsel6;
    uint8_t    dffe_coef6;
};

struct uphy_reg_ae_dffe_stat4 {
    uint8_t    dffe_dsel8;
    uint8_t    dffe_coef8;
};

struct uphy_reg_ae_slicer_th0_stat {
    uint16_t    th0;
};

struct uphy_reg_ae_slicer_th1_stat {
    uint16_t    th1;
};

struct uphy_reg_ae_slicer_th2_stat {
    uint16_t    th2;
};

struct uphy_reg_ae_slicer_th3_stat {
    uint16_t    th3;
};

struct uphy_reg_ae_slicer_th4_stat {
    uint16_t    th4;
};

struct uphy_reg_ae_slicer_th5_stat {
    uint16_t    th5;
};

struct uphy_reg_ae_slicer_th6_stat {
    uint16_t    th6;
};

struct uphy_reg_ae_slicer_th7_stat {
    uint16_t    th7;
};

struct uphy_reg_ae_slicer_th8_stat {
    uint16_t    th8;
};

struct uphy_reg_ae_slicer_th9_stat {
    uint16_t    th9;
};

struct uphy_reg_ae_slicer_th10_stat {
    uint16_t    th10;
};

struct uphy_reg_ae_slicer_th11_stat {
    uint16_t    th11;
};

struct uphy_reg_ae_slicer_th12_stat {
    uint16_t    th12;
};

struct uphy_reg_ae_slicer_th13_stat {
    uint16_t    th13;
};

struct uphy_reg_ae_slicer_th14_stat {
    uint16_t    th14;
};

struct uphy_reg_ae_slicer_th15_stat {
    uint16_t    th15;
};

struct uphy_reg_ae_slicer_th16_stat {
    uint16_t    th16;
};

struct uphy_reg_ae_slicer_th17_stat {
    uint16_t    th17;
};

struct uphy_reg_ae_slicer_th18_stat {
    uint16_t    th18;
};

struct uphy_reg_ae_slicer_th19_stat {
    uint16_t    th19;
};

struct uphy_reg_ae_slicer_th20_stat {
    uint16_t    th20;
};

struct uphy_reg_ae_slicer_th21_stat {
    uint16_t    th21;
};

struct uphy_reg_ae_slicer_h0_stat {
    uint16_t    h0;
};

struct uphy_reg_ae_slicer_h1_stat {
    uint16_t    h1;
};

struct uphy_reg_ae_slicer_h2_stat {
    uint16_t    h2;
};

struct uphy_reg_ae_eq_slicer_state_stat {
    uint8_t    eth_clk_en;
    uint8_t    eth_state;
    uint8_t    eth_op;
};

struct uphy_reg_ae_term_attn_ctx_ctrl {
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_ctle_ctx_ctrl0 {
    uint8_t    hf_gain;
    uint8_t    dc_gain;
};

struct uphy_reg_ae_ctle_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_vga_ctx_ctrl {
    uint8_t    vga_gain;
};

struct uphy_reg_ae_adc_vref_ctx_ctrl {
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_cdr_offset_ctx_ctrl {
    uint8_t    cdr_offset;
};

struct uphy_reg_ae_ffe_ctx_ctrl0 {
    uint8_t    ffe_fm2;
    uint8_t    ffe_fm3;
};

struct uphy_reg_ae_ffe_ctx_ctrl1 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_ffe_ctx_ctrl2 {
    uint8_t    ffe_f3;
    uint8_t    ffe_f2;
};

struct uphy_reg_ae_ffe_ctx_ctrl3 {
    uint8_t    ffe_f5;
    uint8_t    ffe_f4;
};

struct uphy_reg_ae_ffe_ctx_ctrl4 {
    uint8_t    ffe_f7;
    uint8_t    ffe_f6;
};

struct uphy_reg_ae_ffe_ctx_ctrl5 {
    uint8_t    ffe_f8;
};

struct uphy_reg_ae_dffe_ctx_ctrl0 {
    uint8_t    dffe_dsel1;
    uint8_t    dffe_coef1;
    uint8_t    dffe_dsel0;
    uint8_t    dffe_coef0;
};

struct uphy_reg_ae_dffe_ctx_ctrl1 {
    uint8_t    dffe_dsel3;
    uint8_t    dffe_coef3;
    uint8_t    dffe_dsel2;
    uint8_t    dffe_coef2;
};

struct uphy_reg_ae_dffe_ctx_ctrl2 {
    uint8_t    dffe_dsel5;
    uint8_t    dffe_coef5;
    uint8_t    dffe_dsel4;
    uint8_t    dffe_coef4;
};

struct uphy_reg_ae_dffe_ctx_ctrl3 {
    uint8_t    dffe_dsel7;
    uint8_t    dffe_coef7;
    uint8_t    dffe_dsel6;
    uint8_t    dffe_coef6;
};

struct uphy_reg_ae_slicer_eth0_ctx_ctrl {
    uint16_t    eth0;
};

struct uphy_reg_ae_slicer_eth1_ctx_ctrl {
    uint16_t    eth1;
};

struct uphy_reg_ae_slicer_eth2_ctx_ctrl {
    uint16_t    eth2;
};

struct uphy_reg_ae_slicer_eth3_ctx_ctrl {
    uint16_t    eth3;
};

struct uphy_reg_ae_slicer_eth4_ctx_ctrl {
    uint16_t    eth4;
};

struct uphy_reg_ae_slicer_eth5_ctx_ctrl {
    uint16_t    eth5;
};

struct uphy_reg_ae_slicer_eth6_ctx_ctrl {
    uint16_t    eth6;
};

struct uphy_reg_ae_slicer_eth7_ctx_ctrl {
    uint16_t    eth7;
};

struct uphy_reg_ae_eq_state_ctx_ctrl {
    uint8_t    feq_adc_cal_off;
    uint8_t    dffe_peq_en;
    uint8_t    dffe_feq_en;
    uint8_t    eq_train_valid;
    uint8_t    eq_initialized;
};

struct uphy_reg_ae_fe_adc_vos_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_adc_vos_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_adc_vos_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_adc_vos_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_fe_adc_gos_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_adc_gos_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_adc_gos_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_adc_gos_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_fe_vga_vos0_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_vga_vos0_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_vga_vos0_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_vga_vos0_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_fe_vga_vos1_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_vga_vos1_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_vga_vos1_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_vga_vos1_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_fe_ctle_vos_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_ctle_vos_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_ctle_vos_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_ctle_vos_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_fe_scal_phos_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_scal_phos_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_scal_phos_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_scal_phos_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_fe_dme_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_dme_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_dme_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_dme_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_fe_signal_det_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_signal_det_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_signal_det_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_signal_det_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_fe_incr_vos_ctx_ctrl0 {
    uint8_t    vga_gain;
    uint8_t    hf_gain;
    uint8_t    dc_gain;
    uint8_t    term_lpf;
    uint8_t    term_attn_ctrl;
};

struct uphy_reg_ae_fe_incr_vos_ctx_ctrl1 {
    uint8_t    mf_pole;
    uint8_t    mf_gain;
    uint8_t    lf_pole;
    uint8_t    lf_gain;
};

struct uphy_reg_ae_fe_incr_vos_ctx_ctrl2 {
    uint8_t    ffe_f2;
    uint8_t    adc_vref_val;
};

struct uphy_reg_ae_fe_incr_vos_ctx_ctrl3 {
    uint8_t    ffe_f1;
    uint8_t    ffe_fm1;
};

struct uphy_reg_ae_eom_ctrl0 {
    uint8_t    sth_start_mode;
    uint8_t    eom_vsign;
    uint8_t    eye_index;
    uint8_t    fom_init_time;
    uint8_t    fom_timeout;
    uint8_t    ber_grad_inv;
    uint8_t    eom_mode;
};

struct uphy_reg_ae_eom_ctrl1 {
    uint8_t    ber_rnk1_mask;
    uint8_t    ber_rnk2_mask;
};

struct uphy_reg_ae_eom_sth_ovrd_ctrl {
    uint8_t    sth_ovrd;
};

struct uphy_reg_ae_eom_sth_ctrl0 {
    uint16_t    sth0;
};

struct uphy_reg_ae_eom_sth_ctrl1 {
    uint16_t    sth1;
};

struct uphy_reg_ae_eom_sth_ctrl2 {
    uint16_t    sth2;
};

struct uphy_reg_ae_eom_sth_ctrl3 {
    uint16_t    sth3;
};

struct uphy_reg_ae_eom_sth_ctrl4 {
    uint16_t    sth4;
};

struct uphy_reg_ae_eom_sth_ctrl5 {
    uint16_t    sth5;
};

struct uphy_reg_ae_eom_sth_ctrl6 {
    uint16_t    sth6;
};

struct uphy_reg_ae_eom_sth_ctrl7 {
    uint16_t    sth7;
};

struct uphy_reg_ae_eom_sym_filter_ctrl {
    uint8_t    future_d_sel;
    uint8_t    pam2_future_bitpat;
    uint8_t    ber_xk_ovrd;
    uint8_t    xk_mask;
    uint8_t    xk_pattern;
    uint8_t    xk_match;
};

struct uphy_reg_ae_eom_mode_txfir_ctrl0 {
    uint8_t    txfir_cm1_response;
    uint8_t    txfir_cm3_grad_inv;
    uint8_t    txfir_cm2_grad_inv;
    uint8_t    txfir_cm1_grad_inv;
    uint8_t    txfir_c0_grad_inv;
    uint8_t    skip_fom;
    uint8_t    txfir_cm3_th;
};

struct uphy_reg_ae_eom_mode_txfir_ctrl1 {
    uint8_t    txfir_cm2_th;
    uint8_t    txfir_cm1_th;
};

struct uphy_reg_ae_eom_vt_ctrl {
    uint16_t    ber_v;
    uint8_t    ber_t;
};

struct uphy_reg_ae_eom_fom_cdr_offset_ctrl_id0 {
    uint8_t    cdr_offset_scale;
    uint8_t    cdr_offset_max;
    uint8_t    cdr_offset_min;
};

struct uphy_reg_ae_eom_fom_cdr_offset_ctrl_id1 {
    uint8_t    cdr_offset_scale;
    uint8_t    cdr_offset_max;
    uint8_t    cdr_offset_min;
};

struct uphy_reg_ae_feq_fom_hyst_ctrl {
    uint8_t    peq_fom_hyst_th;
    uint8_t    lnsrch_fom_hyst_th;
    uint8_t    fom_hyst_th;
};

struct uphy_reg_ae_eom_meas_mode_ctrl {
    uint8_t    fom_mode;
    uint8_t    eom_fmr_sel;
    uint8_t    eom_fmr_ovrd;
    uint8_t    fom_norm_max_en;
    uint8_t    eom_grad;
    uint8_t    ber_mode;
};

struct uphy_reg_ae_eom_meas_ber_ctrl {
    uint8_t    nblks_max;
    uint8_t    nerrs_min;
};

struct uphy_reg_ae_eom_meas_eye_ctrl {
    uint8_t    pam_eye_sel;
    uint8_t    eyeo_range;
    uint8_t    ber_eye_sel;
};

struct uphy_reg_ae_eom_meas_vt_ctrl {
    uint8_t    ber_t;
    uint16_t    ber_v;
};

struct uphy_reg_ae_eom_feq_mode_ctrl_id0 {
    uint8_t    fom_mode;
    uint8_t    eom_fmr_sel;
    uint8_t    eom_fmr_ovrd;
    uint8_t    fom_norm_max_en;
    uint8_t    eom_grad;
    uint8_t    ber_mode;
};

struct uphy_reg_ae_eom_feq_mode_ctrl_id1 {
    uint8_t    fom_mode;
    uint8_t    eom_fmr_sel;
    uint8_t    eom_fmr_ovrd;
    uint8_t    fom_norm_max_en;
    uint8_t    eom_grad;
    uint8_t    ber_mode;
};

struct uphy_reg_ae_eom_feq_ber_ctrl {
    uint8_t    nblks_max;
    uint8_t    nerrs_min;
};

struct uphy_reg_ae_eom_feq_eye_ctrl {
    uint8_t    pam_eye_sel;
    uint8_t    eyeo_range;
    uint8_t    ber_eye_sel;
};

struct uphy_reg_ae_eom_feq_vt_ctrl {
    uint8_t    ber_t;
    uint16_t    ber_v;
};

struct uphy_reg_ae_eom_txfir_mode_ctrl {
    uint8_t    fom_mode;
    uint8_t    eom_fmr_sel;
    uint8_t    eom_fmr_ovrd;
    uint8_t    fom_norm_max_en;
    uint8_t    eom_grad;
    uint8_t    ber_mode;
};

struct uphy_reg_ae_eom_txfir_ber_ctrl {
    uint8_t    nblks_max;
    uint8_t    nerrs_min;
};

struct uphy_reg_ae_eom_txfir_eye_ctrl {
    uint8_t    pam_eye_sel;
    uint8_t    eyeo_range;
    uint8_t    ber_eye_sel;
};

struct uphy_reg_ae_eom_txfir_vt_ctrl {
    uint8_t    ber_t;
    uint16_t    ber_v;
};

struct uphy_reg_ae_eom_adc_zmax_mode_ctrl {
    uint8_t    fom_mode;
    uint8_t    eom_fmr_sel;
    uint8_t    eom_fmr_ovrd;
    uint8_t    fom_norm_max_en;
    uint8_t    eom_grad;
    uint8_t    ber_mode;
};

struct uphy_reg_ae_eom_adc_zmax_ber_ctrl {
    uint8_t    nblks_max;
    uint8_t    nerrs_min;
};

struct uphy_reg_ae_eom_adc_zmax_eye_ctrl {
    uint8_t    pam_eye_sel;
    uint8_t    eyeo_range;
    uint8_t    ber_eye_sel;
};

struct uphy_reg_ae_eom_adc_zmax_vt_ctrl {
    uint8_t    ber_t;
    uint16_t    ber_v;
};

struct uphy_reg_ae_eom_ffe_zmax_mode_ctrl {
    uint8_t    fom_mode;
    uint8_t    eom_fmr_sel;
    uint8_t    eom_fmr_ovrd;
    uint8_t    fom_norm_max_en;
    uint8_t    eom_grad;
    uint8_t    ber_mode;
};

struct uphy_reg_ae_eom_ffe_zmax_ber_ctrl {
    uint8_t    nblks_max;
    uint8_t    nerrs_min;
};

struct uphy_reg_ae_eom_ffe_zmax_eye_ctrl {
    uint8_t    pam_eye_sel;
    uint8_t    eyeo_range;
    uint8_t    ber_eye_sel;
};

struct uphy_reg_ae_eom_ffe_zmax_vt_ctrl {
    uint8_t    ber_t;
    uint16_t    ber_v;
};

struct uphy_reg_ae_eom_peq_mode_ctrl {
    uint8_t    fom_mode;
    uint8_t    eom_fmr_sel;
    uint8_t    eom_fmr_ovrd;
    uint8_t    fom_norm_max_en;
    uint8_t    eom_grad;
    uint8_t    ber_mode;
};

struct uphy_reg_ae_eom_peq_ber_ctrl {
    uint8_t    nblks_max;
    uint8_t    nerrs_min;
};

struct uphy_reg_ae_eom_peq_eye_ctrl {
    uint8_t    pam_eye_sel;
    uint8_t    eyeo_range;
    uint8_t    ber_eye_sel;
};

struct uphy_reg_ae_eom_peq_vt_ctrl {
    uint8_t    ber_t;
    uint16_t    ber_v;
};

struct uphy_reg_ae_eom_signal_det_mode_ctrl {
    uint8_t    fom_mode;
    uint8_t    eom_fmr_sel;
    uint8_t    eom_fmr_ovrd;
    uint8_t    fom_norm_max_en;
    uint8_t    eom_grad;
    uint8_t    ber_mode;
};

struct uphy_reg_ae_eom_signal_det_ber_ctrl {
    uint8_t    nblks_max;
    uint8_t    nerrs_min;
};

struct uphy_reg_ae_eom_signal_det_eye_ctrl {
    uint8_t    pam_eye_sel;
    uint8_t    eyeo_range;
    uint8_t    ber_eye_sel;
};

struct uphy_reg_ae_eom_signal_det_vt_ctrl {
    uint8_t    ber_t;
    uint16_t    ber_v;
};

struct uphy_reg_ae_margin_ctrl0 {
    uint8_t    margin_en;
    uint8_t    margin_t;
    uint8_t    margin_v;
};

struct uphy_reg_ae_margin_ctrl1 {
    uint8_t    margin_pam2pr1_vdm;
    uint8_t    margin_v_scale;
    uint8_t    margin_cdr_trk_time;
    uint8_t    margin_nblks_max;
};

struct uphy_reg_ae_margin_cdr_offset_ctrl_id0 {
    uint8_t    cdr_offset_max;
    uint8_t    cdr_offset_min;
};

struct uphy_reg_ae_margin_cdr_offset_ctrl_id1 {
    uint8_t    cdr_offset_max;
    uint8_t    cdr_offset_min;
};

struct uphy_reg_ae_eom_state_ctrl {
    uint8_t    fom_state_ovrd;
    uint8_t    fom_op_ovrd;
    uint8_t    fom_state;
    uint8_t    fom_op;
};

struct uphy_reg_ae_eom_fom_stat0 {
    uint16_t    fom;
};

struct uphy_reg_ae_eom_fom_stat1 {
    uint16_t    fom;
};

struct uphy_reg_ae_eom_nblks_stat {
    uint16_t    ber_nblks;
};

struct uphy_reg_ae_eom_nerrs_stat {
    uint8_t    fom_timed_out;
    uint8_t    eye_is_closed;
    uint16_t    ber_nerrs;
};

struct uphy_reg_ae_eom_state_stat {
    uint8_t    fom_state;
    uint8_t    fom_op;
};

struct uphy_reg_ae_eom_test_ctrl0 {
    uint8_t    vos_adc_test_en;
    uint8_t    gos_adc_test_en;
    uint8_t    vos_vga_test_en;
    uint8_t    vos_ctle_test_en;
    uint8_t    latch_phos_test_en;
    uint8_t    latch_adc_vos_test_en;
    uint8_t    latch_adc_gos_test_en;
    uint8_t    fom_retest_mode;
    uint8_t    phos_test_en;
    uint8_t    latch_test_mode;
    uint8_t    vos_test_mode;
    uint8_t    fom_test_mode;
};

struct uphy_reg_ae_eom_test_th_ctrl0 {
    uint8_t    vga_vos_threshold;
    uint8_t    ctle_vos_threshold;
};

struct uphy_reg_ae_eom_test_th_ctrl1 {
    uint8_t    adc_vos_threshold;
    uint8_t    adc_gos_threshold;
};

struct uphy_reg_ae_eom_test_th_ctrl2 {
    uint8_t    phos_threshold;
    uint8_t    fom_threshold;
};

struct uphy_reg_ae_eom_test_ae_err_stat {
    uint16_t    ae_err_flag;
};

struct uphy_reg_ae_eom_test_vos_ctle_vga_stat {
    uint8_t    vga_vos_err_flag;
    uint8_t    ctle_vos_err_flag;
};

struct uphy_reg_ae_eom_test_vos_adc0_stat {
    uint8_t    adc0_vos_err_flag;
    uint8_t    adc0_gos_err_flag;
};

struct uphy_reg_ae_eom_test_vos_adc1_stat {
    uint8_t    adc1_vos_err_flag;
    uint8_t    adc1_gos_err_flag;
};

struct uphy_reg_ae_eom_test_vos_adc2_stat {
    uint8_t    adc2_vos_err_flag;
    uint8_t    adc2_gos_err_flag;
};

struct uphy_reg_ae_eom_test_vos_adc3_stat {
    uint8_t    adc3_vos_err_flag;
    uint8_t    adc3_gos_err_flag;
};

struct uphy_reg_ae_eom_test_vos_adc4_stat {
    uint8_t    adc4_vos_err_flag;
    uint8_t    adc4_gos_err_flag;
};

struct uphy_reg_ae_eom_test_vos_adc5_stat {
    uint8_t    adc5_vos_err_flag;
    uint8_t    adc5_gos_err_flag;
};

struct uphy_reg_ae_eom_test_vos_adc6_stat {
    uint8_t    adc6_vos_err_flag;
    uint8_t    adc6_gos_err_flag;
};

struct uphy_reg_ae_eom_test_vos_adc7_stat {
    uint8_t    adc7_vos_err_flag;
    uint8_t    adc7_gos_err_flag;
};

struct uphy_reg_ae_eom_test_phos_stat {
    uint8_t    phos_err_flag;
};

struct uphy_reg_ae_eom_test_latch_adc0_stat {
    uint8_t    adc0_vos_latch_err_flag;
    uint8_t    adc0_gos_latch_err_flag;
};

struct uphy_reg_ae_eom_test_latch_adc1_stat {
    uint8_t    adc1_vos_latch_err_flag;
    uint8_t    adc1_gos_latch_err_flag;
};

struct uphy_reg_ae_eom_test_latch_adc2_stat {
    uint8_t    adc2_vos_latch_err_flag;
    uint8_t    adc2_gos_latch_err_flag;
};

struct uphy_reg_ae_eom_test_latch_adc3_stat {
    uint8_t    adc3_vos_latch_err_flag;
    uint8_t    adc3_gos_latch_err_flag;
};

struct uphy_reg_ae_eom_test_latch_adc4_stat {
    uint8_t    adc4_vos_latch_err_flag;
    uint8_t    adc4_gos_latch_err_flag;
};

struct uphy_reg_ae_eom_test_latch_adc5_stat {
    uint8_t    adc5_vos_latch_err_flag;
    uint8_t    adc5_gos_latch_err_flag;
};

struct uphy_reg_ae_eom_test_latch_adc6_stat {
    uint8_t    adc6_vos_latch_err_flag;
    uint8_t    adc6_gos_latch_err_flag;
};

struct uphy_reg_ae_eom_test_latch_adc7_stat {
    uint8_t    adc7_vos_latch_err_flag;
    uint8_t    adc7_gos_latch_err_flag;
};

struct uphy_reg_ae_eom_test_latch_phos_stat {
    uint8_t    phos_latch_err_flag;
};

struct uphy_reg_bist_pgen_ctrl0 {
    uint8_t    use_mgmt_clk;
    uint8_t    ssprq_seq2_4_noinv_en;
    uint8_t    pattern_shift;
    uint8_t    bist_type;
    uint8_t    clk_en;
    uint8_t    load_en;
    uint8_t    data_en;
    uint8_t    bist_en;
};

struct uphy_reg_bist_pgen_data_ctrl0 {
    uint16_t    pat_data;
};

struct uphy_reg_bist_pgen_data_ctrl1 {
    uint16_t    pat_data;
};

struct uphy_reg_bist_pgen_data_ctrl2 {
    uint16_t    pat_data;
};

struct uphy_reg_bist_pgen_data_ctrl3 {
    uint16_t    pat_data;
};

struct uphy_reg_bist_pchk_ctrl {
    uint8_t    ssprq_seq2_4_noinv_en;
    uint8_t    err_rd_mode;
    uint8_t    fea_mode;
    uint8_t    pattern_shift;
    uint8_t    bist_type;
    uint8_t    invert;
    uint8_t    sync_mode;
    uint8_t    err_clear;
    uint8_t    bist_en;
};

struct uphy_reg_bist_pchk_data_ctrl0 {
    uint16_t    pat_data;
};

struct uphy_reg_bist_pchk_data_ctrl1 {
    uint16_t    pat_data;
};

struct uphy_reg_bist_pchk_data_ctrl2 {
    uint16_t    pat_data;
};

struct uphy_reg_bist_pchk_data_ctrl3 {
    uint16_t    pat_data;
};

struct uphy_reg_bist_err_flg_stat {
    uint8_t    sync_done;
    uint8_t    err_flag;
};

struct uphy_reg_bist_err_cnt_stat {
    uint16_t    err_cnt;
};

struct uphy_reg_bist_err_data_stat0 {
    uint16_t    err_data;
};

struct uphy_reg_bist_err_data_stat1 {
    uint16_t    err_data;
};

struct uphy_reg_bist_err_data_stat2 {
    uint16_t    err_data;
};

struct uphy_reg_bist_err_data_stat3 {
    uint16_t    err_data;
};

struct uphy_reg_mgmt_loop_ctrl0 {
    uint8_t    nea_drv_z_pcal;
    uint8_t    nea_drv_z_ncal;
    uint8_t    nea_mode;
    uint8_t    nea_en;
    uint8_t    ned_en;
    uint8_t    ned_mode;
};

struct uphy_reg_mgmt_loop_ctrl1 {
    uint8_t    rx_adc_fea_subadc_mode;
    uint8_t    rx_adc_fea_subadc_sel;
    uint8_t    rx_afe_fea_ctrl;
    uint8_t    fea_en;
    uint8_t    fea_mode;
};

struct uphy_reg_mgmt_loop_ctrl2 {
    uint8_t    dlm_fea_sel;
    uint8_t    des_fea_sel;
    uint8_t    adc_fea_samp_sel;
    uint8_t    adc_fea_sel;
};

struct uphy_reg_mgmt_loop_ctrl3 {
    uint8_t    fed_mode_ctrl;
    uint8_t    fed_en;
    uint8_t    fed_mode;
    uint8_t    tx2rx_test_in2out_en;
    uint8_t    rx2pll_refclk_en;
};

struct uphy_reg_mgmt_pmu_ctrl0 {
    uint8_t    pmu_ckdiv2;
    uint8_t    pmu_res_ctrl;
    uint8_t    pmu_leveldet_en;
    uint8_t    pmu_rail_cal_en;
    uint8_t    pmu_rail_high;
    uint8_t    pmu_rail_en;
    uint8_t    pmu_sel;
    uint8_t    pmu_rd_mode;
    uint8_t    pmu_chopper_en;
    uint8_t    pmu_en;
};

struct uphy_reg_mgmt_pmu_ctrl1 {
    uint8_t    pmu_fs_sel;
    uint8_t    pmu_bias_time;
    uint8_t    pmu_load_ovrd;
    uint8_t    pmu_load;
    uint8_t    pmu_start_ovrd;
    uint8_t    pmu_start;
    uint8_t    pmu_en_ovrd;
};

struct uphy_reg_mgmt_pmu_th_ctrl0 {
    uint16_t    pmu_th_min;
};

struct uphy_reg_mgmt_pmu_th_ctrl1 {
    uint16_t    pmu_th_max;
};

struct uphy_reg_mgmt_pmu_stat0 {
    uint8_t    pmu_valid;
    uint8_t    pmu_pass;
    uint16_t    pmu_out;
};

struct uphy_reg_mgmt_pmu_stat1 {
    uint8_t    pmu_done;
    uint8_t    pmu_load;
    uint8_t    pmu_start;
    uint8_t    pmu_en;
    uint8_t    pmu_state;
};

struct uphy_reg_mgmt_atest_ctrl0 {
    uint8_t    rx_tah_atest_sel;
    uint8_t    rx_bias_atest_sel;
    uint8_t    rx_atest_sel;
    uint8_t    tx_atest_sel;
};

struct uphy_reg_mgmt_atest_ctrl1 {
    uint8_t    rx_rvdd_atest_sel;
    uint8_t    tx_rvdd_atest_sel;
    uint8_t    rx_clkrcv_atest_sel;
    uint8_t    tx_clkrcv_atest_sel;
};

struct uphy_reg_mgmt_atest_ctrl2 {
    uint8_t    tx_cal_adc_atest_sel;
    uint8_t    tx_txpll_atest_sel;
    uint8_t    tx_clkbuf_atest_sel;
    uint8_t    tx_bias_atest_sel;
};

struct uphy_reg_mgmt_atest_ctrl3 {
    uint8_t    rx_ctle_atest_sel;
    uint8_t    rx_vga_atest_sel;
    uint8_t    rx_term_atest_sel;
};

struct uphy_reg_mgmt_atest_ctrl4 {
    uint8_t    rx_calcomp_atest_sel;
    uint8_t    rx_adc_atest_sel;
    uint8_t    rx_dco_atest_sel;
};

struct uphy_reg_mgmt_clt_ctrl {
    uint8_t    rx_clt_pulldn_en;
    uint8_t    rx_clt_pullup_en;
    uint8_t    tx_clt_pulldn_en;
    uint8_t    tx_clt_pullup_en;
};

struct uphy_reg_mgmt_obs_hsdac_ctrl {
    uint8_t    hsdac_adc_rank2_sel;
    uint8_t    hsdac_adc_rank1_sel;
    uint8_t    hsdac_sel;
};

struct uphy_reg_mgmt_obs_ctrl {
    uint8_t    obs_data_en;
    uint8_t    obs_data_sel;
    uint8_t    obs_data_adc_rank2_sel;
};

struct uphy_reg_mgmt_obs_imem_ctrl {
    uint8_t    obs_imem_wr_en;
};

struct uphy_reg_mgmt_obs_imem_start_addr {
    uint16_t    addr;
};

struct uphy_reg_mgmt_obs_imem_stop_addr {
    uint16_t    addr;
};

struct uphy_reg_mgmt_obs_imem_stat {
    uint8_t    imem_wr_done;
};

struct uphy_reg_mgmt_obs_stat0 {
    uint16_t    obs_data;
};

struct uphy_reg_mgmt_obs_stat1 {
    uint16_t    obs_data;
};

struct uphy_reg_mgmt_obs_stat2 {
    uint16_t    obs_data;
};

struct uphy_reg_mgmt_obs_stat3 {
    uint16_t    obs_data;
};

struct uphy_reg_mgmt_obs_stat4 {
    uint16_t    obs_data;
};

struct uphy_reg_mgmt_obs_stat5 {
    uint16_t    obs_data;
};

struct uphy_reg_mgmt_obs_stat6 {
    uint16_t    obs_data;
};

struct uphy_reg_mgmt_obs_stat7 {
    uint16_t    obs_data;
};

struct uphy_reg_ae_sys_ctrl {
    uint8_t    ae_ao_clk_en_ovrd;
    uint8_t    ae_ao_clk_en;
    uint8_t    cnt_clear;
    uint8_t    ae_clk_halt_time;
    uint8_t    ae_done_width;
    uint8_t    adc_res_ovrd;
    uint8_t    ae_clk_req_ovrd;
};

struct uphy_reg_ae_sys_lfsr_ctrl0 {
    uint8_t    load_seed_mask;
    uint8_t    load_seed_mode;
    uint8_t    load_en;
};

struct uphy_reg_ae_sys_lfsr_ctrl1 {
    uint16_t    load_val;
};

struct uphy_reg_ae_sys_lfsr_ctrl2 {
    uint16_t    load_val;
};

struct uphy_reg_ae_sys_stat {
    uint8_t    error_ffe_cstr;
    uint8_t    ae_tsense;
    uint8_t    margin_valid;
    uint8_t    fe_ovrd_context;
    uint8_t    ae_state;
};

struct uphy_reg_ae_sys_rxinit_stat {
    uint8_t    abort_cnt;
    uint8_t    done_cnt;
};

struct uphy_reg_ae_sys_cdr_seq_stat {
    uint8_t    abort_cnt;
    uint8_t    done_cnt;
};

struct uphy_reg_ae_sys_cal_stat {
    uint8_t    abort_cnt;
    uint8_t    done_cnt;
};

struct uphy_reg_ae_sys_eq_stat {
    uint8_t    abort_cnt;
    uint8_t    done_cnt;
};

struct uphy_reg_ae_sys_eom_stat {
    uint8_t    abort_cnt;
    uint8_t    done_cnt;
};

struct uphy_reg_ae_sys_margin_stat {
    uint8_t    yield_cnt;
    uint8_t    done_cnt;
};

struct uphy_reg_ae_sys_misc0_ctrl {
    uint16_t    misc0;
};

struct uphy_reg_ae_sys_misc1_ctrl {
    uint16_t    misc1;
};

struct uphy_reg_ae_sys_misc2_ctrl {
    uint16_t    misc2;
};

struct uphy_reg_ae_sys_misc3_ctrl {
    uint16_t    misc3;
};

struct uphy_reg_ae_sys_misc0_stat {
    uint16_t    misc0;
};

struct uphy_reg_ae_sys_misc1_stat {
    uint16_t    misc1;
};

struct uphy_reg_ae_sys_imem_ram_ctrl {
    uint8_t    imem_chksm_en;
    uint8_t    imem_rd_en;
    uint8_t    imem_wr_en;
};

struct uphy_reg_ae_sys_imem_ram_clk_ctrl {
    uint8_t    obs_imem_clk_en;
    uint8_t    imem_clk_en_ovrd;
    uint8_t    imem_wclk_mux_async_mode;
    uint8_t    imem_wclk_mux_sel;
    uint8_t    imem_rclk_mux_sel_ovrd;
    uint8_t    imem_rclk_mux_async_mode;
    uint8_t    imem_rclk_mux_sel;
};

struct uphy_reg_ae_sys_imem_start_addr_ctrl {
    uint16_t    addr;
};

struct uphy_reg_ae_sys_imem_stop_addr_ctrl {
    uint16_t    addr;
};

struct uphy_reg_ae_sys_imem_bmap0_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap1_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap2_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap3_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap4_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap5_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap6_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap7_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap8_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap9_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap10_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap11_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap12_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap13_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap14_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap15_key_ctrl {
    uint8_t    vld;
    uint16_t    key;
};

struct uphy_reg_ae_sys_imem_bmap0_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap1_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap2_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap3_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap4_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap5_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap6_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap7_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap8_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap9_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap10_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap11_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap12_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap13_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap14_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_bmap15_val_ctrl {
    uint16_t    val;
};

struct uphy_reg_ae_sys_imem_ram_data_ctrl {
    uint16_t    wdata;
};

struct uphy_reg_ae_sys_imem_ram_chksm_ctrl {
    uint16_t    chksm;
};

struct uphy_reg_ae_sys_imem_ram_stat {
    uint8_t    imem_rclk_mux_switch_status;
    uint8_t    imem_wclk_mux_switch_status;
    uint8_t    imem_chksm_status;
    uint8_t    imem_chksm_done;
    uint8_t    imem_rd_done;
    uint8_t    imem_rd_rdy;
    uint8_t    imem_wr_done;
    uint8_t    imem_wr_rdy;
};

struct uphy_reg_ae_sys_imem_ram_data_stat {
    uint16_t    rdata;
};

struct uphy_reg_ae_sys_imem_ram_chksm_stat {
    uint16_t    chksm;
};

struct uphy_reg_ae_sys_dmem_ctrl {
    uint8_t    nop_stackerr_clr;
    uint8_t    nop_dbg_cmd;
    uint8_t    nop2nox_dmem_if_ovrd;
    uint8_t    nox2nop_dmem_if_ovrd;
};

struct uphy_reg_ae_sys_dmem_addr_ctrl {
    uint16_t    addr;
};

struct uphy_reg_ae_sys_dmem_wdata_ctrl {
    uint16_t    wdata;
};

struct uphy_reg_ae_sys_dmem_rdata_ctrl {
    uint16_t    rdata;
};

struct uphy_reg_ae_sys_dmem_addr_stat {
    uint16_t    nop_dmem_addr;
};

struct uphy_reg_ae_sys_dmem_wdata_stat {
    uint16_t    nop_dmem_wdata;
};

struct uphy_reg_ae_sys_dmem_rdata_stat {
    uint16_t    nox_dmem_rdata;
};

struct uphy_reg_ae_sys_nop_dbg_ctrl {
    uint16_t    nop_dbg_data;
};

struct uphy_reg_ae_sys_nop_p_stat {
    uint16_t    nop_p;
};

struct uphy_reg_ae_sys_nop_i_stat {
    uint16_t    nop_i;
};

struct uphy_reg_ae_sys_nop_t_stat {
    uint16_t    nop_t;
};

struct uphy_reg_ae_sys_nop_n_stat {
    uint16_t    nop_n;
};

struct uphy_reg_ae_sys_nop_r_stat {
    uint16_t    nop_r;
};

struct uphy_reg_ae_sys_nop_stat {
    uint8_t    nop_rs_unf;
    uint8_t    nop_ds_unf;
    uint8_t    nop_rs_ovf;
    uint8_t    nop_ds_ovf;
    uint8_t    nop_dmem_write;
    uint8_t    nop_bkpt_triggered;
    uint8_t    nop_rsp;
    uint8_t    nop_dsp;
};


/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Function declarations
 ***********************************************/

uint8_t uphy_reg_cln_cfg_id_ctrl_bkv_minor_get(const char *buf);
uint8_t uphy_reg_cln_cfg_id_ctrl_bkv_major_get(const char *buf);
uint8_t uphy_reg_cln_cfg_id_ctrl_variant_get(const char *buf);
uint8_t uphy_reg_cln_cfg_id_ctrl_protocol_get(const char *buf);
int cln_cfg_id_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_pllc_dco_coarse_stat_id0_cal_abort_sticky_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id0_cal_abort_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id0_cal_valid_sticky_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id0_dco_coarse_get(const char *buf);
int pllc_dco_coarse_stat_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_pllc_dco_coarse_stat_id1_cal_abort_sticky_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id1_cal_abort_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id1_cal_valid_sticky_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id1_dco_coarse_get(const char *buf);
int pllc_dco_coarse_stat_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_pllc_dco_coarse_stat_id2_cal_abort_sticky_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id2_cal_abort_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id2_cal_valid_sticky_get(const char *buf);
uint8_t uphy_reg_pllc_dco_coarse_stat_id2_dco_coarse_get(const char *buf);
int pllc_dco_coarse_stat_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_pllc_dlf_accu_stat0_accu1_out_get(const char *buf);
int pllc_dlf_accu_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_pllc_dlf_accu_stat1_accu2_out_get(const char *buf);
int pllc_dlf_accu_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_bgap_fuse_ctrl_speedo_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_bgap_fuse_ctrl_cvb_trim_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_bgap_fuse_ctrl_bg_trim_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_bgap_fuse_ctrl_speedo_get(const char *buf);
uint8_t uphy_reg_mgmt_bgap_fuse_ctrl_cvb_trim_get(const char *buf);
uint8_t uphy_reg_mgmt_bgap_fuse_ctrl_bg_trim_get(const char *buf);
int mgmt_bgap_fuse_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_rcal_stat2_clndln_rcal_val_get(const char *buf);
uint8_t uphy_reg_rcal_stat2_clndln_rcal_tx_p_val_get(const char *buf);
uint8_t uphy_reg_rcal_stat2_clndln_rcal_tx_n_val_get(const char *buf);
uint8_t uphy_reg_rcal_stat2_lmx_rcal_val_get(const char *buf);
int rcal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_dln_cfg_tx_id_ctrl_bkv_minor_get(const char *buf);
uint8_t uphy_reg_dln_cfg_tx_id_ctrl_bkv_major_get(const char *buf);
uint8_t uphy_reg_dln_cfg_tx_id_ctrl_variant_get(const char *buf);
uint8_t uphy_reg_dln_cfg_tx_id_ctrl_protocol_get(const char *buf);
int dln_cfg_tx_id_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_dln_cfg_rx_id_ctrl_bkv_minor_get(const char *buf);
uint8_t uphy_reg_dln_cfg_rx_id_ctrl_bkv_major_get(const char *buf);
uint8_t uphy_reg_dln_cfg_rx_id_ctrl_variant_get(const char *buf);
uint8_t uphy_reg_dln_cfg_rx_id_ctrl_protocol_get(const char *buf);
int dln_cfg_rx_id_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_dln_master_ctrl_fast_sim_get(const char *buf);
uint8_t uphy_reg_dln_master_ctrl_bist_sync_rd_mode_get(const char *buf);
uint8_t uphy_reg_dln_master_ctrl_ae_sync_rd_mode_get(const char *buf);
uint8_t uphy_reg_dln_master_ctrl_rx_sync_rd_mode_get(const char *buf);
uint8_t uphy_reg_dln_master_ctrl_txcal_adc_sync_rd_mode_get(const char *buf);
uint8_t uphy_reg_dln_master_ctrl_txpll_fll_sync_rd_mode_get(const char *buf);
uint8_t uphy_reg_dln_master_ctrl_mgmt_sync_rd_mode_get(const char *buf);
int dln_master_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_dln_clk_ctrl_pdes_clk_mux_async_mode_get(const char *buf);
uint8_t uphy_reg_dln_clk_ctrl_pdes_clk_mux_clk_sel_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_clk_ctrl_pdes_clk_mux_clk_sel_get(const char *buf);
uint8_t uphy_reg_dln_clk_ctrl_fed_tx_clk_mux_async_mode_get(const char *buf);
uint8_t uphy_reg_dln_clk_ctrl_pll_clk_en_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_clk_ctrl_mgmt_clk_en_ovrd_get(const char *buf);
int dln_clk_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_dln_irq_ovrd_nop_rs_unf_error_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_irq_ovrd_nop_rs_ovf_error_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_irq_ovrd_nop_ds_unf_error_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_irq_ovrd_nop_ds_ovf_error_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_irq_ovrd_peq_adc_overload_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_irq_ovrd_feq_adc_overload_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_irq_ovrd_cdr_error_ovrd_get(const char *buf);
uint8_t uphy_reg_dln_irq_ovrd_imem_chksm_error_ovrd_get(const char *buf);
int dln_irq_ovrd_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_dln_irq_clear_nop_rsunf_error_clear_get(const char *buf);
uint8_t uphy_reg_dln_irq_clear_nop_rsovf_error_clear_get(const char *buf);
uint8_t uphy_reg_dln_irq_clear_nop_dsunf_error_clear_get(const char *buf);
uint8_t uphy_reg_dln_irq_clear_nop_dsovf_error_clear_get(const char *buf);
uint8_t uphy_reg_dln_irq_clear_peq_adc_overload_clear_get(const char *buf);
uint8_t uphy_reg_dln_irq_clear_feq_adc_overload_clear_get(const char *buf);
uint8_t uphy_reg_dln_irq_clear_cdr_error_clear_get(const char *buf);
uint8_t uphy_reg_dln_irq_clear_imem_chksm_error_clear_get(const char *buf);
int dln_irq_clear_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_dln_irq_mask_nop_rsunf_error_mask_get(const char *buf);
uint8_t uphy_reg_dln_irq_mask_nop_rsovf_error_mask_get(const char *buf);
uint8_t uphy_reg_dln_irq_mask_nop_dsunf_error_mask_get(const char *buf);
uint8_t uphy_reg_dln_irq_mask_nop_dsovf_error_mask_get(const char *buf);
uint8_t uphy_reg_dln_irq_mask_peq_adc_overload_mask_get(const char *buf);
uint8_t uphy_reg_dln_irq_mask_feq_adc_overload_mask_get(const char *buf);
uint8_t uphy_reg_dln_irq_mask_cdr_error_mask_get(const char *buf);
uint8_t uphy_reg_dln_irq_mask_imem_chksm_error_mask_get(const char *buf);
int dln_irq_mask_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_dln_irq_stat_nop_rsunf_error_get(const char *buf);
uint8_t uphy_reg_dln_irq_stat_nop_rsovf_error_get(const char *buf);
uint8_t uphy_reg_dln_irq_stat_nop_dsunf_error_get(const char *buf);
uint8_t uphy_reg_dln_irq_stat_nop_dsovf_error_get(const char *buf);
uint8_t uphy_reg_dln_irq_stat_peq_adc_overload_get(const char *buf);
uint8_t uphy_reg_dln_irq_stat_feq_adc_overload_get(const char *buf);
uint8_t uphy_reg_dln_irq_stat_cdr_error_get(const char *buf);
uint8_t uphy_reg_dln_irq_stat_imem_chksm_error_get(const char *buf);
int dln_irq_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_dln_misc_ctrl_misc_out_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_misc_ctrl_pwr_valid_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_misc_ctrl_hvdddet_ctrl_get(const char *buf);
int mgmt_dln_misc_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_dln_fuse_ctrl_speedo_get(const char *buf);
int mgmt_dln_fuse_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_dln_misc_stat_pdes_clk_mux_switch_status_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_misc_stat_tx_fifo_clk_mux_switch_status_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_misc_stat_misc_ctrl_get(const char *buf);
int mgmt_dln_misc_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_dln_cln_stat_pll_clk_en_req_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_cln_stat_mgmt_clk_en_req_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_cln_stat_pll_b_clk_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_cln_stat_pll_a_clk_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_cln_stat_bg_valid_get(const char *buf);
int mgmt_dln_cln_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_dln_cln_rcal_stat_rcal_tx_p_val_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_cln_rcal_stat_rcal_tx_n_val_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_cln_rcal_stat_rcal_val_get(const char *buf);
int mgmt_dln_cln_rcal_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_dln_intf_stat_rx_rate_id_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_intf_stat_tx_rate_id_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_intf_stat_rx_pstate_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_intf_stat_tx_pstate_get(const char *buf);
int mgmt_dln_intf_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_dln_pss_stat_rx_pll_clk_valid_error_flag_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_pss_stat_rx_pss_state_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_pss_stat_tx_pll_clk_valid_error_flag_get(const char *buf);
uint8_t uphy_reg_mgmt_dln_pss_stat_tx_pss_state_get(const char *buf);
int mgmt_dln_pss_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rcal_ctrl_rx_rcal_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_rcal_ctrl_tx_rcal_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_rcal_ctrl_rx_rcal_val_get(const char *buf);
uint8_t uphy_reg_mgmt_rcal_ctrl_tx_rcal_p_val_get(const char *buf);
uint8_t uphy_reg_mgmt_rcal_ctrl_tx_rcal_n_val_get(const char *buf);
int mgmt_rcal_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rcal_stat_rx_term_rcal_val_get(const char *buf);
uint8_t uphy_reg_mgmt_rcal_stat_rx_rcal_val_get(const char *buf);
uint8_t uphy_reg_mgmt_rcal_stat_tx_cal_p_val_get(const char *buf);
uint8_t uphy_reg_mgmt_rcal_stat_tx_cal_n_val_get(const char *buf);
int mgmt_rcal_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_aeintf_stat_tx_cal_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_stat_tx_dco_cal_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_stat_tx_pss_ready_get(const char *buf);
int mgmt_tx_aeintf_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_aeintf_dcocal_stat_state_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_dcocal_stat_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_dcocal_stat_abort_req_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_dcocal_stat_abort_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_dcocal_stat_done_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_dcocal_stat_ack_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_dcocal_stat_req_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_dcocal_stat_en_get(const char *buf);
int mgmt_tx_aeintf_dcocal_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_aeintf_txcal_stat_state_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_txcal_stat_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_txcal_stat_abort_req_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_txcal_stat_abort_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_txcal_stat_done_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_txcal_stat_ack_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_txcal_stat_req_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_aeintf_txcal_stat_en_get(const char *buf);
int mgmt_tx_aeintf_txcal_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_aeintf_stat_margin_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_stat_eom_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_stat_eq_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_stat_cal_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_stat_rxinit_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_stat_rx_cdr_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_stat_rx_data_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_stat_rx_pss_ready_get(const char *buf);
int mgmt_rx_aeintf_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_aeintf_rxinit_stat_state_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_rxinit_stat_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_rxinit_stat_abort_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_rxinit_stat_abort_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_rxinit_stat_done_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_rxinit_stat_ack_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_rxinit_stat_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_rxinit_stat_en_get(const char *buf);
int mgmt_rx_aeintf_rxinit_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_aeintf_cal_stat_state_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_cal_stat_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_cal_stat_abort_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_cal_stat_abort_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_cal_stat_done_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_cal_stat_ack_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_cal_stat_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_cal_stat_en_get(const char *buf);
int mgmt_rx_aeintf_cal_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_aeintf_eq_stat_state_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eq_stat_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eq_stat_abort_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eq_stat_abort_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eq_stat_done_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eq_stat_ack_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eq_stat_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eq_stat_en_get(const char *buf);
int mgmt_rx_aeintf_eq_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_aeintf_eom_stat_state_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eom_stat_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eom_stat_abort_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eom_stat_abort_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eom_stat_done_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eom_stat_ack_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eom_stat_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_eom_stat_en_get(const char *buf);
int mgmt_rx_aeintf_eom_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_aeintf_margin_stat_state_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_margin_stat_idle_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_margin_stat_abort_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_margin_stat_abort_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_margin_stat_done_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_margin_stat_ack_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_margin_stat_req_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_aeintf_margin_stat_en_get(const char *buf);
int mgmt_rx_aeintf_margin_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_ctrl_dac_pattern_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_dac_pattern_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_tsync_rstb_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_tsync_rstb_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_tdata_ready_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_tdata_ready_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_tsync_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_tsync_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_tsync_en_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_xdigclk_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_txclkref_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_disable_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_term_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_ctrl_cmh_mode_get(const char *buf);
int mgmt_tx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_ctrl_tsense_ovrd_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_ctrl_tsense_ovrd_val_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_ctrl_rx_xdigclk_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_ctrl_pdes_data_clamp_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_ctrl_pdes_clk_switch_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_ctrl_ac_mode_get(const char *buf);
int mgmt_rx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_tx_clkbuf_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_tx_pll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_tx_clk_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_iqdcc_cal_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_txpll_bypass_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_txpll_bypass_postdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_xdigclk_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_txclkref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_tx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id0_modulation_get(const char *buf);
int mgmt_tx_rate_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_tx_clkbuf_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_tx_pll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_tx_clk_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_iqdcc_cal_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_txpll_bypass_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_txpll_bypass_postdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_xdigclk_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_txclkref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_tx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id1_modulation_get(const char *buf);
int mgmt_tx_rate_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_tx_clkbuf_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_tx_pll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_tx_clk_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_iqdcc_cal_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_txpll_bypass_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_txpll_bypass_postdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_xdigclk_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_txclkref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_tx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id2_modulation_get(const char *buf);
int mgmt_tx_rate_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_tx_clkbuf_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_tx_pll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_tx_clk_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_iqdcc_cal_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_txpll_bypass_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_txpll_bypass_postdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_xdigclk_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_txclkref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_tx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id3_modulation_get(const char *buf);
int mgmt_tx_rate_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_tx_clkbuf_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_tx_pll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_tx_clk_id_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_iqdcc_cal_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_txpll_bypass_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_txpll_bypass_postdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_xdigclk_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_txclkref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_tx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl0_id4_modulation_get(const char *buf);
int mgmt_tx_rate_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id0_tx_fifo_wptr_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id0_sync_dly_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id0_tclk_dly_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id0_dac_predrv_eq_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id0_ser_clk_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id0_ser_flush_time_get(const char *buf);
int mgmt_tx_rate_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id1_tx_fifo_wptr_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id1_sync_dly_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id1_tclk_dly_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id1_dac_predrv_eq_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id1_ser_clk_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id1_ser_flush_time_get(const char *buf);
int mgmt_tx_rate_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id2_tx_fifo_wptr_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id2_sync_dly_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id2_tclk_dly_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id2_dac_predrv_eq_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id2_ser_clk_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id2_ser_flush_time_get(const char *buf);
int mgmt_tx_rate_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id3_tx_fifo_wptr_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id3_sync_dly_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id3_tclk_dly_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id3_dac_predrv_eq_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id3_ser_clk_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id3_ser_flush_time_get(const char *buf);
int mgmt_tx_rate_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id4_tx_fifo_wptr_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id4_sync_dly_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id4_tclk_dly_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id4_dac_predrv_eq_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id4_ser_clk_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rate_ctrl1_id4_ser_flush_time_get(const char *buf);
int mgmt_tx_rate_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id0_adc_res_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id0_mlsd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id0_cdrpd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id0_modulation_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id0_eqtarget_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id0_rx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id0_rank2_way_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id0_rx_nway_get(const char *buf);
int mgmt_rx_rate_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id1_adc_res_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id1_mlsd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id1_cdrpd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id1_modulation_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id1_eqtarget_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id1_rx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id1_rank2_way_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id1_rx_nway_get(const char *buf);
int mgmt_rx_rate_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id2_adc_res_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id2_mlsd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id2_cdrpd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id2_modulation_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id2_eqtarget_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id2_rx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id2_rank2_way_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id2_rx_nway_get(const char *buf);
int mgmt_rx_rate_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id3_adc_res_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id3_mlsd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id3_cdrpd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id3_modulation_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id3_eqtarget_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id3_rx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id3_rank2_way_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id3_rx_nway_get(const char *buf);
int mgmt_rx_rate_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id4_adc_res_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id4_mlsd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id4_cdrpd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id4_modulation_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id4_eqtarget_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id4_rx_rate_pdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id4_rank2_way_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl0_id4_rx_nway_get(const char *buf);
int mgmt_rx_rate_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id0_des_xdigclk_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id0_margin_aeintf_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id0_rx_cdr_misc_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id0_rx_cdr_fll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id0_rx_clk_id_get(const char *buf);
int mgmt_rx_rate_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id1_des_xdigclk_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id1_margin_aeintf_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id1_rx_cdr_misc_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id1_rx_cdr_fll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id1_rx_clk_id_get(const char *buf);
int mgmt_rx_rate_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id2_des_xdigclk_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id2_margin_aeintf_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id2_rx_cdr_misc_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id2_rx_cdr_fll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id2_rx_clk_id_get(const char *buf);
int mgmt_rx_rate_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id3_des_xdigclk_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id3_margin_aeintf_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id3_rx_cdr_misc_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id3_rx_cdr_fll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id3_rx_clk_id_get(const char *buf);
int mgmt_rx_rate_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id4_des_xdigclk_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id4_margin_aeintf_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id4_rx_cdr_misc_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id4_rx_cdr_fll_id_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rate_ctrl1_id4_rx_clk_id_get(const char *buf);
int mgmt_rx_rate_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_tx_enc_ctrl_pam4_2b_lut_get(const char *buf);
int tx_enc_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_rx_dec_ctrl_pam4_2b_lut_get(const char *buf);
uint8_t uphy_reg_rx_dec_ctrl_pam4_dme_lut_get(const char *buf);
uint8_t uphy_reg_rx_dec_ctrl_pam2_pr1_inv_get(const char *buf);
uint8_t uphy_reg_rx_dec_ctrl_pam2_pr0_inv_get(const char *buf);
uint8_t uphy_reg_rx_dec_ctrl_pam2_dme_inv_get(const char *buf);
uint8_t uphy_reg_rx_dec_ctrl_rx_dec_infer_ckg_en_get(const char *buf);
int rx_dec_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl0_entry120_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl0_entry110_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl0_entry101_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl0_entry100_time_get(const char *buf);
int mgmt_tx_timer_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl1_entry210_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl1_entry200_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl1_entry140_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl1_entry130_time_get(const char *buf);
int mgmt_tx_timer_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl2_entry250_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl2_entry240_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl2_entry230_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl2_entry220_time_get(const char *buf);
int mgmt_tx_timer_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl3_entry310_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl3_entry302_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl3_entry301_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl3_entry300_time_get(const char *buf);
int mgmt_tx_timer_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl4_entry400_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl4_entry321_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl4_entry320_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl4_entry311_time_get(const char *buf);
int mgmt_tx_timer_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl5_entry411_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl5_entry410_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl5_entry402_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl5_entry401_time_get(const char *buf);
int mgmt_tx_timer_ctrl5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl6_entry500_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl6_entry440_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl6_entry430_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl6_entry420_time_get(const char *buf);
int mgmt_tx_timer_ctrl6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl7_exit200_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl7_exit100_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl7_entry520_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl7_entry510_time_get(const char *buf);
int mgmt_tx_timer_ctrl7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl8_exit400_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl8_exit310_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl8_exit300_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl8_exit210_time_get(const char *buf);
int mgmt_tx_timer_ctrl8_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl9_exit600_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl9_exit510_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl9_exit500_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl9_exit410_time_get(const char *buf);
int mgmt_tx_timer_ctrl9_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl10_exit730_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl10_exit720_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl10_exit710_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl10_exit700_time_get(const char *buf);
int mgmt_tx_timer_ctrl10_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id0_txpll_nocal_lock_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id0_exit740_time_get(const char *buf);
int mgmt_tx_timer_ctrl11_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id1_txpll_nocal_lock_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id1_exit740_time_get(const char *buf);
int mgmt_tx_timer_ctrl11_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id2_txpll_nocal_lock_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id2_exit740_time_get(const char *buf);
int mgmt_tx_timer_ctrl11_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id3_txpll_nocal_lock_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id3_exit740_time_get(const char *buf);
int mgmt_tx_timer_ctrl11_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id4_txpll_nocal_lock_time_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_timer_ctrl11_id4_exit740_time_get(const char *buf);
int mgmt_tx_timer_ctrl11_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl0_entry200_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl0_entry120_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl0_entry110_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl0_entry100_time_get(const char *buf);
int mgmt_rx_timer_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl1_entry400_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl1_entry300_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl1_entry220_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl1_entry210_time_get(const char *buf);
int mgmt_rx_timer_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl2_entry600_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl2_entry510_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl2_entry500_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl2_entry410_time_get(const char *buf);
int mgmt_rx_timer_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl3_entry620_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl3_entry611_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl3_entry610_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl3_entry601_time_get(const char *buf);
int mgmt_rx_timer_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl4_entry720_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl4_entry710_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl4_entry700_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl4_entry621_time_get(const char *buf);
int mgmt_rx_timer_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl5_entry900_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl5_entry810_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl5_entry800_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl5_entry730_time_get(const char *buf);
int mgmt_rx_timer_ctrl5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl6_exit100_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl6_entry930_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl6_entry920_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl6_entry910_time_get(const char *buf);
int mgmt_rx_timer_ctrl6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl7_exit230_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl7_exit220_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl7_exit210_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl7_exit200_time_get(const char *buf);
int mgmt_rx_timer_ctrl7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl8_exit320_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl8_exit310_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl8_exit301_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl8_exit300_time_get(const char *buf);
int mgmt_rx_timer_ctrl8_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl9_exit410_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl9_exit400_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl9_exit330_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl9_exit321_time_get(const char *buf);
int mgmt_rx_timer_ctrl9_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl10_exit600_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl10_exit500_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl10_exit412_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl10_exit411_time_get(const char *buf);
int mgmt_rx_timer_ctrl10_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl11_exit810_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl11_exit801_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl11_exit800_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl11_exit700_time_get(const char *buf);
int mgmt_rx_timer_ctrl11_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_timer_ctrl12_exit900_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_timer_ctrl12_exit820_time_get(const char *buf);
int mgmt_rx_timer_ctrl12_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_pss_ctrl_pss_timer_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_pss_ctrl_pss_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_pss_ctrl_pss_state_get(const char *buf);
int mgmt_tx_pss_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_pss_ctrl_pss_timer_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_pss_ctrl_pss_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_pss_ctrl_pss_state_get(const char *buf);
int mgmt_rx_pss_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_pss_valid_ctrl_rx_dco_vld_mask_get(const char *buf);
uint8_t uphy_reg_mgmt_pss_valid_ctrl_tx_iqdcc_vld_mask_get(const char *buf);
uint8_t uphy_reg_mgmt_pss_valid_ctrl_tx_dco_vld_mask_get(const char *buf);
uint8_t uphy_reg_mgmt_pss_valid_ctrl_tx_p0p3p0_dco_nocal_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_pss_valid_ctrl_tx_p0p2p0_dco_nocal_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_pss_valid_ctrl_rx_clkrcv_ls_en_clk_error_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_pss_valid_ctrl_tx_drv_clk_ls_en_clk_error_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_pss_valid_ctrl_tx_ser_clk_ls_en_clk_error_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_pss_valid_ctrl_tx_clkrcv_ls_en_clk_error_ovrd_get(const char *buf);
int mgmt_pss_valid_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rvdd_ctrl0_data_rvdd_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl0_hsclk_rvdd_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl0_lsclk_rvdd_ctrl_get(const char *buf);
int mgmt_tx_rvdd_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rvdd_ctrl1_data_rvdd_vref_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl1_hsclk_rvdd_vref_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl1_lsclk_rvdd_vref_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl1_data_rvdd_leaker_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl1_hsclk_rvdd_leaker_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl1_lsclk_rvdd_leaker_mode_get(const char *buf);
int mgmt_tx_rvdd_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_data_rvdd_diode_clamp_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_hsclk_rvdd_diode_clamp_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_lsclk_rvdd_diode_clamp_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_data_rvdd_rz_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_data_rvdd_gm2_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_hsclk_rvdd_rz_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_hsclk_rvdd_gm2_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_lsclk_rvdd_rz_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_rvdd_ctrl2_lsclk_rvdd_gm2_ctrl_get(const char *buf);
int mgmt_tx_rvdd_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rvdd_ctrl0_data_rvdd_vref_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl0_clk_rvdd_vref_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl0_data_rvdd_leaker_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl0_clk_rvdd_leaker_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl0_data_rvdd_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl0_clk_rvdd_ctrl_get(const char *buf);
int mgmt_rx_rvdd_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_rvdd_ctrl1_data_rvdd_diode_clamp_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl1_clk_rvdd_diode_clamp_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl1_data_rvdd_rz_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl1_data_rvdd_gm2_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl1_clk_rvdd_rz_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_rvdd_ctrl1_clk_rvdd_gm2_ctrl_get(const char *buf);
int mgmt_rx_rvdd_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id0_clkrcv_ac_bypass_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id0_clkrcv_bias_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id0_clkrcv_ls_r_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id0_clkrcv_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id0_clkrcv_i_ctrl_get(const char *buf);
int mgmt_tx_clkrcv_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id1_clkrcv_ac_bypass_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id1_clkrcv_bias_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id1_clkrcv_ls_r_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id1_clkrcv_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkrcv_ctrl_id1_clkrcv_i_ctrl_get(const char *buf);
int mgmt_tx_clkrcv_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id0_clkrcv_ac_bypass_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id0_clkrcv_bias_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id0_clkrcv_ls_r_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id0_clkrcv_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id0_clkrcv_i_ctrl_get(const char *buf);
int mgmt_rx_clkrcv_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id1_clkrcv_ac_bypass_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id1_clkrcv_bias_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id1_clkrcv_ls_r_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id1_clkrcv_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_clkrcv_ctrl_id1_clkrcv_i_ctrl_get(const char *buf);
int mgmt_rx_clkrcv_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_fifo_ctrl_fifo_chk_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_fifo_ctrl_fifo_skip_wptr_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_fifo_ctrl_fifo_err_hold_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_fifo_ctrl_fifo_err_clr_get(const char *buf);
int mgmt_tx_fifo_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_cal_drv_ctrl_z_pcal_offset_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_cal_drv_ctrl_z_ncal_offset_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_cal_drv_ctrl_z_pcal_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_cal_drv_ctrl_z_ncal_get(const char *buf);
int mgmt_tx_cal_drv_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_bias_ctrl_cgm_ready_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_bias_ctrl_bg_ready_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_bias_ctrl_bias_ready_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_bias_ctrl_cgm_start_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_bias_ctrl_ptat_slope_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_bias_ctrl_ptat_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_bias_ctrl_bg_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_bias_ctrl_ptat_i_ctrl_get(const char *buf);
int mgmt_tx_bias_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_tx_misc_ctrl_misc_ctrl_get(const char *buf);
int mgmt_tx_misc_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_stat_fifo_latency_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_stat_fifo_err_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_stat_rdet_status_get(const char *buf);
int mgmt_tx_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_ctrl_id0_postdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ctrl_id0_ndiv_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ctrl_id0_mdiv_get(const char *buf);
int mgmt_txpll_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_ctrl_id1_postdiv_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ctrl_id1_ndiv_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ctrl_id1_mdiv_get(const char *buf);
int mgmt_txpll_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_dco_ctrl_id0_dco_fine_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_dco_ctrl_id0_dco_coarse_get(const char *buf);
int mgmt_txpll_dco_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_dco_ctrl_id1_dco_fine_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_dco_ctrl_id1_dco_coarse_get(const char *buf);
int mgmt_txpll_dco_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_filter_ctrl0_id0_pfd_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl0_id0_refsel_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_filter_ctrl0_id0_cp_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl0_id0_lpf_c_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl0_id0_lpf_r_ctrl_get(const char *buf);
int mgmt_txpll_filter_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_filter_ctrl0_id1_pfd_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl0_id1_refsel_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_filter_ctrl0_id1_cp_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl0_id1_lpf_c_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl0_id1_lpf_r_ctrl_get(const char *buf);
int mgmt_txpll_filter_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_filter_ctrl1_id0_preset_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl1_id0_slowloop_fastprecharge_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl1_id0_slowloop_c_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl1_id0_slowloop_r_ctrl_get(const char *buf);
int mgmt_txpll_filter_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_filter_ctrl1_id1_preset_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl1_id1_slowloop_fastprecharge_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl1_id1_slowloop_c_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_filter_ctrl1_id1_slowloop_r_ctrl_get(const char *buf);
int mgmt_txpll_filter_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_ro_ctrl0_id0_ro_drv_xcouple_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl0_id0_ro_drv_ctrl_get(const char *buf);
int mgmt_txpll_ro_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_ro_ctrl0_id1_ro_drv_xcouple_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl0_id1_ro_drv_ctrl_get(const char *buf);
int mgmt_txpll_ro_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_ro_ctrl1_id0_ro_c_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl1_id0_ro_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl1_id0_ro_currentsrc_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl1_id0_ro_psrc_diode_ctrl_get(const char *buf);
int mgmt_txpll_ro_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_ro_ctrl1_id1_ro_c_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl1_id1_ro_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl1_id1_ro_currentsrc_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl1_id1_ro_psrc_diode_ctrl_get(const char *buf);
int mgmt_txpll_ro_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_ro_ctrl2_id0_clkgate_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl2_id0_ro_start_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl2_id0_slowloop_kvco_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl2_id0_ro_kvco_ctrl_get(const char *buf);
int mgmt_txpll_ro_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_ro_ctrl2_id1_clkgate_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl2_id1_ro_start_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl2_id1_slowloop_kvco_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_ro_ctrl2_id1_ro_kvco_ctrl_get(const char *buf);
int mgmt_txpll_ro_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id0_bias_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id0_bias_temp_offset_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id0_bias_temp_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id0_bias_ptat_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id0_bias_ctat_i_ctrl_get(const char *buf);
int mgmt_txpll_bias_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id1_bias_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id1_bias_temp_offset_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id1_bias_temp_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id1_bias_ptat_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_bias_ctrl_id1_bias_ctat_i_ctrl_get(const char *buf);
int mgmt_txpll_bias_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_ctrl_id0_txpll_fll_clk_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_ctrl_id0_dco_fine_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_ctrl_id0_dco_coarse_mode_get(const char *buf);
int mgmt_txpll_cal_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_ctrl_id1_txpll_fll_clk_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_ctrl_id1_dco_fine_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_ctrl_id1_dco_coarse_mode_get(const char *buf);
int mgmt_txpll_cal_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl0_id0_fll_hi_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl0_id0_fll_lo_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl0_id0_fravg_window_get(const char *buf);
int mgmt_txpll_cal_coarse_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl0_id1_fll_hi_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl0_id1_fll_lo_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl0_id1_fravg_window_get(const char *buf);
int mgmt_txpll_cal_coarse_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_txpll_cal_coarse_ctrl1_id0_fll_lock_th_get(const char *buf);
int mgmt_txpll_cal_coarse_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_txpll_cal_coarse_ctrl1_id1_fll_lock_th_get(const char *buf);
int mgmt_txpll_cal_coarse_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl2_id0_timeout_time_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_cal_coarse_ctrl2_id0_higear_time_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl2_id0_logear_time_get(const char *buf);
int mgmt_txpll_cal_coarse_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl2_id1_timeout_time_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_cal_coarse_ctrl2_id1_higear_time_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_coarse_ctrl2_id1_logear_time_get(const char *buf);
int mgmt_txpll_cal_coarse_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl0_id0_fll_hi_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl0_id0_fll_lo_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl0_id0_fravg_window_get(const char *buf);
int mgmt_txpll_cal_fine_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl0_id1_fll_hi_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl0_id1_fll_lo_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl0_id1_fravg_window_get(const char *buf);
int mgmt_txpll_cal_fine_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_txpll_cal_fine_ctrl1_id0_fll_lock_th_get(const char *buf);
int mgmt_txpll_cal_fine_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_txpll_cal_fine_ctrl1_id1_fll_lock_th_get(const char *buf);
int mgmt_txpll_cal_fine_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl2_id0_timeout_time_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_cal_fine_ctrl2_id0_higear_time_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl2_id0_logear_time_get(const char *buf);
int mgmt_txpll_cal_fine_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl2_id1_timeout_time_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_cal_fine_ctrl2_id1_higear_time_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_fine_ctrl2_id1_logear_time_get(const char *buf);
int mgmt_txpll_cal_fine_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_state_ctrl_cal_state_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_state_ctrl_cal_state_get(const char *buf);
int mgmt_txpll_cal_state_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_stat_rcal_val_changed_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_stat_dco_fine_cal_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_stat_dco_coarse_cal_valid_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_cal_stat_dco_fine_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_stat_dco_coarse_get(const char *buf);
int mgmt_txpll_cal_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_txpll_cal_fravg_stat_fravg_get(const char *buf);
int mgmt_txpll_cal_fravg_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_state_stat_cal_fll_locked_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_state_stat_cal_state_get(const char *buf);
int mgmt_txpll_cal_state_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_ctx_stat_id0_dco_fine_cal_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_ctx_stat_id0_dco_coarse_cal_valid_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_cal_ctx_stat_id0_dco_fine_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_ctx_stat_id0_dco_coarse_get(const char *buf);
int mgmt_txpll_cal_ctx_stat_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txpll_cal_ctx_stat_id1_dco_fine_cal_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_ctx_stat_id1_dco_coarse_cal_valid_get(const char *buf);
uint16_t uphy_reg_mgmt_txpll_cal_ctx_stat_id1_dco_fine_get(const char *buf);
uint8_t uphy_reg_mgmt_txpll_cal_ctx_stat_id1_dco_coarse_get(const char *buf);
int mgmt_txpll_cal_ctx_stat_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_iqc_ctrl_id0_iqc_iclk_dly_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_iqc_ctrl_id0_iqc_qclk_dly_get(const char *buf);
int mgmt_tx_clkbuf_iqc_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_iqc_ctrl_id1_iqc_iclk_dly_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_iqc_ctrl_id1_iqc_qclk_dly_get(const char *buf);
int mgmt_tx_clkbuf_iqc_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_dly_ctrl_clkbuf_qclk_dly_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dly_ctrl_clkbuf_qclkb_dly_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dly_ctrl_clkbuf_iclk_dly_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dly_ctrl_clkbuf_iclkb_dly_ctrl_get(const char *buf);
int mgmt_tx_clkbuf_dly_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_i_ctrl_id0_dcc_iclk_vref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_i_ctrl_id0_dcc_iclkb_vref_ctrl_get(const char *buf);
int mgmt_tx_clkbuf_dcc_i_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_i_ctrl_id1_dcc_iclk_vref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_i_ctrl_id1_dcc_iclkb_vref_ctrl_get(const char *buf);
int mgmt_tx_clkbuf_dcc_i_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_q_ctrl_id0_dcc_qclk_vref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_q_ctrl_id0_dcc_qclkb_vref_ctrl_get(const char *buf);
int mgmt_tx_clkbuf_dcc_q_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_q_ctrl_id1_dcc_qclk_vref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_q_ctrl_id1_dcc_qclkb_vref_ctrl_get(const char *buf);
int mgmt_tx_clkbuf_dcc_q_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_bypass_ac_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_dcc_loop_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_qilo_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_serclk_dly_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_dcc_chpclk_div_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_dcc_vref_range_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_adc_buf_gain_attn_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_adc_clk_div_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id0_adc_vref_range_get(const char *buf);
int mgmt_tx_clkbuf_misc_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_bypass_ac_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_dcc_loop_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_qilo_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_serclk_dly_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_dcc_chpclk_div_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_dcc_vref_range_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_adc_buf_gain_attn_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_adc_clk_div_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id1_adc_vref_range_get(const char *buf);
int mgmt_tx_clkbuf_misc_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_bypass_ac_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_dcc_loop_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_qilo_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_serclk_dly_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_dcc_chpclk_div_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_dcc_vref_range_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_adc_buf_gain_attn_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_adc_clk_div_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id2_adc_vref_range_get(const char *buf);
int mgmt_tx_clkbuf_misc_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_bypass_ac_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_dcc_loop_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_qilo_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_serclk_dly_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_dcc_chpclk_div_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_dcc_vref_range_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_adc_buf_gain_attn_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_adc_clk_div_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id3_adc_vref_range_get(const char *buf);
int mgmt_tx_clkbuf_misc_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_bypass_ac_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_dcc_loop_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_qilo_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_serclk_dly_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_dcc_chpclk_div_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_dcc_vref_range_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_adc_buf_gain_attn_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_adc_clk_div_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_misc_ctrl_id4_adc_vref_range_get(const char *buf);
int mgmt_tx_clkbuf_misc_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_dac_pattern_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_dac_pattern_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_adc_vsense_sel_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_adc_vsense_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_tx_vsense_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_tx_vsense_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_cal_drv_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_cal_drv_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_cal_adc_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_cal_adc_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_txclk_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_ovrd_ctrl_txclk_en_get(const char *buf);
int mgmt_tx_clkbuf_ovrd_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id0_iqdcc_cal_valid_mask_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id0_iqdcc_cal_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id0_qdcd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id0_idcd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id0_iqc_mode_get(const char *buf);
int mgmt_tx_iqdcc_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id1_iqdcc_cal_valid_mask_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id1_iqdcc_cal_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id1_qdcd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id1_idcd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_ctrl_id1_iqc_mode_get(const char *buf);
int mgmt_tx_iqdcc_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_iter_ctrl_iqc_iter_get(const char *buf);
uint16_t uphy_reg_mgmt_tx_iqdcc_iter_ctrl_tx_idcd_iter_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_iter_ctrl_tx_qdcd_iter_get(const char *buf);
int mgmt_tx_iqdcc_iter_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_timer_ctrl0_adc_en_wait_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_timer_ctrl0_qdcd_settle_wait_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_timer_ctrl0_idcd_settle_wait_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_timer_ctrl0_iqc_settle_wait_get(const char *buf);
int mgmt_tx_iqdcc_timer_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_timer_ctrl1_glbl_iter_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_timer_ctrl1_adc_reset_wait_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_timer_ctrl1_txclk_en_wait_get(const char *buf);
int mgmt_tx_iqdcc_timer_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_adc_res_ctrl_qdcd_adc_res_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_adc_res_ctrl_idcd_adc_res_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_adc_res_ctrl_iqc_adc_res_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_adc_res_ctrl_ofst_adc_res_get(const char *buf);
int mgmt_tx_iqdcc_adc_res_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl0_iqc_grad_inv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl0_iqc_ofst_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl0_xor_iqc_gain_get(const char *buf);
uint16_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl0_tx_iqc_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl0_iqc_gmac_load_val_get(const char *buf);
int mgmt_tx_iqdcc_iqc_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl1_iqc_gmac_delta_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl1_iqc_gmac_delta_max_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl1_iqc_gmac_delta_min_get(const char *buf);
int mgmt_tx_iqdcc_iqc_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_iqc_ctrl2_iqc_diff_ofst_get(const char *buf);
int mgmt_tx_iqdcc_iqc_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl0_idcd_grad_inv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl0_idcd_ofst_gain_get(const char *buf);
uint16_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl0_tx_idcd_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl0_idcd_gmac_load_val_get(const char *buf);
int mgmt_tx_iqdcc_idcd_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl1_idcd_gmac_delta_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl1_idcd_gmac_delta_max_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl1_idcd_gmac_delta_min_get(const char *buf);
int mgmt_tx_iqdcc_idcd_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl2_idcd_diff_ofst_get(const char *buf);
uint16_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl2_dcc_iclkb_ofst_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_idcd_ctrl2_dcc_iclk_ofst_get(const char *buf);
int mgmt_tx_iqdcc_idcd_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl0_qdcd_grad_inv_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl0_qdcd_ofst_gain_get(const char *buf);
uint16_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl0_tx_qdcd_gain_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl0_qdcd_gmac_load_val_get(const char *buf);
int mgmt_tx_iqdcc_qdcd_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl1_qdcd_gmac_delta_en_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl1_qdcd_gmac_delta_max_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl1_qdcd_gmac_delta_min_get(const char *buf);
int mgmt_tx_iqdcc_qdcd_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl2_qdcd_diff_ofst_get(const char *buf);
uint16_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl2_dcc_qclkb_ofst_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_qdcd_ctrl2_dcc_qclk_ofst_get(const char *buf);
int mgmt_tx_iqdcc_qdcd_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_state_ctrl_iqdcc_cal_state_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_state_ctrl_iqdcc_cal_state_get(const char *buf);
int mgmt_tx_iqdcc_state_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_adc_state_ctrl_cal_adc_reset_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_adc_state_ctrl_cal_adc_reset_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_adc_state_ctrl_iqdcc_adc_state_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_adc_state_ctrl_iqdcc_adc_state_get(const char *buf);
int mgmt_tx_iqdcc_adc_state_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_iqc_stat_iqc_qclk_dly_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_iqc_stat_iqc_iclk_dly_get(const char *buf);
int mgmt_tx_clkbuf_iqc_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_i_stat_dcc_iclk_vref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_i_stat_dcc_iclkb_vref_ctrl_get(const char *buf);
int mgmt_tx_clkbuf_dcc_i_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_q_stat_dcc_qclk_vref_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_clkbuf_dcc_q_stat_dcc_qclkb_vref_ctrl_get(const char *buf);
int mgmt_tx_clkbuf_dcc_q_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_state_stat_iqdcc_qdcd_cal_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_state_stat_iqdcc_idcd_cal_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_state_stat_iqdcc_iqc_cal_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_state_stat_iqdcc_cal_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_tx_iqdcc_state_stat_iqdcc_cal_state_get(const char *buf);
int mgmt_tx_iqdcc_state_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_tx_iqdcc_adc_state_stat_iqdcc_adc_state_get(const char *buf);
int mgmt_tx_iqdcc_adc_state_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqterm_ctrl0_p1_max_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_ctrl0_m3_max_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_ctrl0_tx_fir_scale_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_ctrl0_tx_fir_m0_get(const char *buf);
int mgmt_txeqterm_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqterm_ctrl1_main_tp_en_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_ctrl1_m1_max_get(const char *buf);
uint16_t uphy_reg_mgmt_txeqterm_ctrl1_m2_max_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_ctrl1_cmh_iout_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_ctrl1_cmh_vcm_ctrl_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_ctrl1_cmh_vcm_ctrl_get(const char *buf);
int mgmt_txeqterm_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqterm_ctrl2_tx_amp_val_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_ctrl2_tx_amp_ovrd_get(const char *buf);
int mgmt_txeqterm_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqterm_stat0_fir_pre1_get(const char *buf);
uint16_t uphy_reg_mgmt_txeqterm_stat0_fir_post1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_stat0_drv_amp_get(const char *buf);
int mgmt_txeqterm_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqterm_stat1_fir_pre2_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_stat1_fir_pre3_get(const char *buf);
int mgmt_txeqterm_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqterm_stat2_reverved1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_stat2_fir_c0_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_stat2_reverved0_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqterm_stat2_fir_m_get(const char *buf);
int mgmt_txeqterm_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl_txfir_1tap_en_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl_txfir_3tap_en_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl_txfir_5tap_en_get(const char *buf);
int mgmt_txeqlut_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl0_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl0_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl1_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl1_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl2_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl2_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl3_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl3_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl4_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl4_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl5_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl5_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl6_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl6_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl7_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl7_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl8_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl8_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl8_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl9_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl9_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl9_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl10_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl10_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl10_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl11_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl11_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl11_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl12_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl12_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl12_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl13_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl13_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl13_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl14_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl14_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl14_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl15_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl15_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl15_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl16_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl16_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl16_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl17_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl17_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl17_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl18_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl18_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl18_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl19_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl19_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl19_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl20_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl20_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl20_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl21_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl21_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl21_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl22_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl22_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl22_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl23_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl23_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl23_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl24_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl24_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl24_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl25_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl25_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl25_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl26_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl26_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl26_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl27_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl27_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl27_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl28_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl28_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl28_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl29_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl29_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl29_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl30_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl30_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl30_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_txeqlut_ctrl31_lut1_get(const char *buf);
uint8_t uphy_reg_mgmt_txeqlut_ctrl31_lut0_get(const char *buf);
int mgmt_txeqlut_ctrl31_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_term_ctrl0_term_vddod_mode_nonp0_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_term_ctrl0_p3_rxterm_cmfb_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_term_ctrl0_term_cm_mode_nonp0_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_term_ctrl0_term_vddod_mode_p0_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_term_ctrl0_term_cm_mode_p0_get(const char *buf);
int mgmt_rx_term_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_term_ctrl1_term_ota_bw_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_term_ctrl1_term_vcm_ctrl_get(const char *buf);
int mgmt_rx_term_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_tah_ctrl_id0_tah_i_ctrl_get(const char *buf);
int mgmt_rx_tah_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_tah_ctrl_id1_tah_i_ctrl_get(const char *buf);
int mgmt_rx_tah_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_tah_ctrl_id2_tah_i_ctrl_get(const char *buf);
int mgmt_rx_tah_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_tah_ctrl_id3_tah_i_ctrl_get(const char *buf);
int mgmt_rx_tah_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_tah_ctrl_id4_tah_i_ctrl_get(const char *buf);
int mgmt_rx_tah_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_adc_ctrl_ae_rphase_inv_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_adc_ctrl_adc_clkboost_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_adc_ctrl_reg_byp_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_adc_ctrl_reg_byp_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_adc_ctrl_adc_en_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_adc_ctrl_adc_en_get(const char *buf);
int mgmt_rx_adc_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_bias_ctrl_cgm_start_time_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_bias_ctrl_cgm_ready_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_bias_ctrl_bg_ready_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_bias_ctrl_bias_ready_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_bias_ctrl_cgm_start_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_bias_ctrl_ptat_slope_en_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_bias_ctrl_ptat_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_bias_ctrl_bg_i_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_rx_bias_ctrl_ptat_i_ctrl_get(const char *buf);
int mgmt_rx_bias_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_rx_bias_ctrl1_rx_bias_lut_mode_get(const char *buf);
int mgmt_rx_bias_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_rx_misc_ctrl_id0_misc_ctrl_get(const char *buf);
int mgmt_rx_misc_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_rx_misc_ctrl_id1_misc_ctrl_get(const char *buf);
int mgmt_rx_misc_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_rx_misc_ctrl_id2_misc_ctrl_get(const char *buf);
int mgmt_rx_misc_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_ctrl_id0_cdr_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id0_faa_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id0_frdot_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id0_frest_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id0_dco_fine_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id0_dco_coarse_mode_get(const char *buf);
int ae_cdr_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_ctrl_id1_cdr_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id1_faa_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id1_frdot_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id1_frest_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id1_dco_fine_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id1_dco_coarse_mode_get(const char *buf);
int ae_cdr_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_ctrl_id2_cdr_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id2_faa_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id2_frdot_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id2_frest_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id2_dco_fine_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id2_dco_coarse_mode_get(const char *buf);
int ae_cdr_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_ctrl_id3_cdr_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id3_faa_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id3_frdot_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id3_frest_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id3_dco_fine_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id3_dco_coarse_mode_get(const char *buf);
int ae_cdr_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_ctrl_id4_cdr_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id4_faa_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id4_frdot_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id4_frest_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id4_dco_fine_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_ctrl_id4_dco_coarse_mode_get(const char *buf);
int ae_cdr_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl0_id0_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl0_id0_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl0_id1_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl0_id1_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl0_id2_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl0_id2_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl0_id3_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl0_id3_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl0_id4_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl0_id4_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl1_id0_fll_refclk_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id0_dco_i_diode_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id0_dco_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id0_dco_drv_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id0_dco_core_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id0_dco_c_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl1_id1_fll_refclk_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id1_dco_i_diode_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id1_dco_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id1_dco_drv_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id1_dco_core_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id1_dco_c_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl1_id2_fll_refclk_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id2_dco_i_diode_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id2_dco_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id2_dco_drv_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id2_dco_core_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id2_dco_c_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl1_id3_fll_refclk_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id3_dco_i_diode_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id3_dco_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id3_dco_drv_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id3_dco_core_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id3_dco_c_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl1_id4_fll_refclk_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id4_dco_i_diode_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id4_dco_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id4_dco_drv_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id4_dco_core_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl1_id4_dco_c_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl2_bck_trk_pat_sel_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl2_bck_acq_pat_sel_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl2_dco_freq_dac_vref_precharge_en_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl2_dco_phase_dac_precharge_en_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl2_dco_precharge_en_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl2_dco_ls_en_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl2_dco_ls_en_get(const char *buf);
int ae_cdr_dco_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl3_id0_dco_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id0_dco_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id0_dco_r_short_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl3_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl3_id1_dco_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id1_dco_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id1_dco_r_short_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl3_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl3_id2_dco_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id2_dco_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id2_dco_r_short_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl3_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl3_id3_dco_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id3_dco_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id3_dco_r_short_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl3_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctrl3_id4_dco_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id4_dco_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctrl3_id4_dco_r_short_ctrl_get(const char *buf);
int ae_cdr_dco_ctrl3_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_frest_ctrl_cdr_frest_get(const char *buf);
int ae_cdr_frest_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_frdot_ctrl_cdr_frdot_get(const char *buf);
int ae_cdr_frdot_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_state_ctrl_cdr_state_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cdr_state_ctrl_cdr_aeintf_state_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cdr_state_ctrl_cdr_op_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cdr_state_ctrl_cdr_state_get(const char *buf);
uint8_t uphy_reg_ae_cdr_state_ctrl_cdr_aeintf_state_get(const char *buf);
uint8_t uphy_reg_ae_cdr_state_ctrl_cdr_op_get(const char *buf);
int ae_cdr_state_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_div_ctrl_id0_fll_clk_ctrl_get(const char *buf);
int ae_cdr_fll_div_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_div_ctrl_id1_fll_clk_ctrl_get(const char *buf);
int ae_cdr_fll_div_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_div_ctrl_id2_fll_clk_ctrl_get(const char *buf);
int ae_cdr_fll_div_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_div_ctrl_id3_fll_clk_ctrl_get(const char *buf);
int ae_cdr_fll_div_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_div_ctrl_id4_fll_clk_ctrl_get(const char *buf);
int ae_cdr_fll_div_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_dco_coarse_ctrl0_id0_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_dco_coarse_ctrl0_id0_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_dco_coarse_ctrl0_id0_fll_gain_get(const char *buf);
int ae_cdr_fll_dco_coarse_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_dco_coarse_ctrl0_id1_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_dco_coarse_ctrl0_id1_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_dco_coarse_ctrl0_id1_fll_gain_get(const char *buf);
int ae_cdr_fll_dco_coarse_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_dco_coarse_ctrl1_id0_fll_lock_th_get(const char *buf);
int ae_cdr_fll_dco_coarse_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_dco_coarse_ctrl1_id1_fll_lock_th_get(const char *buf);
int ae_cdr_fll_dco_coarse_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_dco_fine_ctrl0_id0_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_dco_fine_ctrl0_id0_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_dco_fine_ctrl0_id0_fll_gain_get(const char *buf);
int ae_cdr_fll_dco_fine_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_dco_fine_ctrl0_id1_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_dco_fine_ctrl0_id1_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_dco_fine_ctrl0_id1_fll_gain_get(const char *buf);
int ae_cdr_fll_dco_fine_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_dco_fine_ctrl1_id0_fll_lock_th_get(const char *buf);
int ae_cdr_fll_dco_fine_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_dco_fine_ctrl1_id1_fll_lock_th_get(const char *buf);
int ae_cdr_fll_dco_fine_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id0_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id0_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id0_fll_gain_get(const char *buf);
int ae_cdr_fll_frest_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id1_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id1_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id1_fll_gain_get(const char *buf);
int ae_cdr_fll_frest_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id2_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id2_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id2_fll_gain_get(const char *buf);
int ae_cdr_fll_frest_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id3_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id3_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id3_fll_gain_get(const char *buf);
int ae_cdr_fll_frest_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id4_fravg_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id4_fravg_window_get(const char *buf);
uint8_t uphy_reg_ae_cdr_fll_frest_ctrl0_id4_fll_gain_get(const char *buf);
int ae_cdr_fll_frest_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_frest_ctrl1_id0_fll_lock_th_get(const char *buf);
int ae_cdr_fll_frest_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_frest_ctrl1_id1_fll_lock_th_get(const char *buf);
int ae_cdr_fll_frest_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_frest_ctrl1_id2_fll_lock_th_get(const char *buf);
int ae_cdr_fll_frest_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_frest_ctrl1_id3_fll_lock_th_get(const char *buf);
int ae_cdr_fll_frest_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fll_frest_ctrl1_id4_fll_lock_th_get(const char *buf);
int ae_cdr_fll_frest_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id0_pll_dsm3_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id0_pll_freq3_gain_get(const char *buf);
uint16_t uphy_reg_ae_cdr_pll_gain_ctrl0_id0_pll_freq2_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id0_pll_freq2_gain_acq_get(const char *buf);
int ae_cdr_pll_gain_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id1_pll_dsm3_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id1_pll_freq3_gain_get(const char *buf);
uint16_t uphy_reg_ae_cdr_pll_gain_ctrl0_id1_pll_freq2_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id1_pll_freq2_gain_acq_get(const char *buf);
int ae_cdr_pll_gain_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id2_pll_dsm3_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id2_pll_freq3_gain_get(const char *buf);
uint16_t uphy_reg_ae_cdr_pll_gain_ctrl0_id2_pll_freq2_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id2_pll_freq2_gain_acq_get(const char *buf);
int ae_cdr_pll_gain_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id3_pll_dsm3_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id3_pll_freq3_gain_get(const char *buf);
uint16_t uphy_reg_ae_cdr_pll_gain_ctrl0_id3_pll_freq2_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id3_pll_freq2_gain_acq_get(const char *buf);
int ae_cdr_pll_gain_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id4_pll_dsm3_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id4_pll_freq3_gain_get(const char *buf);
uint16_t uphy_reg_ae_cdr_pll_gain_ctrl0_id4_pll_freq2_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl0_id4_pll_freq2_gain_acq_get(const char *buf);
int ae_cdr_pll_gain_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_pll_gain_ctrl1_pll_freq2_gain_bck_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_pll_gain_ctrl1_pll_freq2_gain_bck_acq_get(const char *buf);
int ae_cdr_pll_gain_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_seq_ctrl_id0_ccal_phos_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id0_slicers_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id0_cdr_ccal_phos_expiry_time_get(const char *buf);
uint16_t uphy_reg_ae_cdr_seq_ctrl_id0_cdr_slicers_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id0_cdr_pll_acq_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id0_cdr_ccal_start_time_get(const char *buf);
int ae_cdr_seq_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_seq_ctrl_id1_ccal_phos_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id1_slicers_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id1_cdr_ccal_phos_expiry_time_get(const char *buf);
uint16_t uphy_reg_ae_cdr_seq_ctrl_id1_cdr_slicers_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id1_cdr_pll_acq_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id1_cdr_ccal_start_time_get(const char *buf);
int ae_cdr_seq_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_seq_ctrl_id2_ccal_phos_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id2_slicers_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id2_cdr_ccal_phos_expiry_time_get(const char *buf);
uint16_t uphy_reg_ae_cdr_seq_ctrl_id2_cdr_slicers_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id2_cdr_pll_acq_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id2_cdr_ccal_start_time_get(const char *buf);
int ae_cdr_seq_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_seq_ctrl_id3_ccal_phos_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id3_slicers_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id3_cdr_ccal_phos_expiry_time_get(const char *buf);
uint16_t uphy_reg_ae_cdr_seq_ctrl_id3_cdr_slicers_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id3_cdr_pll_acq_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id3_cdr_ccal_start_time_get(const char *buf);
int ae_cdr_seq_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_seq_ctrl_id4_ccal_phos_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id4_slicers_seq_expiry_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id4_cdr_ccal_phos_expiry_time_get(const char *buf);
uint16_t uphy_reg_ae_cdr_seq_ctrl_id4_cdr_slicers_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id4_cdr_pll_acq_time_get(const char *buf);
uint8_t uphy_reg_ae_cdr_seq_ctrl_id4_cdr_ccal_start_time_get(const char *buf);
int ae_cdr_seq_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_feq_train_seq_ctrl_id0_feq_slicers_addl_trk_time_get(const char *buf);
uint16_t uphy_reg_ae_feq_train_seq_ctrl_id0_feq_ccal_phos_expiry_time_get(const char *buf);
uint8_t uphy_reg_ae_feq_train_seq_ctrl_id0_feq_ffe_slicers_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_feq_train_seq_ctrl_id0_cdr_spin_time_get(const char *buf);
int ae_feq_train_seq_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_feq_train_seq_ctrl_id1_feq_slicers_addl_trk_time_get(const char *buf);
uint16_t uphy_reg_ae_feq_train_seq_ctrl_id1_feq_ccal_phos_expiry_time_get(const char *buf);
uint8_t uphy_reg_ae_feq_train_seq_ctrl_id1_feq_ffe_slicers_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_feq_train_seq_ctrl_id1_cdr_spin_time_get(const char *buf);
int ae_feq_train_seq_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_peq_train_seq_ctrl_id0_peq_ffe_eth_time_get(const char *buf);
int ae_peq_train_seq_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_peq_train_seq_ctrl_id1_peq_ffe_eth_time_get(const char *buf);
int ae_peq_train_seq_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_pll_lock_th_ctrl_id0_pll_unlock_th_get(const char *buf);
int ae_cdr_pll_lock_th_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_pll_lock_th_ctrl_id1_pll_unlock_th_get(const char *buf);
int ae_cdr_pll_lock_th_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_pll_lock_th_ctrl_id2_pll_unlock_th_get(const char *buf);
int ae_cdr_pll_lock_th_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_pll_lock_th_ctrl_id3_pll_unlock_th_get(const char *buf);
int ae_cdr_pll_lock_th_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_pll_lock_th_ctrl_id4_pll_unlock_th_get(const char *buf);
int ae_cdr_pll_lock_th_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id0_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id0_freq_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id0_acq_csdet_grad_dup_off_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_gain_ctrl0_id0_phase_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id0_phase_gain_acq_get(const char *buf);
int ae_cdr_dco_gain_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id1_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id1_freq_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id1_acq_csdet_grad_dup_off_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_gain_ctrl0_id1_phase_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id1_phase_gain_acq_get(const char *buf);
int ae_cdr_dco_gain_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id2_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id2_freq_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id2_acq_csdet_grad_dup_off_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_gain_ctrl0_id2_phase_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id2_phase_gain_acq_get(const char *buf);
int ae_cdr_dco_gain_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id3_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id3_freq_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id3_acq_csdet_grad_dup_off_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_gain_ctrl0_id3_phase_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id3_phase_gain_acq_get(const char *buf);
int ae_cdr_dco_gain_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id4_phase_gain_range_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id4_freq_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id4_acq_csdet_grad_dup_off_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_gain_ctrl0_id4_phase_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl0_id4_phase_gain_acq_get(const char *buf);
int ae_cdr_dco_gain_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_dco_gain_ctrl1_phase_gain_bck_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_gain_ctrl1_phase_gain_bck_acq_get(const char *buf);
int ae_cdr_dco_gain_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id0_pll_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id0_freq_dac_loop_en_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id0_freq_dac_vref_sel_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id0_freq_dac_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id0_freq_dsm_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id0_phase_dac_stack_ctrl_get(const char *buf);
int ae_cdr_dco_ph_freq_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id1_pll_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id1_freq_dac_loop_en_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id1_freq_dac_vref_sel_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id1_freq_dac_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id1_freq_dsm_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id1_phase_dac_stack_ctrl_get(const char *buf);
int ae_cdr_dco_ph_freq_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id2_pll_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id2_freq_dac_loop_en_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id2_freq_dac_vref_sel_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id2_freq_dac_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id2_freq_dsm_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id2_phase_dac_stack_ctrl_get(const char *buf);
int ae_cdr_dco_ph_freq_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id3_pll_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id3_freq_dac_loop_en_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id3_freq_dac_vref_sel_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id3_freq_dac_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id3_freq_dsm_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id3_phase_dac_stack_ctrl_get(const char *buf);
int ae_cdr_dco_ph_freq_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id4_pll_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id4_freq_dac_loop_en_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id4_freq_dac_vref_sel_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id4_freq_dac_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id4_freq_dsm_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ph_freq_ctrl_id4_phase_dac_stack_ctrl_get(const char *buf);
int ae_cdr_dco_ph_freq_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id0_bias_filter_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id0_bias_temp_offset_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id0_bias_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id0_bias_temp_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id0_bias_ptat_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id0_bias_ctat_i_ctrl_get(const char *buf);
int ae_cdr_dco_bias_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id1_bias_filter_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id1_bias_temp_offset_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id1_bias_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id1_bias_temp_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id1_bias_ptat_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id1_bias_ctat_i_ctrl_get(const char *buf);
int ae_cdr_dco_bias_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id2_bias_filter_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id2_bias_temp_offset_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id2_bias_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id2_bias_temp_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id2_bias_ptat_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id2_bias_ctat_i_ctrl_get(const char *buf);
int ae_cdr_dco_bias_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id3_bias_filter_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id3_bias_temp_offset_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id3_bias_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id3_bias_temp_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id3_bias_ptat_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id3_bias_ctat_i_ctrl_get(const char *buf);
int ae_cdr_dco_bias_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id4_bias_filter_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id4_bias_temp_offset_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id4_bias_mode_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id4_bias_temp_slope_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id4_bias_ptat_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_bias_ctrl_id4_bias_ctat_i_ctrl_get(const char *buf);
int ae_cdr_dco_bias_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id0_dco_coarse_tune_timeout_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id0_dco_postcharge_time_get(const char *buf);
int ae_cdr_dco_timer_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id1_dco_coarse_tune_timeout_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id1_dco_postcharge_time_get(const char *buf);
int ae_cdr_dco_timer_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id2_dco_coarse_tune_timeout_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id2_dco_postcharge_time_get(const char *buf);
int ae_cdr_dco_timer_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id3_dco_coarse_tune_timeout_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id3_dco_postcharge_time_get(const char *buf);
int ae_cdr_dco_timer_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id4_dco_coarse_tune_timeout_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_timer_ctrl_id4_dco_postcharge_time_get(const char *buf);
int ae_cdr_dco_timer_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_csdet_ctrl_acq_csdet_frdot_off_get(const char *buf);
uint8_t uphy_reg_ae_cdr_csdet_ctrl_pam4_pr1_seq_err_patsel_get(const char *buf);
uint16_t uphy_reg_ae_cdr_csdet_ctrl_csdet_gain_get(const char *buf);
uint8_t uphy_reg_ae_cdr_csdet_ctrl_csdet_err_thres_trk_get(const char *buf);
uint8_t uphy_reg_ae_cdr_csdet_ctrl_csdet_err_thres_acq_get(const char *buf);
int ae_cdr_csdet_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_spin_ctrl_spin_freq_get(const char *buf);
int ae_cdr_spin_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_stat_cdr_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_stat_dco_fine_tune_valid_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_stat_dco_coarse_tune_valid_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_stat_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_stat_dco_coarse_get(const char *buf);
int ae_cdr_dco_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_frest_stat_frest_get(const char *buf);
int ae_cdr_frest_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_frdot_stat_frdot_get(const char *buf);
int ae_cdr_frdot_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_cdr_fravg_stat_fravg_get(const char *buf);
int ae_cdr_fravg_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_stat_cdr_error_cnt_get(const char *buf);
uint8_t uphy_reg_ae_cdr_stat_cdr_error_get(const char *buf);
uint8_t uphy_reg_ae_cdr_stat_cdr_pll_unlocked_get(const char *buf);
uint8_t uphy_reg_ae_cdr_stat_cdr_fll_locked_get(const char *buf);
uint8_t uphy_reg_ae_cdr_stat_cdr_seq_abort_en_get(const char *buf);
uint8_t uphy_reg_ae_cdr_stat_cdr_seq_en_get(const char *buf);
uint8_t uphy_reg_ae_cdr_stat_cdr_pll_en_get(const char *buf);
uint8_t uphy_reg_ae_cdr_stat_cdr_fll_en_get(const char *buf);
int ae_cdr_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_state_stat_cdr_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cdr_state_stat_cdr_state_get(const char *buf);
uint8_t uphy_reg_ae_cdr_state_stat_cdr_aeintf_state_get(const char *buf);
uint8_t uphy_reg_ae_cdr_state_stat_cdr_op_get(const char *buf);
int ae_cdr_state_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id0_cdr_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id0_dco_fine_tune_valid_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id0_dco_coarse_tune_valid_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_ctx_stat_id0_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id0_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctx_stat_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id1_cdr_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id1_dco_fine_tune_valid_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id1_dco_coarse_tune_valid_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_ctx_stat_id1_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id1_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctx_stat_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id2_cdr_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id2_dco_fine_tune_valid_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id2_dco_coarse_tune_valid_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_ctx_stat_id2_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id2_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctx_stat_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id3_cdr_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id3_dco_fine_tune_valid_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id3_dco_coarse_tune_valid_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_ctx_stat_id3_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id3_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctx_stat_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id4_cdr_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id4_dco_fine_tune_valid_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id4_dco_coarse_tune_valid_get(const char *buf);
uint16_t uphy_reg_ae_cdr_dco_ctx_stat_id4_dco_fine_get(const char *buf);
uint8_t uphy_reg_ae_cdr_dco_ctx_stat_id4_dco_coarse_get(const char *buf);
int ae_cdr_dco_ctx_stat_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_vos_ctrl_ctle_vos_get(const char *buf);
int ae_ctle_vos_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_vos_ctrl_vga_vos_gen_vcal_get(const char *buf);
uint8_t uphy_reg_ae_vga_vos_ctrl_vga_vos_get(const char *buf);
int ae_vga_vos_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_ctrl0_adc_vos_wds_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_ctrl0_adc_vos_ren_get(const char *buf);
int ae_adc_cal_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_ctrl1_adc_gain_wds_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_ctrl1_adc_gain_ren_get(const char *buf);
int ae_adc_cal_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_ctrl2_adc_cal_addr_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_ctrl2_adc_cal_addr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_ctrl2_adc_gain_wds_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_ctrl2_adc_vos_wds_ovrd_get(const char *buf);
int ae_adc_cal_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_val_ctrl_adc_gain_val_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_val_ctrl_adc_vos_val_get(const char *buf);
int ae_adc_cal_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_clk_ctrl_id0_adc_vosdac_clk_opt_get(const char *buf);
int ae_adc_cal_clk_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_clk_ctrl_id1_adc_vosdac_clk_opt_get(const char *buf);
int ae_adc_cal_clk_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_clk_ctrl_id2_adc_vosdac_clk_opt_get(const char *buf);
int ae_adc_cal_clk_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_clk_ctrl_id3_adc_vosdac_clk_opt_get(const char *buf);
int ae_adc_cal_clk_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_clk_ctrl_id4_adc_vosdac_clk_opt_get(const char *buf);
int ae_adc_cal_clk_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_phos_ctrl_phos_ren_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_phos_ctrl_phos_wds_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_phos_ctrl_phos_addr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_phos_ctrl_phos_addr_get(const char *buf);
uint8_t uphy_reg_ae_phos_ctrl_phos_get(const char *buf);
int ae_phos_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_ctrl0_id0_edge_vos_ccal_en_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id0_adc_gain_shift_auto_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id0_ccal_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id0_scal_phos_auto_get(const char *buf);
int ae_cal_vos_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_ctrl0_id1_edge_vos_ccal_en_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id1_adc_gain_shift_auto_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id1_ccal_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id1_scal_phos_auto_get(const char *buf);
int ae_cal_vos_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_ctrl0_id2_edge_vos_ccal_en_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id2_adc_gain_shift_auto_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id2_ccal_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id2_scal_phos_auto_get(const char *buf);
int ae_cal_vos_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_ctrl0_id3_edge_vos_ccal_en_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id3_adc_gain_shift_auto_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id3_ccal_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id3_scal_phos_auto_get(const char *buf);
int ae_cal_vos_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_ctrl0_id4_edge_vos_ccal_en_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id4_adc_gain_shift_auto_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id4_ccal_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl0_id4_scal_phos_auto_get(const char *buf);
int ae_cal_vos_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_ctrl1_ccal_decimated_by4_en_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl1_adc_gain_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl1_adc_vos_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl1_vga_vos_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ctrl1_ctle_vos_grad_inv_get(const char *buf);
int ae_cal_vos_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_term_phcal_en_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_term_phcal_en_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_clkrcv_phcal_en_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_clkrcv_phcal_en_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_vga_gen_vcal_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_vga_gen_vcal_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_tah_squelch_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_vga_squelch_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_ctle_squelch_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_term_squelch_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_tah_squelch_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_vga_squelch_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_ctle_squelch_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_fcal_ctrl_term_squelch_ovrd_get(const char *buf);
int ae_cal_vos_fcal_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id0_blw_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id0_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id0_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id0_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id0_vos_mode_get(const char *buf);
int ae_cal_ctle_vos_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id1_blw_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id1_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id1_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id1_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id1_vos_mode_get(const char *buf);
int ae_cal_ctle_vos_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id2_blw_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id2_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id2_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id2_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id2_vos_mode_get(const char *buf);
int ae_cal_ctle_vos_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id3_blw_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id3_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id3_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id3_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id3_vos_mode_get(const char *buf);
int ae_cal_ctle_vos_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id4_blw_mode_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id4_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id4_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id4_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_ctrl0_id4_vos_mode_get(const char *buf);
int ae_cal_ctle_vos_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl0_ctle_vos_ccal_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl0_ctle_vos_ical_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl0_ctle_vos_fine_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl0_ctle_vos_coarse_step_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl1_ctle_vos_ical_acc_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl1_ctle_vos_fcal_acc_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id0_ctle_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id0_ctle_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id0_ctle_vos_coarse_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id1_ctle_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id1_ctle_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id1_ctle_vos_coarse_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id2_ctle_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id2_ctle_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id2_ctle_vos_coarse_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl2_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id3_ctle_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id3_ctle_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id3_ctle_vos_coarse_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl2_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id4_ctle_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id4_ctle_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl2_id4_ctle_vos_coarse_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl2_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id0_ctle_vos_ccal_trk_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id0_ctle_vos_ccal_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl3_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id1_ctle_vos_ccal_trk_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id1_ctle_vos_ccal_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl3_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id2_ctle_vos_ccal_trk_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id2_ctle_vos_ccal_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl3_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id3_ctle_vos_ccal_trk_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id3_ctle_vos_ccal_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl3_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id4_ctle_vos_ccal_trk_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_ctle_vos_gmac_ctrl3_id4_ctle_vos_ccal_gain_get(const char *buf);
int ae_cal_ctle_vos_gmac_ctrl3_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id0_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id0_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id0_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id0_vos_mode_get(const char *buf);
int ae_cal_vga_vos_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id1_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id1_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id1_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id1_vos_mode_get(const char *buf);
int ae_cal_vga_vos_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id2_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id2_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id2_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id2_vos_mode_get(const char *buf);
int ae_cal_vga_vos_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id3_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id3_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id3_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id3_vos_mode_get(const char *buf);
int ae_cal_vga_vos_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id4_vos_range_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id4_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id4_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl0_id4_vos_mode_get(const char *buf);
int ae_cal_vga_vos_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id0_vos_gain_th_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id0_vga_gain_vos1_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id0_vga_gain_vos0_get(const char *buf);
int ae_cal_vga_vos_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id1_vos_gain_th_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id1_vga_gain_vos1_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id1_vga_gain_vos0_get(const char *buf);
int ae_cal_vga_vos_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id2_vos_gain_th_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id2_vga_gain_vos1_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id2_vga_gain_vos0_get(const char *buf);
int ae_cal_vga_vos_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id3_vos_gain_th_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id3_vga_gain_vos1_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id3_vga_gain_vos0_get(const char *buf);
int ae_cal_vga_vos_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id4_vos_gain_th_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id4_vga_gain_vos1_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_ctrl1_id4_vga_gain_vos0_get(const char *buf);
int ae_cal_vga_vos_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl0_vga_vos_ical_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl0_vga_vos_fine_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl0_vga_vos_coarse_step_get(const char *buf);
int ae_cal_vga_vos_gmac_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl1_vga_vos_ical_acc_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl1_vga_vos_fcal_acc_get(const char *buf);
int ae_cal_vga_vos_gmac_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id0_vga_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id0_vga_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id0_vga_vos_coarse_gain_get(const char *buf);
int ae_cal_vga_vos_gmac_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id1_vga_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id1_vga_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id1_vga_vos_coarse_gain_get(const char *buf);
int ae_cal_vga_vos_gmac_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id2_vga_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id2_vga_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id2_vga_vos_coarse_gain_get(const char *buf);
int ae_cal_vga_vos_gmac_ctrl2_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id3_vga_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id3_vga_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id3_vga_vos_coarse_gain_get(const char *buf);
int ae_cal_vga_vos_gmac_ctrl2_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id4_vga_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id4_vga_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_vga_vos_gmac_ctrl2_id4_vga_vos_coarse_gain_get(const char *buf);
int ae_cal_vga_vos_gmac_ctrl2_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id0_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id0_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id0_vos_mode_get(const char *buf);
int ae_cal_adc_vos_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id1_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id1_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id1_vos_mode_get(const char *buf);
int ae_cal_adc_vos_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id2_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id2_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id2_vos_mode_get(const char *buf);
int ae_cal_adc_vos_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id3_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id3_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id3_vos_mode_get(const char *buf);
int ae_cal_adc_vos_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id4_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id4_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_ctrl_id4_vos_mode_get(const char *buf);
int ae_cal_adc_vos_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl0_adc_vos_ccal_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl0_adc_vos_ical_step_get(const char *buf);
uint16_t uphy_reg_ae_cal_adc_vos_gmac_ctrl0_adc_vos_sprfine_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl0_adc_vos_fine_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl0_adc_vos_coarse_step_get(const char *buf);
int ae_cal_adc_vos_gmac_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl1_adc_vos_ical_iter_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl1_adc_vos_sprfine_iter_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl1_adc_vos_fine_iter_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl1_adc_vos_coarse_iter_get(const char *buf);
int ae_cal_adc_vos_gmac_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl2_adc_vos_ccal_acc_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl2_adc_vos_ical_acc_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl2_adc_vos_fcal_acc_get(const char *buf);
int ae_cal_adc_vos_gmac_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl3_adc_vos_ical_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl3_adc_vos_sprfine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl3_adc_vos_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl3_adc_vos_coarse_gain_get(const char *buf);
int ae_cal_adc_vos_gmac_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl4_edge_vos_ccal_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_vos_gmac_ctrl4_adc_vos_ccal_gain_get(const char *buf);
int ae_cal_adc_vos_gmac_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id0_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id0_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id0_vos_mode_get(const char *buf);
int ae_cal_adc_gain_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id1_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id1_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id1_vos_mode_get(const char *buf);
int ae_cal_adc_gain_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id2_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id2_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id2_vos_mode_get(const char *buf);
int ae_cal_adc_gain_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id3_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id3_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id3_vos_mode_get(const char *buf);
int ae_cal_adc_gain_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id4_vos_ctxid_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id4_vos_ctx_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_ctrl_id4_vos_mode_get(const char *buf);
int ae_cal_adc_gain_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl0_adc_gain_sprfine_iter_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl0_adc_gain_fine_iter_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl0_adc_gain_coarse_iter_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl0_adc_gain_sprfine_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl0_adc_gain_fine_step_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl0_adc_gain_coarse_step_get(const char *buf);
int ae_cal_adc_gain_gmac_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl1_adc_gain_ccal_step_get(const char *buf);
uint16_t uphy_reg_ae_cal_adc_gain_gmac_ctrl1_adc_gain_ccal_win_cnt_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl1_adc_gain_ccal_acc_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl1_adc_gain_fcal_acc_get(const char *buf);
int ae_cal_adc_gain_gmac_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl2_adc_gain_ccal_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl2_adc_gain_sprfine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl2_adc_gain_fine_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_adc_gain_gmac_ctrl2_adc_gain_coarse_gain_get(const char *buf);
int ae_cal_adc_gain_gmac_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_phos_ctrl0_id0_hold_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id0_setup_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id0_strobe_width_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id0_ccal_phos_iter_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id0_ccal_phos_mode_get(const char *buf);
int ae_cal_phos_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_phos_ctrl0_id1_hold_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id1_setup_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id1_strobe_width_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id1_ccal_phos_iter_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id1_ccal_phos_mode_get(const char *buf);
int ae_cal_phos_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_phos_ctrl0_id2_hold_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id2_setup_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id2_strobe_width_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id2_ccal_phos_iter_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id2_ccal_phos_mode_get(const char *buf);
int ae_cal_phos_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_phos_ctrl0_id3_hold_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id3_setup_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id3_strobe_width_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id3_ccal_phos_iter_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id3_ccal_phos_mode_get(const char *buf);
int ae_cal_phos_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_phos_ctrl0_id4_hold_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id4_setup_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id4_strobe_width_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id4_ccal_phos_iter_time_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl0_id4_ccal_phos_mode_get(const char *buf);
int ae_cal_phos_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_phos_ctrl1_ccal_phos_delta_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl1_ccal_phos_gain_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_ctrl1_phos_grad_inv_get(const char *buf);
int ae_cal_phos_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_scal_phos_ctrl0_scal_phos_gain_get(const char *buf);
uint8_t uphy_reg_ae_scal_phos_ctrl0_scal_phos_grad_slp_sel_get(const char *buf);
uint16_t uphy_reg_ae_scal_phos_ctrl0_scal_phos_h0_get(const char *buf);
int ae_scal_phos_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_scal_phos_ctrl1_scal_phos_iter_time_get(const char *buf);
uint8_t uphy_reg_ae_scal_phos_ctrl1_scal_phos_time_get(const char *buf);
uint8_t uphy_reg_ae_scal_phos_ctrl1_scal_phos_pll_lock_time_get(const char *buf);
uint8_t uphy_reg_ae_scal_phos_ctrl1_scal_phos_fll_slicers_time_get(const char *buf);
int ae_scal_phos_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_scal_phos_ctrl2_scal_phos_csdet_off_get(const char *buf);
uint8_t uphy_reg_ae_scal_phos_ctrl2_pll_freq2_gain_scal_get(const char *buf);
uint16_t uphy_reg_ae_scal_phos_ctrl2_phase_gain_scal_get(const char *buf);
uint8_t uphy_reg_ae_scal_phos_ctrl2_scal_phos_valid_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_scal_phos_ctrl2_scal_phos_valid_get(const char *buf);
uint8_t uphy_reg_ae_scal_phos_ctrl2_scal_phos_delta_get(const char *buf);
int ae_scal_phos_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_ccal_state_ctrl_ccal_state_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ccal_state_ctrl_ccal_op_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ccal_state_ctrl_ccal_state_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ccal_state_ctrl_ccal_op_get(const char *buf);
int ae_cal_vos_ccal_state_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_phos_state_ctrl_op_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_state_ctrl_state_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_state_ctrl_aeintf_state_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_state_ctrl_phos_op_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_state_ctrl_phos_state_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_state_ctrl_phos_aeintf_state_get(const char *buf);
int ae_cal_phos_state_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_valid_ctrl0_vga_vos_valid_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_ctrl0_vga_vos_valid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_ctrl0_ctle_vos_valid_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_ctrl0_ctle_vos_valid_get(const char *buf);
int ae_cal_vos_valid_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_valid_ctrl1_adc_vos_valid_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_ctrl1_adc_vos_valid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_ctrl1_adc_gain_valid_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_ctrl1_adc_gain_valid_get(const char *buf);
int ae_cal_vos_valid_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_vos_ctx0_stat0_ctle_vos0_get(const char *buf);
int ae_ctle_vos_ctx0_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_vos_ctx1_stat0_ctle_vos0_get(const char *buf);
int ae_ctle_vos_ctx1_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_vos_ctx2_stat0_ctle_vos0_get(const char *buf);
int ae_ctle_vos_ctx2_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_vos_ctx0_stat_vga_vos1_get(const char *buf);
uint8_t uphy_reg_ae_vga_vos_ctx0_stat_vga_vos0_get(const char *buf);
int ae_vga_vos_ctx0_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_vos_ctx1_stat_vga_vos1_get(const char *buf);
uint8_t uphy_reg_ae_vga_vos_ctx1_stat_vga_vos0_get(const char *buf);
int ae_vga_vos_ctx1_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_vos_ctx2_stat_vga_vos1_get(const char *buf);
uint8_t uphy_reg_ae_vga_vos_ctx2_stat_vga_vos0_get(const char *buf);
int ae_vga_vos_ctx2_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc0_cal_stat0_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc0_cal_stat0_adc_vos_get(const char *buf);
int ae_adc0_cal_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc0_cal_stat1_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc0_cal_stat1_adc_vos_get(const char *buf);
int ae_adc0_cal_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc0_cal_stat2_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc0_cal_stat2_adc_vos_get(const char *buf);
int ae_adc0_cal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc0_cal_stat3_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc0_cal_stat3_adc_vos_get(const char *buf);
int ae_adc0_cal_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc0_cal_stat4_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc0_cal_stat4_adc_vos_get(const char *buf);
int ae_adc0_cal_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc0_cal_stat5_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc0_cal_stat5_adc_vos_get(const char *buf);
int ae_adc0_cal_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc0_cal_stat6_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc0_cal_stat6_adc_vos_get(const char *buf);
int ae_adc0_cal_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc0_cal_stat7_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc0_cal_stat7_adc_vos_get(const char *buf);
int ae_adc0_cal_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc1_cal_stat0_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc1_cal_stat0_adc_vos_get(const char *buf);
int ae_adc1_cal_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc1_cal_stat1_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc1_cal_stat1_adc_vos_get(const char *buf);
int ae_adc1_cal_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc1_cal_stat2_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc1_cal_stat2_adc_vos_get(const char *buf);
int ae_adc1_cal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc1_cal_stat3_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc1_cal_stat3_adc_vos_get(const char *buf);
int ae_adc1_cal_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc1_cal_stat4_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc1_cal_stat4_adc_vos_get(const char *buf);
int ae_adc1_cal_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc1_cal_stat5_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc1_cal_stat5_adc_vos_get(const char *buf);
int ae_adc1_cal_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc1_cal_stat6_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc1_cal_stat6_adc_vos_get(const char *buf);
int ae_adc1_cal_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc1_cal_stat7_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc1_cal_stat7_adc_vos_get(const char *buf);
int ae_adc1_cal_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc2_cal_stat0_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc2_cal_stat0_adc_vos_get(const char *buf);
int ae_adc2_cal_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc2_cal_stat1_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc2_cal_stat1_adc_vos_get(const char *buf);
int ae_adc2_cal_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc2_cal_stat2_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc2_cal_stat2_adc_vos_get(const char *buf);
int ae_adc2_cal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc2_cal_stat3_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc2_cal_stat3_adc_vos_get(const char *buf);
int ae_adc2_cal_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc2_cal_stat4_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc2_cal_stat4_adc_vos_get(const char *buf);
int ae_adc2_cal_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc2_cal_stat5_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc2_cal_stat5_adc_vos_get(const char *buf);
int ae_adc2_cal_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc2_cal_stat6_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc2_cal_stat6_adc_vos_get(const char *buf);
int ae_adc2_cal_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc2_cal_stat7_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc2_cal_stat7_adc_vos_get(const char *buf);
int ae_adc2_cal_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc3_cal_stat0_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc3_cal_stat0_adc_vos_get(const char *buf);
int ae_adc3_cal_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc3_cal_stat1_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc3_cal_stat1_adc_vos_get(const char *buf);
int ae_adc3_cal_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc3_cal_stat2_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc3_cal_stat2_adc_vos_get(const char *buf);
int ae_adc3_cal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc3_cal_stat3_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc3_cal_stat3_adc_vos_get(const char *buf);
int ae_adc3_cal_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc3_cal_stat4_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc3_cal_stat4_adc_vos_get(const char *buf);
int ae_adc3_cal_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc3_cal_stat5_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc3_cal_stat5_adc_vos_get(const char *buf);
int ae_adc3_cal_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc3_cal_stat6_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc3_cal_stat6_adc_vos_get(const char *buf);
int ae_adc3_cal_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc3_cal_stat7_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc3_cal_stat7_adc_vos_get(const char *buf);
int ae_adc3_cal_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc4_cal_stat0_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc4_cal_stat0_adc_vos_get(const char *buf);
int ae_adc4_cal_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc4_cal_stat1_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc4_cal_stat1_adc_vos_get(const char *buf);
int ae_adc4_cal_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc4_cal_stat2_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc4_cal_stat2_adc_vos_get(const char *buf);
int ae_adc4_cal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc4_cal_stat3_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc4_cal_stat3_adc_vos_get(const char *buf);
int ae_adc4_cal_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc4_cal_stat4_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc4_cal_stat4_adc_vos_get(const char *buf);
int ae_adc4_cal_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc4_cal_stat5_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc4_cal_stat5_adc_vos_get(const char *buf);
int ae_adc4_cal_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc4_cal_stat6_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc4_cal_stat6_adc_vos_get(const char *buf);
int ae_adc4_cal_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc4_cal_stat7_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc4_cal_stat7_adc_vos_get(const char *buf);
int ae_adc4_cal_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc5_cal_stat0_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc5_cal_stat0_adc_vos_get(const char *buf);
int ae_adc5_cal_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc5_cal_stat1_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc5_cal_stat1_adc_vos_get(const char *buf);
int ae_adc5_cal_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc5_cal_stat2_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc5_cal_stat2_adc_vos_get(const char *buf);
int ae_adc5_cal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc5_cal_stat3_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc5_cal_stat3_adc_vos_get(const char *buf);
int ae_adc5_cal_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc5_cal_stat4_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc5_cal_stat4_adc_vos_get(const char *buf);
int ae_adc5_cal_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc5_cal_stat5_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc5_cal_stat5_adc_vos_get(const char *buf);
int ae_adc5_cal_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc5_cal_stat6_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc5_cal_stat6_adc_vos_get(const char *buf);
int ae_adc5_cal_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc5_cal_stat7_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc5_cal_stat7_adc_vos_get(const char *buf);
int ae_adc5_cal_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc6_cal_stat0_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc6_cal_stat0_adc_vos_get(const char *buf);
int ae_adc6_cal_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc6_cal_stat1_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc6_cal_stat1_adc_vos_get(const char *buf);
int ae_adc6_cal_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc6_cal_stat2_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc6_cal_stat2_adc_vos_get(const char *buf);
int ae_adc6_cal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc6_cal_stat3_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc6_cal_stat3_adc_vos_get(const char *buf);
int ae_adc6_cal_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc6_cal_stat4_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc6_cal_stat4_adc_vos_get(const char *buf);
int ae_adc6_cal_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc6_cal_stat5_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc6_cal_stat5_adc_vos_get(const char *buf);
int ae_adc6_cal_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc6_cal_stat6_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc6_cal_stat6_adc_vos_get(const char *buf);
int ae_adc6_cal_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc6_cal_stat7_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc6_cal_stat7_adc_vos_get(const char *buf);
int ae_adc6_cal_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc7_cal_stat0_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc7_cal_stat0_adc_vos_get(const char *buf);
int ae_adc7_cal_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc7_cal_stat1_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc7_cal_stat1_adc_vos_get(const char *buf);
int ae_adc7_cal_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc7_cal_stat2_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc7_cal_stat2_adc_vos_get(const char *buf);
int ae_adc7_cal_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc7_cal_stat3_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc7_cal_stat3_adc_vos_get(const char *buf);
int ae_adc7_cal_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc7_cal_stat4_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc7_cal_stat4_adc_vos_get(const char *buf);
int ae_adc7_cal_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc7_cal_stat5_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc7_cal_stat5_adc_vos_get(const char *buf);
int ae_adc7_cal_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc7_cal_stat6_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc7_cal_stat6_adc_vos_get(const char *buf);
int ae_adc7_cal_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc7_cal_stat7_adc_gos_get(const char *buf);
uint8_t uphy_reg_ae_adc7_cal_stat7_adc_vos_get(const char *buf);
int ae_adc7_cal_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_rd_stat0_adc1_cal_val_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_rd_stat0_adc0_cal_val_get(const char *buf);
int ae_adc_cal_rd_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_rd_stat1_adc3_cal_val_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_rd_stat1_adc2_cal_val_get(const char *buf);
int ae_adc_cal_rd_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_rd_stat2_adc5_cal_val_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_rd_stat2_adc4_cal_val_get(const char *buf);
int ae_adc_cal_rd_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_cal_rd_stat3_adc7_cal_val_get(const char *buf);
uint8_t uphy_reg_ae_adc_cal_rd_stat3_adc6_cal_val_get(const char *buf);
int ae_adc_cal_rd_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_phos_stat0_phos1_get(const char *buf);
uint8_t uphy_reg_ae_phos_stat0_phos0_get(const char *buf);
int ae_phos_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_phos_stat1_phos3_get(const char *buf);
uint8_t uphy_reg_ae_phos_stat1_phos2_get(const char *buf);
int ae_phos_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_phos_stat2_phos5_get(const char *buf);
uint8_t uphy_reg_ae_phos_stat2_phos4_get(const char *buf);
int ae_phos_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_phos_stat3_phos7_get(const char *buf);
uint8_t uphy_reg_ae_phos_stat3_phos6_get(const char *buf);
int ae_phos_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_phos_rd_stat_phos_get(const char *buf);
int ae_phos_rd_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_ccal_state_stat_cal_error_cnt_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ccal_state_stat_ccal_state_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_ccal_state_stat_ccal_op_get(const char *buf);
int ae_cal_vos_ccal_state_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_phos_state_stat_phos_op_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_state_stat_phos_state_get(const char *buf);
uint8_t uphy_reg_ae_cal_phos_state_stat_phos_aeintf_state_get(const char *buf);
int ae_cal_phos_state_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_valid_stat0_ctle_vos_ctx1_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat0_ctle_vos_ctx1_valid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat0_ctle_vos_ctx0_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat0_ctle_vos_ctx0_valid_get(const char *buf);
int ae_cal_vos_valid_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_valid_stat1_ctle_vos_ctx2_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat1_ctle_vos_ctx2_valid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat1_vga_vos_ctx0_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat1_vga_vos_ctx0_valid_get(const char *buf);
int ae_cal_vos_valid_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_valid_stat2_vga_vos_ctx2_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat2_vga_vos_ctx2_valid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat2_vga_vos_ctx1_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat2_vga_vos_ctx1_valid_get(const char *buf);
int ae_cal_vos_valid_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cal_vos_valid_stat3_adc_vos_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat3_adc_vos_valid_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat3_adc_gain_initialized_get(const char *buf);
uint8_t uphy_reg_ae_cal_vos_valid_stat3_adc_gain_valid_get(const char *buf);
int ae_cal_vos_valid_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_term_attn_ctrl_id0_term_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id0_term_attn_ctrl_get(const char *buf);
int ae_term_attn_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_term_attn_ctrl_id1_term_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id1_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id1_term_attn_ctrl_get(const char *buf);
int ae_term_attn_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_term_attn_ctrl_id2_term_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id2_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id2_term_attn_ctrl_get(const char *buf);
int ae_term_attn_ctrl_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_term_attn_ctrl_id3_term_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id3_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id3_term_attn_ctrl_get(const char *buf);
int ae_term_attn_ctrl_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_term_attn_ctrl_id4_term_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id4_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctrl_id4_term_attn_ctrl_get(const char *buf);
int ae_term_attn_ctrl_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl0_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl0_id0_dc_gain_get(const char *buf);
int ae_ctle_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl0_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl0_id1_dc_gain_get(const char *buf);
int ae_ctle_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl0_id2_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl0_id2_dc_gain_get(const char *buf);
int ae_ctle_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl0_id3_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl0_id3_dc_gain_get(const char *buf);
int ae_ctle_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl0_id4_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl0_id4_dc_gain_get(const char *buf);
int ae_ctle_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl1_id0_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id0_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id0_lf_gain_get(const char *buf);
int ae_ctle_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl1_id1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id1_lf_gain_get(const char *buf);
int ae_ctle_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl1_id2_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id2_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id2_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id2_lf_gain_get(const char *buf);
int ae_ctle_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl1_id3_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id3_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id3_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id3_lf_gain_get(const char *buf);
int ae_ctle_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl1_id4_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id4_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id4_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl1_id4_lf_gain_get(const char *buf);
int ae_ctle_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl2_id0_ctle_rvdd_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id0_ctle_tia_res_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id0_ctle_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id0_ctle_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id0_ctle_i_ctrl_get(const char *buf);
int ae_ctle_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl2_id1_ctle_rvdd_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id1_ctle_tia_res_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id1_ctle_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id1_ctle_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id1_ctle_i_ctrl_get(const char *buf);
int ae_ctle_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl2_id2_ctle_rvdd_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id2_ctle_tia_res_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id2_ctle_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id2_ctle_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id2_ctle_i_ctrl_get(const char *buf);
int ae_ctle_ctrl2_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl2_id3_ctle_rvdd_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id3_ctle_tia_res_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id3_ctle_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id3_ctle_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id3_ctle_i_ctrl_get(const char *buf);
int ae_ctle_ctrl2_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctrl2_id4_ctle_rvdd_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id4_ctle_tia_res_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id4_ctle_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id4_ctle_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctrl2_id4_ctle_i_ctrl_get(const char *buf);
int ae_ctle_ctrl2_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl0_id0_vga_vcm_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id0_vga_time_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id0_vga_gain_get(const char *buf);
int ae_vga_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl0_id1_vga_vcm_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id1_vga_time_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id1_vga_gain_get(const char *buf);
int ae_vga_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl0_id2_vga_vcm_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id2_vga_time_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id2_vga_gain_get(const char *buf);
int ae_vga_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl0_id3_vga_vcm_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id3_vga_time_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id3_vga_gain_get(const char *buf);
int ae_vga_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl0_id4_vga_vcm_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id4_vga_time_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl0_id4_vga_gain_get(const char *buf);
int ae_vga_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl1_id0_vga_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id0_vga_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id0_vga_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id0_vga_ssf_i_ctrl_get(const char *buf);
int ae_vga_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl1_id1_vga_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id1_vga_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id1_vga_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id1_vga_ssf_i_ctrl_get(const char *buf);
int ae_vga_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl1_id2_vga_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id2_vga_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id2_vga_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id2_vga_ssf_i_ctrl_get(const char *buf);
int ae_vga_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl1_id3_vga_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id3_vga_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id3_vga_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id3_vga_ssf_i_ctrl_get(const char *buf);
int ae_vga_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctrl1_id4_vga_tia_r_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id4_vga_tia_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id4_vga_tas_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_vga_ctrl1_id4_vga_ssf_i_ctrl_get(const char *buf);
int ae_vga_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl0_id0_adc_vref_range_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id0_adc_vref_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id0_adc_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id0_adc_vref_val_get(const char *buf);
int ae_adc_vref_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl0_id1_adc_vref_range_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id1_adc_vref_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id1_adc_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id1_adc_vref_val_get(const char *buf);
int ae_adc_vref_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl0_id2_adc_vref_range_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id2_adc_vref_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id2_adc_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id2_adc_vref_val_get(const char *buf);
int ae_adc_vref_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl0_id3_adc_vref_range_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id3_adc_vref_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id3_adc_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id3_adc_vref_val_get(const char *buf);
int ae_adc_vref_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl0_id4_adc_vref_range_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id4_adc_vref_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id4_adc_i_ctrl_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl0_id4_adc_vref_val_get(const char *buf);
int ae_adc_vref_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl1_id0_closeloop_en_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id0_adc_vref_wds_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id0_adc_vref_wds_get(const char *buf);
int ae_adc_vref_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl1_id1_closeloop_en_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id1_adc_vref_wds_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id1_adc_vref_wds_get(const char *buf);
int ae_adc_vref_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl1_id2_closeloop_en_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id2_adc_vref_wds_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id2_adc_vref_wds_get(const char *buf);
int ae_adc_vref_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl1_id3_closeloop_en_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id3_adc_vref_wds_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id3_adc_vref_wds_get(const char *buf);
int ae_adc_vref_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctrl1_id4_closeloop_en_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id4_adc_vref_wds_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_adc_vref_ctrl1_id4_adc_vref_wds_get(const char *buf);
int ae_adc_vref_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_offset_ctrl_cdr_offset_get(const char *buf);
int ae_cdr_offset_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl0_id0_ffe_fm2_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl0_id0_ffe_fm3_get(const char *buf);
int ae_ffe_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl0_id1_ffe_fm2_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl0_id1_ffe_fm3_get(const char *buf);
int ae_ffe_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl1_id0_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl1_id0_ffe_fm1_get(const char *buf);
int ae_ffe_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl1_id1_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl1_id1_ffe_fm1_get(const char *buf);
int ae_ffe_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl2_id0_ffe_f3_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl2_id0_ffe_f2_get(const char *buf);
int ae_ffe_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl2_id1_ffe_f3_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl2_id1_ffe_f2_get(const char *buf);
int ae_ffe_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl3_id0_ffe_f5_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl3_id0_ffe_f4_get(const char *buf);
int ae_ffe_ctrl3_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl3_id1_ffe_f5_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl3_id1_ffe_f4_get(const char *buf);
int ae_ffe_ctrl3_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl4_id0_ffe_f7_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl4_id0_ffe_f6_get(const char *buf);
int ae_ffe_ctrl4_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl4_id1_ffe_f7_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctrl4_id1_ffe_f6_get(const char *buf);
int ae_ffe_ctrl4_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl5_id0_ffe_f8_get(const char *buf);
int ae_ffe_ctrl5_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctrl5_id1_ffe_f8_get(const char *buf);
int ae_ffe_ctrl5_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctrl0_dffe_dsel1_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl0_dffe_coef1_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl0_dffe_dsel0_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl0_dffe_coef0_get(const char *buf);
int ae_dffe_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctrl1_dffe_dsel3_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl1_dffe_coef3_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl1_dffe_dsel2_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl1_dffe_coef2_get(const char *buf);
int ae_dffe_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctrl2_dffe_dsel5_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl2_dffe_coef5_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl2_dffe_dsel4_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl2_dffe_coef4_get(const char *buf);
int ae_dffe_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctrl3_dffe_dsel7_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl3_dffe_coef7_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl3_dffe_dsel6_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl3_dffe_coef6_get(const char *buf);
int ae_dffe_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctrl4_dffe_dsel8_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctrl4_dffe_coef8_get(const char *buf);
int ae_dffe_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl0_id0_eth0_get(const char *buf);
int ae_slicer_eth_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl0_id1_eth0_get(const char *buf);
int ae_slicer_eth_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl0_id2_eth0_get(const char *buf);
int ae_slicer_eth_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl0_id3_eth0_get(const char *buf);
int ae_slicer_eth_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl0_id4_eth0_get(const char *buf);
int ae_slicer_eth_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl1_eth1_get(const char *buf);
int ae_slicer_eth_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl2_id0_eth2_get(const char *buf);
int ae_slicer_eth_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl2_id1_eth2_get(const char *buf);
int ae_slicer_eth_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl2_id2_eth2_get(const char *buf);
int ae_slicer_eth_ctrl2_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl2_id3_eth2_get(const char *buf);
int ae_slicer_eth_ctrl2_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl2_id4_eth2_get(const char *buf);
int ae_slicer_eth_ctrl2_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl3_eth3_get(const char *buf);
int ae_slicer_eth_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl4_eth4_get(const char *buf);
int ae_slicer_eth_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl5_eth5_get(const char *buf);
int ae_slicer_eth_ctrl5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl6_eth6_get(const char *buf);
int ae_slicer_eth_ctrl6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth_ctrl7_eth7_get(const char *buf);
int ae_slicer_eth_ctrl7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset0_ctrl_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset0_ctrl_id0_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset0_ctrl_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset0_ctrl_id0_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset0_ctrl_id0_dc_gain_get(const char *buf);
int ae_ctle_preset0_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset0_ctrl_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset0_ctrl_id1_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset0_ctrl_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset0_ctrl_id1_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset0_ctrl_id1_dc_gain_get(const char *buf);
int ae_ctle_preset0_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset1_ctrl_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset1_ctrl_id0_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset1_ctrl_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset1_ctrl_id0_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset1_ctrl_id0_dc_gain_get(const char *buf);
int ae_ctle_preset1_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset1_ctrl_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset1_ctrl_id1_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset1_ctrl_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset1_ctrl_id1_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset1_ctrl_id1_dc_gain_get(const char *buf);
int ae_ctle_preset1_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset2_ctrl_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset2_ctrl_id0_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset2_ctrl_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset2_ctrl_id0_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset2_ctrl_id0_dc_gain_get(const char *buf);
int ae_ctle_preset2_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset2_ctrl_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset2_ctrl_id1_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset2_ctrl_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset2_ctrl_id1_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset2_ctrl_id1_dc_gain_get(const char *buf);
int ae_ctle_preset2_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset3_ctrl_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset3_ctrl_id0_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset3_ctrl_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset3_ctrl_id0_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset3_ctrl_id0_dc_gain_get(const char *buf);
int ae_ctle_preset3_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset3_ctrl_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset3_ctrl_id1_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset3_ctrl_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset3_ctrl_id1_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset3_ctrl_id1_dc_gain_get(const char *buf);
int ae_ctle_preset3_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset4_ctrl_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset4_ctrl_id0_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset4_ctrl_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset4_ctrl_id0_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset4_ctrl_id0_dc_gain_get(const char *buf);
int ae_ctle_preset4_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset4_ctrl_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset4_ctrl_id1_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset4_ctrl_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset4_ctrl_id1_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset4_ctrl_id1_dc_gain_get(const char *buf);
int ae_ctle_preset4_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset5_ctrl_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset5_ctrl_id0_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset5_ctrl_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset5_ctrl_id0_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset5_ctrl_id0_dc_gain_get(const char *buf);
int ae_ctle_preset5_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset5_ctrl_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset5_ctrl_id1_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset5_ctrl_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset5_ctrl_id1_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset5_ctrl_id1_dc_gain_get(const char *buf);
int ae_ctle_preset5_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset6_ctrl_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset6_ctrl_id0_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset6_ctrl_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset6_ctrl_id0_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset6_ctrl_id0_dc_gain_get(const char *buf);
int ae_ctle_preset6_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset6_ctrl_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset6_ctrl_id1_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset6_ctrl_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset6_ctrl_id1_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset6_ctrl_id1_dc_gain_get(const char *buf);
int ae_ctle_preset6_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset7_ctrl_id0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset7_ctrl_id0_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset7_ctrl_id0_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset7_ctrl_id0_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset7_ctrl_id0_dc_gain_get(const char *buf);
int ae_ctle_preset7_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_preset7_ctrl_id1_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset7_ctrl_id1_mf_pole_get(const char *buf);
uint16_t uphy_reg_ae_ctle_preset7_ctrl_id1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset7_ctrl_id1_lf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_preset7_ctrl_id1_dc_gain_get(const char *buf);
int ae_ctle_preset7_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl0_id0_peq_tsense_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id0_vref_peq_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id0_dffe_peq_scout_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id0_peq_f1_adapt_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id0_dcg_hfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id0_lfg_mfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id0_lfg_mfg_crs_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id0_peq_train_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id0_feq_train_mode_get(const char *buf);
int ae_eq_train_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl0_id1_peq_tsense_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id1_vref_peq_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id1_dffe_peq_scout_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id1_peq_f1_adapt_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id1_dcg_hfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id1_lfg_mfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id1_lfg_mfg_crs_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id1_peq_train_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id1_feq_train_mode_get(const char *buf);
int ae_eq_train_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl0_id2_peq_tsense_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id2_vref_peq_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id2_dffe_peq_scout_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id2_peq_f1_adapt_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id2_dcg_hfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id2_lfg_mfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id2_lfg_mfg_crs_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id2_peq_train_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id2_feq_train_mode_get(const char *buf);
int ae_eq_train_ctrl0_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl0_id3_peq_tsense_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id3_vref_peq_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id3_dffe_peq_scout_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id3_peq_f1_adapt_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id3_dcg_hfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id3_lfg_mfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id3_lfg_mfg_crs_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id3_peq_train_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id3_feq_train_mode_get(const char *buf);
int ae_eq_train_ctrl0_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl0_id4_peq_tsense_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id4_vref_peq_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id4_dffe_peq_scout_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id4_peq_f1_adapt_skip_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id4_dcg_hfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id4_lfg_mfg_fine_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id4_lfg_mfg_crs_srch_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id4_peq_train_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl0_id4_feq_train_mode_get(const char *buf);
int ae_eq_train_ctrl0_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl1_id0_term_lpf_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id0_cdr_offset_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id0_vref_val_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id0_eq_auto_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id0_rx_dffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id0_rx_ffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id0_rx_ctle_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id0_adapt_id_get(const char *buf);
int ae_eq_train_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl1_id1_term_lpf_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id1_cdr_offset_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id1_vref_val_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id1_eq_auto_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id1_rx_dffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id1_rx_ffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id1_rx_ctle_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id1_adapt_id_get(const char *buf);
int ae_eq_train_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl1_id2_term_lpf_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id2_cdr_offset_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id2_vref_val_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id2_eq_auto_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id2_rx_dffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id2_rx_ffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id2_rx_ctle_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id2_adapt_id_get(const char *buf);
int ae_eq_train_ctrl1_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl1_id3_term_lpf_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id3_cdr_offset_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id3_vref_val_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id3_eq_auto_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id3_rx_dffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id3_rx_ffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id3_rx_ctle_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id3_adapt_id_get(const char *buf);
int ae_eq_train_ctrl1_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl1_id4_term_lpf_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id4_cdr_offset_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id4_vref_val_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id4_eq_auto_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id4_rx_dffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id4_rx_ffe_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id4_rx_ctle_id_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl1_id4_adapt_id_get(const char *buf);
int ae_eq_train_ctrl1_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl2_id0_vga_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id0_hf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id0_mf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id0_mf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id0_lf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id0_lf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id0_dc_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id0_term_attn_mode_get(const char *buf);
int ae_eq_train_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl2_id1_vga_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id1_hf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id1_mf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id1_mf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id1_lf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id1_lf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id1_dc_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id1_term_attn_mode_get(const char *buf);
int ae_eq_train_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl2_id2_vga_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id2_hf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id2_mf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id2_mf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id2_lf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id2_lf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id2_dc_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id2_term_attn_mode_get(const char *buf);
int ae_eq_train_ctrl2_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl2_id3_vga_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id3_hf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id3_mf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id3_mf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id3_lf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id3_lf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id3_dc_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id3_term_attn_mode_get(const char *buf);
int ae_eq_train_ctrl2_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl2_id4_vga_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id4_hf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id4_mf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id4_mf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id4_lf_pole_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id4_lf_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id4_dc_gain_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl2_id4_term_attn_mode_get(const char *buf);
int ae_eq_train_ctrl2_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl3_id0_f8_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id0_f7_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id0_f6_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id0_f5_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id0_f4_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id0_f3_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id0_f2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id0_f1_mode_get(const char *buf);
int ae_eq_train_ctrl3_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl3_id1_f8_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id1_f7_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id1_f6_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id1_f5_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id1_f4_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id1_f3_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id1_f2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id1_f1_mode_get(const char *buf);
int ae_eq_train_ctrl3_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl3_id2_f8_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id2_f7_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id2_f6_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id2_f5_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id2_f4_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id2_f3_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id2_f2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id2_f1_mode_get(const char *buf);
int ae_eq_train_ctrl3_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl3_id3_f8_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id3_f7_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id3_f6_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id3_f5_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id3_f4_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id3_f3_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id3_f2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id3_f1_mode_get(const char *buf);
int ae_eq_train_ctrl3_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl3_id4_f8_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id4_f7_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id4_f6_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id4_f5_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id4_f4_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id4_f3_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id4_f2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl3_id4_f1_mode_get(const char *buf);
int ae_eq_train_ctrl3_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl4_id0_h2_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id0_h1_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id0_dffe_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id0_fm1_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id0_fm2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id0_fm3_mode_get(const char *buf);
int ae_eq_train_ctrl4_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl4_id1_h2_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id1_h1_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id1_dffe_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id1_fm1_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id1_fm2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id1_fm3_mode_get(const char *buf);
int ae_eq_train_ctrl4_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl4_id2_h2_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id2_h1_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id2_dffe_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id2_fm1_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id2_fm2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id2_fm3_mode_get(const char *buf);
int ae_eq_train_ctrl4_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl4_id3_h2_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id3_h1_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id3_dffe_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id3_fm1_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id3_fm2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id3_fm3_mode_get(const char *buf);
int ae_eq_train_ctrl4_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl4_id4_h2_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id4_h1_on_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id4_dffe_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id4_fm1_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id4_fm2_mode_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl4_id4_fm3_mode_get(const char *buf);
int ae_eq_train_ctrl4_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl5_id0_apply_h0_eth_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl5_id0_eth_auto_get(const char *buf);
int ae_eq_train_ctrl5_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl5_id1_apply_h0_eth_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl5_id1_eth_auto_get(const char *buf);
int ae_eq_train_ctrl5_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl5_id2_apply_h0_eth_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl5_id2_eth_auto_get(const char *buf);
int ae_eq_train_ctrl5_id2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl5_id3_apply_h0_eth_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl5_id3_eth_auto_get(const char *buf);
int ae_eq_train_ctrl5_id3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_train_ctrl5_id4_apply_h0_eth_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_train_ctrl5_id4_eth_auto_get(const char *buf);
int ae_eq_train_ctrl5_id4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_term_attn_ctrl_id0_lpf_hfg_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_term_attn_ctrl_id0_attn_time_get(const char *buf);
uint8_t uphy_reg_ae_eq_term_attn_ctrl_id0_attn_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_term_attn_ctrl_id0_attn_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_term_attn_ctrl_id0_attn_min_get(const char *buf);
int ae_eq_term_attn_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_term_attn_ctrl_id1_lpf_hfg_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_term_attn_ctrl_id1_attn_time_get(const char *buf);
uint8_t uphy_reg_ae_eq_term_attn_ctrl_id1_attn_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_term_attn_ctrl_id1_attn_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_term_attn_ctrl_id1_attn_min_get(const char *buf);
int ae_eq_term_attn_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_ctrl_id0_grid_skp_hfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id0_grid_skp_dcg_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id0_grid_skp_mfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id0_grid_skp_mfp_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id0_grid_skp_lfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id0_grid_skp_lfp_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id0_ctle_preset_max_get(const char *buf);
int ae_eq_ctle_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_ctrl_id1_grid_skp_hfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id1_grid_skp_dcg_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id1_grid_skp_mfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id1_grid_skp_mfp_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id1_grid_skp_lfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id1_grid_skp_lfp_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_ctrl_id1_ctle_preset_max_get(const char *buf);
int ae_eq_ctle_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_dc_gain_ctrl_id0_dc_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_dc_gain_ctrl_id0_dc_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_dc_gain_ctrl_id0_dc_gain_min_get(const char *buf);
int ae_eq_ctle_dc_gain_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_dc_gain_ctrl_id1_dc_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_dc_gain_ctrl_id1_dc_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_dc_gain_ctrl_id1_dc_gain_min_get(const char *buf);
int ae_eq_ctle_dc_gain_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_lf_gain_ctrl_id0_lf_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_lf_gain_ctrl_id0_lf_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_lf_gain_ctrl_id0_lf_gain_min_get(const char *buf);
int ae_eq_ctle_lf_gain_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_lf_gain_ctrl_id1_lf_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_lf_gain_ctrl_id1_lf_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_lf_gain_ctrl_id1_lf_gain_min_get(const char *buf);
int ae_eq_ctle_lf_gain_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_lf_pole_ctrl_id0_lf_pole_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_lf_pole_ctrl_id0_lf_pole_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_lf_pole_ctrl_id0_lf_pole_min_get(const char *buf);
int ae_eq_ctle_lf_pole_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_lf_pole_ctrl_id1_lf_pole_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_lf_pole_ctrl_id1_lf_pole_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_lf_pole_ctrl_id1_lf_pole_min_get(const char *buf);
int ae_eq_ctle_lf_pole_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_mf_gain_ctrl_id0_mf_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_mf_gain_ctrl_id0_mf_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_mf_gain_ctrl_id0_mf_gain_min_get(const char *buf);
int ae_eq_ctle_mf_gain_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_mf_gain_ctrl_id1_mf_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_mf_gain_ctrl_id1_mf_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_mf_gain_ctrl_id1_mf_gain_min_get(const char *buf);
int ae_eq_ctle_mf_gain_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_mf_pole_ctrl_id0_mf_pole_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_mf_pole_ctrl_id0_mf_pole_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_mf_pole_ctrl_id0_mf_pole_min_get(const char *buf);
int ae_eq_ctle_mf_pole_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_mf_pole_ctrl_id1_mf_pole_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_mf_pole_ctrl_id1_mf_pole_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_mf_pole_ctrl_id1_mf_pole_min_get(const char *buf);
int ae_eq_ctle_mf_pole_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_hf_gain_ctrl_id0_hf_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_hf_gain_ctrl_id0_hf_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_hf_gain_ctrl_id0_hf_gain_min_get(const char *buf);
int ae_eq_ctle_hf_gain_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ctle_hf_gain_ctrl_id1_hf_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_hf_gain_ctrl_id1_hf_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_ctle_hf_gain_ctrl_id1_hf_gain_min_get(const char *buf);
int ae_eq_ctle_hf_gain_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_vga_gain_ctrl_id0_vga_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_vga_gain_ctrl_id0_vga_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_vga_gain_ctrl_id0_vga_gain_min_get(const char *buf);
int ae_eq_vga_gain_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_vga_gain_ctrl_id1_vga_gain_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_vga_gain_ctrl_id1_vga_gain_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_vga_gain_ctrl_id1_vga_gain_min_get(const char *buf);
int ae_eq_vga_gain_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_cdr_offset_ctrl0_id0_cdr_offset_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_cdr_offset_ctrl0_id0_cdr_offset_min_get(const char *buf);
int ae_eq_cdr_offset_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_cdr_offset_ctrl0_id1_cdr_offset_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_cdr_offset_ctrl0_id1_cdr_offset_min_get(const char *buf);
int ae_eq_cdr_offset_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_cdr_offset_ctrl1_id0_cdr_offset_time_get(const char *buf);
uint8_t uphy_reg_ae_eq_cdr_offset_ctrl1_id0_cdr_offset_step_get(const char *buf);
int ae_eq_cdr_offset_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_cdr_offset_ctrl1_id1_cdr_offset_time_get(const char *buf);
uint8_t uphy_reg_ae_eq_cdr_offset_ctrl1_id1_cdr_offset_step_get(const char *buf);
int ae_eq_cdr_offset_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_agc_ctrl0_id0_zmax_targ_hi_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl0_id0_zmax_targ_lo_get(const char *buf);
int ae_eq_agc_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_agc_ctrl0_id1_zmax_targ_hi_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl0_id1_zmax_targ_lo_get(const char *buf);
int ae_eq_agc_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_agc_ctrl1_id0_zmax_targ_hi_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl1_id0_zmax_targ_lo_get(const char *buf);
int ae_eq_agc_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_agc_ctrl1_id1_zmax_targ_hi_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl1_id1_zmax_targ_lo_get(const char *buf);
int ae_eq_agc_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_agc_ctrl2_id0_feq_vref_iters_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl2_id0_attn_iters_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl2_id0_peq_vref_iters_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl2_id0_vga_iters_get(const char *buf);
int ae_eq_agc_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_agc_ctrl2_id1_feq_vref_iters_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl2_id1_attn_iters_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl2_id1_peq_vref_iters_get(const char *buf);
uint8_t uphy_reg_ae_eq_agc_ctrl2_id1_vga_iters_get(const char *buf);
int ae_eq_agc_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl0_id0_vref_val_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl0_id0_vref_val_min_get(const char *buf);
int ae_eq_adc_vref_val_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl0_id1_vref_val_max_get(const char *buf);
uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl0_id1_vref_val_min_get(const char *buf);
int ae_eq_adc_vref_val_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl1_id0_vref_time_get(const char *buf);
uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl1_id0_peq_adc_vref_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl1_id0_feq_adc_vref_step_get(const char *buf);
int ae_eq_adc_vref_val_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl1_id1_vref_time_get(const char *buf);
uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl1_id1_peq_adc_vref_step_get(const char *buf);
uint8_t uphy_reg_ae_eq_adc_vref_val_ctrl1_id1_feq_adc_vref_step_get(const char *buf);
int ae_eq_adc_vref_val_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ffe_ctrl0_id0_f1_adapt_sel_get(const char *buf);
uint16_t uphy_reg_ae_eq_ffe_ctrl0_id0_cdr_spin_ffe_mask_get(const char *buf);
int ae_eq_ffe_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ffe_ctrl0_id1_f1_adapt_sel_get(const char *buf);
uint16_t uphy_reg_ae_eq_ffe_ctrl0_id1_cdr_spin_ffe_mask_get(const char *buf);
int ae_eq_ffe_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ffe_ctrl1_id0_ffe_outer_taps_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_ctrl1_id0_ffe_inner_taps_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_ctrl1_id0_ffe_outer_taps_gain_acq_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_ctrl1_id0_ffe_inner_taps_gain_acq_get(const char *buf);
int ae_eq_ffe_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ffe_ctrl1_id1_ffe_outer_taps_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_ctrl1_id1_ffe_inner_taps_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_ctrl1_id1_ffe_outer_taps_gain_acq_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_ctrl1_id1_ffe_inner_taps_gain_acq_get(const char *buf);
int ae_eq_ffe_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ffe_ctrl2_ffe_grad_get(const char *buf);
uint16_t uphy_reg_ae_eq_ffe_ctrl2_ffe_grad_inv_get(const char *buf);
int ae_eq_ffe_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_ffe_cstr_ctrl_ffe_cstr_fom_th_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_cstr_ctrl_ffe_cstr_grid_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_cstr_ctrl_ffe_cstr_grid_val_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_cstr_ctrl_feq_adc_cal_off_ovrd_val_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_cstr_ctrl_feq_adc_cal_off_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_cstr_ctrl_ffe_cstr_oe_sum_th_get(const char *buf);
uint8_t uphy_reg_ae_eq_ffe_cstr_ctrl_ffe_cstr_mode_en_get(const char *buf);
int ae_eq_ffe_cstr_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_dffe_ctrl0_feq_dffe_iters_get(const char *buf);
uint8_t uphy_reg_ae_eq_dffe_ctrl0_feq_dffe_delay_get(const char *buf);
uint8_t uphy_reg_ae_eq_dffe_ctrl0_peq_dffe_iters_get(const char *buf);
uint8_t uphy_reg_ae_eq_dffe_ctrl0_peq_dffe_delay_get(const char *buf);
int ae_eq_dffe_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_dffe_ctrl1_max_taps_get(const char *buf);
uint8_t uphy_reg_ae_eq_dffe_ctrl1_hsum_min_get(const char *buf);
int ae_eq_dffe_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_dffe_ctrl2_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_eq_dffe_ctrl2_gmac_gain_get(const char *buf);
int ae_eq_dffe_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_ctrl0_id0_future_bit_sel_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl0_id0_th_delta_scale_get(const char *buf);
int ae_eq_slicer_ctrl0_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_ctrl0_id1_future_bit_sel_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl0_id1_th_delta_scale_get(const char *buf);
int ae_eq_slicer_ctrl0_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_ctrl1_id0_eth7_6_0_gain_acq_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl1_id0_eth5_1_gain_acq_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl1_id0_eth4_2_gain_acq_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl1_id0_eth3_gain_acq_get(const char *buf);
int ae_eq_slicer_ctrl1_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_ctrl1_id1_eth7_6_0_gain_acq_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl1_id1_eth5_1_gain_acq_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl1_id1_eth4_2_gain_acq_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl1_id1_eth3_gain_acq_get(const char *buf);
int ae_eq_slicer_ctrl1_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_ctrl2_id0_eth7_6_0_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl2_id0_eth5_1_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl2_id0_eth4_2_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl2_id0_eth3_gain_trk_get(const char *buf);
int ae_eq_slicer_ctrl2_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_ctrl2_id1_eth7_6_0_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl2_id1_eth5_1_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl2_id1_eth4_2_gain_trk_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_ctrl2_id1_eth3_gain_trk_get(const char *buf);
int ae_eq_slicer_ctrl2_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_ctrl3_eth_grad_inv_get(const char *buf);
int ae_eq_slicer_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_dme_ctrl_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_eq_dme_ctrl_ieee_safe_mode_en_get(const char *buf);
int ae_eq_dme_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_ctrl0_en_mu_cdr_os_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl0_en_mu_lfp_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl0_en_mu_mfp_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl0_en_mu_lfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl0_en_mu_mfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl0_en_mu_hfg_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl0_en_mu_dcg_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl0_shc_mutate_cnt_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl0_shc_pgrid_srch_en_get(const char *buf);
int ae_eq_shc_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_ctrl1_mfp_ln_ord_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl1_lfg_ln_ord_get(const char *buf);
uint16_t uphy_reg_ae_eq_shc_ctrl1_mfg_ln_ord_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl1_hfg_ln_ord_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl1_dcg_ln_ord_get(const char *buf);
int ae_eq_shc_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_ctrl2_cdr_os_ln_ord_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_ctrl2_lfp_ln_ord_get(const char *buf);
int ae_eq_shc_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_dcg_ctrl_dcg_rslice_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_dcg_ctrl_dcg_radius_get(const char *buf);
int ae_eq_shc_dcg_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_lfg_ctrl_lfg_rslice_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_lfg_ctrl_lfg_radius_get(const char *buf);
int ae_eq_shc_lfg_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_lfp_ctrl_lfp_rslice_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_lfp_ctrl_lfp_radius_get(const char *buf);
int ae_eq_shc_lfp_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_mfg_ctrl_mfg_rslice_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_mfg_ctrl_mfg_radius_get(const char *buf);
int ae_eq_shc_mfg_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_mfp_ctrl_mfp_rslice_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_mfp_ctrl_mfp_radius_get(const char *buf);
int ae_eq_shc_mfp_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_hfg_ctrl_hfg_rslice_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_hfg_ctrl_hfg_radius_get(const char *buf);
int ae_eq_shc_hfg_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_shc_cdr_offset_ctrl_cdr_os_mu_scale_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_cdr_offset_ctrl_cdr_os_rslice_get(const char *buf);
uint8_t uphy_reg_ae_eq_shc_cdr_offset_ctrl_cdr_os_radius_get(const char *buf);
int ae_eq_shc_cdr_offset_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_misc_ctrl_id0_spare_ctrl_get(const char *buf);
int ae_eq_misc_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_misc_ctrl_id1_spare_ctrl_get(const char *buf);
int ae_eq_misc_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_state_ctrl_eth_state_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_state_ctrl_eth_state_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_state_ctrl_eth_op_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_state_ctrl_eth_op_get(const char *buf);
int ae_eq_slicer_state_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_valid_ctrl_eq_init_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_valid_ctrl_eq_train_valid_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eq_valid_ctrl_eq_train_valid_get(const char *buf);
int ae_eq_valid_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_term_attn_stat_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_stat_term_attn_ctrl_get(const char *buf);
int ae_term_attn_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_stat0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_stat0_dc_gain_get(const char *buf);
int ae_ctle_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_stat1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_stat1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_stat1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_stat1_lf_gain_get(const char *buf);
int ae_ctle_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_stat_vga_gain_get(const char *buf);
int ae_vga_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_stat_adc_vref_val_get(const char *buf);
int ae_adc_vref_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_offset_stat_cdr_offset_get(const char *buf);
int ae_cdr_offset_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_stat0_ffe_fm2_get(const char *buf);
uint8_t uphy_reg_ae_ffe_stat0_ffe_fm3_get(const char *buf);
int ae_ffe_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_stat1_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_ffe_stat1_ffe_fm1_get(const char *buf);
int ae_ffe_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_stat2_ffe_f3_get(const char *buf);
uint8_t uphy_reg_ae_ffe_stat2_ffe_f2_get(const char *buf);
int ae_ffe_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_stat3_ffe_f5_get(const char *buf);
uint8_t uphy_reg_ae_ffe_stat3_ffe_f4_get(const char *buf);
int ae_ffe_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_stat4_ffe_f7_get(const char *buf);
uint8_t uphy_reg_ae_ffe_stat4_ffe_f6_get(const char *buf);
int ae_ffe_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_stat5_ffe_f8_get(const char *buf);
int ae_ffe_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_stat0_dffe_dsel1_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat0_dffe_coef1_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat0_dffe_dsel0_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat0_dffe_coef0_get(const char *buf);
int ae_dffe_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_stat1_dffe_dsel3_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat1_dffe_coef3_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat1_dffe_dsel2_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat1_dffe_coef2_get(const char *buf);
int ae_dffe_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_stat2_dffe_dsel5_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat2_dffe_coef5_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat2_dffe_dsel4_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat2_dffe_coef4_get(const char *buf);
int ae_dffe_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_stat3_dffe_dsel7_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat3_dffe_coef7_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat3_dffe_dsel6_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat3_dffe_coef6_get(const char *buf);
int ae_dffe_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_dffe_stat4_dffe_dsel8_get(const char *buf);
uint8_t uphy_reg_ae_dffe_stat4_dffe_coef8_get(const char *buf);
int ae_dffe_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th0_stat_th0_get(const char *buf);
int ae_slicer_th0_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th1_stat_th1_get(const char *buf);
int ae_slicer_th1_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th2_stat_th2_get(const char *buf);
int ae_slicer_th2_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th3_stat_th3_get(const char *buf);
int ae_slicer_th3_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th4_stat_th4_get(const char *buf);
int ae_slicer_th4_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th5_stat_th5_get(const char *buf);
int ae_slicer_th5_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th6_stat_th6_get(const char *buf);
int ae_slicer_th6_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th7_stat_th7_get(const char *buf);
int ae_slicer_th7_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th8_stat_th8_get(const char *buf);
int ae_slicer_th8_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th9_stat_th9_get(const char *buf);
int ae_slicer_th9_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th10_stat_th10_get(const char *buf);
int ae_slicer_th10_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th11_stat_th11_get(const char *buf);
int ae_slicer_th11_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th12_stat_th12_get(const char *buf);
int ae_slicer_th12_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th13_stat_th13_get(const char *buf);
int ae_slicer_th13_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th14_stat_th14_get(const char *buf);
int ae_slicer_th14_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th15_stat_th15_get(const char *buf);
int ae_slicer_th15_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th16_stat_th16_get(const char *buf);
int ae_slicer_th16_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th17_stat_th17_get(const char *buf);
int ae_slicer_th17_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th18_stat_th18_get(const char *buf);
int ae_slicer_th18_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th19_stat_th19_get(const char *buf);
int ae_slicer_th19_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th20_stat_th20_get(const char *buf);
int ae_slicer_th20_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_th21_stat_th21_get(const char *buf);
int ae_slicer_th21_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_h0_stat_h0_get(const char *buf);
int ae_slicer_h0_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_h1_stat_h1_get(const char *buf);
int ae_slicer_h1_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_h2_stat_h2_get(const char *buf);
int ae_slicer_h2_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_slicer_state_stat_eth_clk_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_state_stat_eth_state_get(const char *buf);
uint8_t uphy_reg_ae_eq_slicer_state_stat_eth_op_get(const char *buf);
int ae_eq_slicer_state_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_term_attn_ctx_ctrl_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_term_attn_ctx_ctrl_term_attn_ctrl_get(const char *buf);
int ae_term_attn_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctx_ctrl0_dc_gain_get(const char *buf);
int ae_ctle_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ctle_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_ctle_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_ctle_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_vga_ctx_ctrl_vga_gain_get(const char *buf);
int ae_vga_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_adc_vref_ctx_ctrl_adc_vref_val_get(const char *buf);
int ae_adc_vref_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_cdr_offset_ctx_ctrl_cdr_offset_get(const char *buf);
int ae_cdr_offset_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctx_ctrl0_ffe_fm2_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctx_ctrl0_ffe_fm3_get(const char *buf);
int ae_ffe_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctx_ctrl1_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctx_ctrl1_ffe_fm1_get(const char *buf);
int ae_ffe_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctx_ctrl2_ffe_f3_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctx_ctrl2_ffe_f2_get(const char *buf);
int ae_ffe_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctx_ctrl3_ffe_f5_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctx_ctrl3_ffe_f4_get(const char *buf);
int ae_ffe_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctx_ctrl4_ffe_f7_get(const char *buf);
uint8_t uphy_reg_ae_ffe_ctx_ctrl4_ffe_f6_get(const char *buf);
int ae_ffe_ctx_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_ffe_ctx_ctrl5_ffe_f8_get(const char *buf);
int ae_ffe_ctx_ctrl5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctx_ctrl0_dffe_dsel1_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl0_dffe_coef1_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl0_dffe_dsel0_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl0_dffe_coef0_get(const char *buf);
int ae_dffe_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctx_ctrl1_dffe_dsel3_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl1_dffe_coef3_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl1_dffe_dsel2_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl1_dffe_coef2_get(const char *buf);
int ae_dffe_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctx_ctrl2_dffe_dsel5_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl2_dffe_coef5_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl2_dffe_dsel4_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl2_dffe_coef4_get(const char *buf);
int ae_dffe_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_dffe_ctx_ctrl3_dffe_dsel7_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl3_dffe_coef7_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl3_dffe_dsel6_get(const char *buf);
uint8_t uphy_reg_ae_dffe_ctx_ctrl3_dffe_coef6_get(const char *buf);
int ae_dffe_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth0_ctx_ctrl_eth0_get(const char *buf);
int ae_slicer_eth0_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth1_ctx_ctrl_eth1_get(const char *buf);
int ae_slicer_eth1_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth2_ctx_ctrl_eth2_get(const char *buf);
int ae_slicer_eth2_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth3_ctx_ctrl_eth3_get(const char *buf);
int ae_slicer_eth3_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth4_ctx_ctrl_eth4_get(const char *buf);
int ae_slicer_eth4_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth5_ctx_ctrl_eth5_get(const char *buf);
int ae_slicer_eth5_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth6_ctx_ctrl_eth6_get(const char *buf);
int ae_slicer_eth6_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_slicer_eth7_ctx_ctrl_eth7_get(const char *buf);
int ae_slicer_eth7_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eq_state_ctx_ctrl_feq_adc_cal_off_get(const char *buf);
uint8_t uphy_reg_ae_eq_state_ctx_ctrl_dffe_peq_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_state_ctx_ctrl_dffe_feq_en_get(const char *buf);
uint8_t uphy_reg_ae_eq_state_ctx_ctrl_eq_train_valid_get(const char *buf);
uint8_t uphy_reg_ae_eq_state_ctx_ctrl_eq_initialized_get(const char *buf);
int ae_eq_state_ctx_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_adc_vos_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_adc_vos_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_adc_vos_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_vos_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_adc_vos_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_adc_gos_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_adc_gos_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_adc_gos_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_adc_gos_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_adc_gos_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_vga_vos0_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_vga_vos0_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_vga_vos0_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos0_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_vga_vos0_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_vga_vos1_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_vga_vos1_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_vga_vos1_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_vga_vos1_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_vga_vos1_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_ctle_vos_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_ctle_vos_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_ctle_vos_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_ctle_vos_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_ctle_vos_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_scal_phos_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_scal_phos_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_scal_phos_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_scal_phos_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_scal_phos_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_dme_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_dme_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_dme_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_dme_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_dme_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_dme_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_dme_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_dme_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_dme_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_signal_det_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_signal_det_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_signal_det_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_signal_det_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_signal_det_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl0_vga_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl0_hf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl0_dc_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl0_term_lpf_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl0_term_attn_ctrl_get(const char *buf);
int ae_fe_incr_vos_ctx_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl1_mf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl1_mf_gain_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl1_lf_pole_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl1_lf_gain_get(const char *buf);
int ae_fe_incr_vos_ctx_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl2_ffe_f2_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl2_adc_vref_val_get(const char *buf);
int ae_fe_incr_vos_ctx_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl3_ffe_f1_get(const char *buf);
uint8_t uphy_reg_ae_fe_incr_vos_ctx_ctrl3_ffe_fm1_get(const char *buf);
int ae_fe_incr_vos_ctx_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_ctrl0_sth_start_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_ctrl0_eom_vsign_get(const char *buf);
uint8_t uphy_reg_ae_eom_ctrl0_eye_index_get(const char *buf);
uint8_t uphy_reg_ae_eom_ctrl0_fom_init_time_get(const char *buf);
uint8_t uphy_reg_ae_eom_ctrl0_fom_timeout_get(const char *buf);
uint8_t uphy_reg_ae_eom_ctrl0_ber_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_eom_ctrl0_eom_mode_get(const char *buf);
int ae_eom_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_ctrl1_ber_rnk1_mask_get(const char *buf);
uint8_t uphy_reg_ae_eom_ctrl1_ber_rnk2_mask_get(const char *buf);
int ae_eom_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_sth_ovrd_ctrl_sth_ovrd_get(const char *buf);
int ae_eom_sth_ovrd_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_sth_ctrl0_sth0_get(const char *buf);
int ae_eom_sth_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_sth_ctrl1_sth1_get(const char *buf);
int ae_eom_sth_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_sth_ctrl2_sth2_get(const char *buf);
int ae_eom_sth_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_sth_ctrl3_sth3_get(const char *buf);
int ae_eom_sth_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_sth_ctrl4_sth4_get(const char *buf);
int ae_eom_sth_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_sth_ctrl5_sth5_get(const char *buf);
int ae_eom_sth_ctrl5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_sth_ctrl6_sth6_get(const char *buf);
int ae_eom_sth_ctrl6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_sth_ctrl7_sth7_get(const char *buf);
int ae_eom_sth_ctrl7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_sym_filter_ctrl_future_d_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_sym_filter_ctrl_pam2_future_bitpat_get(const char *buf);
uint8_t uphy_reg_ae_eom_sym_filter_ctrl_ber_xk_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_sym_filter_ctrl_xk_mask_get(const char *buf);
uint8_t uphy_reg_ae_eom_sym_filter_ctrl_xk_pattern_get(const char *buf);
uint8_t uphy_reg_ae_eom_sym_filter_ctrl_xk_match_get(const char *buf);
int ae_eom_sym_filter_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_mode_txfir_ctrl0_txfir_cm1_response_get(const char *buf);
uint8_t uphy_reg_ae_eom_mode_txfir_ctrl0_txfir_cm3_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_eom_mode_txfir_ctrl0_txfir_cm2_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_eom_mode_txfir_ctrl0_txfir_cm1_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_eom_mode_txfir_ctrl0_txfir_c0_grad_inv_get(const char *buf);
uint8_t uphy_reg_ae_eom_mode_txfir_ctrl0_skip_fom_get(const char *buf);
uint8_t uphy_reg_ae_eom_mode_txfir_ctrl0_txfir_cm3_th_get(const char *buf);
int ae_eom_mode_txfir_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_mode_txfir_ctrl1_txfir_cm2_th_get(const char *buf);
uint8_t uphy_reg_ae_eom_mode_txfir_ctrl1_txfir_cm1_th_get(const char *buf);
int ae_eom_mode_txfir_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_vt_ctrl_ber_v_get(const char *buf);
uint8_t uphy_reg_ae_eom_vt_ctrl_ber_t_get(const char *buf);
int ae_eom_vt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_fom_cdr_offset_ctrl_id0_cdr_offset_scale_get(const char *buf);
uint16_t uphy_reg_ae_eom_fom_cdr_offset_ctrl_id0_cdr_offset_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_fom_cdr_offset_ctrl_id0_cdr_offset_min_get(const char *buf);
int ae_eom_fom_cdr_offset_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_fom_cdr_offset_ctrl_id1_cdr_offset_scale_get(const char *buf);
uint16_t uphy_reg_ae_eom_fom_cdr_offset_ctrl_id1_cdr_offset_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_fom_cdr_offset_ctrl_id1_cdr_offset_min_get(const char *buf);
int ae_eom_fom_cdr_offset_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_feq_fom_hyst_ctrl_peq_fom_hyst_th_get(const char *buf);
uint8_t uphy_reg_ae_feq_fom_hyst_ctrl_lnsrch_fom_hyst_th_get(const char *buf);
uint8_t uphy_reg_ae_feq_fom_hyst_ctrl_fom_hyst_th_get(const char *buf);
int ae_feq_fom_hyst_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_meas_mode_ctrl_fom_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_meas_mode_ctrl_eom_fmr_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_meas_mode_ctrl_eom_fmr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_meas_mode_ctrl_fom_norm_max_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_meas_mode_ctrl_eom_grad_get(const char *buf);
uint8_t uphy_reg_ae_eom_meas_mode_ctrl_ber_mode_get(const char *buf);
int ae_eom_meas_mode_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_meas_ber_ctrl_nblks_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_meas_ber_ctrl_nerrs_min_get(const char *buf);
int ae_eom_meas_ber_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_meas_eye_ctrl_pam_eye_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_meas_eye_ctrl_eyeo_range_get(const char *buf);
uint8_t uphy_reg_ae_eom_meas_eye_ctrl_ber_eye_sel_get(const char *buf);
int ae_eom_meas_eye_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_meas_vt_ctrl_ber_t_get(const char *buf);
uint16_t uphy_reg_ae_eom_meas_vt_ctrl_ber_v_get(const char *buf);
int ae_eom_meas_vt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id0_fom_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id0_eom_fmr_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id0_eom_fmr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id0_fom_norm_max_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id0_eom_grad_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id0_ber_mode_get(const char *buf);
int ae_eom_feq_mode_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id1_fom_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id1_eom_fmr_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id1_eom_fmr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id1_fom_norm_max_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id1_eom_grad_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_mode_ctrl_id1_ber_mode_get(const char *buf);
int ae_eom_feq_mode_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_feq_ber_ctrl_nblks_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_ber_ctrl_nerrs_min_get(const char *buf);
int ae_eom_feq_ber_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_feq_eye_ctrl_pam_eye_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_eye_ctrl_eyeo_range_get(const char *buf);
uint8_t uphy_reg_ae_eom_feq_eye_ctrl_ber_eye_sel_get(const char *buf);
int ae_eom_feq_eye_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_feq_vt_ctrl_ber_t_get(const char *buf);
uint16_t uphy_reg_ae_eom_feq_vt_ctrl_ber_v_get(const char *buf);
int ae_eom_feq_vt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_txfir_mode_ctrl_fom_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_txfir_mode_ctrl_eom_fmr_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_txfir_mode_ctrl_eom_fmr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_txfir_mode_ctrl_fom_norm_max_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_txfir_mode_ctrl_eom_grad_get(const char *buf);
uint8_t uphy_reg_ae_eom_txfir_mode_ctrl_ber_mode_get(const char *buf);
int ae_eom_txfir_mode_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_txfir_ber_ctrl_nblks_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_txfir_ber_ctrl_nerrs_min_get(const char *buf);
int ae_eom_txfir_ber_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_txfir_eye_ctrl_pam_eye_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_txfir_eye_ctrl_eyeo_range_get(const char *buf);
uint8_t uphy_reg_ae_eom_txfir_eye_ctrl_ber_eye_sel_get(const char *buf);
int ae_eom_txfir_eye_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_txfir_vt_ctrl_ber_t_get(const char *buf);
uint16_t uphy_reg_ae_eom_txfir_vt_ctrl_ber_v_get(const char *buf);
int ae_eom_txfir_vt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_adc_zmax_mode_ctrl_fom_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_adc_zmax_mode_ctrl_eom_fmr_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_adc_zmax_mode_ctrl_eom_fmr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_adc_zmax_mode_ctrl_fom_norm_max_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_adc_zmax_mode_ctrl_eom_grad_get(const char *buf);
uint8_t uphy_reg_ae_eom_adc_zmax_mode_ctrl_ber_mode_get(const char *buf);
int ae_eom_adc_zmax_mode_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_adc_zmax_ber_ctrl_nblks_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_adc_zmax_ber_ctrl_nerrs_min_get(const char *buf);
int ae_eom_adc_zmax_ber_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_adc_zmax_eye_ctrl_pam_eye_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_adc_zmax_eye_ctrl_eyeo_range_get(const char *buf);
uint8_t uphy_reg_ae_eom_adc_zmax_eye_ctrl_ber_eye_sel_get(const char *buf);
int ae_eom_adc_zmax_eye_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_adc_zmax_vt_ctrl_ber_t_get(const char *buf);
uint16_t uphy_reg_ae_eom_adc_zmax_vt_ctrl_ber_v_get(const char *buf);
int ae_eom_adc_zmax_vt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_ffe_zmax_mode_ctrl_fom_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_ffe_zmax_mode_ctrl_eom_fmr_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_ffe_zmax_mode_ctrl_eom_fmr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_ffe_zmax_mode_ctrl_fom_norm_max_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_ffe_zmax_mode_ctrl_eom_grad_get(const char *buf);
uint8_t uphy_reg_ae_eom_ffe_zmax_mode_ctrl_ber_mode_get(const char *buf);
int ae_eom_ffe_zmax_mode_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_ffe_zmax_ber_ctrl_nblks_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_ffe_zmax_ber_ctrl_nerrs_min_get(const char *buf);
int ae_eom_ffe_zmax_ber_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_ffe_zmax_eye_ctrl_pam_eye_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_ffe_zmax_eye_ctrl_eyeo_range_get(const char *buf);
uint8_t uphy_reg_ae_eom_ffe_zmax_eye_ctrl_ber_eye_sel_get(const char *buf);
int ae_eom_ffe_zmax_eye_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_ffe_zmax_vt_ctrl_ber_t_get(const char *buf);
uint16_t uphy_reg_ae_eom_ffe_zmax_vt_ctrl_ber_v_get(const char *buf);
int ae_eom_ffe_zmax_vt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_peq_mode_ctrl_fom_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_peq_mode_ctrl_eom_fmr_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_peq_mode_ctrl_eom_fmr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_peq_mode_ctrl_fom_norm_max_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_peq_mode_ctrl_eom_grad_get(const char *buf);
uint8_t uphy_reg_ae_eom_peq_mode_ctrl_ber_mode_get(const char *buf);
int ae_eom_peq_mode_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_peq_ber_ctrl_nblks_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_peq_ber_ctrl_nerrs_min_get(const char *buf);
int ae_eom_peq_ber_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_peq_eye_ctrl_pam_eye_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_peq_eye_ctrl_eyeo_range_get(const char *buf);
uint8_t uphy_reg_ae_eom_peq_eye_ctrl_ber_eye_sel_get(const char *buf);
int ae_eom_peq_eye_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_peq_vt_ctrl_ber_t_get(const char *buf);
uint16_t uphy_reg_ae_eom_peq_vt_ctrl_ber_v_get(const char *buf);
int ae_eom_peq_vt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_signal_det_mode_ctrl_fom_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_signal_det_mode_ctrl_eom_fmr_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_signal_det_mode_ctrl_eom_fmr_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_signal_det_mode_ctrl_fom_norm_max_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_signal_det_mode_ctrl_eom_grad_get(const char *buf);
uint8_t uphy_reg_ae_eom_signal_det_mode_ctrl_ber_mode_get(const char *buf);
int ae_eom_signal_det_mode_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_signal_det_ber_ctrl_nblks_max_get(const char *buf);
uint8_t uphy_reg_ae_eom_signal_det_ber_ctrl_nerrs_min_get(const char *buf);
int ae_eom_signal_det_ber_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_signal_det_eye_ctrl_pam_eye_sel_get(const char *buf);
uint8_t uphy_reg_ae_eom_signal_det_eye_ctrl_eyeo_range_get(const char *buf);
uint8_t uphy_reg_ae_eom_signal_det_eye_ctrl_ber_eye_sel_get(const char *buf);
int ae_eom_signal_det_eye_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_signal_det_vt_ctrl_ber_t_get(const char *buf);
uint16_t uphy_reg_ae_eom_signal_det_vt_ctrl_ber_v_get(const char *buf);
int ae_eom_signal_det_vt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_margin_ctrl0_margin_en_get(const char *buf);
uint8_t uphy_reg_ae_margin_ctrl0_margin_t_get(const char *buf);
uint8_t uphy_reg_ae_margin_ctrl0_margin_v_get(const char *buf);
int ae_margin_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_margin_ctrl1_margin_pam2pr1_vdm_get(const char *buf);
uint8_t uphy_reg_ae_margin_ctrl1_margin_v_scale_get(const char *buf);
uint8_t uphy_reg_ae_margin_ctrl1_margin_cdr_trk_time_get(const char *buf);
uint8_t uphy_reg_ae_margin_ctrl1_margin_nblks_max_get(const char *buf);
int ae_margin_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_margin_cdr_offset_ctrl_id0_cdr_offset_max_get(const char *buf);
uint8_t uphy_reg_ae_margin_cdr_offset_ctrl_id0_cdr_offset_min_get(const char *buf);
int ae_margin_cdr_offset_ctrl_id0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_margin_cdr_offset_ctrl_id1_cdr_offset_max_get(const char *buf);
uint8_t uphy_reg_ae_margin_cdr_offset_ctrl_id1_cdr_offset_min_get(const char *buf);
int ae_margin_cdr_offset_ctrl_id1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_state_ctrl_fom_state_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_state_ctrl_fom_op_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_eom_state_ctrl_fom_state_get(const char *buf);
uint8_t uphy_reg_ae_eom_state_ctrl_fom_op_get(const char *buf);
int ae_eom_state_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_fom_stat0_fom_get(const char *buf);
int ae_eom_fom_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_fom_stat1_fom_get(const char *buf);
int ae_eom_fom_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_nblks_stat_ber_nblks_get(const char *buf);
int ae_eom_nblks_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_nerrs_stat_fom_timed_out_get(const char *buf);
uint8_t uphy_reg_ae_eom_nerrs_stat_eye_is_closed_get(const char *buf);
uint16_t uphy_reg_ae_eom_nerrs_stat_ber_nerrs_get(const char *buf);
int ae_eom_nerrs_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_state_stat_fom_state_get(const char *buf);
uint8_t uphy_reg_ae_eom_state_stat_fom_op_get(const char *buf);
int ae_eom_state_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_ctrl0_vos_adc_test_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_gos_adc_test_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_vos_vga_test_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_vos_ctle_test_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_latch_phos_test_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_latch_adc_vos_test_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_latch_adc_gos_test_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_fom_retest_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_phos_test_en_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_latch_test_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_vos_test_mode_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_ctrl0_fom_test_mode_get(const char *buf);
int ae_eom_test_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_th_ctrl0_vga_vos_threshold_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_th_ctrl0_ctle_vos_threshold_get(const char *buf);
int ae_eom_test_th_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_th_ctrl1_adc_vos_threshold_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_th_ctrl1_adc_gos_threshold_get(const char *buf);
int ae_eom_test_th_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_th_ctrl2_phos_threshold_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_th_ctrl2_fom_threshold_get(const char *buf);
int ae_eom_test_th_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_eom_test_ae_err_stat_ae_err_flag_get(const char *buf);
int ae_eom_test_ae_err_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_ctle_vga_stat_vga_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_ctle_vga_stat_ctle_vos_err_flag_get(const char *buf);
int ae_eom_test_vos_ctle_vga_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_adc0_stat_adc0_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_adc0_stat_adc0_gos_err_flag_get(const char *buf);
int ae_eom_test_vos_adc0_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_adc1_stat_adc1_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_adc1_stat_adc1_gos_err_flag_get(const char *buf);
int ae_eom_test_vos_adc1_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_adc2_stat_adc2_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_adc2_stat_adc2_gos_err_flag_get(const char *buf);
int ae_eom_test_vos_adc2_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_adc3_stat_adc3_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_adc3_stat_adc3_gos_err_flag_get(const char *buf);
int ae_eom_test_vos_adc3_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_adc4_stat_adc4_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_adc4_stat_adc4_gos_err_flag_get(const char *buf);
int ae_eom_test_vos_adc4_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_adc5_stat_adc5_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_adc5_stat_adc5_gos_err_flag_get(const char *buf);
int ae_eom_test_vos_adc5_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_adc6_stat_adc6_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_adc6_stat_adc6_gos_err_flag_get(const char *buf);
int ae_eom_test_vos_adc6_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_vos_adc7_stat_adc7_vos_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_vos_adc7_stat_adc7_gos_err_flag_get(const char *buf);
int ae_eom_test_vos_adc7_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_phos_stat_phos_err_flag_get(const char *buf);
int ae_eom_test_phos_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_adc0_stat_adc0_vos_latch_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_latch_adc0_stat_adc0_gos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_adc0_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_adc1_stat_adc1_vos_latch_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_latch_adc1_stat_adc1_gos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_adc1_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_adc2_stat_adc2_vos_latch_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_latch_adc2_stat_adc2_gos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_adc2_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_adc3_stat_adc3_vos_latch_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_latch_adc3_stat_adc3_gos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_adc3_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_adc4_stat_adc4_vos_latch_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_latch_adc4_stat_adc4_gos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_adc4_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_adc5_stat_adc5_vos_latch_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_latch_adc5_stat_adc5_gos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_adc5_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_adc6_stat_adc6_vos_latch_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_latch_adc6_stat_adc6_gos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_adc6_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_adc7_stat_adc7_vos_latch_err_flag_get(const char *buf);
uint8_t uphy_reg_ae_eom_test_latch_adc7_stat_adc7_gos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_adc7_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_eom_test_latch_phos_stat_phos_latch_err_flag_get(const char *buf);
int ae_eom_test_latch_phos_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_bist_pgen_ctrl0_use_mgmt_clk_get(const char *buf);
uint8_t uphy_reg_bist_pgen_ctrl0_ssprq_seq2_4_noinv_en_get(const char *buf);
uint8_t uphy_reg_bist_pgen_ctrl0_pattern_shift_get(const char *buf);
uint8_t uphy_reg_bist_pgen_ctrl0_bist_type_get(const char *buf);
uint8_t uphy_reg_bist_pgen_ctrl0_clk_en_get(const char *buf);
uint8_t uphy_reg_bist_pgen_ctrl0_load_en_get(const char *buf);
uint8_t uphy_reg_bist_pgen_ctrl0_data_en_get(const char *buf);
uint8_t uphy_reg_bist_pgen_ctrl0_bist_en_get(const char *buf);
int bist_pgen_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_pgen_data_ctrl0_pat_data_get(const char *buf);
int bist_pgen_data_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_pgen_data_ctrl1_pat_data_get(const char *buf);
int bist_pgen_data_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_pgen_data_ctrl2_pat_data_get(const char *buf);
int bist_pgen_data_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_pgen_data_ctrl3_pat_data_get(const char *buf);
int bist_pgen_data_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_bist_pchk_ctrl_ssprq_seq2_4_noinv_en_get(const char *buf);
uint8_t uphy_reg_bist_pchk_ctrl_err_rd_mode_get(const char *buf);
uint8_t uphy_reg_bist_pchk_ctrl_fea_mode_get(const char *buf);
uint8_t uphy_reg_bist_pchk_ctrl_pattern_shift_get(const char *buf);
uint8_t uphy_reg_bist_pchk_ctrl_bist_type_get(const char *buf);
uint8_t uphy_reg_bist_pchk_ctrl_invert_get(const char *buf);
uint8_t uphy_reg_bist_pchk_ctrl_sync_mode_get(const char *buf);
uint8_t uphy_reg_bist_pchk_ctrl_err_clear_get(const char *buf);
uint8_t uphy_reg_bist_pchk_ctrl_bist_en_get(const char *buf);
int bist_pchk_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_pchk_data_ctrl0_pat_data_get(const char *buf);
int bist_pchk_data_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_pchk_data_ctrl1_pat_data_get(const char *buf);
int bist_pchk_data_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_pchk_data_ctrl2_pat_data_get(const char *buf);
int bist_pchk_data_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_pchk_data_ctrl3_pat_data_get(const char *buf);
int bist_pchk_data_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_bist_err_flg_stat_sync_done_get(const char *buf);
uint8_t uphy_reg_bist_err_flg_stat_err_flag_get(const char *buf);
int bist_err_flg_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_err_cnt_stat_err_cnt_get(const char *buf);
int bist_err_cnt_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_err_data_stat0_err_data_get(const char *buf);
int bist_err_data_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_err_data_stat1_err_data_get(const char *buf);
int bist_err_data_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_err_data_stat2_err_data_get(const char *buf);
int bist_err_data_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_bist_err_data_stat3_err_data_get(const char *buf);
int bist_err_data_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_loop_ctrl0_nea_drv_z_pcal_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl0_nea_drv_z_ncal_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl0_nea_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl0_nea_en_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl0_ned_en_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl0_ned_mode_get(const char *buf);
int mgmt_loop_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_loop_ctrl1_rx_adc_fea_subadc_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl1_rx_adc_fea_subadc_sel_get(const char *buf);
uint16_t uphy_reg_mgmt_loop_ctrl1_rx_afe_fea_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl1_fea_en_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl1_fea_mode_get(const char *buf);
int mgmt_loop_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_loop_ctrl2_dlm_fea_sel_get(const char *buf);
uint16_t uphy_reg_mgmt_loop_ctrl2_des_fea_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl2_adc_fea_samp_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl2_adc_fea_sel_get(const char *buf);
int mgmt_loop_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_loop_ctrl3_fed_mode_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl3_fed_en_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl3_fed_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl3_tx2rx_test_in2out_en_get(const char *buf);
uint8_t uphy_reg_mgmt_loop_ctrl3_rx2pll_refclk_en_get(const char *buf);
int mgmt_loop_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_ckdiv2_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_res_ctrl_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_leveldet_en_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_rail_cal_en_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_rail_high_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_rail_en_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_rd_mode_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_chopper_en_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl0_pmu_en_get(const char *buf);
int mgmt_pmu_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_pmu_ctrl1_pmu_fs_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl1_pmu_bias_time_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl1_pmu_load_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl1_pmu_load_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl1_pmu_start_ovrd_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl1_pmu_start_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_ctrl1_pmu_en_ovrd_get(const char *buf);
int mgmt_pmu_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_pmu_th_ctrl0_pmu_th_min_get(const char *buf);
int mgmt_pmu_th_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_pmu_th_ctrl1_pmu_th_max_get(const char *buf);
int mgmt_pmu_th_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_pmu_stat0_pmu_valid_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_stat0_pmu_pass_get(const char *buf);
uint16_t uphy_reg_mgmt_pmu_stat0_pmu_out_get(const char *buf);
int mgmt_pmu_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_pmu_stat1_pmu_done_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_stat1_pmu_load_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_stat1_pmu_start_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_stat1_pmu_en_get(const char *buf);
uint8_t uphy_reg_mgmt_pmu_stat1_pmu_state_get(const char *buf);
int mgmt_pmu_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_atest_ctrl0_rx_tah_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl0_rx_bias_atest_sel_get(const char *buf);
uint16_t uphy_reg_mgmt_atest_ctrl0_rx_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl0_tx_atest_sel_get(const char *buf);
int mgmt_atest_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_atest_ctrl1_rx_rvdd_atest_sel_get(const char *buf);
uint16_t uphy_reg_mgmt_atest_ctrl1_tx_rvdd_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl1_rx_clkrcv_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl1_tx_clkrcv_atest_sel_get(const char *buf);
int mgmt_atest_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_atest_ctrl2_tx_cal_adc_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl2_tx_txpll_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl2_tx_clkbuf_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl2_tx_bias_atest_sel_get(const char *buf);
int mgmt_atest_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_atest_ctrl3_rx_ctle_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl3_rx_vga_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl3_rx_term_atest_sel_get(const char *buf);
int mgmt_atest_ctrl3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_atest_ctrl4_rx_calcomp_atest_sel_get(const char *buf);
uint16_t uphy_reg_mgmt_atest_ctrl4_rx_adc_atest_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_atest_ctrl4_rx_dco_atest_sel_get(const char *buf);
int mgmt_atest_ctrl4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_clt_ctrl_rx_clt_pulldn_en_get(const char *buf);
uint8_t uphy_reg_mgmt_clt_ctrl_rx_clt_pullup_en_get(const char *buf);
uint8_t uphy_reg_mgmt_clt_ctrl_tx_clt_pulldn_en_get(const char *buf);
uint8_t uphy_reg_mgmt_clt_ctrl_tx_clt_pullup_en_get(const char *buf);
int mgmt_clt_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_obs_hsdac_ctrl_hsdac_adc_rank2_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_obs_hsdac_ctrl_hsdac_adc_rank1_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_obs_hsdac_ctrl_hsdac_sel_get(const char *buf);
int mgmt_obs_hsdac_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_obs_ctrl_obs_data_en_get(const char *buf);
uint8_t uphy_reg_mgmt_obs_ctrl_obs_data_sel_get(const char *buf);
uint8_t uphy_reg_mgmt_obs_ctrl_obs_data_adc_rank2_sel_get(const char *buf);
int mgmt_obs_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_obs_imem_ctrl_obs_imem_wr_en_get(const char *buf);
int mgmt_obs_imem_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_imem_start_addr_addr_get(const char *buf);
int mgmt_obs_imem_start_addr_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_imem_stop_addr_addr_get(const char *buf);
int mgmt_obs_imem_stop_addr_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_mgmt_obs_imem_stat_imem_wr_done_get(const char *buf);
int mgmt_obs_imem_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_stat0_obs_data_get(const char *buf);
int mgmt_obs_stat0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_stat1_obs_data_get(const char *buf);
int mgmt_obs_stat1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_stat2_obs_data_get(const char *buf);
int mgmt_obs_stat2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_stat3_obs_data_get(const char *buf);
int mgmt_obs_stat3_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_stat4_obs_data_get(const char *buf);
int mgmt_obs_stat4_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_stat5_obs_data_get(const char *buf);
int mgmt_obs_stat5_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_stat6_obs_data_get(const char *buf);
int mgmt_obs_stat6_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_mgmt_obs_stat7_obs_data_get(const char *buf);
int mgmt_obs_stat7_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_ctrl_ae_ao_clk_en_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_sys_ctrl_ae_ao_clk_en_get(const char *buf);
uint8_t uphy_reg_ae_sys_ctrl_cnt_clear_get(const char *buf);
uint8_t uphy_reg_ae_sys_ctrl_ae_clk_halt_time_get(const char *buf);
uint8_t uphy_reg_ae_sys_ctrl_ae_done_width_get(const char *buf);
uint8_t uphy_reg_ae_sys_ctrl_adc_res_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_sys_ctrl_ae_clk_req_ovrd_get(const char *buf);
int ae_sys_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_lfsr_ctrl0_load_seed_mask_get(const char *buf);
uint8_t uphy_reg_ae_sys_lfsr_ctrl0_load_seed_mode_get(const char *buf);
uint8_t uphy_reg_ae_sys_lfsr_ctrl0_load_en_get(const char *buf);
int ae_sys_lfsr_ctrl0_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_lfsr_ctrl1_load_val_get(const char *buf);
int ae_sys_lfsr_ctrl1_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_lfsr_ctrl2_load_val_get(const char *buf);
int ae_sys_lfsr_ctrl2_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_stat_error_ffe_cstr_get(const char *buf);
uint8_t uphy_reg_ae_sys_stat_ae_tsense_get(const char *buf);
uint8_t uphy_reg_ae_sys_stat_margin_valid_get(const char *buf);
uint8_t uphy_reg_ae_sys_stat_fe_ovrd_context_get(const char *buf);
uint8_t uphy_reg_ae_sys_stat_ae_state_get(const char *buf);
int ae_sys_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_rxinit_stat_abort_cnt_get(const char *buf);
uint8_t uphy_reg_ae_sys_rxinit_stat_done_cnt_get(const char *buf);
int ae_sys_rxinit_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_cdr_seq_stat_abort_cnt_get(const char *buf);
uint8_t uphy_reg_ae_sys_cdr_seq_stat_done_cnt_get(const char *buf);
int ae_sys_cdr_seq_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_cal_stat_abort_cnt_get(const char *buf);
uint8_t uphy_reg_ae_sys_cal_stat_done_cnt_get(const char *buf);
int ae_sys_cal_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_eq_stat_abort_cnt_get(const char *buf);
uint8_t uphy_reg_ae_sys_eq_stat_done_cnt_get(const char *buf);
int ae_sys_eq_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_eom_stat_abort_cnt_get(const char *buf);
uint8_t uphy_reg_ae_sys_eom_stat_done_cnt_get(const char *buf);
int ae_sys_eom_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_margin_stat_yield_cnt_get(const char *buf);
uint8_t uphy_reg_ae_sys_margin_stat_done_cnt_get(const char *buf);
int ae_sys_margin_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_misc0_ctrl_misc0_get(const char *buf);
int ae_sys_misc0_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_misc1_ctrl_misc1_get(const char *buf);
int ae_sys_misc1_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_misc2_ctrl_misc2_get(const char *buf);
int ae_sys_misc2_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_misc3_ctrl_misc3_get(const char *buf);
int ae_sys_misc3_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_misc0_stat_misc0_get(const char *buf);
int ae_sys_misc0_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_misc1_stat_misc1_get(const char *buf);
int ae_sys_misc1_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_ram_ctrl_imem_chksm_en_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_ctrl_imem_rd_en_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_ctrl_imem_wr_en_get(const char *buf);
int ae_sys_imem_ram_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_ram_clk_ctrl_obs_imem_clk_en_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_clk_ctrl_imem_clk_en_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_clk_ctrl_imem_wclk_mux_async_mode_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_clk_ctrl_imem_wclk_mux_sel_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_clk_ctrl_imem_rclk_mux_sel_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_clk_ctrl_imem_rclk_mux_async_mode_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_clk_ctrl_imem_rclk_mux_sel_get(const char *buf);
int ae_sys_imem_ram_clk_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_start_addr_ctrl_addr_get(const char *buf);
int ae_sys_imem_start_addr_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_stop_addr_ctrl_addr_get(const char *buf);
int ae_sys_imem_stop_addr_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap0_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap0_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap0_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap1_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap1_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap1_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap2_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap2_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap2_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap3_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap3_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap3_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap4_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap4_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap4_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap5_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap5_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap5_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap6_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap6_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap6_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap7_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap7_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap7_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap8_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap8_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap8_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap9_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap9_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap9_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap10_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap10_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap10_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap11_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap11_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap11_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap12_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap12_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap12_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap13_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap13_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap13_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap14_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap14_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap14_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_bmap15_key_ctrl_vld_get(const char *buf);
uint16_t uphy_reg_ae_sys_imem_bmap15_key_ctrl_key_get(const char *buf);
int ae_sys_imem_bmap15_key_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap0_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap0_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap1_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap1_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap2_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap2_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap3_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap3_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap4_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap4_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap5_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap5_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap6_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap6_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap7_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap7_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap8_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap8_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap9_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap9_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap10_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap10_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap11_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap11_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap12_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap12_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap13_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap13_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap14_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap14_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_bmap15_val_ctrl_val_get(const char *buf);
int ae_sys_imem_bmap15_val_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_ram_data_ctrl_wdata_get(const char *buf);
int ae_sys_imem_ram_data_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_ram_chksm_ctrl_chksm_get(const char *buf);
int ae_sys_imem_ram_chksm_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_imem_ram_stat_imem_rclk_mux_switch_status_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_stat_imem_wclk_mux_switch_status_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_stat_imem_chksm_status_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_stat_imem_chksm_done_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_stat_imem_rd_done_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_stat_imem_rd_rdy_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_stat_imem_wr_done_get(const char *buf);
uint8_t uphy_reg_ae_sys_imem_ram_stat_imem_wr_rdy_get(const char *buf);
int ae_sys_imem_ram_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_ram_data_stat_rdata_get(const char *buf);
int ae_sys_imem_ram_data_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_imem_ram_chksm_stat_chksm_get(const char *buf);
int ae_sys_imem_ram_chksm_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_dmem_ctrl_nop_stackerr_clr_get(const char *buf);
uint8_t uphy_reg_ae_sys_dmem_ctrl_nop_dbg_cmd_get(const char *buf);
uint8_t uphy_reg_ae_sys_dmem_ctrl_nop2nox_dmem_if_ovrd_get(const char *buf);
uint8_t uphy_reg_ae_sys_dmem_ctrl_nox2nop_dmem_if_ovrd_get(const char *buf);
int ae_sys_dmem_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_dmem_addr_ctrl_addr_get(const char *buf);
int ae_sys_dmem_addr_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_dmem_wdata_ctrl_wdata_get(const char *buf);
int ae_sys_dmem_wdata_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_dmem_rdata_ctrl_rdata_get(const char *buf);
int ae_sys_dmem_rdata_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_dmem_addr_stat_nop_dmem_addr_get(const char *buf);
int ae_sys_dmem_addr_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_dmem_wdata_stat_nop_dmem_wdata_get(const char *buf);
int ae_sys_dmem_wdata_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_dmem_rdata_stat_nox_dmem_rdata_get(const char *buf);
int ae_sys_dmem_rdata_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_nop_dbg_ctrl_nop_dbg_data_get(const char *buf);
int ae_sys_nop_dbg_ctrl_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_nop_p_stat_nop_p_get(const char *buf);
int ae_sys_nop_p_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_nop_i_stat_nop_i_get(const char *buf);
int ae_sys_nop_i_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_nop_t_stat_nop_t_get(const char *buf);
int ae_sys_nop_t_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_nop_n_stat_nop_n_get(const char *buf);
int ae_sys_nop_n_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint16_t uphy_reg_ae_sys_nop_r_stat_nop_r_get(const char *buf);
int ae_sys_nop_r_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);

uint8_t uphy_reg_ae_sys_nop_stat_nop_rs_unf_get(const char *buf);
uint8_t uphy_reg_ae_sys_nop_stat_nop_ds_unf_get(const char *buf);
uint8_t uphy_reg_ae_sys_nop_stat_nop_rs_ovf_get(const char *buf);
uint8_t uphy_reg_ae_sys_nop_stat_nop_ds_ovf_get(const char *buf);
uint8_t uphy_reg_ae_sys_nop_stat_nop_dmem_write_get(const char *buf);
uint8_t uphy_reg_ae_sys_nop_stat_nop_bkpt_triggered_get(const char *buf);
uint16_t uphy_reg_ae_sys_nop_stat_nop_rsp_get(const char *buf);
uint8_t uphy_reg_ae_sys_nop_stat_nop_dsp_get(const char *buf);
int ae_sys_nop_stat_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);


int sx_spice_uphy_reg_init(void);
void sx_spice_uphy_reg_deinit(void);

#endif /* SX_SPICE_UPHY_REG_AUTO_H_ */
