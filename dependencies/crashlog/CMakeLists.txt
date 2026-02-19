message(STATUS "Fetching crashlog...")

FetchContent_Declare(
  crashlog
  GIT_REPOSITORY https://github.com/0liteyear/crashlog.git
  GIT_TAG        ddc7ea9
)

FetchContent_MakeAvailable(crashlog)