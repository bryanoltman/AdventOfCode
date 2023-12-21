#include <catch2/catch.hpp>

#include "19/19.h"

using namespace std;

static auto TAGS = "Day 19";

TEST_CASE("ParseInput", TAGS)
{
  auto input = ParseInput("inputs/19.test.txt");
  REQUIRE(input.workflows["in"].rules.size() == 2);
  REQUIRE(input.workflows["in"].rules[0].parameter == 's');
  REQUIRE(input.workflows["in"].rules[0].gt == false);
  REQUIRE(input.workflows["in"].rules[0].cmp == 1351);
  REQUIRE(input.workflows["in"].rules[0].result == "px");
  REQUIRE(input.parts.size() == 5);
  REQUIRE(input.parts[0].x == 787);
  REQUIRE(input.parts[0].m == 2655);
  REQUIRE(input.parts[0].a == 1222);
  REQUIRE(input.parts[0].s == 2876);
}

// TEST_CASE("Part 1", TAGS)
// {
//   auto input = ParseInput("inputs/19.test.txt");
//   REQUIRE(PartOne(input) == 0);
// }

// TEST_CASE("Part 2", TAGS)
// {
//   auto input = ParseInput("inputs/19.test.txt");
//   REQUIRE(PartTwo(input) == 0);
// }