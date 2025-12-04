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

let map = parseInput(input);

test("part1", () => {
  expect(part1(map)).toBe(13);
});

test("part2", () => {
  expect(part2(map)).toBe(0);
});
