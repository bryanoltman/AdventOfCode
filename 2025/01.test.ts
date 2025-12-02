import { expect, test } from "bun:test";
import { parseInput, part1, part2 } from "./01";

const input = `
L68
L30
R48
L5
R60
L55
L1
L99
R14
L82
`;

let instructions = parseInput(input);

test("part1", () => {
  expect(part1(instructions)).toBe(3);
});

test("part2", () => {
  expect(
    part2([
      { direction: "L", steps: 50 },
      { direction: "R", steps: 100 },
      { direction: "R", steps: 1000 },
    ])
  ).toBe(12);
  expect(part2(instructions)).toBe(6);
});
