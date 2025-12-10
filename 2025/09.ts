type Coord2D = {
  x: number;
  y: number;
};

type Line = {
  beg: Coord2D;
  end: Coord2D;
};

export function parseInput(input: string): Coord2D[] {
  return input
    .split("\n")
    .map((l) => l.trim())
    .filter((l) => l.length > 0)
    .map((l) => {
      const parts = l.split(",");
      return {
        x: Number(parts[0]!),
        y: Number(parts[1]!),
      };
    });
}

export function part1(input: Coord2D[]): number {
  let largestArea = 0;
  for (let i = 0; i < input.length; i++) {
    const a = input[i]!;
    for (let j = i + 1; j < input.length; j++) {
      const b = input[j]!;
      const width = Math.abs(b.x - a.x) + 1;
      const height = Math.abs(b.y - a.y) + 1;
      const area = width * height;
      if (area > largestArea) {
        largestArea = area;
      }
    }
  }

  return largestArea;
}

function isLineHorizontal(line: Line): boolean {
  return line.beg.y == line.end.y;
}

function linesIntersect(a: Line, b: Line): boolean {
  const isAHorizontal = isLineHorizontal(a);
  const isAVertical = !isAHorizontal;
  const isBHorizontal = isLineHorizontal(b);
  const isBVertical = !isBHorizontal;
  if (isAHorizontal && isBHorizontal) {
    return false;
  }
  if (isAVertical && isBVertical) {
    return false;
  }

  const hLine = isAHorizontal ? a : b;
  const vLine = isAHorizontal ? b : a;
  const intersects =
    hLine.beg.y >= vLine.beg.y &&
    hLine.beg.y <= vLine.end.y &&
    hLine.beg.x <= vLine.beg.x &&
    hLine.end.x >= vLine.beg.x;
  return intersects;
}

export function part2(input: Coord2D[]): number {
  const lines: Line[] = [];
  var currentPoint = input[0]!;
  for (let i = 0; i < input.length - 1; i++) {
    const nextPoint = input[i + 1]!;
    lines.push({
      beg: currentPoint,
      end: nextPoint,
    });

    currentPoint = nextPoint;
  }
  lines.push({ beg: currentPoint, end: input[0]! });

  let largestArea = 0;
  for (let i = 0; i < input.length; i++) {
    const a = input[i]!;
    for (let j = i + 1; j < input.length; j++) {
      const b = input[j]!;
      const rectLines: Line[] = [
        { beg: a, end: { x: a.x, y: b.y } },
        { beg: { x: a.x, y: b.y }, end: b },
        { beg: b, end: { x: b.x, y: a.y } },
        { beg: { x: b.x, y: a.y }, end: a },
      ];

      let hasIntersection = false;
      for (const l of lines) {
        for (const c of rectLines) {
          if (linesIntersect(l, c)) {
            hasIntersection = true;
            break;
          }
        }
        if (hasIntersection) break;
      }
      if (hasIntersection) {
        continue;
      }

      const width = Math.abs(b.x - a.x) + 1;
      const height = Math.abs(b.y - a.y) + 1;
      const area = width * height;

      if (area > largestArea) {
        largestArea = area;
      }
    }
  }

  // 2107952020 is too high
  return largestArea;
}

const inputFile = Bun.file("./data/09.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
