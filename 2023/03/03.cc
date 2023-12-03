#include "shared/shared.h"

#include <iostream>

using namespace std;

CharMatrix ReadInput(string file_path)
{
    auto lines = ReadLines(file_path);
    return CharMatrix(lines);
}

int main(int argc, char const *argv[])
{
    auto input = ReadInput("inputs/03.test.txt");
    input.Print();

    return 0;
}
