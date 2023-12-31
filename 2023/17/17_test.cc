#include <catch2/catch.hpp>

#include "17/17.h"

using namespace std;

static auto TAGS = "Day 17";

TEST_CASE("ParseInput", TAGS) { auto input = ParseInput("inputs/17.test.txt"); }

TEST_CASE("Part 1", TAGS)
{
  auto input = ParseInput("inputs/17.test.txt");
  REQUIRE(PartOne(input) == 102);
}

TEST_CASE("Part 2", TAGS)
{
  auto input = ParseInput("inputs/17.test.txt");
  REQUIRE(PartTwo(input) == 0);
}