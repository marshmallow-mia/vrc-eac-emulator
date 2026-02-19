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
if(WIN32)
    link_libraries(minhook)
    # Build both components on Windows
    add_subdirectory(src/win)
    add_subdirectory(src/linux)
endif()
