#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <concepts>
#include <ranges>

auto binary_search(std::ranges::random_access_range auto const &rg,
                   auto target) {
  if (std::ranges::size(rg) == 0) {
    return -1;
  }
  auto left{std::ranges::begin(rg)};
  auto right{std::ranges::end(rg) - 1};

  while (left <= right) {
    auto mid{left + (right - left) / 2};

    if (*mid == target)
      return static_cast<int>(std::distance(std::ranges::begin(rg), mid));

    if (*mid < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

TEST_CASE("Example 1") {
  std::vector<int> input{-1, 0, 3, 5, 9, 12};
  CHECK(binary_search(input, 9) == 4);
  CHECK(binary_search(std::vector<int>{}, 1) == -1);
  CHECK(binary_search(std::vector<int>{1}, 1) == 0);
  CHECK(binary_search(std::vector<int>{1, 2}, 1) == 0);
  CHECK(binary_search(std::vector<int>{1, 2, 3}, 1) == 0);
  CHECK(binary_search(std::vector<int>{1, 2, 3, 4}, 1) == 0);
  CHECK(binary_search(std::vector<int>{1, 2, 3, 4, 5}, 1) == 0);
  CHECK(binary_search(std::vector<int>{1, 2, 3, 4, 5}, 2) == 1);
  CHECK(binary_search(std::vector<int>{1, 2, 3, 4, 5}, 3) == 2);
  CHECK(binary_search(std::vector<int>{1, 2, 3, 4, 5}, 4) == 3);
  CHECK(binary_search(std::vector<int>{1, 2, 3, 4, 5}, 5) == 4);
  CHECK(binary_search(std::vector<int>{1, 2, 3, 4, 5}, -1) == -1);
}

TEST_CASE("Example 2") {
  CHECK(binary_search(std::vector<int>{-1, 0, 3, 5, 9, 12}, 3) == 2);
}

TEST_CASE("Example 3") {
  CHECK(binary_search(
            std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
            12) == 12);
}
