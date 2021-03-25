#include "Grid.hpp"

#include <algorithm>

#include "Tile.hpp"

using namespace gpcpp::c04;
Grid::Grid(class Game *Game) : Actor(Game), SelectedTile(nullptr) {
  Tiles.resize(NumbersOfRow);
  for (auto &Tile : Tiles) {
    Tile.resize(NumbersOfColumn);
  }

  for (int I = 0; I < NumbersOfRow; ++I) {
    for (int J = 0; J < NumbersOfColumn; ++J) {
      Tiles[I][J] = new Tile(getGame());
      Tiles[I][J]->setPosition(
          {TileSize / 2.0f + static_cast<float>(J) * TileSize,
           StartY + static_cast<float>(I) * TileSize});
    }
  }

  getStartTile()->setTileState(Tile::Start);
  getGoalTile()->setTileState(Tile::Base);

  for (int I = 0; I < NumbersOfRow; ++I) {
    for (int J = 0; J < NumbersOfColumn; ++J) {
      if (I > 0)
        Tiles[I][J]->Adjacent.push_back(Tiles[I - 1][J]);
      if (I < NumbersOfRow - 1)
        Tiles[I][J]->Adjacent.push_back(Tiles[I + 1][J]);
      if (J > 0)
        Tiles[I][J]->Adjacent.push_back(Tiles[I][J - 1]);
      if (J < NumbersOfColumn - 1)
        Tiles[I][J]->Adjacent.push_back(Tiles[I][J + 1]);
    }
  }

  findPath(getGoalTile(), getStartTile());
  updatePathTiles(getStartTile());

  NextEnemy = EnemyTime;
}

void Grid::updateActor(float DeltaTime) {
  Actor::updateActor(DeltaTime);
  NextEnemy -= DeltaTime;
  if (NextEnemy <= 0) {
    //  new Enemy(getGame());
    NextEnemy += EnemyTime;
  }
}

void Grid::processClick(int x, int y) {
  y -= static_cast<int>(StartY - TileSize / 2);
  if (y < 0)
    return;
  x /= static_cast<int>(TileSize);
  y /= static_cast<int>(TileSize);
  if (0 <= x && x < NumbersOfColumn && 0 <= y && y < NumbersOfRow)
    selectTile(y, x);
}

bool Grid::findPath(struct Tile *Start, struct Tile *Goal) {
  for (int I = 0; I < NumbersOfRow; ++I) {
    for (int J = 0; J < NumbersOfColumn; ++J) {
      Tiles[I][J]->Cost = 0;
      Tiles[I][J]->IsInOpenSet = false;
      Tiles[I][J]->IsInClosedSet = false;
    }
  }

  std::vector<Tile *> OpenSet;
  auto Current = Start;
  Current->IsInClosedSet = true;

  auto GoalPosition = Goal->getPosition();

  do {
    for (auto Neighbor : Current->Adjacent) {
      if (Neighbor->IsBlocked || Neighbor->IsInClosedSet)
        continue;

      auto NewCost = Current->Cost + TileSize;
      if (Neighbor->IsInOpenSet) {
        Neighbor->Parent = Current;
        Neighbor->Heuristic =
            glm::distance(Neighbor->getPosition(), GoalPosition);
        Neighbor->Cost = NewCost;
        OpenSet.emplace_back(Neighbor);
        Neighbor->IsInOpenSet = true;
      } else {
        if (NewCost < Neighbor->Cost) {
          Neighbor->Parent = Current;
          Neighbor->Cost = NewCost;
        }
      }
    }

    if (OpenSet.empty())
      break;

    auto I = std::min_element(OpenSet.begin(), OpenSet.end(),
                              [](Tile *A, Tile *B) { return A->F() < B->F(); });

    Current = *I;
    OpenSet.erase(I);
    Current->IsInOpenSet = false;
    Current->IsInClosedSet = true;
  } while (Current != Goal);

  return Current == Goal;
}

void Grid::buildTower() {
  if (!SelectedTile || SelectedTile->IsBlocked)
    return;

  SelectedTile->IsBlocked = true;
  if (findPath(getGoalTile(), getStartTile())) {
    //    auto Tower = new Tower(getGame());
    //    Tower->setPosition(SelectedTile->getPosition());
  } else {
    SelectedTile->IsBlocked = false;
    findPath(getGoalTile(), getStartTile());
  }
  updatePathTiles(getStartTile());
}

class Tile *Grid::getStartTile() {
  return Tiles[StartRow][StartColumn];
}

class Tile *Grid::getGoalTile() {
  return Tiles[GoalRow][GoalColumn];
}

void Grid::selectTile(size_t Row, size_t Column) {
  auto State = Tiles[Row][Column]->getTileState();
  if (State == Tile::Start || State == Tile::Base)
    return;

  if (SelectedTile)
    SelectedTile->toggleSelect();
  SelectedTile = Tiles[Row][Column];
  SelectedTile->toggleSelect();
}

void Grid::updatePathTiles(struct Tile *Start) {
  for (int I = 0; I < NumbersOfRow; ++I) {
    for (int J = 0; J < NumbersOfColumn; ++J) {
      if (!(I == StartRow && J == StartColumn) &&
          !(I == GoalRow && J == GoalColumn)) {
        Tiles[I][J]->setTileState(Tile::Default);
      }
    }
  }

  auto Current = Start->Parent;
  auto E = getGoalTile();
  while (Current != E) {
    Current->setTileState(Tile::Path);
    Current = Current->Parent;
  }
}
