#include <iostream>

#include "15/15.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Input input = ParseInput("inputs/15.txt");

    cout << "Part One: " << PartOne(input) << endl;
    cout << "Part Two: " << PartTwo(input) << endl;

    return 0;
}
