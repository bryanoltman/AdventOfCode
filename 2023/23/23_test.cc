#include <catch2/catch.hpp>

#include "23/23.h"

using namespace std;

static auto TAGS = "Day 23";

TEST_CASE("ParseInput", TAGS) { auto input = ParseInput("inputs/23.test.txt"); }

TEST_CASE("Part 1", TAGS)
{
  auto input = ParseInput("inputs/23.test.txt");
  REQUIRE(PartOne(input) == 94);
}

TEST_CASE("Part 2", TAGS)
{
  auto input = ParseInput("inputs/23.test.txt");
  REQUIRE(PartTwo(input) == 154);
}