#include <cstddef>
#include <iostream>

#include "06/06.h"

using namespace std;

size_t PartOne(Input input) {
  vector<size_t> race_win_ways;
  for (auto &race : input) {
    auto wins = 0;
    for (auto hold_duration = 0; hold_duration <= race.duration;
         hold_duration++) {
      auto remaining_race_time = race.duration - hold_duration;
      // Picks up 1 ml/ms per second held
      auto speed = hold_duration;

      auto distance = remaining_race_time * speed;
      if (distance > race.distance) {
        wins++;
      }
    }

    race_win_ways.push_back(wins);
  }

  auto ret = 0;
  for (auto win_way : race_win_ways) {
    if (ret == 0) {
      ret = win_way;
    } else {
      ret *= win_way;
    }
  }

  return ret;
}

size_t PartTwo(Input input) {
  auto wins = 0;
  auto race = input[0];
  for (auto hold_duration = 0; hold_duration <= race.duration;
       hold_duration++) {
    auto remaining_race_time = race.duration - hold_duration;
    // Picks up 1 ml/ms per second held
    auto speed = hold_duration;

    auto distance = remaining_race_time * speed;
    if (distance > race.distance) {
      wins++;
    }
  }

  return wins;
}