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
EXTRA_CFLAGS += $(SXD_KERNEL_EXTRA_CFLAGS)
KBUILD_EXTRA_SYMBOLS := $(EXTRA_SYMVERS)
obj-m += sx_core.o

sx_core-objs := sx_core_main.o                  \
                dev_callbacks.o                 \
                emad.o                          \
                internal_log.o                  \
                dev_init.o                      \
                dev_db.o                        \
                dbg.o                           \
                dbg_host_ifc.o                  \
                dbg_db.o                        \
                health_check.o                  \
                qos_emad.o                 		\
                counter.o                       \
                skb_hook.o                      \
                cq.o                            \
                intf.o                          \
                dq.o                            \
                eq.o                            \
                alloc.o                         \
                cmd.o                           \
                reset.o                         \
                fw_common.o                     \
                fw_reg.o                        \
                fw_cmd.o                        \
                icm.o                           \
                ioctl.o                         \
                ioctl_cmd_ifc.o                 \
                ioctl_common.o                  \
                ioctl_db.o                      \
                ioctl_dpt.o                     \
                ioctl_host_ifc.o                \
                ioctl_misc.o                    \
                ioctl_pci.o                     \
                ioctl_reg.o                     \
                ioctl_sgmii.o                   \
                mmap.o                          \
                sx_dpt.o                        \
                sx_proc.o                       \
                sx_clock.o                      \
                sx_clock_spc1.o                 \
                sx_clock_spc2_3.o               \
                ptp_common.o                    \
                ptp_spc1.o                      \
                ptp_spc2_3.o                    \
                sx_dbg_dump_proc.o              \
                auto_registers/sx_proc_auto.o   \
                auto_registers/ioctl_reg_auto.o \
                auto_registers/reg.o            \
                auto_registers/fw_reg_auto.o    \
                sgmii.o                         \
                sgmii_cr_space.o                \
                sgmii_dev_db.o                  \
                sgmii_emad.o                    \
                sgmii_mad.o                     \
                sgmii_transaction.o             \
                sgmii_transport.o               \
                map.o                           \
                sx_af_counters.o                \
                sx_af_dbg_info.o                \
                bulk_cntr_event.o               \
                bulk_cntr_db.o                  \
                ber_monitor.o                   \
                trace_func.o                    \
                drop_monitor.o                  \
                cr_dump.o                       \
                sysfs_asic.o                    \
                sx_module_sysfs_eeprom.o        \
                synce.o                         \
                sx_module_sysfs_s3ip.o

