export function parseInput(input: string): string[] {
  return input
    .split("\n")
    .map((e) => e.trim())
    .filter((e) => e.length > 0);
}

function largestNumberFromBatteryBank(bank: string, numDigits: number): number {
  const nums = bank.split("").map((c) => Number(c));
  let numsToGo = numDigits;
  let currentNumberIndex = 0;
  var selectedBatteries = <number[]>[];
  for (; numsToGo > 0; numsToGo--) {
    let candidateNextNumberIdx = 0;
    let candidateNextNumber = 0;
    for (var i = currentNumberIndex; i < nums.length - numsToGo + 1; i++) {
      let test = nums[i]!;
      if (test > candidateNextNumber) {
        candidateNextNumber = test;
        candidateNextNumberIdx = i;
      }
    }
    selectedBatteries.push(candidateNextNumber);
    currentNumberIndex = candidateNextNumberIdx + 1;
  }

  return Number(selectedBatteries.join(""));
}

export function part1(banks: string[]): number {
  return banks.reduce(
    (acc, current) => acc + largestNumberFromBatteryBank(current, 2),
    0
  );
}

export function part2(banks: string[]): number {
  return banks.reduce(
    (acc, current) => acc + largestNumberFromBatteryBank(current, 12),
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
