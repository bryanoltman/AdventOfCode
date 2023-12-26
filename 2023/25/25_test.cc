#include <catch2/catch.hpp>

#include "25/25.h"

using namespace std;

static auto TAGS = "Day 25";

TEST_CASE("ParseInput", TAGS)
{
  auto input = ParseInput("inputs/25.test.txt");
  REQUIRE(input.size() == 13);
  REQUIRE(input["pzl"].name == "pzl");
  REQUIRE(input["pzl"].linked_components ==
          (vector<string>){"lsr", "hfx", "nvd"});
}

TEST_CASE("Part 1", TAGS)
{
  auto input = ParseInput("inputs/25.test.txt");
  REQUIRE(PartOne(input) == 0);
}

TEST_CASE("Part 2", TAGS)
{
  auto input = ParseInput("inputs/25.test.txt");
  REQUIRE(PartTwo(input) == 0);
}