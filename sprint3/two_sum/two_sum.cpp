#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <unordered_map>
#include <vector>

#include <fmt/ranges.h>

namespace doctest
{
template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T>& in) { return fmt::format("{}", in).c_str(); }
};
} // namespace doctest

std::vector<int> two_sum(std::vector<int>& nums, int target)
{
  std::unordered_map<int,int> numsIndexes{};
  for(size_t curr{0}; curr < nums.size(); ++curr)
  {
    if(int complement = target - nums[curr]; numsIndexes.find(complement) != numsIndexes.end()){
      return {numsIndexes[complement], curr};
    }
    numsIndexes[nums[curr]] = curr;
  }

  return {0,0};
}

TEST_CASE("Example 1")
{
  std::vector<int> in{2,7,11,15};
  REQUIRE(two_sum(in, 9) == std::vector<int>{0,1});
}

TEST_CASE("Example 2")
{
  std::vector<int> in{3,2,4};
  REQUIRE(two_sum(in, 6) == std::vector<int>{1,2});
}
