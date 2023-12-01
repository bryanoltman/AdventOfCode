#include <iostream>

#include "day01.hpp"
#include "common.hpp"

std::vector<std::string> ReadInput(std::string file_path) {
  return ReadFile(file_path);
}

bool IsAsciiNumber(char c) {
  return c >= 48 && c <= 57;
}

char FirstDigitChar(string str) {
  for(char& c : str) {
    if (IsAsciiNumber(c)) {
      return c;
    }
  }
  
  cout << "No digit found in " << str << endl;
  exit(-1);
}

char LastDigitChar(string str) {
  reverse(str.begin(), str.end());
  for(char& c : str) {
    if (IsAsciiNumber(c)) {
      return c;
    }
  }
  
  cout << "No digit found in " << str << endl;
  exit(-1);
}


uint32_t PartOne(vector<string> input) {
  uint32_t acc = 0;
  for (string& str : input) {
    auto first_digit = FirstDigitChar(str);
    auto last_digit = LastDigitChar(str);
    string digits_str("");
    digits_str.push_back(first_digit);
    digits_str.push_back(last_digit);
    auto number = stoi(digits_str);
    acc += number;
  }
  
  return acc;
}

