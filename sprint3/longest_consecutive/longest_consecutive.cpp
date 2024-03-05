#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/ranges.h>
#include <ranges>
#include <unordered_map>

int longest_consecutive(std::vector<int>& nums)
{
    if (nums.empty())
        return 0;

    std::unordered_set<int> nums_set(nums.begin(), nums.end());
    int longest_cons = 1;
    std::ranges::for_each(nums_set | std::views::filter([&](int num) { return !nums_set.contains(num - 1); }),
                          [&](int num) mutable
                          {
                              auto cons_view = std::views::iota(num + 1) |
                                               std::views::take_while([&](int n) { return nums_set.contains(n); });
                              int streak = 1 + std::ranges::distance(cons_view);
                              longest_cons = std::max(longest_cons, streak);
                          });
    return longest_cons;
}

TEST_CASE("Example 1")
{
    auto in = std::vector<int>{100, 4, 200, 1, 3, 2};
    REQUIRE(longest_consecutive(in) == 4);
}

TEST_CASE("Example 2")
{
    auto in = std::vector<int>{0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    REQUIRE(longest_consecutive(in) == 9);
}

TEST_CASE("TC 1")
{
    auto in = std::vector<int>{0};
    REQUIRE(longest_consecutive(in) == 1);
}

TEST_CASE("TC 2")
{
    auto in = std::vector<int>{0, -1};
    REQUIRE(longest_consecutive(in) == 2);
}
