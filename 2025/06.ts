type Operation = "+" | "*";

type WorksheetColumn = {
  numbers: number[];
  operation: Operation;
};

type RawWorksheetColumn = {
  numbers: string[];
  operation: Operation;
};

export function parseInputPart1(input: string): WorksheetColumn[] {
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

  return ret;
}

const addOp = (a: number, b: number) => a + b;
const multOp = (a: number, b: number) => a * b;

function processColumn(column: WorksheetColumn): number {
  const op = column.operation == "*" ? multOp : addOp;
  return column.numbers.reduce((acc, curr) => op(acc, curr));
}

export function part1(input: WorksheetColumn[]): number {
  return input
    .map((c) => processColumn(c))
    .reduce((acc, curr) => addOp(acc, curr));
}

export function parseInputPart2(input: string): RawWorksheetColumn[] {
  const lines = input.split("\n").filter((l) => l.length > 0);
  const numLines = lines.slice(0, lines.length - 1);
  const opLine = lines[lines.length - 1]!;

  let ret = <RawWorksheetColumn[]>[];
  let currIdx = 0;
  while (currIdx < opLine.length) {
    let op = opLine[currIdx] as Operation;
    let nextIdx = currIdx + 1;
    while (opLine[nextIdx] == " ") {
      nextIdx += 1;
    }
    let columnWidth = nextIdx - currIdx;
    // Subtract one to account for the single space padding between columns
    if (nextIdx != opLine.length) {
      columnWidth -= 1;
    }

    let numberStrings = <string[]>[];
    for (const numLine of numLines) {
      numberStrings.push(numLine.slice(currIdx, currIdx + columnWidth));
    }
    ret.push({
      operation: op,
      numbers: numberStrings,
    });
    currIdx = nextIdx;
  }

  return ret;
}

function processPart2Column(column: RawWorksheetColumn): number {
  let numbers = <number[]>[];

  for (let i = column.numbers[0]!.length - 1; i >= 0; i--) {
    let currNumber = "";
    for (const num of column.numbers) {
      currNumber += num[i]!;
    }
    numbers.push(Number(currNumber));
  }

  const op = column.operation == "*" ? multOp : addOp;
  return numbers.reduce((acc, curr) => op(acc, curr));
}

export function part2(input: RawWorksheetColumn[]): number {
  return input.map(processPart2Column).reduce((acc, curr) => addOp(acc, curr));
}

const inputFile = Bun.file("./data/06.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const inputPart1 = parseInputPart1(await inputFile.text());
  console.log(`part 1: ${part1(inputPart1)}`);
  const inputPart2 = parseInputPart2(await inputFile.text());
  console.log(`part 2: ${part2(inputPart2)}`);
}
