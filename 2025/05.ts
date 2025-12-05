export type Range = {
  beg: number;
  end: number;
};

type Input = {
  ranges: Range[];
  ingredientIDs: number[];
};

export function parseInput(input: string): Input {
  const [rangeStrs, idStrs] = input.split("\n\n");

  const ranges = rangeStrs!
    .split("\n")
    .map((s) => s.trim())
    .filter((s) => s.length > 0)
    .map((s) => {
      const parts = s.split("-");
      return {
        beg: Number(parts[0]),
        end: Number(parts[1]),
      };
    });
  const ids = idStrs!
    .split("\n")
    .map((s) => s.trim())
    .filter((s) => s.length > 0)
    .map((e) => Number(e));

  return {
    ranges: ranges,
    ingredientIDs: ids,
  };
}

export function part1(input: Input): number {
  let freshIngredientCount = 0;
  for (const id of input.ingredientIDs) {
    let isFresh = false;
    for (const range of input.ranges) {
      if (id >= range.beg && id <= range.end) {
        isFresh = true;
        break;
      }
    }

    if (isFresh) {
      freshIngredientCount += 1;
    }
  }

  return freshIngredientCount;
}

export function mergeRanges(ranges: Range[]): Range[] {
  if (ranges.length === 0) {
    return [];
  }

  // Sort the ranges by their start values
  const sortedRanges = [...ranges].sort((a, b) => a.beg - b.beg);
  const merged = <Range[]>[];
  let currentMergedRange = sortedRanges[0]!;
  for (let i = 1; i < sortedRanges.length; i++) {
    const nextRange = sortedRanges[i]!;

    // If ranges overlap, combine them
    if (nextRange.beg <= currentMergedRange.end) {
      currentMergedRange.end = Math.max(currentMergedRange.end, nextRange.end);
    } else {
      merged.push(currentMergedRange);
      currentMergedRange = nextRange;
    }
  }

  // Add the last merged range
  merged.push(currentMergedRange);

  return merged;
}

export function part2(input: Input): number {
  const ranges = mergeRanges(input.ranges);
  let sum = 0;
  for (const r of ranges) {
    sum += r.end - r.beg + 1;
  }

  return sum;
}

const inputFile = Bun.file("./data/05.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
