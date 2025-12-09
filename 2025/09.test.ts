import { expect, test } from "bun:test";
import { parseInput, part1, part2 } from "./09";

const rawInput = `7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3
`;

let input = parseInput(rawInput);

test("part1", () => {
  expect(part1(input)).toBe(50);
});

test("part2", () => {
  expect(part2(input)).toBe(0);
});
