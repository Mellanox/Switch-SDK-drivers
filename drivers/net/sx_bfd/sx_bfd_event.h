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

#ifndef __SX_BFD_EVENT_H_
#define __SX_BFD_EVENT_H_

#include <net/sock.h>
#include "sx_bfd_socket.h"
#include "sx_bfd_rx_session.h"

void sx_bfd_event_send_packet(struct sx_bfd_rx_session *session,
                              char                     *packet,
                              uint32_t                  size,
                              struct metadata          *metadata,
                              unsigned long             bfd_user_space_pid);
void sx_bfd_event_send_timeout(struct sx_bfd_rx_session *session);

#endif /* __SX_BFD_EVENT_H_ */
