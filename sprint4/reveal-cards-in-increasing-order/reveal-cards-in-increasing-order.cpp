#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "fmt/ranges.h"

namespace doctest
{
template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T>& in) { return fmt::format("{}", in).c_str(); }
};
} // namespace doctest

std::vector<int> revealAlg(std::vector<int> v)
{
    std::vector<int> res{};
    while (!v.empty())
    {
        auto& card = v.front();
        res.push_back(card);
        v.erase(v.begin());
        if (v.size() > 1)
        {
            v.push_back(v.front());
            v.erase(v.begin());
        }
    }

    return res;
}

std::vector<int> deckRevealedIncreasing(std::vector<int>& deck)
{
    std::ranges::sort(deck);
    return revealAlg(deck);
}

//              [7, 13, 11, 17]
// reveal 7 ->  [11, 17, 13]
// reveal 11 -> [13, 17]
// reveal 13 -> [17]
// reveal 17;

// [7, 11, 13, 17] -> [7, 13, 11, 17]
// [7] -> [13, 17, 11]
// [7, 13] -> [11, 17]
// [7, 13, 11, 17]

TEST_CASE("Example 1")
{
    auto in = std::vector<int>{11, 17, 13};
    REQUIRE(std::ranges::is_sorted(revealAlg(deckRevealedIncreasing(in))));
}

TEST_CASE("Example 2")
{
    auto in = std::vector<int>{1, 1000};
    REQUIRE(std::ranges::is_sorted(revealAlg(deckRevealedIncreasing(in))));
}

TEST_CASE("Example 3")
{
    auto in = std::vector<int>{17, 13, 11, 2, 3, 5, 7};
    //                                                      [2, 3, 5, 7, 11, 13, 17]
    REQUIRE((deckRevealedIncreasing(in)) == std::vector<int>{2, 13, 3, 11, 5, 17, 7});

//     [2, 13, 3, 11, 5, 17, 7]
    // [2] -> [3, 11, 5, 17, 7, 13]
    // [2, 3] ->     [5, 17, 7, 13, 11]
    // [2, 3, 5] ->          7, 13, 11, 17]
    // [2, 3, 5, 7 ] ->             11, 17, 13]
    // [2, 3, 5, 7, 11] ->                  13, 17]
    // [2, 3, 5, 7, 11, 13] ->                  17]
    // [2, 3, 5, 7, 11, 13, 17] ->                ]
}

// [11, 13, 17]
// [11, ]
