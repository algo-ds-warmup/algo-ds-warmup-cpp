#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <unordered_set>

bool contains_duplicate(std::vector<int>& nums)
{
    std::unordered_set<int> cache;
    for (const auto& el : nums)
    {
        if (auto [_, inserted] = cache.insert(el); !inserted)
        {
            return true;
        }
    }
    return false;
}

TEST_CASE("Example 1")
{
    auto in = std::vector<int>{1, 2, 3, 1};
    REQUIRE(contains_duplicate(in));
}

TEST_CASE("Example 2")
{
    auto in = std::vector<int>{1,1,1,3,3,4,3,2,4,2};
    REQUIRE(contains_duplicate(in));
}
