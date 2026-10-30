#include <algorithm>
#include <array>
#include <cstddef>
#include <vector>

#include "metros.h"

// Generates a synthetic week of waiting times. Rather than relying on a random
// number generator, whose results depend on the standard library, the "random"
// values are computed from the driver and the hour, so that every computer
// generates exactly the same week.

constexpr int kMinutesPerHour = 60;
constexpr std::size_t kPercent = 100;

// Number of drivers in each metro area
constexpr std::array<std::size_t, kMetroCount> kDriverCounts{
    40'000, 25'000, 12'000, 10'000, 8'000, 5'000};

// Chance that a driver is online, for each hour of the day (%)
constexpr std::array<std::size_t, kHoursPerDay> kOnlinePercents{
    5,  4,  3,  3,  4,  8,   // 00:00 to 05:59
    15, 25, 25, 18, 15, 15,  // 06:00 to 11:59
    18, 15, 12, 15, 25, 30,  // 12:00 to 17:59
    28, 22, 18, 15, 12, 8,   // 18:00 to 23:59
};

// Typical waiting time of an online driver, for each hour of the day (min)
constexpr std::array<int, kHoursPerDay> kBaseWaits{
    30, 35, 40, 40, 35, 25,  // 00:00 to 05:59
    15, 10, 10, 15, 20, 18,  // 06:00 to 11:59
    15, 20, 25, 20, 12, 10,  // 12:00 to 17:59
    12, 15, 18, 20, 22, 25,  // 18:00 to 23:59
};

// Extra waiting time in each metro area, which has fewer riders per driver
// than Los Angeles (min)
constexpr std::array<int, kMetroCount> kMetroExtraWaits{0, 0, 3, 8, 6, 10};

// Variation of the waiting time between drivers: -5 to +5 minutes
constexpr std::size_t kVariationRange = 11;

// Returns a value in [0, bound) that looks random, but only depends on
// `driver` and `hour`.
std::size_t Scramble(std::size_t driver, std::size_t hour, std::size_t bound) {
  constexpr std::size_t kDriverFactor = 2'654'435'761;
  constexpr std::size_t kHourFactor = 40'503;
  constexpr std::size_t kShift = 29;
  std::size_t value = driver * kDriverFactor + hour * kHourFactor;
  value ^= value >> kShift;
  value *= kDriverFactor;
  value ^= value >> kShift;
  return value % bound;
}

std::vector<Driver> GenerateDrivers() {
  std::vector<Driver> drivers;
  for (std::size_t m = 0; m < kMetroCount; ++m) {
    for (std::size_t i = 0; i < kDriverCounts[m]; ++i) {
      std::size_t id = drivers.size();
      Driver driver{.metro = static_cast<Metro>(m)};
      for (std::size_t h = 0; h < kHoursPerWeek; ++h) {
        std::size_t hour_of_day = h % kHoursPerDay;
        if (Scramble(id, h, kPercent) >= kOnlinePercents[hour_of_day]) {
          continue;  // Offline: no waiting time
        }
        int variation =
            static_cast<int>(Scramble(id, h + kHoursPerWeek, kVariationRange)) -
            static_cast<int>(kVariationRange / 2);
        driver.waits[h] = std::clamp(
            kBaseWaits[hour_of_day] + kMetroExtraWaits[m] + variation, 0,
            kMinutesPerHour);
      }
      drivers.push_back(driver);
    }
  }
  return drivers;
}
