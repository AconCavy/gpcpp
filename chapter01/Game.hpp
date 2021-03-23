#ifndef GPCPP_CHAPTER01_GAME_HPP_
#define GPCPP_CHAPTER01_GAME_HPP_

#include <SDL2/SDL.h>
#include <vector>
#include <glm/glm.hpp>

namespace gpcpp::c01 {

struct Paddle {
  glm::vec2 Position;
  int Direction;
};

struct Ball {
  glm::vec2 Position;
  glm::vec2 Velocity;
};

class Game {
public:
  Game();
  bool initialize();
  void runLoop();
  void shutdown();

private:
  void processInput();
  void updateGame();
  void generateOutput();

  SDL_Window *Window;
  SDL_Renderer *Renderer;
  bool IsRunning;

  std::vector<Paddle> Players;
  std::vector<Ball> Balls;

  Uint32 TicksCount;
};

} // namespace gpcpp::c01

#endif //GPCPP_CHAPTER01_GAME_HPP_
