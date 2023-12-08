#include <catch2/catch.hpp>

#include "08/08.h"

using namespace std;

static auto TAGS = "Day 08";

TEST_CASE("Parses input", TAGS) {
  auto input = ParseInput("inputs/08.test2.txt");
  REQUIRE(input.directions == "LLR");
  REQUIRE(input.nodes.size() == 3);
  REQUIRE(input.nodes["AAA"] == (pair<string, string>)make_pair("BBB", "BBB"));
  REQUIRE(input.nodes["BBB"] == (pair<string, string>)make_pair("AAA", "ZZZ"));
  REQUIRE(input.nodes["ZZZ"] == (pair<string, string>)make_pair("ZZZ", "ZZZ"));
}

TEST_CASE("Part 1 (first test input)", TAGS) {
  auto input = ParseInput("inputs/08.test.txt");
  REQUIRE(PartOne(input) == 2);
}

TEST_CASE("Part 1 (second test input)", TAGS) {
  auto input = ParseInput("inputs/08.test2.txt");
  REQUIRE(PartOne(input) == 6);
}

// TEST_CASE("Part 2", TAGS) {
//   auto input = ParseInput("inputs/07.test.txt", true);
//   REQUIRE(PartTwo(input) == 5905);
// }