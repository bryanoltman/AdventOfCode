export function parseInput(input: string): string[] {
  return input
    .split("\n")
    .map((e) => e.trim())
    .filter((e) => e.length > 0);
}

function largestNumberFromBatteryBank(bank: string): number {
  const nums = bank.split("").map((c) => Number(c));
  let biggestFirstNum = 0;
  let firstNumIdx = 0;
  for (let i = 0; i < nums.length - 1; i++) {
    const currentNum = nums[i]!;
    if (currentNum > biggestFirstNum) {
      biggestFirstNum = currentNum;
      firstNumIdx = i;
    }
  }

  let biggestSecondNum = 0;
  for (let i = firstNumIdx + 1; i < nums.length; i++) {
    const currentNum = nums[i]!;
    if (currentNum > biggestSecondNum) {
      biggestSecondNum = currentNum;
    }
  }

  return biggestFirstNum * 10 + biggestSecondNum;
}

export function part1(banks: string[]): number {
  return banks.reduce(
    (acc, current) => acc + largestNumberFromBatteryBank(current),
    0
  );
}

export function part2(ranges: string[]): number {
  return 0;
}

const inputFile = Bun.file("./data/03.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
