#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <algorithm>
#include <span>
#include <utility>
#include <vector>

// naive implementation
int max_area_of_island(const std::vector<std::vector<int>> &grid) {
  using Position = std::pair<int, int>;
  using Area = std::vector<Position>;
  using Areas = std::vector<Area>;
  Areas areas;

  if (grid.size() == 1) {
    int longest_area{0};
    int current{0};
    for (auto k{0}; k < grid[0].size(); ++k) {
      if (grid[0][k] == 0) {
        longest_area = std::max(current, longest_area);
        current = 0;
      } else {
        current += 1;
      }
    }
    return std::max(current, longest_area);
  }

}

TEST_CASE("Longest sequence in one line") {
  CHECK(max_area_of_island(std::vector<std::vector<int>>{
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}}) == 1);
  CHECK(max_area_of_island(std::vector<std::vector<int>>{
            {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}}) == 3);
  CHECK(max_area_of_island(std::vector<std::vector<int>>{
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}) == 13);
  CHECK(max_area_of_island(std::vector<std::vector<int>>{
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}) == 0);
}

/* TEST_CASE("Example1") { */
/*   std::vector<std::vector<int>> grid{{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
 */
/*                                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
 */
/*                                      {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
 */
/*                                      {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
 */
/*                                      {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
 */
/*                                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
 */
/*                                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
 */
/*                                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
 * 0}}; */
/*   CHECK(max_area_of_island(grid) == 6); */
/* } */
/**/
/* TEST_CASE("Example2") { */
/*   std::vector<std::vector<int>> grid{{0, 0, 0, 0, 0}}; */
/*   CHECK(max_area_of_island(grid) == 0); */
/* } */

