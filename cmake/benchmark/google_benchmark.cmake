if(TARGET benchmark::benchmark)
  return()
endif()

message(STATUS "Third-party (external): creating target 'benchmark::benchmark'")

include(FetchContent)

set(BENCHMARK_DOWNLOAD_DEPENDENCIES on)
set(BENCHMARK_ENABLE_LTO on)
set(CMAKE_BUILD_TYPE Release)

FetchContent_Declare(
  benchmark 
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
)

FetchContent_MakeAvailable(benchmark)
