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
add_executable(max_prod_of_3 sprint2/max_prod_of_3/max_prod_of_3.cpp)
add_executable(widest_vertical_area sprint2/widest_vertical_area/widest_vertical_area.cpp)
add_executable(contains_duplicate sprint3/contains_duplicate/contains_duplicate.cpp)

add_executable(two_sum sprint3/two_sum/two_sum.cpp)


target_link_libraries(binary_search PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(koko PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(find-minimum-in-rotated-sorted-array PRIVATE fmt::fmt doctest::doctest)

target_link_libraries(sorting_bm PRIVATE fmt::fmt benchmark::benchmark)
target_link_libraries(trim_mean PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(dominant_index PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(third_max PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(relative_ranks PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(max_prod_of_3 PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(widest_vertical_area PRIVATE fmt::fmt doctest::doctest)


target_link_libraries(contains_duplicate PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(two_sum PRIVATE fmt::fmt doctest::doctest)
