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
  std::array<std::size_t, kMetroCount> counts{};
  for (const Driver& driver : drivers) {
    ++counts[ToUnderlying(driver.metro)];
  }

  std::array<std::size_t, kMetroCount + 1> starts{};
  for (std::size_t metro = 0; metro < kMetroCount; ++metro) {
    starts[metro + 1] = starts[metro] + counts[metro];
  }
  return starts;
}

std::array<int, kHoursPerWeek> TotalsOfRange(const std::vector<Driver>& drivers,
                                             std::size_t first,
                                             std::size_t last) {
  assert(first <= last && last <= drivers.size());
  std::array<int, kHoursPerWeek> totals{};
  for (std::size_t d = first; d < last; ++d) {
    for (std::size_t h = 0; h < kHoursPerWeek; ++h) {
      totals[h] += drivers[d].waits[h];
    }
  }
  return totals;
}

std::array<std::array<int, kHoursPerWeek>, kMetroCount> TotalsByMetro(
    const std::vector<Driver>& drivers) {
  const std::array<std::size_t, kMetroCount + 1> starts = MetroStarts(drivers);
  std::array<std::array<int, kHoursPerWeek>, kMetroCount> partials{};
  for (std::size_t metro = 0; metro < kMetroCount; ++metro) {
    partials[metro] = TotalsOfRange(drivers, starts[metro], starts[metro + 1]);
  }
  return partials;
}

std::array<int, kHoursPerWeek> CombineTotals(
    const std::array<std::array<int, kHoursPerWeek>, kMetroCount>& partials) {
  std::array<int, kHoursPerWeek> totals{};
  for (std::size_t metro = 0; metro < kMetroCount; ++metro) {
    for (std::size_t h = 0; h < kHoursPerWeek; ++h) {
      totals[h] += partials[metro][h];
    }
  }
  return totals;
}
