cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME algo-ds-warmup)

project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(cmake)

add_executable(binary_sort sprint1/binary_sort/binary_sort.cpp)

target_link_libraries(binary_sort PRIVATE fmt::fmt doctest::doctest)
