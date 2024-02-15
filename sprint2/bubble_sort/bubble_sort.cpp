#include <benchmark/benchmark.h>
#include <fmt/ranges.h>
#include <random>
#include <vector>

template <typename T>
std::vector<T> generate_random_vector(
    size_t n, T min_value = T{}, T max_value = T{},
    std::mt19937::result_type seed = std::random_device()()) {

  // Initialize random number generator and distribution
  std::mt19937 gen(seed);
  std::uniform_real_distribution<> distr(min_value, max_value);

  // Generate random numbers and store in vector
  std::vector<T> result(n);
  std::generate(result.begin(), result.end(), [&]() { return distr(gen); });

  return result;
}

static void BM_bubble_sort_naive(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto input = generate_random_vector<int>(state.range(0));
    state.ResumeTiming();

    while (true) {
      bool sorted{true};
      for (auto left{input.begin()}, right{std::next(left)};
           right < input.end(); ++left, ++right) {
        if (*left > *right) {
          std::iter_swap(left, right);
          sorted = false;
        }
      }
      if (sorted)
        break;
    }
  }
  state.SetComplexityN(state.range(0));
}

static void BM_bubble_sort_decrease_rg(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto input = generate_random_vector<int>(state.range(0));
    state.ResumeTiming();

    auto beg{input.begin()};
    auto end{input.end()};
    while (true) {
      bool sorted{true};
      for (auto left{beg}, right{std::next(left)}; right < end;
           ++left, ++right) {
        if (*left > *right) {
          std::iter_swap(left, right);
          sorted = false;
        }
      }
      end = std::prev(end);
      if (sorted)
        break;
    }
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_bubble_sort_naive)
    ->RangeMultiplier(8)
    ->Range(1 << 12, 1 << 22)
    ->Iterations(3)
    ->Complexity();

BENCHMARK(BM_bubble_sort_decrease_rg)
    ->RangeMultiplier(8)
    ->Range(1 << 12, 1 << 22)
    ->Iterations(3)
    ->Complexity();

BENCHMARK_MAIN();
