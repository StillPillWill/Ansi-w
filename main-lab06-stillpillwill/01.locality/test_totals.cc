#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

#include "totals.h"

// Tests the functions of totals.h.
//
// Each assertion aborts the program if it fails, so the first failure is
// always the next thing to fix.

// Four drivers, whose waiting time is 0 after the first few hours of the week
std::vector<std::array<int, kHoursPerWeek>> SampleWaits() {
  return {{1, 2, 3}, {4, 5}, {6}, {0, 0, 7}};
}

void TestTotalsHourByHour() {
  const std::array<int, kHoursPerWeek> totals = TotalsHourByHour(SampleWaits());
  assert(totals[0] == 11);
  assert(totals[1] == 7);
  assert(totals[2] == 10);
  assert(totals[3] == 0);
  assert(totals[kHoursPerWeek - 1] == 0);
  std::cout << "TotalsHourByHour: ok\n";
}

void TestTotalsDriverByDriver() {
  const std::vector<std::array<int, kHoursPerWeek>> waits = SampleWaits();
  assert(TotalsDriverByDriver(waits) == TotalsHourByHour(waits));

  // No driver at all
  assert(TotalsDriverByDriver({}) == TotalsHourByHour({}));

  // The whole week, as in program benchmark
  const std::vector<std::array<int, kHoursPerWeek>> week = GenerateWaits();
  assert(TotalsDriverByDriver(week) == TotalsHourByHour(week));
  std::cout << "TotalsDriverByDriver: ok\n";
}

int main() {
  TestTotalsHourByHour();
  TestTotalsDriverByDriver();
}
