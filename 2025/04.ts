export function parseInput(input: string): string[][] {
  return [];
}

export function part1(map: string[][]): number {
  return 0;
}

export function part2(map: string[][]): number {
  return 0;
}

const inputFile = Bun.file("./data/04.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
