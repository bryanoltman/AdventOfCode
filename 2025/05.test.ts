import { expect, test } from "bun:test";
import { mergeRanges, parseInput, part1, part2 } from "./05";

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

test("mergeRanges", () => {
  const ranges = [
    { beg: 0, end: 1 },
    { beg: 0, end: 2 },
    { beg: 2, end: 4 },
  ];
  expect(mergeRanges(ranges)).toEqual([{ beg: 0, end: 4 }]);
});

test("part2", () => {
  expect(part2(input)).toBe(14);
});
