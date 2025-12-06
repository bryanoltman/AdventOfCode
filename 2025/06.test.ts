import { expect, test } from "bun:test";
import { parseInputPart1, parseInputPart2, part1, part2 } from "./06";

const rawInput = `
123 328  51 64 
 45 64  387 23 
  6 98  215 314
*   +   *   +  `;

let inputPart1 = parseInputPart1(rawInput);
let inputPart2 = parseInputPart2(rawInput);

test("part1", () => {
  expect(part1(inputPart1)).toBe(4277556);
});

test("part2", () => {
  expect(part2(inputPart2)).toBe(3263827);
});
