#include <catch2/catch.hpp>

#include "13/13.h"

using namespace std;

static auto TAGS = "Day 13";

TEST_CASE("ParseInput", TAGS) { auto input = ParseInput("inputs/13.test.txt"); }

TEST_CASE("Part 1", TAGS) {
  auto input = ParseInput("inputs/13.test.txt");
  REQUIRE(PartOne(input) == 21);
}

TEST_CASE("Part 2", TAGS) {
  auto input = ParseInput("inputs/13.test.txt");
  REQUIRE(PartTwo(input) == 525152);
}