
# Compile kernel modules with memtrack (memory debugger)
if (MEMTRACK)
    message (STATUS "Compiles with memtrack")
    add_subdirectory(memtrack)
endif()

