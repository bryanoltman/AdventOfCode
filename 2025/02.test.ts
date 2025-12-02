import { expect, test } from "bun:test";
import { isIDInvalidPart2, parseInput, part1, part2 } from "./02";

const input = `11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124`;

let ranges = parseInput(input);

test("part1", () => {
  expect(part1(ranges)).toBe(1227775554);
});

test("part2", () => {
  // expect(isIDInvalidPart2("2121212124")).toBe(false);
  expect(part2(ranges)).toBe(4174379265);
});
