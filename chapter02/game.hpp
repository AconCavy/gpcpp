#ifndef GPCPP_CHAPTER02_GAME_HPP
#define GPCPP_CHAPTER02_GAME_HPP

#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "actor.hpp"
#include "spriteComponent.hpp"
#include "ship.hpp"

namespace gpcpp::c02 {

class Game {
public:
  Game();
  bool initialize();
  void runLoop();
  void shutdown();
  void addActor(Actor *A);
  void removeActor(Actor *A);
  void addSprite(SpriteComponent *SC);
  void removeSprite(SpriteComponent *SC);
  SDL_Texture *getTexture(const std::string &FileName);

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

  class Ship *Ship;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_GAME_HPP
