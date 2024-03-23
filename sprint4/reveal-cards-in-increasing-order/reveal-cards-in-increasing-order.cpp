#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "fmt/core.h"
#include "fmt/ranges.h"
#include <deque>

namespace doctest
{
template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T>& in) { return fmt::format("{}", in).c_str(); }
};
} // namespace doctest

std::vector<int> deckRevealedIncreasing(std::vector<int>& deck)
{
    std::ranges::sort(deck);
    if (deck.size() <= 2)
        return deck;

    std::deque<int> res;
    auto rIt = deck.rbegin();
    res.push_front(*rIt);

    rIt++;
    res.push_front(*rIt);

    while (++rIt != deck.rend())
    {
        res.push_front(res.back());
        res.pop_back();
        res.push_front(*rIt);
    }

    return {res.begin(), res.end()};
}

TEST_CASE("Example 3")
{
    auto in = std::vector<int>{17, 13, 11, 2, 3, 5, 7};
    REQUIRE((deckRevealedIncreasing(in)) == std::vector<int>{2, 13, 3, 11, 5, 17, 7});
}
