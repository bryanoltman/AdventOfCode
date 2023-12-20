#include <catch2/catch.hpp>

#include "18/18.h"

using namespace std;

static auto TAGS = "Day 18";

TEST_CASE("ParseInput", TAGS)
{
  auto input = ParseInput("inputs/18.test.txt");
  REQUIRE(input.front().direction == RIGHT);
  REQUIRE(input.front().distance == 6);
  REQUIRE(input.front().color == 0x70c710);
  REQUIRE(input.back().direction == UP);
  REQUIRE(input.back().distance == 2);
  REQUIRE(input.back().color == 0x7a21e3);
}

TEST_CASE("Part 1", TAGS)
{
  auto input = ParseInput("inputs/18.test.txt");
  REQUIRE(PartOne(input) == 62);
}

TEST_CASE("Part 2", TAGS)
{
  auto input = ParseInput("inputs/18.test.txt");
  REQUIRE(PartTwo(input) == 0);
}