#include <catch2/catch.hpp>

#include "11/11.h"

using namespace std;

static auto TAGS = "Day 11";

TEST_CASE("FindGalaxies", TAGS)
{
    auto input = ParseInput("inputs/11.test.txt");
    auto galaxies = FindGalaxies(input);
    REQUIRE(galaxies.size() == 9);
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(3, 0)) != galaxies.end());
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(7, 1)) != galaxies.end());
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(0, 2)) != galaxies.end());
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(6, 4)) != galaxies.end());
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(1, 5)) != galaxies.end());
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(9, 6)) != galaxies.end());
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(7, 8)) != galaxies.end());
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(0, 9)) != galaxies.end());
    // REQUIRE(find(galaxies.begin(), galaxies.end(), make_pair(4, 9)) != galaxies.end());
}

TEST_CASE("EmptyRows", TAGS)
{
    auto input = ParseInput("inputs/11.test.txt");
    auto empty_rows = EmptyRows(input);
    REQUIRE(empty_rows.size() == 2);
    REQUIRE(empty_rows.find(3) != empty_rows.end());
    REQUIRE(empty_rows.find(7) != empty_rows.end());
}

TEST_CASE("EmptyColumns", TAGS)
{
    auto input = ParseInput("inputs/11.test.txt");
    auto empty_cols = EmptyColumns(input);
    REQUIRE(empty_cols.size() == 3);
    REQUIRE(empty_cols.find(2) != empty_cols.end());
    REQUIRE(empty_cols.find(5) != empty_cols.end());
    REQUIRE(empty_cols.find(8) != empty_cols.end());
}

TEST_CASE("DistanceBetweenGalaxies", TAGS)
{
    auto input = ParseInput("inputs/11.test.txt");
    auto a = make_pair(1, 5);
    auto b = make_pair(4, 9);
    auto empty_rows = EmptyRows(input);
    auto empty_cols = EmptyColumns(input);

    REQUIRE(DistanceBetweenGalaxies(input, a, b, empty_rows, empty_cols, 2) == 9);
}

TEST_CASE("Part 1", TAGS)
{
    auto input = ParseInput("inputs/11.test.txt");
    REQUIRE(PartOne(input) == 374);
}

// AoC did not give a solution for part 2 with an expansion rate of 1000000.
// This test was used for checking the solutions provided for expansion rates
// of 10 and 100.
TEST_CASE("ComputeDistances", TAGS)
{
    auto input = ParseInput("inputs/11.test.txt");
    REQUIRE(ComputeDistances(input, 10) == 1030);
    REQUIRE(ComputeDistances(input, 100) == 8410);
}