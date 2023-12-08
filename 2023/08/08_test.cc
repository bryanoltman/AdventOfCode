#include <catch2/catch.hpp>

#include "08/08.h"

using namespace std;

static auto TAGS = "Day 08";

TEST_CASE("Part 1 (first test input)", TAGS) {
  auto input = ParseInput("inputs/08.test.txt", false);
  REQUIRE(PartOne(input) == 6440);
}

TEST_CASE("Part 1 (second test input)", TAGS) {
  auto input = ParseInput("inputs/08.test2.txt", false);
  REQUIRE(PartOne(input) == 6440);
}

// TEST_CASE("Part 2", TAGS) {
//   auto input = ParseInput("inputs/07.test.txt", true);
//   REQUIRE(PartTwo(input) == 5905);
// }