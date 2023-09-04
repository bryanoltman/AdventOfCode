use std::collections::{BTreeSet, HashMap, HashSet};

use regex::Regex;

type Input = HashMap<char, HashSet<char>>;

#[aoc2018::main(07)]
fn main(input: &str) -> (String, usize) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_input(input: &str) -> Input {
    let line_regex = Regex::new(r"Step (\w) must be finished before step (\w) can begin").unwrap();
    let chars = input
        .lines()
        .map(|line| {
            let captures = line_regex.captures(line).unwrap();
            (
                captures[1].chars().next().unwrap(),
                captures[2].chars().next().unwrap(),
            )
        })
        .collect::<Vec<(char, char)>>();

    let mut ret = Input::new();
    for (a, b) in chars {
        ret.entry(a).or_insert(HashSet::new()).insert(b);
        ret.entry(b).or_insert(HashSet::new());
    }

    ret
}

fn part1(input: &Input) -> String {
    let mut incomplete_steps: HashMap<char, HashSet<char>> = input.clone();

    let mut incomplete_keys = input.keys().cloned().collect::<BTreeSet<char>>();

    let mut executed_steps = Vec::<char>::new();
    while !incomplete_keys.is_empty() {
        let next_step = incomplete_keys
            .iter()
            .find(|k| !incomplete_steps.values().any(|set| set.contains(k)))
            .unwrap()
            .clone();
        executed_steps.push(next_step);
        incomplete_steps.remove(&next_step);
        incomplete_keys.remove(&next_step);
    }

    executed_steps.iter().collect()
}

fn part2(input: &Input) -> usize {
    0
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT: &str = "Step C must be finished before step A can begin.
Step C must be finished before step F can begin.
Step A must be finished before step B can begin.
Step A must be finished before step D can begin.
Step B must be finished before step E can begin.
Step D must be finished before step E can begin.
Step F must be finished before step E can begin.";

    #[test]
    fn parses_input() {
        let parsed_input = parse_input(&INPUT);
        assert_eq!(
            parsed_input[&'C'],
            HashSet::from_iter(vec!['A', 'F'].into_iter())
        );
        assert_eq!(
            parsed_input[&'A'],
            HashSet::from_iter(vec!['B', 'D'].into_iter())
        );
        assert_eq!(
            parsed_input[&'B'],
            HashSet::from_iter(vec!['E'].into_iter())
        );
        assert_eq!(
            parsed_input[&'D'],
            HashSet::from_iter(vec!['E'].into_iter())
        );
        assert_eq!(
            parsed_input[&'F'],
            HashSet::from_iter(vec!['E'].into_iter())
        );
        assert_eq!(parsed_input[&'E'], HashSet::new());
    }

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(&INPUT)), "CABDFE");
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(&parse_input(&INPUT)), 16);
    }
}
