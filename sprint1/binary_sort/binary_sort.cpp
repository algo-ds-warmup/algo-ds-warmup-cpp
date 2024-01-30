#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <ranges>

// required return type -> int 
inline int binary_search(const std::ranges::random_access_range auto &rg, auto target)
  requires std::is_same_v<decltype(target), std::ranges::range_value_t<decltype(rg)>>
{
  using namespace std::ranges;

  auto left{begin(rg)};
  auto right{prev(end(rg))};

  while(distance(left, right) >= 0)
  {
    auto mid = next(left, (distance(left, right) / 2));
    [[unlikely]]
    if(*mid == target)
      return std::distance(begin(rg), mid);

    if(*mid > target)
      right = prev(mid);
    
    if(*mid < target)
      left = next(mid);
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
