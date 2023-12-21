#include <catch2/catch.hpp>

#include "20/20.h"

using namespace std;

static auto TAGS = "Day 20";

TEST_CASE("ParseInput", TAGS)
{
  auto input = ParseInput("inputs/20.test.txt");
  Module broadcast_module = input["broadcaster"];
  REQUIRE(broadcast_module.destinations == (vector<string>){"a", "b", "c"});
}

TEST_CASE("Part 1", TAGS)
{
  auto input = ParseInput("inputs/20.test.txt");
  REQUIRE(PartOne(input) == 0);
}

TEST_CASE("Part 2", TAGS)
{
  auto input = ParseInput("inputs/20.test.txt");
  REQUIRE(PartTwo(input) == 0);
}