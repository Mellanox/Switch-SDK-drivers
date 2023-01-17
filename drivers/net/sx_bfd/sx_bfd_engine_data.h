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

#ifndef __SX_BFD_ENGINE_DATA_H_
#define __SX_BFD_ENGINE_DATA_H_
#include <net/sock.h>
#include "sx_bfd_socket.h"
/*
 *  Initialize BFD data engine
 */
int sx_bfd_engine_data_init(void);

/*
 *  De-initialize BFD data engine
 */
void sx_bfd_engine_data_deinit(void);

void recv_packet(struct socket        *t_sock,
                 enum sx_bfd_sock_type sock_type,
                 uint32_t              vrf_id,
                 unsigned long         bfd_user_space_pid);


#endif /* __SX_BFD_ENGINE_DATA_H_ */
