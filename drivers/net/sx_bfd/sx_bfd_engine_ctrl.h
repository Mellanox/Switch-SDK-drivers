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

#ifndef __SX_BFD_ENGINE_CTRL_H_
#define __SX_BFD_ENGINE_CTRL_H_


/*
 *  Initialize BFD control engine
 */
int sx_bfd_engine_ctrl_init(void);

/*
 *  De-initialize BFD control engine
 */
void sx_bfd_engine_ctrl_deinit(void);

/*
 *  get session statistics
 */
int sx_bfd_get_sess_stats(char * data, uint8_t session_type, uint8_t clear_stats);


#endif /* __SX_BFD_ENGINE_CTRL_H_ */
