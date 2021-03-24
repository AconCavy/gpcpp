#include <queue>
#include <unordered_map>
#include <vector>

namespace gpcpp {

struct GraphNode {
  std::vector<GraphNode *> Adjacent;
};

struct Graph {
  std::vector<GraphNode *> Nodes;
};

struct WeightedEdge {
  struct WeightedGraphNode *From;
  struct WeightedGraphNode *To;
  float Weight;
};

struct WeightedGraphNode {
  std::vector<WeightedEdge *> Edges;
};

struct WeightedGraph {
  std::vector<WeightedGraphNode *> Nodes;
};

using NodeToParentMap =
    std::unordered_map<const GraphNode *, const GraphNode *>;

bool BFS(const Graph &Graph, const GraphNode *Start, const GraphNode *Goal,
         NodeToParentMap &OutMap) {
  bool Result = false;
  std::queue<const GraphNode *> Q;
  Q.emplace(Start);

  while (!Q.empty()) {
    const auto Current = Q.front();
    Q.pop();
    if (Current == Goal) {
      Result = true;
      break;
    }

    for (const auto Next : Current->Adjacent) {
      const auto Parent = OutMap[Next];
      if (Parent == nullptr && Next != Start) {
        OutMap[Next] = Current;
        Q.emplace(Next);
      }
    }
  }

  return Result;
}

float ComputeHeuristic(const WeightedGraphNode *A, const WeightedGraphNode *B) {
  return 0.0f;
}

struct GBFSScratch {
  const WeightedEdge *ParentEdge = nullptr;
  float Heuristic = 0.0f;
  bool IsInOpenSet = false;
  bool IsInClosedSet = false;
};

using GBFSMap = std::unordered_map<const WeightedGraphNode *, GBFSScratch>;

bool GBFS(const WeightedGraph &Graph, const WeightedGraphNode *Start,
          const WeightedGraphNode *Goal, GBFSMap &OutMap) {
  std::vector<const WeightedGraphNode *> OpenSet;
  const WeightedGraphNode *Current = Start;
  OutMap[Current].IsInClosedSet = true;

  do {
    for (const auto Edge : Current->Edges) {
      const auto Neighbor = Edge->To;
      auto Data = OutMap[Neighbor];
      if (Data.IsInClosedSet)
        continue;

      Data.ParentEdge = Edge;
      if (Data.IsInOpenSet)
        continue;

      Data.Heuristic = ComputeHeuristic(Neighbor, Goal);
      Data.IsInOpenSet = true;
      OpenSet.emplace_back(Neighbor);
    }

    if (OpenSet.empty())
      break;

    auto I = std::min_element(
        OpenSet.begin(), OpenSet.end(),
        [&OutMap](const WeightedGraphNode *A, const WeightedGraphNode *B) {
          return OutMap[A].Heuristic < OutMap[B].Heuristic;
        });

    Current = *I;
    OpenSet.erase(I);
    OutMap[Current].IsInOpenSet = false;
    OutMap[Current].IsInClosedSet = true;
  } while (Current != Goal);

  return Current == Goal;
}

struct AStarScratch {
  const WeightedEdge *ParentEdge = nullptr;
  float Heuristic = 0.0f;
  float Cost = 0.0f;
  bool IsInOpenSet = false;
  bool IsInClosedSet = false;
};

using AStarMap = std::unordered_map<const WeightedGraphNode *, AStarScratch>;

bool AStar(const WeightedGraph &Graph, const WeightedGraphNode *Start,
           const WeightedGraphNode *Goal, AStarMap &OutMap) {
  std::vector<const WeightedGraphNode *> OpenSet;
  const WeightedGraphNode *Current = Start;
  OutMap[Current].IsInClosedSet = true;

  do {
    for (const auto Edge : Current->Edges) {
      const auto Neighbor = Edge->To;
      auto Data = OutMap[Neighbor];
      if (Data.IsInClosedSet)
        continue;

      Data.ParentEdge = Edge;
      if (Data.IsInOpenSet) {
        auto Cost = OutMap[Current].Cost + Edge->Weight;
        if (Cost < Data.Cost) {
          Data.ParentEdge = Edge;
          Data.Cost = Cost;
        }
      } else {
        Data.ParentEdge = Edge;
        Data.Heuristic = ComputeHeuristic(Neighbor, Goal);
        Data.Cost = OutMap[Current].Cost + Edge->Weight;
        Data.IsInOpenSet = true;
        OpenSet.emplace_back(Neighbor);
      }
    }

    if (OpenSet.empty())
      break;

    auto I = std::min_element(
        OpenSet.begin(), OpenSet.end(),
        [&OutMap](const WeightedGraphNode *A, const WeightedGraphNode *B) {
          const auto SA = OutMap[A];
          const auto SB = OutMap[B];
          return SA.Heuristic + SA.Cost < SB.Heuristic + SB.Cost;
        });

    Current = *I;
    OpenSet.erase(I);
    OutMap[Current].IsInOpenSet = false;
    OutMap[Current].IsInClosedSet = true;
  } while (Current != Goal);

  return Current == Goal;
}

} // namespace gpcpp