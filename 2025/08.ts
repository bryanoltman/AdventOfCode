type Coord3D = {
  x: number;
  y: number;
  z: number;
};

type CoordDistance = {
  a: Coord3D;
  b: Coord3D;
  distance: number;
};

function distanceSquared(a: Coord3D, b: Coord3D): number {
  return (
    Math.pow(b.x - a.x, 2) + Math.pow(b.y - a.y, 2) + Math.pow(b.z - a.z, 2)
  );
}

function coordinateDistances(coords: Coord3D[]): CoordDistance[] {
  const ret: CoordDistance[] = [];
  for (let i = 0; i < coords.length; i++) {
    for (let j = i + 1; j < coords.length; j++) {
      const a = coords[i]!;
      const b = coords[j]!;
      ret.push({ a, b, distance: distanceSquared(a, b) });
    }
  }
  return ret;
}

export function parseInput(input: string): Coord3D[] {
  return input
    .split("\n")
    .map((l) => l.trim())
    .filter((l) => l.length > 0)
    .map((l) => {
      const parts = l.split(",");
      return {
        x: Number(parts[0]!),
        y: Number(parts[1]!),
        z: Number(parts[2]!),
      };
    });
}

export function part1(input: Coord3D[], iterations: number = 1000): number {
  const distances = coordinateDistances(input).sort(
    (a, b) => a.distance - b.distance
  );
  let circuits: Set<Coord3D>[] = [];
  for (const coord of input) {
    const newSet: Set<Coord3D> = new Set();
    newSet.add(coord);
    circuits.push(newSet);
  }

  for (let i = 0; i < iterations; i++) {
    const distance = distances[i]!;
    const leftCircuitIdx = circuits.findIndex((c) => c.has(distance.a))!;
    const rightCircuitIdx = circuits.findIndex((c) => c.has(distance.b))!;
    if (leftCircuitIdx === rightCircuitIdx) {
      continue;
    }

    const leftCircuit = circuits[leftCircuitIdx]!;
    const rightCircuit = circuits[rightCircuitIdx]!;
    for (const point of rightCircuit.values()) {
      leftCircuit.add(point);
    }
    circuits = circuits.filter((c) => c != rightCircuit);
  }

  return circuits
    .map((c) => c.size)
    .sort((a, b) => b - a)
    .slice(0, 3)
    .reduce((acc, curr) => acc * curr);
}

export function part2(input: Coord3D[]): number {
  const distances = coordinateDistances(input).sort(
    (a, b) => a.distance - b.distance
  );
  let circuits: Set<Coord3D>[] = [];
  for (const coord of input) {
    const newSet: Set<Coord3D> = new Set();
    newSet.add(coord);
    circuits.push(newSet);
  }

  let lastDistance = distances[0]!;
  for (let i = 0; circuits.length > 1; i++) {
    lastDistance = distances[i]!;
    const leftCircuitIdx = circuits.findIndex((c) => c.has(lastDistance.a))!;
    const rightCircuitIdx = circuits.findIndex((c) => c.has(lastDistance.b))!;
    if (leftCircuitIdx === rightCircuitIdx) {
      continue;
    }

    const leftCircuit = circuits[leftCircuitIdx]!;
    const rightCircuit = circuits[rightCircuitIdx]!;
    for (const point of rightCircuit.values()) {
      leftCircuit.add(point);
    }
    circuits.splice(rightCircuitIdx, 1);
  }

  return lastDistance.a.x * lastDistance.b.x;
}

const inputFile = Bun.file("./data/08.txt");
const inputFileExists = await inputFile.exists();
if (inputFileExists) {
  const input = parseInput(await inputFile.text());
  console.log(`part 1: ${part1(input)}`);
  console.log(`part 2: ${part2(input)}`);
}
