#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/ranges.h>

#include <functional>
#include <numeric>
#include <ranges>

namespace doctest
{
template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T>& in) { return fmt::format("{}", in).c_str(); }
};
} // namespace doctest

template <typename Range, typename Cmp = std::ranges::less>
void insertion_sort(Range& rg, Cmp cmp = {})
{
    auto begin{std::begin(rg)};
    auto end{std::end(rg)};

    for (auto cur{std::next(begin)}; cur < end; ++cur)
    {
        auto tmp = *cur;
        auto l{std::prev(cur)};
        while (l >= begin && cmp(tmp, *l))
        {
            *std::next(l) = *l;
            --l;
        }
        *std::next(l) = tmp;
    }
}

int max_of_3(std::vector<int>& nums)
{
    insertion_sort(nums);

    auto max_positive_v = nums | std::views::reverse | std::views::take(3) | std::views::common;
    auto max_positive = std::accumulate(std::next(std::begin(max_positive_v)), std::end(max_positive_v),
                                        *max_positive_v.begin(), std::multiplies<>{});

    auto max_negative_v = nums | std::views::take(2) | std::views::common;
    auto max_negative = std::accumulate(std::next(std::begin(max_negative_v)), std::end(max_negative_v),
                                        *max_negative_v.begin(), std::multiplies<>{});
    if (nums.size() >= 3)
        max_negative *= nums.back();

    return std::max(max_negative, max_positive);
}

TEST_CASE("Sorting")
{
    auto in = std::vector<int>{1, 2, 3};
    insertion_sort(in, std::greater<>{});
    CHECK(in == std::vector<int>{3, 2, 1});
}

TEST_CASE("Example 1")
{
    auto in = std::vector<int>{1, 2, 3};
    CHECK(max_of_3(in) == 6);
}

TEST_CASE("Example 2")
{
    auto in = std::vector<int>{1, 2, 3, 4};
    CHECK(max_of_3(in) == 24);
}

TEST_CASE("TC1")
{
    auto in = std::vector<int>{-100, -2, -3, 1};
    CHECK(max_of_3(in) == 300);
}

TEST_CASE("TC2")
{
    auto in = std::vector<int>{-1, -2, 1, 2, 3};
    CHECK(max_of_3(in) == 6);
}
