type Operation = "+" | "*";

type WorksheetColumn = {
  numbers: number[];
  operation: Operation;
};

type Input = WorksheetColumn[];

export function parseInput(input: string): Input {
  const lines = input
    .split("\n")
    .map((l) => l.trim())
    .filter((l) => l.length > 0);
  const numLines = lines.slice(0, lines.length - 1);
  const opLine = lines[lines.length - 1]!;

  const numRows = numLines
    .map((l) => l.split(/\s+/))
    .map((numStrs) => numStrs.map((c) => Number(c)));
  const opRow: Operation[] = opLine.split(/\s+/).map((c) => c as Operation);
  let ret = <WorksheetColumn[]>[];
  for (let i = 0; i < numRows[0]!.length; i++) {
    ret.push({ numbers: numRows.map((n) => n[i]!), operation: opRow[i]! });
  }

  console.log(ret);
  return ret;
}

const addOp = (a: number, b: number) => a + b;
const multOp = (a: number, b: number) => a * b;

function processColumn(column: WorksheetColumn): number {
  const op = column.operation == "*" ? multOp : addOp;
  return column.numbers.reduce((acc, curr) => op(acc, curr));
}

export function part1(input: Input): number {
  return input
    .map((c) => processColumn(c))
    .reduce((acc, curr) => addOp(acc, curr));
}

export function part2(input: Input): number {
  return 0;
}

const inputFile = Bun.file("./data/06.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
