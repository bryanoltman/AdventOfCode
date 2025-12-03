export function parseInput(input: string): string[] {
  return input
    .split("\n")
    .map((e) => e.trim())
    .filter((e) => e.length > 0);
}

function largestTwoDigitNumberFromBatteryBank(bank: string): number {
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

function largestNumberFromBatteryBank(
  nums: number[],
  acc: number[],
  numDigits: number
): number {
  // console.log("nums", nums, "acc", acc, "numDigits", numDigits);
  if (numDigits == 0) {
    return Number(acc.map((e) => e.toString()).join(""));
  }

  let largestSoFar = 0;
  for (let i = 0; i < nums.length; i++) {
    const firstNum = nums[i]!;
    const subStr = nums.slice(i + 1);
    const curr = largestNumberFromBatteryBank(
      subStr,
      [...acc, firstNum],
      numDigits - 1
    );
    if (curr > largestSoFar) {
      largestSoFar = curr;
    }
  }

  return largestSoFar;
}

function largestTwelveDigitNumberFromBatteryBank(bank: string): number {
  const nums = bank.split("").map((c) => Number(c));
  return largestNumberFromBatteryBank(nums, [], 12);
}

export function part1(banks: string[]): number {
  return banks.reduce(
    (acc, current) => acc + largestTwoDigitNumberFromBatteryBank(current),
    0
  );
}

export function part2(banks: string[]): number {
  return banks.reduce(
    (acc, current) => acc + largestTwelveDigitNumberFromBatteryBank(current),
    0
  );
}

const inputFile = Bun.file("./data/03.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
