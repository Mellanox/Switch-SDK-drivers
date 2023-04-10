
# Global path location
set (SXD_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Extra CFLAGS for kernel modules
if (MEMTRACK)
    set (MEMTRACK_EXTRA_CFLAGS_VAR "-include ${CMAKE_CURRENT_BINARY_DIR}/drivers/net/mlx_sx/debug/memtrack/mtrack.h")
    set (MEMTRACK_EXTRA_SYMVERS_VAR "${CMAKE_CURRENT_BINARY_DIR}/drivers/net/mlx_sx/debug/memtrack/Module.symvers")
endif()
set (SXD_KERNEL_EXTRA_CFLAGS_VAR
    "${MEMTRACK_EXTRA_CFLAGS_VAR} -I${CMAKE_CURRENT_BINARY_DIR}/include -I${CMAKE_CURRENT_BINARY_DIR}/include/stub"
)
set (EXTRA_SYMVERS_VAR
    "${MEMTRACK_EXTRA_SYMVERS_VAR} ${CMAKE_CURRENT_BINARY_DIR}/drivers/net/mlx_sx/Module.symvers"
)

# Compilation flags and defenitions for kernel modules
set (KCFLAGS "-D__KERNEL__ $ENV{KCFLAGS} -Wno-stringop-truncation -Wframe-larger-than=4096 -Wno-date-time")

if (OS_RELEASE MATCHES "3.10.0-693.*")
    string(APPEND KCFLAGS " -DCONFIG_SX_RHEL_7_4")
elseif (OS_RELEASE MATCHES "3.10.0-957.*")
    string(APPEND KCFLAGS " -DCONFIG_SX_RHEL_7_6")
elseif (OS_RELEASE MATCHES "4.18.0-372.*")
    string(APPEND KCFLAGS " -DCONFIG_SX_RHEL_8_6")
elseif (OS_RELEASE MATCHES "4.18.0-408.*")
    string(APPEND KCFLAGS " -DCONFIG_SX_CENTOS_8_4")
endif()

# Common module compilation command
set (MODULE_CMD_COMMON ${CMAKE_MAKE_PROGRAM} -C ${SX_KERNEL_MODULE_BUILD_PATH} SXD_KERNEL_EXTRA_CFLAGS=${SXD_KERNEL_EXTRA_CFLAGS_VAR} KCFLAGS=${KCFLAGS})

# Copy kernel code to out-of-tree
set (COPY_SXD_KERNEL_TARGET copy_sxd_kernel_src)
add_custom_target(${COPY_SXD_KERNEL_TARGET} ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB_RECURSE INCLUDE_HEADERS_ALL CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_subdirectory(drivers/net)
# Runs "/sbin/depmod -a" on install stage, post kernel module install in dirvers subdirectory.
# This subdirectory should be last.
add_subdirectory(sx_scripts)
