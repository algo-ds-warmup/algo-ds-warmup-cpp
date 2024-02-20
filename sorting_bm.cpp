#include <benchmark/benchmark.h>
#include <fmt/ranges.h>
#include <random>
#include <ranges>
#include <vector>

enum class DATA_ORDER { SORTED, REVERSED, RANDOM };
template <typename T>
std::vector<T>
generate_random_vector(size_t n, DATA_ORDER order = DATA_ORDER::RANDOM,
                       T min_value = 0,
                       T max_value = std::numeric_limits<T>::max()) {
  std::vector<T> result;
  result.reserve(n);

  auto view = std::views::iota(min_value, max_value) | std::views::take(n);
  if (order == DATA_ORDER::SORTED) {
    std::ranges::copy(view, std::back_inserter(result));
  } else if (order == DATA_ORDER::REVERSED) {
    std::ranges::copy(view | std::views::reverse, std::back_inserter(result));
  } else if (order == DATA_ORDER::RANDOM) {
    std::ranges::copy(view, std::back_inserter(result));
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::ranges::shuffle(result, gen);
  }

  return result;
}

template <typename... Args>
static void BM_insertion_sort(benchmark::State &state, Args &&...args) {
  state.PauseTiming();
  auto args_tuple = std::make_tuple(std::move(args)...);
  auto order = std::get<0>(args_tuple);
  auto input = generate_random_vector<int>(state.range(0), order);
  state.ResumeTiming();

  for (auto _ : state) {
    for (int i{1}; i < input.size(); ++i) {
      auto tmp{input[i]};
      int k{i};
      while (k > 0 && input[k - 1] > tmp) {
        input[k] = input[k - 1];
        --k;
      }
      input[k] = tmp;
    }
  }
  state.SetComplexityN(state.range(0));
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

/* BENCHMARK(BM_bubble_sort_naive) */
/*     ->RangeMultiplier(8) */
/*     ->Range(1 << 12, 1 << 22) */
/*     ->Iterations(3) */
/*     ->Complexity(); */
/**/
/* BENCHMARK(BM_bubble_sort_decrease_rg) */
/*     ->RangeMultiplier(8) */
/*     ->Range(1 << 12, 1 << 22) */
/*     ->Iterations(3) */
/*     ->Complexity(); */

/* BENCHMARK(BM_insertion_sort)->Name("InsertionSort") */

BENCHMARK_CAPTURE(BM_insertion_sort, Sorted, DATA_ORDER::SORTED)
    ->Range(1 << 12, 1 << 16)
    ->Iterations(3)
    ->Complexity();
BENCHMARK_CAPTURE(BM_insertion_sort, Random, DATA_ORDER::RANDOM)
    ->Range(1 << 12, 1 << 16)
    ->Iterations(3)
    ->Complexity();
BENCHMARK_CAPTURE(BM_insertion_sort, Reversed, DATA_ORDER::REVERSED)
    ->Range(1 << 12, 1 << 16)
    ->Iterations(3)
    ->Complexity();

BENCHMARK_MAIN();
