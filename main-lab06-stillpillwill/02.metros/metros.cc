#include "metros.h"

#include <cassert>

// Implements the totals declared in metros.h.

// Provided
std::array<int, kHoursPerWeek> TotalsHourByHour(
    const std::vector<Driver>& drivers) {
  std::array<int, kHoursPerWeek> totals{};
  for (std::size_t h = 0; h < kHoursPerWeek; ++h) {
    for (std::size_t d = 0; d < drivers.size(); ++d) {
      totals[h] += drivers[d].waits[h];
    }
  }
  return totals;
}

std::array<std::size_t, kMetroCount + 1> MetroStarts(
    const std::vector<Driver>& drivers) {
  // TODO
  return {};
}

std::array<int, kHoursPerWeek> TotalsOfRange(const std::vector<Driver>& drivers,
                                             std::size_t first,
                                             std::size_t last) {
  assert(first <= last && last <= drivers.size());
  // TODO
  return {};
}

std::array<std::array<int, kHoursPerWeek>, kMetroCount> TotalsByMetro(
    const std::vector<Driver>& drivers) {
  // TODO
  return {};
}

std::array<int, kHoursPerWeek> CombineTotals(
    const std::array<std::array<int, kHoursPerWeek>, kMetroCount>& partials) {
  // TODO
  return {};
}
