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
  let largestArea = 0;
  for (let i = 0; i < input.length; i++) {
    const a = input[i]!;
    for (let j = i + 1; j < input.length; j++) {
      const b = input[j]!;
      const width = Math.abs(b.x - a.x) + 1;
      const height = Math.abs(b.y - a.y) + 1;
      const area = width * height;
      if (area > largestArea) {
        largestArea = area;
      }
    }
  }

  return largestArea;
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
