#include "totals.h"

// Implements the totals declared in totals.h.

// Provided
std::array<int, kHoursPerWeek> TotalsHourByHour(
    const std::vector<std::array<int, kHoursPerWeek>>& waits) {
  std::array<int, kHoursPerWeek> totals{};
  for (std::size_t h = 0; h < kHoursPerWeek; ++h) {
    for (std::size_t d = 0; d < waits.size(); ++d) {
      totals[h] += waits[d][h];
    }
  }
  return totals;
}

std::array<int, kHoursPerWeek> TotalsDriverByDriver(
    const std::vector<std::array<int, kHoursPerWeek>>& waits) {
  std::array<int, kHoursPerWeek> totals{};
  for (std::size_t d = 0; d < waits.size(); ++d) {
    for (std::size_t h = 0; h < kHoursPerWeek; ++h) {
      totals[h] += waits[d][h];
    }
  }
  return totals;
}
