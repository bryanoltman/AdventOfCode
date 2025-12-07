type Grid = string[][];

export function parseInput(input: string): Grid {
  return input.split("\n").map((l) => l.split(""));
}

export function part1(input: Grid): number {
  let numSplits = 0;
  let startIndex = input[0]!.indexOf("S");
  let currentRowIndexes = new Set<number>();
  currentRowIndexes.add(startIndex);
  for (let i = 0; i < input.length - 1; i++) {
    let nextRowIndexes = new Set<number>();
    let nextRow = input[i + 1]!;
    for (const currentRowIndex of currentRowIndexes) {
      if (nextRow[currentRowIndex] == ".") {
        nextRowIndexes.add(currentRowIndex);
      } else if (nextRow[currentRowIndex] == "^") {
        nextRowIndexes.add(currentRowIndex + 1);
        nextRowIndexes.add(currentRowIndex - 1);
        numSplits += 1;
      }
    }
    currentRowIndexes = nextRowIndexes;
  }

  return numSplits;
}

export function part2(input: Grid): number {
  return 0;
}

const inputFile = Bun.file("./data/07.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
