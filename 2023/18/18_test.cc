#include <catch2/catch.hpp>

#include "18/18.h"

using namespace std;

static auto TAGS = "Day 18";

TEST_CASE("ParseInput", TAGS) { auto input = ParseInput("inputs/18.test.txt"); }

TEST_CASE("Part 1", TAGS) {
  auto input = ParseInput("inputs/18.test.txt");
  REQUIRE(PartOne(input) == 0);
}

TEST_CASE("Part 2", TAGS) {
  auto input = ParseInput("inputs/18.test.txt");
  REQUIRE(PartTwo(input) == 0);
}