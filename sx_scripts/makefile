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
## $Id: Makefile 9120 2006-08-28 13:01:07Z vlad $

all:
.PHONY: all kernel install_kernel install clean clean_kernel
.PHONY: install_kernel_mlx_sx
	
.DELETE_ON_ERROR:
.NOTPARALLEL:

include ./configure.mk.kernel

DEPMOD  = /sbin/depmod
	
ifeq ($(CONFIG_MEMTRACK),m)
        export KERNEL_MEMTRACK_CFLAGS = -include $(CWD)/drivers/net/mlx_sx/debug/memtrack/mtrack.h
else
        export KERNEL_MEMTRACK_CFLAGS =
endif

export OPEN_ISCSI_MODULES = iscsi_tcp.ko libiscsi.ko scsi_transport_iscsi.ko

configure.mk.kernel:
	@echo Please run ./configure
	@exit 1

# Option -Wno-date-time is needed only for GCC 4.9 or higher
# Currently only native compiler is checked
c1 = $(shell cat /proc/version |sed 's/^.*gcc version //'|cut -d' ' -f1|cut -d'.' -f1)
c2 = $(shell cat /proc/version |sed 's/^.*gcc version //'|cut -d' ' -f1|cut -d'.' -f2)
gcc_4_9 =  $(shell [ $(c1) -gt 4 -o \( $(c1) -eq 4 -a $(c2) -ge 9 \) ] && echo 1)
ifeq ($(gcc_4_9),1)
	export GCC_NO_DATE_TIME = -Wno-date-time
else        
	export GCC_NO_DATE_TIME = 
endif

all: kernel

install: install_kernel
install_kernel: install_modules

autoconf_h=$(shell /bin/ls -1 $(KBLD)/include/*/autoconf.h 2> /dev/null | head -1)
kconfig_h=$(shell /bin/ls -1 $(KBLD)/include/*/kconfig.h 2> /dev/null | head -1)

ifeq ($(kconfig_h),)
kconfig_h=$(shell /bin/ls -1 $(KSRC)/include/*/kconfig.h 2> /dev/null | head -1)
endif

ifneq ($(kconfig_h),)
KCONFIG_H = -include $(kconfig_h)
else
KCONFIG_H = -include include/linux/kconfig.h
endif

# Enforcing order for make -j support

ifeq ($(CONFIG_SX_CORE),m)
install_kernel:   install_kernel_mlx_sx
install_scripts_during_make: install_kernel_mlx_sx
endif

ifeq ($(CONFIG_SX_NETDEV),m)
install_kernel:   install_kernel_sx_netdev
install_scripts_during_make: install_kernel_sx_netdev
install_kernel_sx_netdev: install_kernel_mlx_sx
install_kernel_memtrack: install_kernel_sx_netdev
endif

ifeq ($(CONFIG_SX_EMAD_DUMP),m)
install_kernel:   install_kernel_sx_emad_dump
install_scripts_during_make: install_kernel_sx_emad_dump
install_kernel_sx_emad_dump: install_kernel_mlx_sx
install_kernel_memtrack: install_kernel_sx_emad_dump
endif

ifeq ($(CONFIG_SX_BFD),m)
install_kernel:   install_kernel_sx_bfd
install_scripts_during_make: install_kernel_sx_bfd
install_kernel_sx_bfd: install_kernel_mlx_sx
install_kernel_memtrack: install_kernel_sx_bfd
endif

ifeq ($(CONFIG_MLXFW),m)
install_kernel:   install_kernel_mlxfw
install_scripts_during_make: install_kernel_mlxfw
install_kernel_mlxfw: install_kernel_mlx_sx
install_kernel_memtrack: install_kernel_mlxfw
endif

ifeq ($(CONFIG_MEMTRACK),m)
install_kernel:   install_kernel_memtrack
install_scripts_during_make: install_kernel_memtrack
endif

ifneq ($(CONFIG_SEPERATED_SCRIPTS_INSTALL),y)
install_kernel:   install_scripts
install_scripts:  install_scripts_during_make
endif

V ?= 1

ifneq ($(findstring 3.10,$(KVERSION))$(findstring 3.13,$(KVERSION))$(findstring 3.14,$(KVERSION))$(findstring 3.16,$(KVERSION))$(findstring 4.9,$(KVERSION))$(findstring 4.15,$(KVERSION))$(findstring 4.19,$(KVERSION)),)
MLNX_LINUX_AUTOCONF_FILE = include/generated/autoconf.h
MLNX_LINUX_KCONFIG_FILE =  $(KCONFIG_H)
ifeq (exists, $(shell [ -d "/lib/modules/${KVERSION}/source" ] && echo exists ))
MLNX_LINUX_EXTRA_INCLUDE_FOLDERS = \
		-I$(KSRC)/arch/$$(SRCARCH)/include/uapi \
		-I$(KSRC)/include/uapi \
		-I$(KBLD)/arch/$$(SRCARCH)/include/generated/uapi \
		-I$(KBLD)/arch/$$(SRCARCH)/include/generated \
		-I$(KBLD)/include/generated/uapi
else 
MLNX_LINUX_EXTRA_INCLUDE_FOLDERS = \
		-Iarch/$$(SRCARCH)/include/uapi \
		-Iinclude/uapi \
		-Iarch/$$(SRCARCH)/include/generated/uapi \
		-Iarch/$$(SRCARCH)/include/generated \
		-Iinclude/generated/uapi
endif
else
MLNX_LINUX_AUTOCONF_FILE = include/linux/autoconf.h
endif

ifneq ($(MLNX_EXTERNAL_OFED),)
MLNX_EXTERNAL_OFED_INCLUDE=-I$(MLNX_EXTERNAL_OFED)
endif

#########################
#	make kernel	#
#########################
#NB: The LINUXINCLUDE value comes from main kernel Makefile
#    with local directories prepended. This eventually affects
#    CPPFLAGS in the kernel Makefile
kernel:
	@echo "Building kernel modules"
	@echo "Kernel version: $(KVERSION)"
	@echo "Modules directory: $(DESTDIR)$(MODULES_DIR)"
	@echo "Kernel sources: $(KBLD)"
	if [ "x" != "x$(EXTRA_SWITCHX_SDK_KERNEL_SYMVERS)" ] ; then \cp -fv $(EXTRA_SWITCHX_SDK_KERNEL_SYMVERS) . || exit 1 ; fi
	@echo "Using GCC_NO_DATE_TIME=$(GCC_NO_DATE_TIME)"		
	env CWD=$(CWD) BACKPORT_INCLUDES=$(BACKPORT_INCLUDES) \
		$(MAKE) -C $(KBLD) SUBDIRS="$(CWD)" \
		V=$(V) $(WITH_MAKE_PARAMS) \
		CONFIG_SX_CORE_DEBUG=$(CONFIG_SX_CORE_DEBUG) \
		CONFIG_SX_CORE=$(CONFIG_SX_CORE) \
        CONFIG_SX_NETDEV=$(CONFIG_SX_NETDEV) \
        CONFIG_SX_EMAD_DUMP=$(CONFIG_SX_EMAD_DUMP) \
        CONFIG_SX_BFD=$(CONFIG_SX_BFD) \
        CONFIG_MLXFW=$(CONFIG_MLXFW) \
		CONFIG_MEMTRACK=$(CONFIG_MEMTRACK) \
		CONFIG_DEBUG_INFO=$(CONFIG_DEBUG_INFO) \
		LINUXINCLUDE=' \
		$(MLNX_EXTERNAL_OFED_INCLUDE) \
		-include $(MLNX_LINUX_AUTOCONF_FILE) \
		-include $(CWD)/include/linux/autoconf.h \
		$(MLNX_LINUX_KCONFIG_FILE) \
		$(BACKPORT_INCLUDES) \
		-I$(CWD)/include \
		-I$(CWD)/drivers/net/mlx_sx/debug/memtrack \
		-Iinclude \
		-Iarch/$$(SRCARCH)/include \
		$$(if $$(KBUILD_SRC),-Iinclude2 -I$$(srctree)/include) \
		-I$$(srctree)/arch/$$(SRCARCH)/include \
		$(MLNX_LINUX_EXTRA_INCLUDE_FOLDERS) \
		$(KERNEL_MEMTRACK_CFLAGS) \
		' \
		KCFLAGS="-DSYSTEM_PCI $(KCFLAGS) -Werror -Wall -Wswitch -Wunused -Wno-format-truncation -Wno-stringop-truncation -Wframe-larger-than=4096 $(GCC_NO_DATE_TIME)" \
		modules


KERNEL_MODS_STAGING_FOLDER ?= $(CWD)/../kernel_modules_staging_folder
#########################
#	Install kernel	#
#########################
install_modules: kernel
	@echo "Installing kernel modules"
	rm -rfv $(KERNEL_MODS_STAGING_FOLDER)
	mkdir -p $(KERNEL_MODS_STAGING_FOLDER)
	$(MAKE) -C $(KBLD) SUBDIRS="$(CWD)" \
		INSTALL_MOD_PATH=$(KERNEL_MODS_STAGING_FOLDER) \
		$(WITH_MAKE_PARAMS) modules_install;


install_kernel_memtrack: install_modules
	# Copy new memtrack kernel modules to $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug/memtrack
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/net/mlx_sx/debug/memtrack ]; then \
		/bin/rm -rfv $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug/memtrack; \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug; \
		\cp -Rv $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/net/mlx_sx/debug/memtrack $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug; \
	fi;
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/mlx_sx/debug/memtrack ]; then \
		/bin/rm -rfv $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug/memtrack; \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug; \
		\cp -Rv $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/mlx_sx/debug/memtrack $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug/; \
	elif [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra ]; then \
		/bin/rm -rfv $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug/memtrack; \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug; \
		\cp -Rv $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/debug/memtrack; \
	fi;

	if [ ! -n "$(DESTDIR)" ]; then $(DEPMOD) -r -ae $(KVERSION);fi;


install_kernel_mlx_sx: install_modules
	# Copy new mlx_sx kernel module to $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/drivers/net/mlx_sx ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/drivers/net/mlx_sx/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx; \
	fi; \
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/mlx_sx ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/mlx_sx/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/ ; \
	elif [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlx_sx/ ; \
	fi;
	if [ ! -n "$(DESTDIR)" ]; then $(DEPMOD) -r -ae $(KVERSION);fi;

install_scripts:
	mkdir -p $(DESTDIR)/etc/udev/rules.d
	cp $(CWD)/sx_scripts/91-sx.rules $(DESTDIR)/etc/udev/rules.d
	mkdir -p $(DESTDIR)/etc/modprobe.d
	cp $(CWD)/sx_scripts/sx.modprobe.conf $(DESTDIR)/etc/modprobe.d
	cp $(CWD)/sx_scripts/blacklist-sx.conf $(DESTDIR)/etc/modprobe.d
	mkdir -p $(DESTDIR)/etc/init.d
	cp $(CWD)/sx_scripts/sxdkernel $(DESTDIR)/etc/init.d


install_kernel_sx_netdev: install_modules
        # Copy new sx_netdev kernel module to $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_netdev
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/drivers/net/sx_netdev ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_netdev; \
	fi; \
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/sx_netdev ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_netdev; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/sx_netdev/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_netdev/ ; \
	elif [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_netdev; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_netdev/ ; \
	fi;

	if [ ! -n "$(DESTDIR)" ]; then $(DEPMOD) -r -ae $(KVERSION);fi;

install_kernel_sx_emad_dump: install_modules
        # Copy new sx_emad_dump kernel module to $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_emad_dump
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/drivers/net/sx_emad_dump ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_emad_dump; \
	fi; \
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/sx_emad_dump ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_emad_dump; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/sx_emad_dump/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_emad_dump/ ; \
	elif [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_emad_dump; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_emad_dump/ ; \
	fi;

	if [ ! -n "$(DESTDIR)" ]; then $(DEPMOD) -r -ae $(KVERSION);fi;

install_kernel_sx_bfd: install_modules
        # Copy new sx_bfd kernel module to $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_bfd
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/drivers/net/sx_bfd ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_bfd; \
	fi; \
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/sx_bfd ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_bfd; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/sx_bfd/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_bfd/ ; \
	elif [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_bfd; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/sx_bfd/ ; \
	fi;

	if [ ! -n "$(DESTDIR)" ]; then $(DEPMOD) -r -ae $(KVERSION);fi;

install_kernel_mlxfw: install_modules
        # Copy new mlxfw kernel module to $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlxfw
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/drivers/net/mlxfw ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlxfw; \
	fi; \
	if [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/mlxfw ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlxfw; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/drivers/net/mlxfw/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlxfw/ ; \
	elif [ -d $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra ]; then \
		mkdir -p $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlxfw; \
		\cp -v $(KERNEL_MODS_STAGING_FOLDER)/lib/modules/$(KVERSION)/extra/*.ko $(DESTDIR)$(MODULES_DIR)/kernel/drivers/net/mlxfw/ ; \
	fi;
	mkdir -p $(DESTDIR)/usr/bin/
	\cp -v $(CWD)/sx_scripts/sxdfwburn.sh $(DESTDIR)/usr/bin/

	if [ ! -n "$(DESTDIR)" ]; then $(DEPMOD) -r -ae $(KVERSION);fi;

clean: clean_kernel

clean_kernel:
	$(MAKE) -C $(KBLD) SUBDIRS="$(CWD)" $(WITH_MAKE_PARAMS) clean

help:
	@echo
	@echo kernel: 		        build kernel modules
	@echo all: 		        build kernel modules
	@echo
	@echo install_kernel:	        install kernel modules under $(DESTDIR)$(MODULES_DIR)
	@echo install:	        	run install_kernel
	@echo
	@echo clean:	        	delete kernel modules binaries
	@echo clean_kernel:	        delete kernel modules binaries
	@echo
