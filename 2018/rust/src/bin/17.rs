use std::ops::Range;

#[derive(Debug, PartialEq, Eq)]
struct Vein {
    x: Range<usize>,
    y: Range<usize>,
}

#[derive(Debug, PartialEq, Eq)]
struct Input {
    veins: Vec<Vein>,
}

const WATER_SOURCE_X: usize = 500;

#[aoc2018::main(17)]
fn main(input: &str) -> (i64, i64) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_maybe_range_string(input: &str) -> Range<usize> {
    let trimmed = input.trim();
    let (_, range_str) = trimmed.split_once('=').unwrap();
    if !range_str.contains("..") {
        let start_and_finish = range_str.parse::<usize>().unwrap();
        start_and_finish..start_and_finish
    } else {
        let (start_str, end_str) = range_str.split_once("..").unwrap();
        start_str.parse().unwrap()..end_str.parse().unwrap()
    }
}

fn parse_line(line: &str) -> Vein {
    let (str1, str2) = line.split_once(',').unwrap();
    let range1 = parse_maybe_range_string(str1);
    let range2 = parse_maybe_range_string(str2);

    if str1.starts_with('x') {
        Vein {
            x: range1,
            y: range2,
        }
    } else {
        Vein {
            x: range2,
            y: range1,
        }
    }
}

fn parse_input(input: &str) -> Input {
    Input {
        veins: input.lines().map(parse_line).collect(),
    }
}

fn part1(input: &Input) -> i64 {
    0
}

fn part2(input: &Input) -> i64 {
    0
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT: &str = "x=495, y=2..7
y=7, x=495..501
x=501, y=3..7
x=498, y=2..4
x=506, y=1..2
x=498, y=10..13
x=504, y=10..13
y=13, x=498..504";

    #[test]
    fn parses_input() {
        let parsed_input = parse_input(INPUT);
        assert_eq!(
            parsed_input.veins[0],
            Vein {
                x: 495..495,
                y: 2..7
            }
        );
        assert_eq!(
            parsed_input.veins[1],
            Vein {
                x: 495..501,
                y: 7..7
            }
        );
    }

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(INPUT)), 57);
    }
}
