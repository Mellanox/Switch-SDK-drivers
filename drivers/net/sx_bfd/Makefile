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

obj-$(CONFIG_SX_BFD) += sx_bfd.o
sx_bfd-objs := sx_bfd_main.o sx_bfd_rx_session.o sx_bfd_tx_session.o sx_bfd_cdev.o sx_bfd_engine_ctrl.o sx_bfd_engine_data.o sx_bfd_socket.o sx_bfd_workqueue.o sx_bfd_event.o

sx_bfd-y := sx_bfd.o

#all:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
#
#clean:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
