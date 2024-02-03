cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME algo-ds-warmup)

project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(cmake)

add_executable(binary_search sprint1/binary_search/binary_search.cpp)
add_executable(find-minimum-in-rotated-sorted-array sprint1/find-minimum-in-rotated-sorted-array/find-minimum-in-rotated-sorted-array.cpp)

target_link_libraries(binary_search PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(find-minimum-in-rotated-sorted-array PRIVATE fmt::fmt doctest::doctest)
