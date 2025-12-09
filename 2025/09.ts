type Coord2D = {
  x: number;
  y: number;
};

export function parseInput(input: string): Coord2D[] {
  return input
    .split("\n")
    .map((l) => l.trim())
    .filter((l) => l.length > 0)
    .map((l) => {
      const parts = l.split(",");
      return {
        x: Number(parts[0]!),
        y: Number(parts[1]!),
      };
    });
}

export function part1(input: Coord2D[]): number {
  return 0;
}

export function part2(input: Coord2D[]): number {
  return 0;
}

const inputFile = Bun.file("./data/09.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
