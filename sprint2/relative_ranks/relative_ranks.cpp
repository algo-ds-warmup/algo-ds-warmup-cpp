#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/ranges.h>
#include <limits>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

static constexpr std::string_view FIRST_PLACE{"Gold Medal"};
static constexpr std::string_view SECOND_PLACE{"Silver Medal"};
static constexpr std::string_view THIRD_PLACE{"Bronze Medal"};

namespace doctest
{
template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T>& in) { return fmt::format("{}", in).c_str(); }
};
} // namespace doctest

constexpr inline std::string place_to_string(int place)
{
    using namespace std::string_literals;
    switch (place)
    {
        case 0:
            return "Gold Medal"s;
        case 1:
            return "Silver Medal"s;
        case 2:
            return "Bronze Medal"s;
        default:
            return std::to_string(place + 1);
    }
}

std::vector<std::string> find_relative_ranks_v2(std::vector<int>& score)
{
    auto in = std::vector<std::pair<int, size_t>>{};
    in.reserve(score.size());
    std::ranges::move(score | std::views::transform([k = 0](int i) mutable { return std::make_pair(i, k++); }),
                      std::back_inserter(in));
    std::ranges::sort(in, std::ranges::greater(), &std::pair<int, size_t>::first);
    fmt::print("{}\n", in);

    auto result = std::vector<std::string>(in.size());
    std::ranges::for_each(
        in, [&result, i = 0](auto pos) mutable { result[pos] = std::move(place_to_string(i++)); },
        &std::pair<int, size_t>::second);

    return result;
}

std::vector<std::string> find_relative_ranks(std::vector<int>& score)
{
    using namespace std::string_literals;
    std::vector<std::string> result(score.size());
    static constinit auto place_ranks = std::views::iota(0, std::numeric_limits<int>::max()) |
                                        std::views::take(1 << 6) |
                                        std::views::transform(
                                            [](int i)
                                            {
                                                switch (i)
                                                {
                                                    case 0:
                                                        return "Gold Medal"s;
                                                    case 1:
                                                        return "Silver Medal"s;
                                                    case 2:
                                                        return "Bronze Medal"s;
                                                    default:
                                                        return std::to_string(i + 1);
                                                }
                                            });

    std::unordered_map<int, size_t> initial_pos;
    for (size_t i{0}; i < score.size(); ++i)
        initial_pos[score[i]] = i;

    // selection search to find max elems
    for (size_t i{0}; i < score.size(); ++i)
    {
        // find max
        auto max{i};
        for (size_t k{i + 1}; k < score.size(); ++k)
        {
            if (score[max] < score[k])
                max = k;
        }

        // place max pos elen on i-place, NOTE: if same nothing will happen
        std::swap(score[i], score[max]);
        /* fmt::print("{} | i: {}, max: {}, init_pos:{}\n",score, i, max,
         * initial_pos[score[i]]); */

        // place on max-place it's rank
        result[initial_pos[score[i]]] = place_ranks[i];
    }
    return result;
}

/* TEST_CASE("Example 1") */
/* { */
/*     auto in = std::vector{5, 4, 3, 2, 1}; */
/**/
/*     CHECK(find_relative_ranks(in) == std::vector<std::string>{"Gold Medal", "Silver Medal", "Bronze Medal", "4",
 * "5"}); */
/* } */
/**/
/* TEST_CASE("Example 2") */
/* { */
/*     auto in = std::vector{10, 3, 8, 9, 4}; */
/**/
/*     CHECK(find_relative_ranks(in) == std::vector<std::string>{"Gold Medal", "5", "Bronze Medal", "Silver Medal",
 * "4"}); */
/* } */
/**/
/* TEST_CASE("Example 3") */
/* { */
/*     auto in = std::vector{5, 4, 3, 2, 1}; */
/**/
/*     CHECK(find_relative_ranks_v2(in) == */
/*           std::vector<std::string>{"Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"}); */
/* } */

TEST_CASE("Example 4")
{
    auto in = std::vector{10, 3, 8, 9, 4};

    CHECK(find_relative_ranks_v2(in) ==
          std::vector<std::string>{"Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"});
}
