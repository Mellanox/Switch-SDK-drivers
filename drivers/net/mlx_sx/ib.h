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
