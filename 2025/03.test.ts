import { expect, test } from "bun:test";
import { parseInput, part1, part2 } from "./03";

const input = `
987654321111111
811111111111119
234234234234278
818181911112111
`;

let ranges = parseInput(input);

test("part1", () => {
  expect(part1(ranges)).toBe(357);
});

test("part2", () => {
  expect(part2(ranges)).toBe(3121910778619);
});
