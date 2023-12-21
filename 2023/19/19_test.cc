#include <catch2/catch.hpp>

#include "19/19.h"

using namespace std;

static auto TAGS = "Day 19";

TEST_CASE("ParseInput", TAGS)
{
  auto input = ParseInput("inputs/19.test.txt");
  // REQUIRE(input.workflows["in"].rules.size() == 1);
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