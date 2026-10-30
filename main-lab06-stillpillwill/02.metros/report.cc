#include <array>
#include <chrono>
#include <cstddef>
#include <format>
#include <iostream>
#include <vector>

#include "metros.h"

// Measures the time elapsed since its creation
class Stopwatch {
 public:
  double ElapsedMs() const {
    std::chrono::duration<double, std::milli> elapsed =
        std::chrono::steady_clock::now() - start_;
    return elapsed.count();
  }

 private:
  std::chrono::steady_clock::time_point start_ =
      std::chrono::steady_clock::now();
};

// Prints the name of a metro area.
void PrintMetro(Metro metro) {
  switch (metro) {
    case Metro::kLosAngeles:
      std::cout << "Los Angeles";
      break;
    case Metro::kBayArea:
      std::cout << "Bay Area";
      break;
    case Metro::kSanDiego:
      std::cout << "San Diego";
      break;
    case Metro::kInlandEmpire:
      std::cout << "Inland Empire";
      break;
    case Metro::kSacramento:
      std::cout << "Sacramento";
      break;
    case Metro::kFresno:
      std::cout << "Fresno";
      break;
  }
}

int main() {
  constexpr double kMinutesPerHour = 60.0;

  Stopwatch generate_watch;
  const std::vector<Driver> drivers = GenerateDrivers();
  std::cout << std::format("Generating {} drivers: {:.1f} ms\n", drivers.size(),
                           generate_watch.ElapsedMs());

  Stopwatch metro_watch;
  const std::array<std::array<int, kHoursPerWeek>, kMetroCount> partials =
      TotalsByMetro(drivers);
  std::cout << std::format("TotalsByMetro():    {:6.1f} ms\n",
                           metro_watch.ElapsedMs());

  Stopwatch combine_watch;
  const std::array<int, kHoursPerWeek> combined = CombineTotals(partials);
  std::cout << std::format("CombineTotals():    {:6.1f} ms\n",
                           combine_watch.ElapsedMs());
  if (combined != TotalsHourByHour(drivers)) {
    std::cout << "(CombineTotals() doesn't match TotalsHourByHour() yet)\n";
  }

  std::cout << '\n';
  const std::array<std::size_t, kMetroCount + 1> starts = MetroStarts(drivers);
  for (std::size_t m = 0; m < kMetroCount; ++m) {
    std::size_t count = starts[m + 1] - starts[m];
    int minutes = 0;
    for (int total : partials[m]) {
      minutes += total;
    }
    double hours_each = 0.0;
    if (count > 0) {
      hours_each = minutes / kMinutesPerHour / static_cast<double>(count);
    }
    std::cout << std::format("{:6} drivers, {:4.1f} unpaid hours each: ", count,
                             hours_each);
    PrintMetro(static_cast<Metro>(m));
    std::cout << '\n';
  }
}
