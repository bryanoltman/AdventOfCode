import Collections
import Foundation

struct Edge {
  let destination: Point
  let weight: Int
}

// A custom struct for the (distance, vertex) pair
struct Node: Comparable, Hashable {
  let distance: Int
  let point: Point

  static func < (lhs: Node, rhs: Node) -> Bool {
    return lhs.distance < rhs.distance
  }
}

struct Vertex: Hashable {
  let point: Point
  let neighbors: [Node]
}

typealias DijkstraGraph = [Vertex]

func gridToDjikstraGraph<T>(grid: Grid<T>) -> DijkstraGraph {
  grid.points.map { point in
    Vertex(
      point: point,
      neighbors: grid.neighbors(point: point).map { Node(distance: 1, point: $0) }
    )
  }
}

func dijkstraImpl(
  graph: DijkstraGraph,
  source sourcePoint: Point
) {

}

func dijkstra(
  graph: DijkstraGraph,
  source sourcePoint: Point,
  target targetPoint: Point,
  canVisit: (_ from: Point, _ to: Point) -> Bool?
) -> Int? {
  let targetVertex = graph.first { $0.point == targetPoint }!
  var heap = Heap<Node>()
  var distances = [Vertex: Int]()
  for vertex in graph {
    distances[vertex] = Int.max
  }

  heap.insert(Node(distance: 0, point: sourcePoint))
  while let currentNode = heap.popMin() {
    let currentDistance = currentNode.distance
    let currentPoint = currentNode.point
    let currentVertex = graph.first { $0.point == currentPoint }!
    if currentDistance > distances[currentVertex]! {
      continue
    }

    for neighbor in currentVertex.neighbors {
      if let canProceed = canVisit(currentPoint, neighbor.point), !canProceed {
        continue
      }

      let newDistance = currentDistance + neighbor.distance
      let neighborVertex = graph.first { $0.point == neighbor.point }!
      if newDistance < distances[neighborVertex]! {
        distances[neighborVertex] = newDistance
        heap.insert(Node(distance: newDistance, point: neighbor.point))
      }
    }
  }

  return distances[targetVertex] == Int.max ? nil : distances[targetVertex]
}
