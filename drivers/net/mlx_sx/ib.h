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

#ifndef SX_IB_H
#define SX_IB_H


struct ib_header_lrh {
    u8     vl_lver;
    u8     sl_lnh;
    __be16 dlid;
    __be16 packet_length;
    __be16 slid;
};
struct ib_header_bth {
    u8     opcode;
    u8     se_m_pad_tver;
    __be16 pkey;
    __be32 dest_qp;
    __be32 a_psn;
};
struct ib_header_deth {
    __be32 qkey;
    __be32 src_qp;
};
struct ib_header_grh {
    __be32 ipver_tclass_flowLabel;
    __be16 pay_len;
    u8     nxt_hdr;
    u8     hop_lmt;
    u8     sgid[16];
    u8     dgid[16];
};
struct ib_header_unicast {
    struct ib_header_lrh  lrh;
    struct ib_header_bth  bth;
    struct ib_header_deth deth;
};
struct ib_header_multicast {
    struct ib_header_lrh  lrh;
    struct ib_header_grh  grh;
    struct ib_header_bth  bth;
    struct ib_header_deth deth;
};


#endif /* SX_IB_H */
