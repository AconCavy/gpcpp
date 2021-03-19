#ifndef GPCPP_CHAPTER01_GAME_HPP_
#define GPCPP_CHAPTER01_GAME_HPP_

#include <SDL2/SDL.h>
#include <vector>
#include "vector2.hpp"

namespace gpcpp::c01 {

struct Paddle {
  gpcpp::utils::Vector2 position;
  int direction;
};

struct Ball {
  gpcpp::utils::Vector2 position;
  gpcpp::utils::Vector2 velocity;
};

class Game {
public:
  Game();
  bool Initialize();
  void RunLoop();
  void Shutdown();

private:
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

  SDL_Window *_window;
  SDL_Renderer *_renderer;
  bool _isRunning;

  std::vector<Paddle> _players;
  std::vector<Ball> _balls;

  Uint32 _ticksCount;

};

}

#endif //GPCPP_CHAPTER01_GAME_HPP_
