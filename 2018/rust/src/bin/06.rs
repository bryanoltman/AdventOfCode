use std::collections::HashSet;

type Input = Vec<Point>;

#[derive(Hash, Debug, PartialEq, Eq, Clone, Copy)]
struct Point {
    x: i32,
    y: i32,
}

fn manhattan_distance(a: Point, b: Point) -> u32 {
    ((a.x - b.x).abs() + (a.y - b.y).abs()) as u32
}

#[aoc2018::main(06)]
fn main(input: &str) -> (usize, usize) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_line(line: &str) -> Point {
    let (x_str, y_str) = line.split_once(",").unwrap();
    Point {
        x: x_str.trim().parse().unwrap(),
        y: y_str.trim().parse().unwrap(),
    }
}

fn parse_input(input: &str) -> Input {
    input.lines().map(|l| parse_line(l)).collect()
}

fn part1(input: &Input) -> usize {
    let max_x = input.iter().map(|p| p.x).max().unwrap() + 1;
    let max_y = input.iter().map(|p| p.y).max().unwrap() + 1;
    let mut grid = vec![vec![-1; max_x as usize]; max_y as usize];

    println!("filling grid");
    for y in 0..max_y {
        for x in 0..max_x {
            let current_point = Point { x, y };
            let mut distances: Vec<(usize, u32)> = input
                .iter()
                .enumerate()
                .map(|(i, p)| (i, manhattan_distance(*p, current_point)))
                .collect();
            distances.sort_by_key(|d| d.1);
            // Points with no closest input coordinate (i.e., two or more inputs
            // are equidistant) remain -1. Otherwise, they are assigned the
            // index of the input coordinate.
            if distances[0].1 < distances[1].1 {
                grid[y as usize][x as usize] = distances[0].0 as i32;
            }
        }
    }

    println!("filled grid");

    println!("removing non-finite areas");
    // Start with the full list, we'll remove the coordinates whose indicies
    // we find along the edges of the grid
    let mut finite_areas: HashSet<Point> = HashSet::from_iter(input.iter().cloned());
    for y in 0..max_y {
        let min_index = grid[y as usize][0];
        if min_index != -1 {
            finite_areas.remove(&input[min_index as usize]);
        }
        let max_index = grid[y as usize][(max_x - 1) as usize];
        if max_index != -1 {
            finite_areas.remove(&input[max_index as usize]);
        }
    }

    for x in 0..max_x {
        let min_index = grid[0][x as usize];
        if min_index != -1 {
            finite_areas.remove(&input[min_index as usize]);
        }
        let max_index = grid[(max_y - 1) as usize][x as usize];
        if max_index != -1 {
            finite_areas.remove(&input[max_index as usize]);
        }
    }
    println!("removed non-finite areas");

    println!("computing largest area");
    let flattened_grid = grid.into_iter().flatten().collect::<Vec<i32>>();
    let mut max_size = 0;
    for coord in finite_areas {
        let input_index = input.iter().position(|p| *p == coord).unwrap();
        let num_points = flattened_grid
            .iter()
            .filter(|idx| **idx == input_index as i32)
            .count();
        if num_points > max_size {
            max_size = num_points;
        }
    }
    println!("computed largest area");

    max_size
}

fn part2(input: &Input) -> usize {
    let max_x = input.iter().map(|p| p.x).max().unwrap() + 1;
    let max_y = input.iter().map(|p| p.y).max().unwrap() + 1;
    let mut grid = vec![vec![0; max_x as usize]; max_y as usize];
    for y in 0..max_y {
        for x in 0..max_x {
            let current_point = Point { x, y };
            let distance_sum: u32 = input
                .iter()
                .map(|p| manhattan_distance(current_point, *p))
                .sum();
            grid[y as usize][x as usize] = distance_sum as i32;
        }
    }

    grid.into_iter()
        .flatten()
        // Note: for testing, we should compare the sum against 32 instead
        // of 10000
        .filter(|distance_sum| *distance_sum < 10000)
        .count()
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
    fn parses_input() {
        let parsed = parse_input(&INPUT);
        assert_eq!(parsed.len(), 6);
        assert_eq!(parsed[0], Point { x: 1, y: 1 });
        assert_eq!(parsed[1], Point { x: 1, y: 6 });
        assert_eq!(parsed[2], Point { x: 8, y: 3 });
        assert_eq!(parsed[3], Point { x: 3, y: 4 });
        assert_eq!(parsed[4], Point { x: 5, y: 5 });
        assert_eq!(parsed[5], Point { x: 8, y: 9 });
    }

    #[test]
    fn computes_manhattan_distance() {
        assert_eq!(
            manhattan_distance(Point { x: 1, y: 1 }, Point { x: 2, y: 2 }),
            2,
        );
        assert_eq!(
            manhattan_distance(Point { x: 1, y: 1 }, Point { x: 1, y: 4 }),
            3,
        );
        assert_eq!(
            manhattan_distance(Point { x: 1, y: 4 }, Point { x: 1, y: 1 }),
            3,
        );
        assert_eq!(
            manhattan_distance(Point { x: -1, y: -1 }, Point { x: 1, y: 1 }),
            4,
        );
    }

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(&INPUT)), 17);
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(&parse_input(&INPUT)), 16);
    }
}
