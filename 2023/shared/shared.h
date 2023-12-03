#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> ReadLines(std::string file_path)
{
    vector<string> lines;
    ifstream file(file_path);

    if (!file.is_open()) {
        cerr << "Unable to open file: " << file_path << endl;
        exit(-1);
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    return lines;
}