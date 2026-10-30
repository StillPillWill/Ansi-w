#include <algorithm>
#include <array>
#include <cstddef>
#include <vector>

#include "totals.h"

// Generates a synthetic week of waiting times. Rather than relying on a random
// number generator, whose results depend on the standard library, the "random"
// values are computed from the driver and the hour, so that every computer
// generates exactly the same week.

constexpr std::size_t kDriverCount = 100'000;
constexpr int kMinutesPerHour = 60;
constexpr std::size_t kPercent = 100;

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

std::vector<std::array<int, kHoursPerWeek>> GenerateWaits() {
  std::vector<std::array<int, kHoursPerWeek>> waits(kDriverCount);
  for (std::size_t d = 0; d < waits.size(); ++d) {
    for (std::size_t h = 0; h < kHoursPerWeek; ++h) {
      std::size_t hour_of_day = h % kHoursPerDay;
      if (Scramble(d, h, kPercent) >= kOnlinePercents[hour_of_day]) {
        continue;  // Offline: no waiting time
      }
      int variation =
          static_cast<int>(Scramble(d, h + kHoursPerWeek, kVariationRange)) -
          static_cast<int>(kVariationRange / 2);
      waits[d][h] =
          std::clamp(kBaseWaits[hour_of_day] + variation, 0, kMinutesPerHour);
    }
  }
  return waits;
}
