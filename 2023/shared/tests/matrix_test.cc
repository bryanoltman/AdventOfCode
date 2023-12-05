#include <catch2/catch.hpp>
#include <vector>

#include "shared/shared.h"

using namespace std;

static auto TEST_TAG = "CharMatrix";

TEST_CASE("Parses from lines input", TEST_TAG)
{
    vector<string> lines = { "123", "456", "789", "abc" };
    auto matrix = CharMatrix(lines);
    REQUIRE(matrix.Width() == 3);
    REQUIRE(matrix.Height() == 4);
}

TEST_CASE("Identifies non-diagonal neighbors", TEST_TAG)
{
    vector<string> lines = { "123", "456", "789", "abc" };
    auto matrix = CharMatrix(lines);

    auto five_neighbors = matrix.Neighbors(1, 1, false);
    REQUIRE(five_neighbors.size() == 4);
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('2'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('4'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('6'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('8'));
}

TEST_CASE("Identifies diagonal neighbors", TEST_TAG)
{
    vector<string> lines = { "123", "456", "789", "abc" };
    auto matrix = CharMatrix(lines);
    auto five_neighbors = matrix.Neighbors(1, 1);
    REQUIRE(five_neighbors.size() == 8);
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('1'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('2'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('3'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('4'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('6'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('7'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('8'));
    REQUIRE_THAT(five_neighbors, Catch::VectorContains('9'));
}