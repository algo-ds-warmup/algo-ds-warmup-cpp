#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/ranges.h>
#include <ranges>
#include <unordered_map>

int longest_consecutive(std::vector<int>& nums)
{
    if (nums.empty())
        return 0;
    auto v = std::views::all(nums) | std::views::transform([](int el) { return std::pair<int, int>{el, 1}; });
    std::unordered_map<int, int> value_cons{v.begin(), v.end()};
    int longest_cons{1};
    for (auto i{0}; i < nums.size(); ++i)
    {
        auto curr = std::next(nums.begin(), i);
        int cons{0};
        for (auto v = *curr; value_cons.contains(v) && value_cons[v]; --v)
        {
          value_cons[v] = 0;
          cons += 1;
        }
        for (auto v = *curr + 1; value_cons.contains(v) && value_cons[v]; ++v)
        {
          value_cons[v] = 0;
          cons += 1;
        }

        longest_cons = std::max(longest_cons, cons);
    }
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
