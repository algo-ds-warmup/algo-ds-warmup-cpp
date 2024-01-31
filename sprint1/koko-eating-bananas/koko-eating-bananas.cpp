#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <ranges>

inline int min_eating_spead(std::ranges::random_access_range auto &piles, int hours)
{
  return -1;
}


TEST_CASE("Example 1")
{
  auto piles = std::vector{3,6,7,11};
  CHECK(min_eating_spead(piles, 8) == 4);
}

TEST_CASE("Example 2")
{
  auto piles = std::vector{30,11,23,4,20};
  CHECK(min_eating_spead(piles, 5) == 30);
}
