// A week of unpaid waiting time of app-based drivers in California, in each
// metro area.
//
// The data is synthetic: it follows a plausible pattern, but the figures are
// not meant to be accurate.

#include <array>
#include <cstddef>
#include <vector>

// Hour 0 of the week is Monday from 00:00 to 01:00, and hour 167 is Sunday
// from 23:00 to 24:00.
constexpr std::size_t kHoursPerDay = 24;
constexpr std::size_t kHoursPerWeek = 7 * kHoursPerDay;

// Metro area in which a driver works
enum class Metro : std::size_t {
  kLosAngeles,
  kBayArea,
  kSanDiego,
  kInlandEmpire,
  kSacramento,
  kFresno,
};

constexpr std::size_t kMetroCount = 6;

// Converts a metro area into its underlying value, e.g., to use it as an
// index (same as std::to_underlying() in C++23).
constexpr std::size_t ToUnderlying(Metro metro) {
  return static_cast<std::size_t>(metro);
}

// A driver, along with their unpaid waiting time for each hour of the week,
// in minutes (0 to 60)
struct Driver {
  Metro metro = Metro::kLosAngeles;
  std::array<int, kHoursPerWeek> waits{};
};

// Provided in generate.cc

// Returns 100,000 drivers, sorted by metro area.
std::vector<Driver> GenerateDrivers();

// Defined in metros.cc

// Returns the total waiting time of all the drivers, for each hour of the
// week, as in Part #1. Visits the drivers column by column, i.e., hour by hour.
std::array<int, kHoursPerWeek> TotalsHourByHour(
    const std::vector<Driver>& drivers);

// Returns the index of the first driver of each metro area, followed by the
// number of drivers, so that metro area m spans indices [starts[m],
// starts[m + 1]). The drivers must be sorted by metro area.
std::array<std::size_t, kMetroCount + 1> MetroStarts(
    const std::vector<Driver>& drivers);

// Returns the total waiting time of the drivers of indices [first, last) only,
// for each hour of the week.
std::array<int, kHoursPerWeek> TotalsOfRange(const std::vector<Driver>& drivers,
                                             std::size_t first,
                                             std::size_t last);

// Returns the total waiting time of the drivers of each metro area, for each
// hour of the week. The drivers must be sorted by metro area.
std::array<std::array<int, kHoursPerWeek>, kMetroCount> TotalsByMetro(
    const std::vector<Driver>& drivers);

// Returns the total waiting time of all the metro areas, for each hour of the
// week.
std::array<int, kHoursPerWeek> CombineTotals(
    const std::array<std::array<int, kHoursPerWeek>, kMetroCount>& partials);
