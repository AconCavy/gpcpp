#ifndef GPCPP_CHAPTER04_GRID_HPP
#define GPCPP_CHAPTER04_GRID_HPP

#include "Actor.hpp"

namespace gpcpp::c04 {

class Grid : public Actor {
public:
  explicit Grid(class Game *Game);

  void updateActor(float DeltaTime) override;
  void processClick(int x, int y);
  bool findPath(class Tile *Start, class Tile *Goal);
  void buildTower();

  class Tile *getStartTile();
  class Tile *getGoalTile();

private:
  void selectTile(size_t Row, size_t Column);
  void updatePathTiles(class Tile *Start);

  class Tile *SelectedTile;
  std::vector<std::vector<class Tile *>> Tiles;
  float NextEnemy;

  const size_t NumbersOfRow = 7;
  const size_t NumbersOfColumn = 16;
  const size_t StartRow = 3;
  const size_t StartColumn = 0;
  const size_t GoalRow = 3;
  const size_t GoalColumn = 15;
  const float StartY = 192;
  const float TileSize = 64;
  const float EnemyTime = 1.5f;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_GRID_HPP
