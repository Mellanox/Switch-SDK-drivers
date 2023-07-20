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

#ifndef __SX_BFD_CDEV_H_
#define __SX_BFD_CDEV_H_

typedef int (*parse_cmd_func)(char* data, int cmd);

/*
 *  Initialize BFD cdev
 */
int sx_bfd_cdev_init(parse_cmd_func func);

/*
 *  De-initialize BFD cdev
 */
void sx_bfd_cdev_deinit(void);


#endif /* __SX_BFD_CDEV_H_ */
