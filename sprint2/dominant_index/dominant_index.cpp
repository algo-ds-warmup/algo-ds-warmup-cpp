#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <fmt/ranges.h>

int dominant_index(const std::vector<int>& nums)
{
  if(nums.size() < 2)
    return -1;

  int max[2]{0, 1};
  if(nums[1] > nums[0])
  {
    max[0] = 1;
    max[1] = 0;
  }

  for(size_t i{2}; i < nums.size(); ++i)
  {
    if(nums[i] > nums[max[1]])
    {
      if(nums[i] > nums[max[0]]){
        max[1] = max[0];
        max[0] = i;
      } else
      {
        max[1] = i;
      }
    }
  }
  /* fmt::print("{}\n", max); */
  return (nums[max[0]] >> 1) >= nums[max[1]] ? max[0] : -1;
}

TEST_CASE("Example 1") {
  CHECK(dominant_index(std::vector{3,6,1,0}) == 1);
}

TEST_CASE("Example 2") {
  CHECK(dominant_index(std::vector{1,2,3,4}) == -1);
}

TEST_CASE("TC1"){
  CHECK(dominant_index(std::vector{1,0}) == 0);
}

TEST_CASE("TC2"){
  CHECK(dominant_index(std::vector{0,0,3,2}) == -1);
}
