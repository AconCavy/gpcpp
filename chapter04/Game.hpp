#ifndef GPCPP_CHAPTER04_GAME_HPP
#define GPCPP_CHAPTER04_GAME_HPP

#include <SDL.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace gpcpp::c04 {

class Game {
public:
  Game();
  bool initialize();
  void runLoop();
  void shutdown();

  void addActor(class Actor *A);
  void removeActor(class Actor *A);
  void addSprite(class SpriteComponent *SC);
  void removeSprite(class SpriteComponent *SC);
  SDL_Texture *getTexture(const std::string &FileName);

  class Grid *getGrid() {
    return Grid;
  }

  std::vector<class Enemy *> &getEnemies() { return Enemies; }
  class Enemy *getNearestEnemy(const glm::vec2 &Position);

  const int Height = 768;
  const int Width = 1024;
  const int FPS = 60;
  const int DeltaCount = 1000 / FPS;

private:
  void processInput();
  void updateGame();
  void generateOutput();
  void loadData();
  void unloadData();

  SDL_Window *Window;
  SDL_Renderer *Renderer;
  bool IsRunning;
  Uint32 TicksCount;

  bool UpdatingActors;
  std::vector<class Actor *> Actors;
  std::vector<class Actor *> PendingActors;
  std::vector<class SpriteComponent *> Sprites;
  std::unordered_map<std::string, SDL_Texture *> Textures;

  std::vector<class Enemy *> Enemies;
  class Grid *Grid;
  float NextEnemy;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_GAME_HPP
