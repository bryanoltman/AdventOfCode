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
        let next_step = *incomplete_keys
            .iter()
            .find(|k| !incomplete_steps.values().any(|set| set.contains(k)))
            .unwrap();
        executed_steps.push(next_step);
        incomplete_steps.remove(&next_step);
        incomplete_keys.remove(&next_step);
    }

    executed_steps.iter().collect()
}

fn time_for_step(step: char) -> u32 {
    60 + (step as u32 - 64)
}

fn part2(input: &Input) -> usize {
    let mut passed_seconds = 0;
    let mut incomplete_steps: HashMap<char, HashSet<char>> = input.clone();
    let mut incomplete_keys = input.keys().cloned().collect::<BTreeSet<char>>();
    let mut executed_steps = Vec::<char>::new();

    // 4 workers, represented as a tuple of (current step, seconds remaining on step)
    // 'a' is used as a dummy value
    let mut workers = [('a', 0), ('a', 0), ('a', 0), ('a', 0), ('a', 0)];
    let mut active_steps = HashSet::<char>::new();

    while !incomplete_keys.is_empty() {
        for worker in workers.iter_mut() {
            if worker.1 == 0 {
                if worker.0 != 'a' {
                    executed_steps.push(worker.0);
                    incomplete_keys.remove(&worker.0);
                    incomplete_steps.remove(&worker.0);
                    active_steps.remove(&worker.0);
                }
                let maybe_next_step = incomplete_keys.iter().find(|k| {
                    !active_steps.contains(k)
                        && !incomplete_steps.values().any(|set| set.contains(k))
                });
                if maybe_next_step.is_none() {
                    continue;
                }

                let next_step = *maybe_next_step.unwrap();
                active_steps.insert(next_step);
                active_steps.insert(next_step);
                worker.0 = next_step;
                worker.1 = time_for_step(next_step);
            }

            worker.1 -= 1
        }

        passed_seconds += 1
    }

    passed_seconds - 1
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
        let parsed_input = parse_input(INPUT);
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
        assert_eq!(part1(&parse_input(INPUT)), "CABDFE");
    }

    #[test]
    fn test_time_for_step() {
        assert_eq!(time_for_step('A'), 61);
        assert_eq!(time_for_step('B'), 62);
        assert_eq!(time_for_step('Z'), 86);
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(&parse_input(INPUT)), 15);
    }
}
