#include "common.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


//vector<string> ReadFile(string file_path) {
//  ifstream inFile;
//  inFile.open(file_path);
//
//  vector<string> ret;
//  string line;
//  while (std::getline(inFile, line)) {
//    std::istringstream ss(line);
//    ret.emplace_back(std::istream_iterator<int>(ss), std::istream_iterator<int>());
//  }
//
//  return ret;
//}

std::vector<std::string> ReadFile(string filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
      std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return lines;
}
