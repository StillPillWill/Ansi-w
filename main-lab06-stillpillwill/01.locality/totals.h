// A week of unpaid waiting time of app-based drivers in California.
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

// Provided in generate.cc

// Returns the waiting time of 100,000 drivers, for each hour of the week, in
// minutes (0 to 60): waits[d][h] is the waiting time of driver d during hour h.
std::vector<std::array<int, kHoursPerWeek>> GenerateWaits();

// Defined in totals.cc

// Returns the total waiting time of all the drivers, for each hour of the
// week. Visits the table column by column, i.e., hour by hour.
std::array<int, kHoursPerWeek> TotalsHourByHour(
    const std::vector<std::array<int, kHoursPerWeek>>& waits);

// Same as TotalsHourByHour(), but visits the table row by row, i.e., driver by
// driver.
std::array<int, kHoursPerWeek> TotalsDriverByDriver(
    const std::vector<std::array<int, kHoursPerWeek>>& waits);
