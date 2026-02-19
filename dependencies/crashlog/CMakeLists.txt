message(STATUS "Fetching crashlog...")

FetchContent_Declare(
  crashlog
  GIT_REPOSITORY https://github.com/0liteyear/crashlog.git
  GIT_TAG        ddc7ea9da992f66a95aa371e184e83826df9eb41
)

FetchContent_MakeAvailable(crashlog)