#include <catch2/catch.hpp>

#include "12/12.h"

using namespace std;

static auto TAGS = "Day 12";

TEST_CASE("Part 1", TAGS) {
  auto input = ParseInput("inputs/12.test.txt");
  REQUIRE(PartOne(input) == 0);
}

TEST_CASE("Part 2", TAGS) {
  auto input = ParseInput("inputs/12.test.txt");
  REQUIRE(PartTwo(input) == 0);
}