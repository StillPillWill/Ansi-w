#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

#include "metros.h"

// Tests the functions of metros.h, in the order of the handout.
//
// Each assertion aborts the program if it fails, so the first failure is
// always the next thing to fix.

// Four drivers, whose waiting time is 0 after the first few hours of the week
std::vector<Driver> SampleDrivers() {
  return {
      {.metro = Metro::kLosAngeles, .waits = {1, 2, 3}},
      {.metro = Metro::kLosAngeles, .waits = {4, 5}},
      {.metro = Metro::kSanDiego, .waits = {6}},
      {.metro = Metro::kFresno, .waits = {0, 0, 7}},
  };
}

void TestMetroStarts() {
  constexpr std::array<std::size_t, kMetroCount + 1> kSampleStarts{0, 2, 2, 3,
                                                                   3, 3, 4};
  assert(MetroStarts(SampleDrivers()) == kSampleStarts);

  // No driver at all
  constexpr std::array<std::size_t, kMetroCount + 1> kNoStarts{};
  assert(MetroStarts({}) == kNoStarts);

  // All the drivers in a single metro area
  const std::vector<Driver> sacramento{{.metro = Metro::kSacramento},
                                       {.metro = Metro::kSacramento},
                                       {.metro = Metro::kSacramento}};
  constexpr std::array<std::size_t, kMetroCount + 1> kSacramentoStarts{
      0, 0, 0, 0, 0, 3, 3};
  assert(MetroStarts(sacramento) == kSacramentoStarts);
  std::cout << "MetroStarts: ok\n";
}

void TestTotalsOfRange() {
  const std::vector<Driver> drivers = SampleDrivers();

  // Second and third drivers only
  const std::array<int, kHoursPerWeek> middle = TotalsOfRange(drivers, 1, 3);
  assert(middle[0] == 10);
  assert(middle[1] == 5);
  assert(middle[2] == 0);

  // Empty range
  const std::array<int, kHoursPerWeek> empty = TotalsOfRange(drivers, 2, 2);
  assert(empty[0] == 0);
  assert(empty[1] == 0);

  // Every driver
  assert(TotalsOfRange(drivers, 0, drivers.size()) ==
         TotalsHourByHour(drivers));
  std::cout << "TotalsOfRange: ok\n";
}

void TestTotalsByMetro() {
  const std::array<std::array<int, kHoursPerWeek>, kMetroCount> partials =
      TotalsByMetro(SampleDrivers());

  const std::array<int, kHoursPerWeek>& los_angeles =
      partials[ToUnderlying(Metro::kLosAngeles)];
  assert(los_angeles[0] == 5);
  assert(los_angeles[1] == 7);
  assert(los_angeles[2] == 3);

  const std::array<int, kHoursPerWeek>& san_diego =
      partials[ToUnderlying(Metro::kSanDiego)];
  assert(san_diego[0] == 6);
  assert(san_diego[1] == 0);

  const std::array<int, kHoursPerWeek>& fresno =
      partials[ToUnderlying(Metro::kFresno)];
  assert(fresno[0] == 0);
  assert(fresno[2] == 7);

  // Metro areas without any driver
  constexpr std::array<int, kHoursPerWeek> kNoTotals{};
  assert(partials[ToUnderlying(Metro::kBayArea)] == kNoTotals);
  assert(partials[ToUnderlying(Metro::kInlandEmpire)] == kNoTotals);
  assert(partials[ToUnderlying(Metro::kSacramento)] == kNoTotals);
  std::cout << "TotalsByMetro: ok\n";
}

void TestCombineTotals() {
  std::array<std::array<int, kHoursPerWeek>, kMetroCount> partials{};
  partials[ToUnderlying(Metro::kLosAngeles)][0] = 1;
  partials[ToUnderlying(Metro::kFresno)][0] = 2;
  partials[ToUnderlying(Metro::kSanDiego)][kHoursPerWeek - 1] = 3;
  const std::array<int, kHoursPerWeek> totals = CombineTotals(partials);
  assert(totals[0] == 3);
  assert(totals[1] == 0);
  assert(totals[kHoursPerWeek - 1] == 3);

  const std::vector<Driver> drivers = SampleDrivers();
  assert(CombineTotals(TotalsByMetro(drivers)) == TotalsHourByHour(drivers));
  std::cout << "CombineTotals: ok\n";
}

// The whole week, as in program report
void TestWeek() {
  const std::vector<Driver> drivers = GenerateDrivers();
  assert(MetroStarts(drivers)[kMetroCount] == drivers.size());
  assert(CombineTotals(TotalsByMetro(drivers)) == TotalsHourByHour(drivers));
  std::cout << "Week: ok\n";
}

int main() {
  TestMetroStarts();
  TestTotalsOfRange();
  TestTotalsByMetro();
  TestCombineTotals();
  TestWeek();
}
