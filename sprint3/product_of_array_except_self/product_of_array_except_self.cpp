#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <fmt/ranges.h>

#include <unordered_map>
#include <ranges>
#include <numeric>

namespace doctest
{
template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T>& in) { return fmt::format("{}", in).c_str(); }
};
} // namespace doctest


// in: [1,2,3,4]
//  1           : [1]
//  1,2         : [2]
//  1,2,3       : [6]
//  1,2,3,4     : [24]

std::vector<int> productExceptSelf(std::vector<int>& nums)
{
  std::vector<int32_t> left_product(nums.size(),1), righ_product(nums.size(),1), res(nums.size(), 1);

  left_product[0] = nums[0];
  righ_product[nums.size()-1] = nums[nums.size()-1];
  
  for(auto i{1}; i < nums.size(); ++i)
  {
    left_product[i] = left_product[i-1] * nums[i];
  }
  for(int i{nums.size() - 2}; i >= 0; --i)
  {
    righ_product[i] = righ_product[i+1] * nums[i];
  }

  res[0] = righ_product[1];
  res[nums.size()-1] = left_product[left_product.size()-2];

  for(auto i{1}; i < nums.size() - 1; ++i)
  {
    res[i] = left_product[i-1] * righ_product[i+1];
  }

  return res;
  
}


TEST_CASE("Example 1") {
  auto in = std::vector<int>{1,2,3,4};
  REQUIRE(productExceptSelf(in) == std::vector<int>{24,12,8,6});
}

TEST_CASE("Example 2") {
  auto in = std::vector<int>{-1,1,0,-3,3};
  REQUIRE(productExceptSelf(in) == std::vector<int>{0,0,9,0,0});
}
