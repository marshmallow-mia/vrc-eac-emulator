include(FetchContent)

message(STATUS "Installing all required dependencies")

add_subdirectory(plog)
add_subdirectory(libhv)

# Only include Windows-specific dependencies on Windows
if(WIN32)
    add_subdirectory(minhook)
    add_subdirectory(crashlog)
endif()