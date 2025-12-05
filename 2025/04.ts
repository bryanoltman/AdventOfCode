type GridValue = "@" | ".";

type Point = {
  x: number;
  y: number;
};

export function parseInput(input: string): GridValue[][] {
  let grid = <GridValue[][]>[];
  for (const line of input
    .split("\n")
    .map((l) => l.trim())
    .filter((l) => l.length > 0)) {
    let row = <GridValue[]>[];
    for (const c of line.split("")) {
      if (c == "." || c == "@") {
        row.push(c);
      } else {
        throw new Error(`unexpected grid point value ${c}`);
      }
    }

    grid.push(row);
  }

  return grid;
}

function neighborPoints(map: any[][], point: Point): Point[] {
  if (map.length == 0) {
    return [];
  }

  const potentialNeighbors = [
    // Top row
    { x: point.x - 1, y: point.y - 1 },
    { x: point.x, y: point.y - 1 },
    { x: point.x + 1, y: point.y - 1 },

    // Middle row
    { x: point.x - 1, y: point.y },
    { x: point.x + 1, y: point.y },

    // Bottom row
    { x: point.x - 1, y: point.y + 1 },
    { x: point.x, y: point.y + 1 },
    { x: point.x + 1, y: point.y + 1 },
  ];

  return potentialNeighbors.filter(
    (p) => p.x >= 0 && p.x < map[0]!.length && p.y >= 0 && p.y < map.length
  );
}

function neighbors<T>(map: T[][], point: Point): T[] {
  return neighborPoints(map, point).map((p) => map[p.y]![p.x]!);
}

export function part1(map: GridValue[][]): number {
  let accessibleRolls = 0;
  for (let y = 0; y < map.length; y++) {
    for (let x = 0; x < map[0]!.length; x++) {
      const pointValue = map[y]![x]!;
      if (pointValue != "@") {
        continue;
      }
      const neighborRolls = neighbors(map, { x, y }).filter((v) => v == "@");
      if (neighborRolls.length < 4) {
        accessibleRolls += 1;
      }
    }
  }

  return accessibleRolls;
}

export function part2(map: GridValue[][]): number {
  let currentMap = map;
  let accessibleRolls = 0;
  let hasChanged = false;

  do {
    let newMap = <GridValue[][]>[];
    hasChanged = false;
    for (let y = 0; y < currentMap.length; y++) {
      let newRow = <GridValue[]>[];
      for (let x = 0; x < currentMap[0]!.length; x++) {
        const pointValue = currentMap[y]![x]!;
        if (pointValue != "@") {
          newRow.push(pointValue);
          continue;
        }
        const neighborRolls = neighbors(currentMap, { x, y }).filter(
          (v) => v == "@"
        );
        if (neighborRolls.length < 4) {
          accessibleRolls += 1;
          hasChanged = true;
          newRow.push(".");
        } else {
          newRow.push(pointValue);
        }
      }
      newMap.push(newRow);
    }
    currentMap = newMap;
  } while (hasChanged);

  return accessibleRolls;
}

const inputFile = Bun.file("./data/04.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
