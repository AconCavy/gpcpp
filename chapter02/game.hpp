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
  bool Initialize();
  void RunLoop();
  void Shutdown();
  void AddActor(Actor *actor);
  void RemoveActor(Actor *actor);
  void AddSprite(SpriteComponent *sprite);
  void RemoveSprite(SpriteComponent *sprite);
  SDL_Texture *GetTexture(const std::string &fileName);

private:
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();
  void LoadData();
  void UnloadData();

  SDL_Window *_window;
  SDL_Renderer *_renderer;
  bool _isRunning;
  Uint32 _ticksCount;

  bool _updatingActors;
  std::vector<class Actor *> _actors;
  std::vector<class Actor *> _pendingActors;
  std::vector<class SpriteComponent *> _sprites;
  std::unordered_map<std::string, SDL_Texture *> _textures;

  class Ship *_ship;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_GAME_HPP
