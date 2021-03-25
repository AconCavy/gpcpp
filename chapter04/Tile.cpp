#include "Tile.hpp"

#include <string>

#include "Game.hpp"
#include "SpriteComponent.hpp"

using namespace gpcpp::c04;

Tile::Tile(class Game *Game)
    : Actor(Game), Parent(nullptr), IsBlocked(false), Sprite(nullptr),
      CurrentState(Default), IsSelected(false), IsInClosedSet(false),
      IsInOpenSet(false), Heuristic(0), Cost(0) {
  Sprite = new SpriteComponent(this);
  updateTexture();
}

void Tile::toggleSelect() {
  IsSelected = !IsSelected;
  updateTexture();
}

void Tile::setTileState(TileState TileState) {
  CurrentState = TileState;
  updateTexture();
}

void Tile::updateTexture() {
  std::string FileName;
  switch (CurrentState) {
  case Start:
    FileName = "assets/TileTan.png";
    break;
  case Base:
    FileName = "assets/TileGreen.png";
    break;
  case Path:
    FileName =
        IsSelected ? "assets/TileGreySelected.png" : "assets/TileGrey.png";
    break;
  case Default:
  default:
    FileName =
        IsSelected ? "assets/TileBrownSelected.png" : "assets/TileBrown.png";
    break;
  }

  Sprite->setTexture(getGame()->getTexture(FileName));
}
