
# Global path location
set (SXD_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Extra CFLAGS for kernel modules
if (MEMTRACK)
    set (MEMTRACK_EXTRA_CFLAGS_VAR "-include ${CMAKE_CURRENT_SOURCE_DIR}/drivers/net/mlx_sx/debug/memtrack/mtrack.h")
    set (MEMTRACK_EXTRA_SYMVERS_VAR "${CMAKE_CURRENT_BINARY_DIR}/drivers/net/mlx_sx/debug/memtrack/Module.symvers")
endif()
set (SXD_KERNEL_EXTRA_CFLAGS_VAR
    "${MEMTRACK_EXTRA_CFLAGS_VAR} -I${CMAKE_CURRENT_SOURCE_DIR}/include -I${CMAKE_CURRENT_SOURCE_DIR}/include/stub"
)
set (EXTRA_SYMVERS_VAR
    "${MEMTRACK_EXTRA_SYMVERS_VAR} ${CMAKE_CURRENT_BINARY_DIR}/drivers/net/mlx_sx/Module.symvers"
)

# Compilation flags and defenitions for kernel modules
set (KCFLAGS "-D__KERNEL__ $ENV{KCFLAGS} -Werror -Wall -Wswitch -Wunused -Wno-format-truncation -Wno-stringop-truncation -Wframe-larger-than=4096 -Wno-date-time")

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
set (MODULE_CMD_COMMON $(MAKE) -C ${SX_KERNEL_MODULE_BUILD_PATH} SX_SDK_VERSION=${CMAKE_PROJECT_VERSION} SXD_KERNEL_EXTRA_CFLAGS=${SXD_KERNEL_EXTRA_CFLAGS_VAR} KCFLAGS=${KCFLAGS})

# build the directory tree (without files) before building the modules
execute_process(
    COMMAND bash -c "pushd ${CMAKE_CURRENT_SOURCE_DIR}/drivers; find . -type d -exec mkdir -p '${CMAKE_CURRENT_BINARY_DIR}/drivers/{}' \;; popd"
    OUTPUT_QUIET
)

add_subdirectory(drivers/net)
# Runs "/sbin/depmod -a" on install stage, post kernel module install in dirvers subdirectory.
# This subdirectory should be last.
add_subdirectory(sx_scripts)
