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

#ifndef _SX_DPT_H_
#define _SX_DPT_H_

#include <linux/pci.h>
#include <linux/mlx_sx/device.h>


#define SX_GET_PCI_BUS_ID(x)  (((x) & 0xFF0000) >> 16)
#define SX_GET_PCI_DEV_ID(x)  (((x) & 0x00FF00) >> 8)
#define SX_GET_PCI_FUNC_ID(x) ((x) & 0xFF)

/*
 *   struct per SX chip
 */
struct sx_dpt_info {
    /* spinlock_t				dpt_lock; */
    struct sx_dev           *sx_dev;
    enum ku_dpt_path_type    cmd_path;
    enum ku_dpt_path_type    emad_path;
    enum ku_dpt_path_type    mad_path;
    enum ku_dpt_path_type    cr_access_path;
    bool                     is_ifc_valid[DPT_PATH_MAX + 1];
    uint8_t                  is_local[DPT_PATH_MAX + 1];
    struct ku_dpt_i2c_info   sx_i2c_info;
    struct ku_dpt_pcie_info  sx_pcie_info;
    struct ku_dpt_sgmii_info sx_sgmii_info;
    u32                      in_mb_size;
    u32                      in_mb_offset;
    u32                      out_mb_size;
    u32                      out_mb_offset;
    u64                      fw_rev;
};
struct sx_dpt_s {
    struct sx_dpt_info dpt_info[MAX_NUM_OF_REMOTE_SWITCHES + 1];
};

/**
 * This function is used to init dpt table: 1. set the default
 * dpt path to i2c 2. set all dpt devs is_exists to FALSE
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_init(void);
int sx_dpt_init_default_dev(struct sx_dev *sx_dev);
int sx_dpt_init_dev_pci(struct sx_dev *sx_dev);

/**
 * This function returns true if the given dev is valid
 *
 *
 * param[in] returns: 1 true
 *      0 false
 */

bool sx_dpt_is_valid(int sx_dev_id);
int sx_dpt_alloc_dev_id(int* dpt_dev_id, struct sx_dev *sx_dev);
void sx_dpt_set_dev(int sx_dev_id, struct sx_dev *sx_dev);

struct sx_dev * sx_dpt_get_dev_from_id(int sx_dev_id);

/**
 * This function returns true if the given path is valid for
 * the given device, or false otherwise.
 *
 * param[in] returns: 1 true
 *	   0 false
 */
bool sx_dpt_is_path_valid(int sx_dev_id, enum  ku_dpt_path_type path);

/**
 * This function will add path to entry dev_id in DPT. The path
 * should be provided with remote device description. For example
 * , if added path is I2C than path_data should be i2c_dev_id.
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_add_dev_path(int                    sx_dev_id,
                        enum  ku_dpt_path_type path,
                        union ku_dpt_path_info path_data,
                        uint8_t                is_local);


/**
 * This function with params dev_id and path will invalidate the
 * given "path" at index DEV_ID in DPT. All other paths will
 * remains without changes.
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_remove_dev_path(int sx_dev_id, enum ku_dpt_path_type path);

/**
 * This function with params dev_id and path will invalidate all paths
 * at index DEV_ID in DPT.
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_remove_dev(int sx_dev_id, int restart_flow);

/**
 * This function is used to change cmd dpt path : i2c , pci-e , sgmii
 * by changing the callbacks to appropriate interface functions
 * To validate if the change is succeeded need to make some wr/rd
 * to check if the new interface is working
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_set_cmd_path(int sx_dev_id, enum  ku_dpt_path_type cmd_path);

/**
 * This function is used to change emad dpt path : i2c , pci-e , sgmii
 * by changing the callbacks to appropriate interface functions
 * To validate if the change is succeeded need to make some
 * wr/rd to check if the new interface is working
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_set_emad_path(int sx_dev_id, enum  ku_dpt_path_type emad_path);

/**
 * This function is used to change mad dpt path : i2c , pci-e ,
 * sgmii by changing the callbacks to appropriate interface
 * functions To validate if the change is succeeded need to make
 * some wr/rd to check if the new interface is working
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_set_mad_path(int sx_dev_id, enum  ku_dpt_path_type mad_path);

/**
 * This function is used to change mad dpt path : i2c , pci-e ,
 * sgmii by changing the callbacks to appropriate interface
 * functions To validate if the change is succeeded need to make
 * some wr/rd to check if the new interface is working
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_set_cr_access_path(int                    sx_dev_id,
                              enum  ku_dpt_path_type cr_access_path);

/**
 * This functions will perform access through cmd_path defined in DPT : I2C,PCI,SGMII.
 * Each writel in driver should be replaced to sx_dpt_write_u32.
 *
 * param[in] returns: 0 success
 *	   !0 error
 */
int sx_dpt_i2c_writel(int i2c_dev_id, u32 reg, u32 value);
int sx_dpt_i2c_write_buf(int i2c_dev_id, unsigned int i2c_offset,
                         unsigned char *buf, int size);
int sx_dpt_i2c_read_buf(int i2c_dev_id, unsigned int i2c_offset,
                        unsigned char *buf, int size);


/**
 * This functions will perform access through cmd_path defined in DPT : I2C,PCI,SGMII.
 * Each readl in driver should be replaced to sx_dpt_read_u32.
 * param[in] returns: 0 success
 *	   !0 error
 */
u32 sx_dpt_i2c_readl(int dev_id, u32 address, int *err);

/**
 * This functions will send emads according emad_path defined in DPT : I2C,PCI,SGMII.
 */
int sx_dpt_send_emad(int sx_dev_id, struct sk_buff *skb, struct isx_meta *meta);

int sx_dpt_send_mad(int sx_dev_id, struct sk_buff *skb, struct isx_meta *meta);

/**
 * This functions will return sx_dev_id of received emads
 * according emad_path defined in DPT : I2C,PCI,SGMII
 */
int sx_dpt_get_sx_dev_id(struct sk_buff *skb, int *sx_dev_id);

/**
 * This functions will read VPD. or WR/RD some scratch register by emad
 */
int sx_dpt_validate_new_emad_path(int sx_dev_id);

/*
 * This functions will read VPD. or WR/RD some scratch register by mad
 */
int sx_dpt_validate_new_mad_path(int sx_dev_id);
void sx_dpt_dump(void);
int sx_dpt_get_cmd_path(int sx_dev_id);
int sx_dpt_get_i2c_info(int sx_dev_id, struct ku_dpt_i2c_info** i2c_info);
int sx_dpt_get_pcie_info(int sx_dev_id, struct ku_dpt_pcie_info** pcie_info);
int sx_dpt_get_i2c_dev_by_id(int sx_dev_id, int *i2c_dev);
int sx_dpt_get_sx_dev_by_id(int sx_dev_id, struct sx_dev **dev);
int sx_dpt_get_cmd_sx_dev_by_id(int sx_dev_id, struct sx_dev **dev);
int sx_dpt_find_pci_dev(unsigned int sx_pci_dev_id,
                        int vendor, int device, struct pci_dev **sx_pci_dev);
int sx_dpt_stub_i2c_write(int i2c_dev_id, int offset, int len, u8 *in_out_buf);
int sx_dpt_stub_i2c_read(int i2c_dev_id, int offset, int len, u8 *in_out_buf);
int sx_dpt_stub_i2c_write_dword(int i2c_dev_id, int offset, u32 val);
int sx_dpt_stub_i2c_read_dword(int i2c_dev_id, int offset, u32 *val);
int sx_dpt_stub_i2c_enforce(int i2c_dev_id);
int sx_dpt_stub_i2c_release(int i2c_dev_id);
int sx_dpt_get_emad_path(int sx_dev_id);
int sx_dpt_cr_space_read(int dev_id, unsigned int address,
                         unsigned char *buf, int size);
int sx_dpt_cr_space_write(int dev_id, unsigned int address,
                          unsigned char *buf, int size);
int sx_dpt_move(int dst_dev_id, int src_dev_id);
int sx_dpt_is_dev_pci_attached(int sx_dev_id);
#endif /* ifndef _SX_DPT_H_ */
