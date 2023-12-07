#include <catch2/catch.hpp>

#include "06/06.h"

using namespace std;

static auto TAGS = "Day 06";

TEST_CASE("Part 1", TAGS) {
  Input input = {
      {7, 9},   //
      {15, 40}, //
      {30, 200} //
  };
  REQUIRE(PartOne(input) == 288);
}

TEST_CASE("Part 2", TAGS) {
  Input input = {
      {71530, 940200}, //
  };
  REQUIRE(PartTwo(input) == 71503);
}