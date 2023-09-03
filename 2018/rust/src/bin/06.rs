type Input = Vec<Point>;

#[derive(Hash, Debug, PartialEq, Eq)]
struct Point {
    x: i32,
    y: i32,
}

#[aoc2018::main(06)]
fn main(input: &str) -> (i32, i32) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_input(input: &str) -> Input {
    vec![]
}

fn part1(input: &Input) -> i32 {
    0
}

fn part2(input: &Input) -> i32 {
    0
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT: &str = "1, 1
1, 6
8, 3
3, 4
5, 5
8, 9";

    #[test]
    fn parses_input() {}

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(&INPUT)), 17);
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(&parse_input(&INPUT)), 0);
    }
}
