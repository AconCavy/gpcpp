#ifndef GPCPP_UTILS_SEARCH_HPP
#define GPCPP_UTILS_SEARCH_HPP

#include <queue>
#include <unordered_map>
#include <vector>

namespace gpcpp::c04 {

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

struct GBFSScratch {
  const WeightedEdge *ParentEdge = nullptr;
  float Heuristic = 0.0f;
  bool IsInOpenSet = false;
  bool IsInClosedSet = false;
};

struct AStarScratch {
  const WeightedEdge *ParentEdge = nullptr;
  float Heuristic = 0.0f;
  float Cost = 0.0f;
  bool IsInOpenSet = false;
  bool IsInClosedSet = false;
};

struct GameState {
  enum SquareState { Empty, X, O };
  SquareState Board[3][3];
};

struct GameTreeNode {
  std::vector<GameTreeNode *> Children;
  GameState State;
};

using NodeToParentMap =
    std::unordered_map<const GraphNode *, const GraphNode *>;
bool doBFS(const Graph &Graph, const GraphNode *Start, const GraphNode *Goal,
           NodeToParentMap &OutMap);

float computeHeuristic(const WeightedGraphNode *A, const WeightedGraphNode *B);

using GBFSMap = std::unordered_map<const WeightedGraphNode *, GBFSScratch>;
bool doGBFS(const WeightedGraph &Graph, const WeightedGraphNode *Start,
            const WeightedGraphNode *Goal, GBFSMap &OutMap);

using AStarMap = std::unordered_map<const WeightedGraphNode *, AStarScratch>;
bool doAStar(const WeightedGraph &Graph, const WeightedGraphNode *Start,
             const WeightedGraphNode *Goal, AStarMap &OutMap);

float computeScore(const GameState &State);

float computeMaxScore(const GameTreeNode *Node);

float computeMinScore(const GameTreeNode *Node);

const GameTreeNode *doMinimaxDecide(const GameTreeNode *Root);

float computeAlphaBetaMaxScore(const GameTreeNode *Node, float alpha,
                               float beta);

float computeAlphaBetaMinScore(const GameTreeNode *Node, float alpha,
                               float beta);

const GameTreeNode *doAlphaBetaDecide(const GameTreeNode *Root);

} // namespace gpcpp::c04

#endif // GPCPP_UTILS_SEARCH_HPP
