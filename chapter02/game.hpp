#ifndef GPCPP_CHAPTER02_GAME_HPP
#define GPCPP_CHAPTER02_GAME_HPP

#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>

#include "actor.hpp"
#include "spriteComponent.hpp"

namespace gpcpp::c02 {

class Game {
public:
  Game();
  bool Initialize();
  void RunLoop();
  void Shutdown();
  void AddActor(Actor *actor);
  void RemoveActor(Actor *actor);
  void AddSprite(SpriteComponent *sprite);

private:
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

  SDL_Window *_window;
  SDL_Renderer *_renderer;
  bool _isRunning;
  Uint32 _ticksCount;

  bool _updatingActors;
  std::vector<class Actor *> _actors;
  std::vector<class Actor *> _pendingActors;
  std::vector<class SpriteComponent *> _sprites;

};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_GAME_HPP
