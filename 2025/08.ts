type Coord3D = {
  x: number;
  y: number;
  z: number;
};

export function parseInput(input: string): Coord3D[] {
  return input.split("\n").map((l) => {
    const parts = l.split(",");
    return {
      x: Number(parts[0]!),
      y: Number(parts[1]!),
      z: Number(parts[2]!),
    };
  });
}

export function part1(input: Coord3D[]): number {
  return 0;
}

export function part2(input: Coord3D[]): number {
  return 0;
}

const inputFile = Bun.file("./data/07.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
