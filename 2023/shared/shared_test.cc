#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "shared/shared.h"

using namespace std;

TEST(MatrixTest, Parsing) {
  vector<string> lines = {"123", "456", "789", "abc"};
  auto matrix = CharMatrix(lines);
  EXPECT_EQ(matrix.Width(), 3);
  EXPECT_EQ(matrix.Height(), 4);
  EXPECT_EQ(matrix.chars[1][2], '6');
}

TEST(MatrixTest, NeighborPointsWithoutDiagonal) {
  vector<string> lines = {"123", "456", "789", "abc"};
  auto matrix = CharMatrix(lines);
  // 1,1 is
  auto neighbors = matrix.Neighbors(1, 1, false);
  EXPECT_EQ(neighbors, vector<char>{'1', '2', '3'});
}