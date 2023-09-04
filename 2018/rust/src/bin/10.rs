use regex::Regex;

type Input = Vec<(Point, Point)>;

#[derive(Debug, PartialEq, Eq)]
struct Point {
    x: i32,
    y: i32,
}

#[aoc2018::main(10)]
fn main(input: &str) -> (String, usize) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_point_str(point_str: &str) -> Point {
    let (x_str, y_str) = point_str.split_once(",").unwrap();
    Point {
        x: x_str.trim().parse().unwrap(),
        y: y_str.trim().parse().unwrap(),
    }
}

fn parse_input(input: &str) -> Input {
    let line_regex = Regex::new(r"position=<(.*)> velocity=<(.*)>").unwrap();
    input
        .lines()
        .map(|l| {
            let captures = line_regex.captures(l).unwrap();
            (parse_point_str(&captures[1]), parse_point_str(&captures[2]))
        })
        .collect()
}

fn part1(input: &Input) -> String {
    "".to_string()
}

fn part2(input: &Input) -> usize {
    0
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT: &str = "position=< 9,  1> velocity=< 0,  2>
position=< 7,  0> velocity=<-1,  0>
position=< 3, -2> velocity=<-1,  1>
position=< 6, 10> velocity=<-2, -1>
position=< 2, -4> velocity=< 2,  2>
position=<-6, 10> velocity=< 2, -2>
position=< 1,  8> velocity=< 1, -1>
position=< 1,  7> velocity=< 1,  0>
position=<-3, 11> velocity=< 1, -2>
position=< 7,  6> velocity=<-1, -1>
position=<-2,  3> velocity=< 1,  0>
position=<-4,  3> velocity=< 2,  0>
position=<10, -3> velocity=<-1,  1>
position=< 5, 11> velocity=< 1, -2>
position=< 4,  7> velocity=< 0, -1>
position=< 8, -2> velocity=< 0,  1>
position=<15,  0> velocity=<-2,  0>
position=< 1,  6> velocity=< 1,  0>
position=< 8,  9> velocity=< 0, -1>
position=< 3,  3> velocity=<-1,  1>
position=< 0,  5> velocity=< 0, -1>
position=<-2,  2> velocity=< 2,  0>
position=< 5, -2> velocity=< 1,  2>
position=< 1,  4> velocity=< 2,  1>
position=<-2,  7> velocity=< 2, -2>
position=< 3,  6> velocity=<-1, -1>
position=< 5,  0> velocity=< 1,  0>
position=<-6,  0> velocity=< 2,  0>
position=< 5,  9> velocity=< 1, -2>
position=<14,  7> velocity=<-2,  0>
position=<-3,  6> velocity=< 2, -1>";

    #[test]
    fn parses_input() {
        let parsed_input = parse_input(&INPUT);
        assert_eq!(
            parsed_input[0],
            (Point { x: 9, y: 1 }, Point { x: 0, y: 2 })
        );
        assert_eq!(
            parsed_input.last().unwrap(),
            &(Point { x: -3, y: 6 }, Point { x: 2, y: -1 })
        );
    }

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(&INPUT)), "CABDFE");
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(&parse_input(&INPUT)), 15);
    }
}
