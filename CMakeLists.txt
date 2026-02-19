cmake_minimum_required(VERSION 3.29)
project(EOSEmulator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(dependencies)
include_directories(${plog_SOURCE_DIR}/include)

file(GLOB_RECURSE includes_deps
        "includes/*.hpp"
        "includes/*.h"

        "src/common/*.cpp"
        "src/common/*.hpp"
        "src/common/*.h"
)
include_directories(includes)
include_directories(src)

# Build platform-specific components based on the target platform
# Note: Both src/win and src/linux build Windows DLLs that require WIN32 APIs.
# src/linux builds version.dll for use with Wine on Linux.
# src/win builds EOSSDK-Win64-Shipping.dll for native Windows.
if(WIN32)
    link_libraries(minhook)
    # Build both components on Windows
    add_subdirectory(src/win)
    add_subdirectory(src/linux)
endif()
