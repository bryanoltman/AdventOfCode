import { expect, test } from "bun:test";
import { parseInput, part1, part2 } from "./05";

const rawInput = `
3-5
10-14
16-20
12-18

1
5
8
11
17
32`;

let input = parseInput(rawInput);

test("part1", () => {
  expect(part1(input)).toBe(3);
});

test("part2", () => {
  expect(part2(input)).toBe(0);
});
