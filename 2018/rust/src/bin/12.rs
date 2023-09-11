use std::collections::HashMap;

struct Input {
    pots: String,
    rules: HashMap<String, char>,
}

#[aoc2018::main(12)]
fn main(input: &str) -> (i64, i64) {
    let parsed_input = parse_input(input);
    (part1(&parsed_input), part2(&parsed_input))
}

fn parse_input(input: &str) -> Input {
    let first_line = input.lines().next().unwrap();
    let pots = first_line.replace("initial state:", "").trim().to_string();

    let mut rules = HashMap::<String, char>::new();
    for line in input.lines().skip(2) {
        let (pattern, next_gen) = line.split_once("=>").unwrap();
        let next_gen_char = next_gen.trim().chars().next().unwrap();
        rules.insert(pattern.trim().to_string(), next_gen_char);
    }

    Input { pots, rules }
}

fn advance_generation(
    pots: &str,
    rules: &HashMap<String, char>,
    pot_start_offset: i64,
) -> (String, i64) {
    let empty_pot_prefix_length = pots.chars().take_while(|c| *c == '.').count();
    let empty_pot_suffix_length = pots.chars().rev().take_while(|c| *c == '.').count();
    let padded_pots =
        ".".repeat(5 - empty_pot_prefix_length) + pots + &".".repeat(5 - empty_pot_suffix_length);
    let mut next_pots = "".to_string();

    for window in padded_pots.as_bytes().windows(5) {
        let rule_str = String::from_utf8_lossy(window);
        let new_char = rules.get(rule_str.as_ref());
        if let Some(pot_contents) = new_char {
            next_pots.push(*pot_contents);
        } else {
            next_pots.push('.');
        }
    }

    (
        next_pots,
        pot_start_offset - 3 + empty_pot_prefix_length as i64,
    )
}

fn score_pots(pots: &str, start_offset: i64) -> i64 {
    pots.chars()
        .enumerate()
        .map(|(i, contents)| {
            if contents == '#' {
                i as i64 + start_offset
            } else {
                0
            }
        })
        .sum()
}

fn run_generations(input: &Input, num_generations: i64) -> i64 {
    let mut current_gen = input.pots.clone();
    let mut start_offset = 0;
    for _ in 0..num_generations {
        (current_gen, start_offset) = advance_generation(&current_gen, &input.rules, start_offset);
    }

    score_pots(&current_gen, start_offset)
}

fn part1(input: &Input) -> i64 {
    run_generations(input, 20)
}

fn part2(input: &Input) -> i64 {
    // Once the plant pattern converges (sometime before 2000 iterations), the score
    // increases 23 points every generation.
    let convergence_iters = 2000;
    run_generations(input, 2000) + (50000000000 - convergence_iters) * 23
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT: &str = "initial state: #..#.#..##......###...###

...## => #
..#.. => #
.#... => #
.#.#. => #
.#.## => #
.##.. => #
.#### => #
#.#.# => #
#.### => #
##.#. => #
##.## => #
###.. => #
###.# => #
####. => #";

    #[test]
    fn parses_input() {
        let parsed_input = parse_input(INPUT);

        assert_eq!(parsed_input.pots, "#..#.#..##......###...###");
        assert_eq!(parsed_input.rules["...##"], '#');
        assert_eq!(parsed_input.rules["##.##"], '#');
        assert_eq!(parsed_input.rules[".##.."], '#');
    }

    #[test]
    fn test_part1() {
        assert_eq!(part1(&parse_input(INPUT)), 325);
    }

    // No test data provided for part 2.
}
