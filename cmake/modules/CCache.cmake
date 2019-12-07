cmake_minimum_required(VERSION 3.6)

find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
    # Support Unix Makefiles and Ninja
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")

    message(STATUS "CCache activated")
else()
    message(STATUS "CCache is not active")
endif()
