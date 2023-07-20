#
#                 - Mellanox Confidential and Proprietary -
#
# Copyright (C) January 2018, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
#
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#
#
EXTRA_CFLAGS += $(SXD_KERNEL_EXTRA_CFLAGS)
KBUILD_EXTRA_SYMBOLS := $(EXTRA_SYMVERS)
obj-m += sx_bfd.o
sx_bfd-objs := sx_bfd_main.o        \
               sx_bfd_rx_session.o  \
               sx_bfd_tx_session.o  \
               sx_bfd_cdev.o        \
               sx_bfd_engine_ctrl.o \
               sx_bfd_engine_data.o \
               sx_bfd_socket.o      \
               sx_bfd_workqueue.o   \
               sx_bfd_event.o

