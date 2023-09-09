use std::collections::VecDeque;

use regex::Regex;

#[derive(Debug, PartialEq, Eq)]
struct Input {
    num_players: usize,
    last_marble_value: usize,
}

#[aoc2018::main(09)]
fn main(input: &str) -> (usize, usize) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_input(input: &str) -> Input {
    let input_regex = Regex::new(r"(\d+) players; last marble is worth (\d+) points").unwrap();
    let captures = input_regex.captures(input).unwrap();
    let num_players = captures[1].parse::<usize>().unwrap();
    let last_marble_value = captures[2].parse::<usize>().unwrap();
    Input {
        num_players,
        last_marble_value,
    }
}

fn get_high_score(input: &Input) -> usize {
    let mut circle = VecDeque::with_capacity(input.last_marble_value);
    circle.push_back(0);
    let mut scores = vec![0; input.num_players];

    for i in 1..=input.last_marble_value {
        if i % 23 == 0 {
            for _ in 0..7 {
                let back = circle.pop_back().unwrap();
                circle.push_front(back);
            }
            scores[i % input.num_players] += circle.pop_front().unwrap() + i;
        } else {
            for _ in 0..2 {
                let front = circle.pop_front().unwrap();
                circle.push_back(front);
            }
            circle.push_front(i);
        }
    }

    *scores.iter().max().unwrap()
}

fn part1(input: &Input) -> usize {
    get_high_score(input)
}

fn part2(input: &Input) -> usize {
    let updated_input = Input {
        num_players: input.num_players,
        last_marble_value: input.last_marble_value * 100,
    };
    get_high_score(&updated_input)
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT1: &str = "10 players; last marble is worth 1618 points";
    static INPUT2: &str = "13 players; last marble is worth 7999 points";
    static INPUT3: &str = "17 players; last marble is worth 1104 points";
    static INPUT4: &str = "21 players; last marble is worth 6111 points";
    static INPUT5: &str = "30 players; last marble is worth 5807 points";

    #[test]
    fn parses_input() {
        assert_eq!(
            parse_input(INPUT1),
            Input {
                num_players: 10,
                last_marble_value: 1618
            }
        );
        assert_eq!(
            parse_input(INPUT2),
            Input {
                num_players: 13,
                last_marble_value: 7999
            }
        );

        assert_eq!(
            parse_input(INPUT3),
            Input {
                num_players: 17,
                last_marble_value: 1104
            }
        );

        assert_eq!(
            parse_input(INPUT4),
            Input {
                num_players: 21,
                last_marble_value: 6111
            }
        );

        assert_eq!(
            parse_input(INPUT5),
            Input {
                num_players: 30,
                last_marble_value: 5806
            }
        );
    }

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(INPUT1)), 8317);
        assert_eq!(part1(&parse_input(INPUT2)), 146373);
        assert_eq!(part1(&parse_input(INPUT3)), 2764);
        assert_eq!(part1(&parse_input(INPUT4)), 54718);
        assert_eq!(part1(&parse_input(INPUT5)), 37305);
    }

    // No test data given for part 2
}
