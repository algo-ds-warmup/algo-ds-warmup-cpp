cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME algo-ds-warmup)

project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(cmake)

#sprint1
add_executable(binary_search sprint1/binary_search/binary_search.cpp)
add_executable(koko sprint1/koko-eating-bananas/koko-eating-bananas.cpp)
add_executable(find-minimum-in-rotated-sorted-array sprint1/find-minimum-in-rotated-sorted-array/find-minimum-in-rotated-sorted-array.cpp)

#sprint2
add_executable(sorting_bm sorting_bm.cpp)
add_executable(trim_mean sprint2/trim_mean/trim_mean.cpp)
add_executable(dominant_index sprint2/dominant_index/dominant_index.cpp)
add_executable(third_max sprint2/third_max/third_max.cpp)
add_executable(relative_ranks sprint2/relative_ranks/relative_ranks.cpp)



target_link_libraries(binary_search PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(koko PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(find-minimum-in-rotated-sorted-array PRIVATE fmt::fmt doctest::doctest)

target_link_libraries(sorting_bm PRIVATE fmt::fmt benchmark::benchmark)
target_link_libraries(trim_mean PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(dominant_index PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(third_max PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(relative_ranks PRIVATE fmt::fmt doctest::doctest)


