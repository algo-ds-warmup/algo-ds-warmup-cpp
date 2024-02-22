#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/ranges.h>

#include <algorithm>
#include <ranges>
#include <vector>

namespace doctest
{
template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T>& in) { return fmt::format("{}", in).c_str(); }
};
} // namespace doctest

template <typename Cmp = std::ranges::less>
void selection_sort(auto& r, Cmp cmp = {})
{
    for (auto curr = std::begin(r); curr != std::end(r); ++curr)
    {
        auto target = curr;
        for (auto i = std::next(curr); i != std::end(r); ++i)
        {
            if (cmp(*i, *target))
            {
                target = i;
            }
        }
        std::iter_swap(target, curr);
    }
}

int max_width_of_vertical_area(std::vector<std::vector<int>>& points)
{
    selection_sort(points, [](const auto& v_l, const auto& v_r) { return v_l[0] < v_r[0]; });
    auto v = points |
             std::views::transform([](const std::vector<int>& point) { return std::make_pair(point[0], point[1]); }) |
             std::views::keys;
    int widest_area{0};
    int prev = v[0];
    std::ranges::for_each(v,
                          [&widest_area, &prev](int p)
                          {
                              widest_area = std::max(widest_area, p - prev);
                              prev = p;
                          });

    return widest_area;
}

TEST_CASE("Selection sort test")
{
    SUBCASE("sorted")
    {
        auto in = std::vector<int>{1, 2, 3, 4, 5};
        selection_sort(in);
        CHECK_EQ(in, std::vector<int>{1, 2, 3, 4, 5});
    }

    SUBCASE("unsorted 2")
    {
        auto in = std::vector<int>{5, 4, 3, 2, 1};
        selection_sort(in);
        CHECK_EQ(in, std::vector<int>{1, 2, 3, 4, 5});
    }

    SUBCASE("unsorted 3")
    {
        auto in = std::vector<int>{55, 3, 1, 1, 999876789, 987853567};
        selection_sort(in);
        CHECK_EQ(in, std::vector<int>{1, 1, 3, 55, 987853567, 999876789});
    }
    SUBCASE("unsorted 4")
    {
        auto in = std::vector<int>{3, 9, 1, 1, 5, 8};
        selection_sort(in);
        CHECK_EQ(in, std::vector<int>{1,1,3,5,8,9});
    }
}

TEST_CASE("Example 1")
{
    auto in = std::vector<std::vector<int>>{{8, 7}, {9, 9}, {7, 4}, {9, 7}};
    CHECK(max_width_of_vertical_area(in) == 1);
}

TEST_CASE("Example 2")
{
    auto in = std::vector<std::vector<int>>{{3, 1}, {9, 0}, {1, 0}, {1, 4}, {5, 3}, {8, 8}};
    CHECK(max_width_of_vertical_area(in) == 3);
}

TEST_CASE("TC1")
{
    auto in = std::vector<std::vector<int>>{{{1, 5}, {1, 70}, {3, 1000}, {55, 700}, {999876789, 53}, {987853567, 12}}};
    CHECK(max_width_of_vertical_area(in) == 987853512);
}
