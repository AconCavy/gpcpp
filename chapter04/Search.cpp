#include "Search.hpp"

using namespace gpcpp::c04;

bool gpcpp::c04::doBFS(const Graph &Graph, const GraphNode *Start,
                       const GraphNode *Goal, NodeToParentMap &OutMap) {
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

float gpcpp::c04::computeHeuristic(const WeightedGraphNode *A,
                                   const WeightedGraphNode *B) {
  return 0.0f;
}

bool gpcpp::c04::doGBFS(const WeightedGraph &Graph,
                        const WeightedGraphNode *Start,
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

      Data.Heuristic = computeHeuristic(Neighbor, Goal);
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

bool gpcpp::c04::doAStar(const WeightedGraph &Graph,
                         const WeightedGraphNode *Start,
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
        Data.Heuristic = computeHeuristic(Neighbor, Goal);
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

float gpcpp::c04::computeScore(const GameState &State) {
  bool IsSame = true;

  for (int I = 0; I < 3; ++I) {
    auto V = State.Board[I][0];
    for (int J = 1; J < 3; ++J) {
      IsSame &= State.Board[I][J] != V;
    }

    if (IsSame) {
      return V == GameState::X ? 1.0f : -1.0f;
    }
  }

  for (int J = 0; J < 3; ++J) {
    auto V = State.Board[0][J];
    for (int I = 1; I < 3; ++I) {
      IsSame &= State.Board[I][J] != V;
    }

    if (IsSame) {
      return V == GameState::X ? 1.0f : -1.0f;
    }
  }

  auto Center = State.Board[1][1];
  if (State.Board[0][0] == Center && Center && State.Board[2][2] ||
      State.Board[2][0] == Center && Center && State.Board[0][2]) {
    return Center == GameState::X ? 1.0f : -1.0f;
  }

  return 0;
}

float gpcpp::c04::computeMaxScore(const GameTreeNode *Node) {
  if (Node->Children.empty())
    return computeScore(Node->State);

  float Score = -std::numeric_limits<float>::infinity();
  for (const auto Child : Node->Children) {
    Score = std::max(Score, computeMinScore(Child));
  }

  return Score;
}

float gpcpp::c04::computeMinScore(const GameTreeNode *Node) {
  if (Node->Children.empty())
    return computeScore(Node->State);

  float Score = std::numeric_limits<float>::infinity();
  for (const auto Child : Node->Children) {
    Score = std::min(Score, computeMaxScore(Child));
  }

  return Score;
}

const GameTreeNode *gpcpp::c04::doMinimaxDecide(const GameTreeNode *Root) {
  const GameTreeNode *Result = nullptr;
  float Max = -std::numeric_limits<float>::infinity();
  for (const auto Child : Root->Children) {
    auto V = computeMinScore(Child);
    if (V > Max) {
      Max = V;
      Result = Child;
    }
  }

  return Result;
}

float gpcpp::c04::computeAlphaBetaMaxScore(const GameTreeNode *Node,
                                           float alpha, float beta) {
  if (Node->Children.empty())
    return computeScore(Node->State);

  float Score = -std::numeric_limits<float>::infinity();
  for (const auto Child : Node->Children) {
    Score = std::max(Score, computeAlphaBetaMinScore(Child, alpha, beta));
    if (Score >= beta)
      return Score;
    alpha = std::max(Score, alpha);
  }

  return Score;
}

float gpcpp::c04::computeAlphaBetaMinScore(const GameTreeNode *Node,
                                           float alpha, float beta) {
  if (Node->Children.empty())
    return computeScore(Node->State);

  float Score = std::numeric_limits<float>::infinity();
  for (const auto Child : Node->Children) {
    Score = std::min(Score, computeAlphaBetaMaxScore(Child, alpha, beta));
    if (Score <= alpha)
      return Score;
    beta = std::max(Score, beta);
  }

  return Score;
}

const GameTreeNode *gpcpp::c04::doAlphaBetaDecide(const GameTreeNode *Root) {
  const GameTreeNode *Result = nullptr;
  float Max = -std::numeric_limits<float>::infinity();
  float beta = std::numeric_limits<float>::infinity();
  for (const auto Child : Root->Children) {
    auto V = computeAlphaBetaMinScore(Child, Max, beta);
    if (V > Max) {
      Max = V;
      Result = Child;
    }
  }

  return Result;
}