#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <algorithm>
#include <limits>
#include <numeric>
#include <ranges>
#include <vector>

#include <fmt/ranges.h>

// log n
int find_min(const std::vector<int> &nums) {
  int left{0};
  int right = nums.size() - 1;
  int min{nums[0]};

  while (left <= right) {
    auto mid = std::midpoint(left, right);
    min = std::min(nums[mid], min);

    fmt::print("[{} : {}], mid={}\n", nums[left], nums[right], nums[mid]);

    if (nums[right] > nums[mid] && nums[right] > nums[left]) {
      return std::min(nums[left], min);

    } else {
      // rotated only
      if (nums[mid] < nums[left]) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
  }

  return min;
}

TEST_CASE("Example 1") { CHECK(find_min({3, 4, 5, 1, 2}) == 1); }
TEST_CASE("Example 2") { CHECK(find_min({4, 5, 6, 7, 0, 1, 2}) == 0); }
TEST_CASE("Example 3") { CHECK(find_min({11, 13, 15, 17}) == 11); }

TEST_CASE("TC 1") { CHECK(find_min({5, 1, 2, 3, 4}) == 1); }
TEST_CASE("TC 2") { CHECK(find_min({2, 3, 1}) == 1); }
TEST_CASE("TC 3") { CHECK(find_min({1}) == 1); }
TEST_CASE("TC 4") { CHECK(find_min({2, 3, 4, 5, 1}) == 1); }
TEST_CASE("TC 5") { CHECK(find_min({7, 8, 1, 2, 3, 4, 5, 6}) == 1); }
TEST_CASE("TC 6") { CHECK(find_min({4,5,1,2,3}) == 1); }
