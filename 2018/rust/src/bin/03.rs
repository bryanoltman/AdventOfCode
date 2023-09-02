use std::collections::HashMap;

#[derive(Hash, Debug, PartialEq, Eq)]
struct Point {
    x: i32,
    y: i32,
}

#[derive(Hash, Debug, PartialEq, Eq)]
struct Size {
    width: u32,
    height: u32,
}

#[derive(Hash, Debug, PartialEq, Eq)]
struct Rect {
    origin: Point,
    size: Size,
}

#[derive(Hash, Debug, PartialEq, Eq)]
struct Claim {
    id: i32,
    rect: Rect,
}

impl Rect {
    fn covered_coords(&self) -> Vec<Point> {
        let mut ret = Vec::<Point>::new();
        for x in self.origin.x..(self.origin.x + (self.size.width as i32)) {
            for y in self.origin.y..(self.origin.y + (self.size.height as i32)) {
                ret.push(Point { x, y })
            }
        }

        ret
    }
}

#[aoc2018::main(03)]
fn main(input: &str) -> (usize, i32) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_line(line: &str) -> Claim {
    let (id_input, coords) = line.split_once("@").unwrap();
    let (origin_str, size_str) = coords.split_once(":").unwrap();
    let (x_str, y_str) = origin_str.split_once(",").unwrap();
    let (width_str, height_str) = size_str.split_once("x").unwrap();
    let mut id_str = id_input.to_string();
    id_str.remove(0);

    Claim {
        id: id_str.trim().parse().unwrap(),
        rect: Rect {
            origin: Point {
                x: x_str.trim().parse().unwrap(),
                y: y_str.trim().parse().unwrap(),
            },
            size: Size {
                width: width_str.trim().parse().unwrap(),
                height: height_str.trim().parse().unwrap(),
            },
        },
    }
}

fn parse_input(input: &str) -> Vec<Claim> {
    input.lines().map(|l| parse_line(l)).collect()
}

fn part1(input: &Vec<Claim>) -> usize {
    let mut coord_count: HashMap<Point, u32> = HashMap::<Point, u32>::new();
    for claim in input {
        for coord in claim.rect.covered_coords() {
            let count = coord_count.get(&coord).unwrap_or(&0);
            coord_count.insert(coord, *count + 1);
        }
    }

    coord_count.values().filter(|v| **v >= 2).count()
}

fn part2(input: &Vec<Claim>) -> i32 {
    let mut grid = vec![vec![0; 2000]; 2000];
    let mut claims_map: HashMap<i32, &Claim> = input.iter().map(|c| (c.id, c)).collect();
    for claim in input {
        for point in claim.rect.covered_coords() {
            let value = grid[point.y as usize][point.x as usize];
            if value != 0 {
                claims_map.remove(&value);
                claims_map.remove(&claim.id);
            }
            grid[point.y as usize][point.x as usize] = claim.id;
        }
    }

    if claims_map.len() != 1 {
        panic!("More than one claim satisfies condition");
    }

    *claims_map.keys().next().unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT: &str = "#1 @ 1,3: 4x4
#2 @ 3,1: 4x4
#3 @ 5,5: 2x2";

    #[test]
    fn parses_input() {
        assert_eq!(
            parse_input("#1 @ 1,3: 4x4"),
            vec![Claim {
                id: 1,
                rect: Rect {
                    origin: Point { x: 1, y: 3 },
                    size: Size {
                        width: 4,
                        height: 4
                    }
                }
            }]
        );
    }

    #[test]
    fn covered_coords_test() {
        let rect = Rect {
            origin: Point { x: 1, y: 3 },
            size: Size {
                width: 4,
                height: 4,
            },
        };
        let coords = rect.covered_coords();
        assert_eq!(coords.len(), 16);
        assert!(coords.contains(&Point { x: 1, y: 3 }));
        assert!(coords.contains(&Point { x: 1, y: 4 }));
        assert!(coords.contains(&Point { x: 1, y: 5 }));
        assert!(coords.contains(&Point { x: 1, y: 6 }));
        assert!(coords.contains(&Point { x: 2, y: 3 }));
        assert!(coords.contains(&Point { x: 2, y: 4 }));
        assert!(coords.contains(&Point { x: 2, y: 5 }));
        assert!(coords.contains(&Point { x: 2, y: 6 }));
        assert!(coords.contains(&Point { x: 3, y: 3 }));
        assert!(coords.contains(&Point { x: 3, y: 4 }));
        assert!(coords.contains(&Point { x: 3, y: 5 }));
        assert!(coords.contains(&Point { x: 3, y: 6 }));
        assert!(coords.contains(&Point { x: 4, y: 3 }));
        assert!(coords.contains(&Point { x: 4, y: 4 }));
        assert!(coords.contains(&Point { x: 4, y: 5 }));
        assert!(coords.contains(&Point { x: 4, y: 6 }));
    }

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(&INPUT)), 4);
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(&parse_input(&INPUT)), 3);
    }
}
