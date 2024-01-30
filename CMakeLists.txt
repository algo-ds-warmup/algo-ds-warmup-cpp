cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME algo-ds-warmup)

project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(cmake)

add_executable(binary_search sprint1/binary_search/binary_search.cpp)

target_link_libraries(binary_search PRIVATE fmt::fmt doctest::doctest)
