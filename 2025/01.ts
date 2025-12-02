type Direction = "L" | "R";
type Instruction = {
  direction: Direction;
  steps: number;
};

export function parseInput(input: string): Instruction[] {
  return input
    .split("\n")
    .map((line) => line.trim())
    .filter((line) => line.length > 0)
    .map((line) => {
      const direction = line[0] as Direction;
      const steps = parseInt(line.slice(1));
      return {
        direction,
        steps,
      };
    });
}

export function part1(instructions: Instruction[]) {
  let dial = 50;
  let numZeroes = 0;
  for (const instruction of instructions) {
    if (instruction.direction === "L") {
      dial -= instruction.steps;
    } else {
      dial += instruction.steps;
    }

    dial = dial % 100;
    if (dial < 0) {
      dial += 100;
    }

    if (dial == 0) {
      numZeroes += 1;
    }
  }

  return numZeroes;
}

export function part2(instructions: Instruction[]) {
  let dial = 50;
  let numZeroes = 0;
  for (const instruction of instructions) {
    const dialStart = dial;
    // const zeroesAtTurnStart = numZeroes;
    if (instruction.direction === "L") {
      dial -= instruction.steps;
    } else {
      dial += instruction.steps;
    }

    if (dial === 0) {
      numZeroes += 1;
    } else if (dial < 0) {
      while (dial < 0) {
        dial += 100;
        numZeroes += 1;
      }
      if (dialStart === 0) {
        numZeroes -= 1;
      }
      if (dial === 0) {
        numZeroes += 1;
      }
    } else if (dial > 99) {
      while (dial > 99) {
        dial -= 100;
        numZeroes += 1;
      }
    }

    // console.log(
    //   `${instruction.direction}${instruction.steps}`,
    //   `${dialStart}->${dial}`,
    //   numZeroes,
    //   "+".repeat(numZeroes - zeroesAtTurnStart)
    // );
  }

  return numZeroes;
}

const inputFile = Bun.file("./data/01.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
