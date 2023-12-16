#include <iostream>

#include "16/16.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Input input = ParseInput("inputs/16.txt");

    cout << "Part One: " << PartOne(input) << endl;
    cout << "Part Two: " << PartTwo(input) << endl;

    return 0;
}
