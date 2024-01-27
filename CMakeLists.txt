cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME algo-ds-warmup)

project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(cmake)

add_executable(max_area_of_island sprint1/max_area_of_island/max_area_of_island.cpp)
target_link_libraries(max_area_of_island PRIVATE fmt::fmt doctest::doctest)
