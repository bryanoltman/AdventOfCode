type IDRange = {
  beg: number;
  end: number;
};

export function parseInput(input: string): IDRange[] {
  const rangeStrings = input.split(",");
  return rangeStrings.map((s) => {
    const parts = s.split("-");
    return {
      beg: Number(parts[0]),
      end: Number(parts[1]),
    };
  });
}

export function isIDInvalidPart2(id: string): boolean {
  for (var substrLength = 1; substrLength <= id.length / 2; substrLength++) {
    const candidate = id.slice(0, substrLength);
    let isMatch = true;
    var i = 0;
    for (; i < id.length; i += substrLength) {
      const test = id.slice(i, i + substrLength);

      if (candidate != test) {
        isMatch = false;
        break;
      }
    }

    if (i != id.length) {
      continue;
    }

    if (isMatch) {
      return true;
    }
  }

  return false;
}

function isIDInvalidPart1(id: string): boolean {
  const startIdx = 0;
  const midIdx = id.length / 2;
  const endIdx = id.length;
  return id.slice(startIdx, midIdx) == id.slice(midIdx, endIdx);
}

export function part1(ranges: IDRange[]): number {
  let invalidIDs = new Set<number>();
  let invalidIdSum = 0;
  for (const r of ranges) {
    for (var i = r.beg; i <= r.end; i++) {
      if (isIDInvalidPart1(i.toString())) {
        if (!invalidIDs.has(i)) {
          invalidIDs.add(i);
          invalidIdSum += i;
        }
      }
    }
  }

  return invalidIdSum;
}

export function part2(ranges: IDRange[]): number {
  let invalidIDs = new Set<number>();
  let invalidIdSum = 0;
  for (const r of ranges) {
    for (var i = r.beg; i <= r.end; i++) {
      if (isIDInvalidPart2(i.toString())) {
        if (!invalidIDs.has(i)) {
          invalidIDs.add(i);
          invalidIdSum += i;
        }
      }
    }
  }

  return invalidIdSum;
}

const inputFile = Bun.file("./data/02.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
