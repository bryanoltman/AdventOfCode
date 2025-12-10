import { expect, test } from "bun:test";
import { parseInput, part1, part2 } from "./10";

const rawInput = `[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
`;

let input = parseInput(rawInput);

test("part1", () => {
  expect(part1(input)).toBe(7);
});

test("part2", () => {
  expect(part2(input)).toBe(0);
});
