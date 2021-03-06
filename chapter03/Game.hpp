#ifndef GPCPP_CHAPTER03_GAME_HPP
#define GPCPP_CHAPTER03_GAME_HPP

#include <SDL.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace gpcpp::c03 {

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
  void addAsteroid(class Asteroid *A);
  void removeAsteroid(class Asteroid *A);
  std::vector<class Asteroid *> getAsteroids() { return Asteroids; }
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
  std::vector<class Asteroid *> Asteroids;
};

} // namespace gpcpp::c03

#endif // GPCPP_CHAPTER03_GAME_HPP
