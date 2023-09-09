use std::collections::HashSet;

#[aoc2018::main(01)]
fn main(input: &str) -> (i32, i32) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_input(input: &str) -> Vec<i32> {
    input
        .lines()
        .map(|s| s.trim())
        .map(|s| s.parse().unwrap())
        .collect()
}

fn part1(input: &[i32]) -> i32 {
    input.iter().sum()
}

fn part2(input: &[i32]) -> i32 {
    let mut seen_freqs = HashSet::<i32>::new();
    let mut freq = 0;
    for freq_change in input.iter().cycle() {
        freq += freq_change;
        if seen_freqs.contains(&freq) {
            return freq;
        }

        seen_freqs.insert(freq);
    }

    panic!("We escaped the loop without returning 😱");
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT: &str = "+1
-2
+3
+1";

    #[test]
    fn parses_input() {
        assert_eq!(parse_input(INPUT), vec![1, -2, 3, 1]);
    }

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(INPUT)), 3);
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(&parse_input(INPUT)), 2);
    }
}
