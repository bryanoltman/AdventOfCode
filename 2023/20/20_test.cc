#include <catch2/catch.hpp>

#include "20/20.h"

using namespace std;

static auto TAGS = "Day 20";

TEST_CASE("ParseInput", TAGS)
{
  auto input = ParseInput("inputs/20.test2.txt");
  Module broadcast_module = input["broadcaster"];
  REQUIRE(broadcast_module.destinations == (vector<string>){"a"});
  REQUIRE(input["a"].destinations == (vector<string>){"inv", "con"});
  REQUIRE(input["inv"].is_conjunction);
}

TEST_CASE("Part 1", TAGS)
{
  auto input = ParseInput("inputs/20.test.txt");
  REQUIRE(PartOne(input) == 32000000);
}

TEST_CASE("Part 1 (second input)", TAGS)
{
  auto input = ParseInput("inputs/20.test2.txt");
  REQUIRE(PartOne(input) == 11687500);
}
