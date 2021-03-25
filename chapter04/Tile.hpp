#ifndef GPCPP_CHAPTER04_TILE_HPP
#define GPCPP_CHAPTER04_TILE_HPP

#include "Actor.hpp"

namespace gpcpp::c04 {

class Tile : public Actor {
public:
  enum TileState { Default, Path, Start, Base };

  explicit Tile(class Game *Game);

  void toggleSelect();

  [[nodiscard]] TileState getTileState() const { return CurrentState; }
  [[nodiscard]] Tile *getParent() const { return Parent; }

  void setTileState(TileState TileState);

private:
  void updateTexture();

  std::vector<Tile *> Adjacent;
  Tile *Parent;
  bool IsInOpenSet;
  bool IsInClosedSet;
  bool IsBlocked;
  bool IsSelected;

  class SpriteComponent *Sprite;
  TileState CurrentState;
};
} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_TILE_HPP
