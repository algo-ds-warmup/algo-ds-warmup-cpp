include(fmt/fmt.cmake)
target_compile_options(fmt INTERFACE -Wno-everything )
set_target_properties(fmt PROPERTIES CXX_CLANG_TIDY "")
message(STATUS "fmt included")

include(doctest/doctest.cmake)
target_compile_options(doctest INTERFACE -Wno-everything )
set_target_properties(doctest PROPERTIES CXX_CLANG_TIDY "")
message(STATUS "doctest included")

include(benchmark/google_benchmark.cmake)
target_compile_options(benchmark INTERFACE -Wno-everything )
set_target_properties(benchmark PROPERTIES CXX_CLANG_TIDY "")
message(STATUS "benchmark included")
