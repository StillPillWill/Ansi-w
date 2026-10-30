#include <array>
#include <chrono>
#include <cstddef>
#include <format>
#include <iostream>
#include <vector>

#include "totals.h"

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

// Prints an hour of the week, e.g., "Friday 17:00".
void PrintHour(std::size_t hour) {
  switch (hour / kHoursPerDay) {
    case 0:
      std::cout << "Monday";
      break;
    case 1:
      std::cout << "Tuesday";
      break;
    case 2:
      std::cout << "Wednesday";
      break;
    case 3:
      std::cout << "Thursday";
      break;
    case 4:
      std::cout << "Friday";
      break;
    case 5:
      std::cout << "Saturday";
      break;
    default:
      std::cout << "Sunday";
      break;
  }
  std::cout << std::format(" {:02}:00", hour % kHoursPerDay);
}

// Returns the hour of the week with the largest total.
std::size_t PeakHour(const std::array<int, kHoursPerWeek>& totals) {
  std::size_t peak = 0;
  for (std::size_t h = 1; h < kHoursPerWeek; ++h) {
    if (totals[h] > totals[peak]) {
      peak = h;
    }
  }
  return peak;
}

int main() {
  constexpr int kMinutesPerHour = 60;

  Stopwatch generate_watch;
  const std::vector<std::array<int, kHoursPerWeek>> waits = GenerateWaits();
  std::cout << std::format("Generating {} drivers: {:.1f} ms\n", waits.size(),
                           generate_watch.ElapsedMs());

  Stopwatch hour_watch;
  const std::array<int, kHoursPerWeek> totals = TotalsHourByHour(waits);
  std::cout << std::format("TotalsHourByHour():     {:6.1f} ms\n",
                           hour_watch.ElapsedMs());

  Stopwatch driver_watch;
  const std::array<int, kHoursPerWeek> driver_totals =
      TotalsDriverByDriver(waits);
  std::cout << std::format("TotalsDriverByDriver(): {:6.1f} ms\n",
                           driver_watch.ElapsedMs());
  if (driver_totals != totals) {
    std::cout
        << "(TotalsDriverByDriver() doesn't match TotalsHourByHour() yet)\n";
  }

  std::size_t peak = PeakHour(totals);
  std::cout << "Most unpaid waiting: ";
  PrintHour(peak);
  std::cout << std::format(" ({} hours in total)\n",
                           totals[peak] / kMinutesPerHour);
}
