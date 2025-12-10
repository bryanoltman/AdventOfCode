type Light = "." | "#";

type Machine = {
  lights: Light[];
  buttons: number[][];
  joltages: number[];
};

function machineFromLine(line: string): Machine {
  const parts = line.split(" ");
  const lights = parts[0]!
    .replaceAll("[", "")
    .replaceAll("]", "")
    .split(",")
    .map((c) => c as Light);

  const joltages = parts[parts.length - 1]!.replaceAll("{", "")
    .replaceAll("}", "")
    .split(",")
    .map((n) => Number(n));

  let buttonParts = parts;
  buttonParts.shift();
  buttonParts.pop();
  let buttons = buttonParts.map((p) =>
    p
      .replaceAll("(", "")
      .replaceAll(")", "")
      .split(",")
      .map((n) => Number(n))
  );

  return { lights, buttons, joltages };
}

export function parseInput(input: string): Machine[] {
  return input
    .split("\n")
    .map((l) => l.trim())
    .filter((l) => l.length > 0)
    .map((l) => machineFromLine(l));
}

export function part1(input: Machine[]): number {
  return 0;
}

export function part2(input: Machine[]): number {
  return 0;
}

const inputFile = Bun.file("./data/10.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
