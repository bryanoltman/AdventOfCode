use std::collections::HashSet;

type Input = str;

#[aoc2018::main(05)]
fn main(input: &str) -> (u32, u32) {
    let parsed_input = parse_input(input);
    (part1(parsed_input), part2(parsed_input))
}

fn parse_input(input: &str) -> &Input {
    input
}

fn react_polymer(input: &str) -> String {
    let mut has_reacted = true;
    let mut current_polymer = input.to_string();
    while has_reacted {
        let mut next_polymer = "".to_string();
        has_reacted = false;
        let mut i = 0;
        while i < current_polymer.len() {
            let current_char = current_polymer.as_bytes()[i] as char;
            if i == current_polymer.len() - 1 {
                next_polymer.push(current_char);
                break;
            }

            let next_char = current_polymer.as_bytes()[i + 1] as char;
            if current_char.is_lowercase()
                && next_char.is_uppercase()
                && next_char.to_ascii_lowercase() == current_char
                || current_char.is_uppercase()
                    && next_char.is_lowercase()
                    && next_char.to_ascii_uppercase() == current_char
            {
                has_reacted = true;
                i += 2;
                continue;
            }

            next_polymer.push(current_char);
            i += 1;
        }

        current_polymer = next_polymer;
    }

    current_polymer
}

fn part1(input: &Input) -> u32 {
    react_polymer(input).len() as u32
}

fn part2(input: &Input) -> u32 {
    let all_chars: HashSet<char> = input.chars().map(|c| c.to_ascii_lowercase()).collect();
    let mut min_length = u32::MAX;
    for c in all_chars {
        let modified_polymer = input
            .to_string()
            .replace(&c.to_string(), "")
            .replace(&c.to_ascii_uppercase().to_string(), "");
        let reacted_length = react_polymer(&modified_polymer).len() as u32;
        if reacted_length < min_length {
            min_length = reacted_length;
        }
    }

    min_length
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT: &str = "dabAcCaCBAcCcaDA";

    #[test]
    fn test_part1() {
        assert_eq!(part1(parse_input(INPUT)), 10);
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(parse_input(INPUT)), 4);
    }
}
