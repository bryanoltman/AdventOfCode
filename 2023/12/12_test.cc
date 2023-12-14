#include <catch2/catch.hpp>

#include "12/12.h"

using namespace std;

static auto TAGS = "Day 12";

TEST_CASE("ParseInput", TAGS) {
  auto input = ParseInput("inputs/12.test.txt");
  REQUIRE(input[0].spring_condition == "???.###");
  REQUIRE(input[0].arrangement == (vector<size_t>){1, 1, 3});
}

TEST_CASE("SpringMatchesArrangement", TAGS) {
  REQUIRE(SpringMatchesArrangement("#.#.###", {1, 1, 3}));
  REQUIRE(SpringMatchesArrangement(".#...#....###.", {1, 1, 3}));
  REQUIRE(SpringMatchesArrangement(".#.###.#.######", {1, 3, 1, 6}));
  REQUIRE(SpringMatchesArrangement("####.#...#...", {4, 1, 1}));
  REQUIRE(SpringMatchesArrangement("#....######..#####.", {1, 6, 5}));
  REQUIRE(SpringMatchesArrangement(".###.##....#", {3, 2, 1}));
  REQUIRE(!SpringMatchesArrangement(".###.##....#", {4, 2, 1}));
  REQUIRE(!SpringMatchesArrangement("#.#.###", {1, 1, 4}));
  REQUIRE(!SpringMatchesArrangement(".#.###.#.######", {2, 3, 1, 4}));
  REQUIRE(!SpringMatchesArrangement(".#...#....###.", {2, 1, 3}));
  REQUIRE(!SpringMatchesArrangement(".###.##.....", {3, 2, 1}));
}

TEST_CASE("NumPossibleStrings", TAGS) {
  // .###.##.#...
  // .###.##..#..
  // .###.##...#.
  // .###.##....#
  // .###..##.#..
  // .###..##..#.
  // .###..##...#
  // .###...##.#.
  // .###...##..#
  // .###....##.#
  REQUIRE(NumPossibleStrings("?###????????", {3, 2, 1}) == 10);
}

TEST_CASE("UnfoldRecord", TAGS) {
  SpringRecord input = {"???.###", {1, 1, 3}};
  auto unfolded = UnfoldRecord(input);
  REQUIRE(unfolded.spring_condition ==
          "???.###????.###????.###????.###????.###");
  REQUIRE(unfolded.arrangement ==
          (vector<size_t>){1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 3});
}

TEST_CASE("Part 1", TAGS) {
  auto input = ParseInput("inputs/12.test.txt");
  REQUIRE(PartOne(input) == 21);
}

TEST_CASE("Part 2", TAGS) {
  auto input = ParseInput("inputs/12.test.txt");
  REQUIRE(PartTwo(input) == 0);
}