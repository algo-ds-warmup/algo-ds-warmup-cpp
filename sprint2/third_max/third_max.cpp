#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/ranges.h>

int third_max(std::vector<int> nums){
  if(nums.empty())
    return -1;
  if(nums.size() == 1)
    return nums[0];

  size_t max_n{1};
  for(size_t m{0}; m < nums.size(); ++m)
  {
    size_t next_max_pos{m};
    for(size_t i{m+1}; i < nums.size(); ++i)
    {
      if(nums[i] >= nums[next_max_pos]){
        next_max_pos = i;
      }
    }

    if(next_max_pos != m)
    {
      std::swap(nums[m], nums[next_max_pos]);
    }

    if(nums[m] != nums[std::min(m, m-1)] && ++max_n == 3){
      return nums[m];
    }
  }

  return nums[0];

}

TEST_CASE("Example 1"){
  auto in = std::vector{3,2,1};
  CHECK(third_max(in) == 1);
}


TEST_CASE("Example 2"){
  auto in = std::vector{1,2};
  CHECK(third_max(in) == 2);
}


TEST_CASE("Example 3"){
  auto in = std::vector{2,2,3,1};
  CHECK(third_max(in) == 1);
}


TEST_CASE("TC1")
{
  auto in = std::vector{1,2,2,5,3,5};
  CHECK(third_max(in) == 2);
}

