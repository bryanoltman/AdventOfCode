import { expect, test } from "bun:test";
import { parseInput, part1, part2 } from "./04";

const input = `
..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
`;

let ranges = parseInput(input);

test("part1", () => {
  expect(part1(ranges)).toBe(0);
});

test("part2", () => {
  expect(part2(ranges)).toBe(0);
});
