use std::collections::HashMap;

#[aoc2018::main(02)]
fn main(input: &str) -> (i32, String) {
    (part1(input), part2(input))
}

fn letters_count(string: &str) -> HashMap<char, u32> {
    let mut map = HashMap::<char, u32>::new();
    for character in string.chars() {
        let count = map.get(&character).unwrap_or(&0);
        map.insert(character, count + 1);
    }
    map
}

fn part1(input: &str) -> i32 {
    let mut twos = 0;
    let mut threes = 0;
    for line in input.lines() {
        let count_map = letters_count(line);
        if count_map.iter().any(|(_, v)| v == &2) {
            twos += 1;
        }
        if count_map.iter().any(|(_, v)| v == &3) {
            threes += 1;
        }
    }

    twos * threes
}

fn diff_positions(a: &str, b: &str) -> Vec<usize> {
    let mut positions = Vec::<usize>::new();
    for (i, (ca, cb)) in a.chars().zip(b.chars()).enumerate() {
        if ca != cb {
            positions.push(i);
        }
    }
    return positions;
}

fn part2(input: &str) -> String {
    let lines: Vec<&str> = input.lines().collect();

    for i in 0..lines.len() {
        for j in (i + 1)..lines.len() {
            let a = lines[i];
            let b = lines[j];
            let diffs = diff_positions(a, b);
            if diffs.len() != 1 {
                continue;
            }
            let mut str_a = a.to_string();
            str_a.remove(diffs[0]);
            return str_a;
        }
    }

    panic!("no match found");
}

#[cfg(test)]
mod tests {
    use super::*;

    static INPUT1: &str = "abcdef
bababc
abbcde
abcccd
aabcdd
abcdee
ababab";

    static INPUT2: &str = "abcde
fghij
klmno
pqrst
fguij
axcye
wvxyz";

    #[test]
    fn test_part1() {
        assert_eq!(part1(INPUT1), 12);
    }

    #[test]
    fn test_part2() {
        assert_eq!(part2(INPUT2), "fgij")
    }
}
