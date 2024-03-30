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

#sprint3
add_executable(two_sum sprint3/two_sum/two_sum.cpp)
add_executable(contains_duplicate sprint3/contains_duplicate/contains_duplicate.cpp)
add_executable(product_of_array_except_self sprint3/product_of_array_except_self/product_of_array_except_self.cpp)
add_executable(longest_consecutive sprint3/longest_consecutive/longest_consecutive.cpp)

#sprint4
add_executable(valid_parentheses sprint4/valid_parentheses/valid_parentheses.cpp)
add_executable(min-stack sprint4/min-stack/min-stack.cpp)
add_executable(implement-stack-using-queues ./sprint4/implement-stack-using-queues/implement-stack-using-queues.cpp)
add_executable(reveal-cards-in-increasing-order ./sprint4/reveal-cards-in-increasing-order/reveal-cards-in-increasing-order.cpp)
add_executable(merge-two-sorted-lists ./sprint4/merge-two-sorted-lists/merge-two-sorted-lists.cpp)
add_executable(add-two-numbers sprint4/add-two-numbers/add-two-numbers.cpp)
add_executable(reverse-linked-list ./sprint4/reverse-linked-list/reverse-linked-list.cpp)


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
target_link_libraries(product_of_array_except_self PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(longest_consecutive PRIVATE fmt::fmt doctest::doctest)

target_link_libraries(valid_parentheses PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(min-stack PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(implement-stack-using-queues PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(reveal-cards-in-increasing-order PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(merge-two-sorted-lists PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(add-two-numbers PRIVATE fmt::fmt doctest::doctest)
target_link_libraries(reverse-linked-list PRIVATE fmt::fmt doctest::doctest)
