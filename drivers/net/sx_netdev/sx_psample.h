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

#ifndef SX_PSAMPLE_H
#define SX_PSAMPLE_H

#if IS_ENABLED(CONFIG_PSAMPLE)

void sx_psample_set_synd(struct sx_dev       *dev,
                         u16                  synd,
                         enum sx_dev_event    event,
                         union sx_event_data *event_data);
void sx_psample_set_port_sample_ret(u8  local_port,
                                    u32 rate);
void sx_psample_cleanup(void);

#else /* IS_ENABLED(CONFIG_PSAMPLE) */

void sx_psample_set_synd(struct sx_dev *dev, u16 synd, enum sx_dev_event event, union sx_event_data *event_data)
{
}

void sx_psample_set_port_sample_ret(u8 local_port, u32 rate)
{
}

void sx_psample_cleanup(void)
{
}
#endif /* IS_ENABLED(CONFIG_PSAMPLE) */

#endif /* SX_PSAMPLE_H */
