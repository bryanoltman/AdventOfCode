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
  let startIndex = input[0]!.indexOf("S");
  let currentRowIndexCounts = new Map<number, number>();
  currentRowIndexCounts.set(startIndex, 1);
  for (let i = 0; i < input.length - 1; i++) {
    let nextRowIndexCounts = new Map<number, number>();
    let nextRow = input[i + 1]!;
    for (const currentRowIndex of currentRowIndexCounts.keys()) {
      const currentValue = currentRowIndexCounts.get(currentRowIndex)!;
      if (nextRow[currentRowIndex] == "^") {
        nextRowIndexCounts.set(
          currentRowIndex + 1,
          (nextRowIndexCounts.get(currentRowIndex + 1) ?? 0) + currentValue
        );
        nextRowIndexCounts.set(
          currentRowIndex - 1,
          (nextRowIndexCounts.get(currentRowIndex - 1) ?? 0) + currentValue
        );
      } else {
        nextRowIndexCounts.set(
          currentRowIndex,
          (nextRowIndexCounts.get(currentRowIndex) ?? 0) + currentValue
        );
      }
    }
    currentRowIndexCounts = nextRowIndexCounts;
  }

  return [...currentRowIndexCounts.values()].reduce(
    (acc, curr) => acc + curr,
    0
  );
}

const inputFile = Bun.file("./data/07.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
