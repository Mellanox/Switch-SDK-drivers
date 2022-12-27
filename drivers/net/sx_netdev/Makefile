#
#                 - Mellanox Confidential and Proprietary -
#
# Copyright (C) January 2010, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
#
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#
#

EXTRA_CFLAGS += $(SXD_KERNEL_EXTRA_CFLAGS) -I$(src)
KBUILD_EXTRA_SYMBOLS := $(EXTRA_SYMVERS)
obj-m += sx_netdev.o

sx_netdev-objs := sx_netdev_main.o      \
                  sx_netdev_rtnetlink.o \
                  sx_bridge_rtnetlink.o \
                  sx_psample.o          \
                  sx_netdev_module_sysfs_eeprom.o \
                  synce.o                         \
                  sx_netdev_module_sysfs_s3ip.o

