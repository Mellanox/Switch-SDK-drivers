EXTRA_CFLAGS += $(KERNEL_MEMTRACK_CFLAGS) \
		-I$(CWD)/include \
		-I$(CWD)/drivers/net/mlx_sx/debug/memtrack \

obj-$(CONFIG_SX_CORE)           += drivers/net/mlx_sx/
obj-$(CONFIG_MEMTRACK)          += drivers/net/mlx_sx/debug/memtrack/
obj-$(CONFIG_SX_NETDEV)           += drivers/net/sx_netdev/
obj-$(CONFIG_SX_EMAD_DUMP)        += drivers/net/sx_emad_dump/
obj-$(CONFIG_SX_SPICE_DUMP)        += drivers/net/sx_spice_dump/
obj-$(CONFIG_SX_BFD)              += drivers/net/sx_bfd/
