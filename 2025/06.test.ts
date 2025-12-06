import { expect, test } from "bun:test";
import { parseInput, part1, part2 } from "./06";

const rawInput = `
123 328  51 64 
 45 64  387 23 
  6 98  215 314
*   +   *   +  `;

let input = parseInput(rawInput);

test("part1", () => {
  expect(part1(input)).toBe(4277556);
});

test("part2", () => {
  expect(part2(input)).toBe(0);
});
