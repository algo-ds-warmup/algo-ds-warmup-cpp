#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <numeric>

inline int min_eating_spead(std::ranges::random_access_range auto &piles,
                            int hours) {
  long long left{1};
  long long right{*std::ranges::max_element(piles)};
  long long speed{right};

  while (left <= right) {
    long long mid = std::midpoint(left, right);

    long long int h = std::accumulate(std::ranges::begin(piles), std::ranges::end(piles),
                            0LL, [mid](long long ret, long long bananas) {
                              return ret + (bananas + mid - 1) / mid;
                            });

    if (h <= hours) {
      speed = std::min(mid, speed);
      right = mid - 1;
    } else
      left = mid + 1;

  }

  return speed;
}

TEST_CASE("Example 1") {
  auto piles = std::vector{3, 6, 7, 11};
  CHECK(min_eating_spead(piles, 8) == 4);
}

TEST_CASE("Example 2") {
  auto piles = std::vector{30, 11, 23, 4, 20};
  CHECK(min_eating_spead(piles, 5) == 30);
}

TEST_CASE("TC 1")
{ 
  auto piles = std::vector{805306368,805306368,805306368};
  CHECK(min_eating_spead(piles, 1000000000) == 3);
}
