
install(
    PROGRAMS sx.modprobe.conf blacklist-sx.conf
    DESTINATION etc/modprobe.d/
)

install(
    PROGRAMS sxdkernel
    DESTINATION etc/init.d/
)

if (NOT SKIP_DEPMOD_IN_INSTALL_PHASE)
    install(CODE "set(POSTINST_SCRIPT_PATH \"${CMAKE_SOURCE_DIR}/cmake/postinst\")")
    install(SCRIPT ${CMAKE_SOURCE_DIR}/cmake/depmod.cmake)
endif()
