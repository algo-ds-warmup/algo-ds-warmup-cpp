#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <fmt/ranges.h>

#include <concepts>
#include <numeric>
#include <algorithm>
#include <vector>

void bubble_sort(std::ranges::forward_range auto& rg){
  auto begin{std::begin(rg)};
  auto end{std::end(rg)};
  
  while(true)
  {
    bool sorted{true};
    for(auto l{begin}, r{std::next(begin)}; r < end; ++l, ++r){
      if(*l > *r){
        std::iter_swap(l, r);
        sorted = false;
      }
    }
    end = std::prev(end);
    if(sorted) break;
  }
}

double trim_mean(std::vector<int>& vec){
  bubble_sort(vec);
  size_t ten_procent = std::size(vec) / 10;
  auto begin{std::next(vec.begin(), ten_procent/2)};
  auto end{std::prev(vec.end(), ten_procent/2)};
  size_t sz = std::distance(begin, end);

  double mean = std::accumulate(begin, end, double{0.0}, [sz](double res, int elem) { return res + (static_cast<double>(elem) / sz); });
  return mean;
}

TEST_CASE("Example 1"){
  auto input = std::vector{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3};
  CHECK(trim_mean(input) == doctest::Approx(2.000));
}

TEST_CASE("Example 2"){
  auto input = std::vector{6,2,7,5,1,2,0,3,10,2,5,0,5,5,0,8,7,6,8,0};
  CHECK(trim_mean(input) == doctest::Approx(4.000));
}

TEST_CASE("Example 3"){
  auto input = std::vector{6,0,7,0,7,5,7,8,3,4,0,7,8,1,6,8,1,1,2,4,8,1,9,5,4,3,8,5,10,8,6,6,1,0,6,10,8,2,3,4};
  CHECK(trim_mean(input) == doctest::Approx(4.77778));
}

// TODO: understand why it does not work
/* TEST_CASE("use reduce to calculate mean value"){ */
/*   std::vector<int> in{1,1,1,1,1}; */
/*   auto sz = in.size(); */
/*   CHECK_EQ(std::reduce(in.begin(), in.end(), 0.0, [sz](double res, int elem) { */
/*         return res + (static_cast<double>(elem) / sz); */
        /* return res + (double)elem / sz; */
/*         }), doctest::Approx(1.0)); */
/* } */
