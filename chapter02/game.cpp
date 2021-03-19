#include <SDL2/SDL_image.h>

#include "game.hpp"

using namespace std;
using namespace gpcpp::utils;

namespace gpcpp::c02 {

const int Height = 768;
const int Width = 1024;
const int Fps = 60;
const int DeltaCount = 1000 / Fps;

Game::Game() : _window(nullptr), _renderer(nullptr), _isRunning(true) {
}

bool Game::Initialize() {
  int sdlResult = SDL_Init(SDL_INIT_VIDEO);
  if (sdlResult != 0) {
	SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
	return false;
  }

  int imgResult = IMG_Init(IMG_INIT_PNG);
  if (imgResult == 0) {
	SDL_Log("Failed to initialize SDL_Image: %s", IMG_GetError());
	return false;
  }

  _window = SDL_CreateWindow("Game Programming in C++ (Chapter 01)", 100, 100, Width, Height, 0);
  if (!_window) {
	SDL_Log("Failed to create window: %s", SDL_GetError());
	return false;
  }

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!_renderer) {
	SDL_Log("Failed to create renderer: %s", SDL_GetError());
	return false;
  }

  return true;
}

void Game::RunLoop() {
  while (_isRunning) {
	ProcessInput();
	UpdateGame();
	GenerateOutput();
  }
}

void Game::Shutdown() {
  SDL_DestroyRenderer(_renderer);
}

void Game::ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
	switch (event.type) {
	case SDL_QUIT: _isRunning = false;
	  break;
	}
  }

  const Uint8 *state = SDL_GetKeyboardState(nullptr);
  if (state[SDL_SCANCODE_ESCAPE])
	_isRunning = false;

}

void Game::UpdateGame() {
  // Calculate delta time
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + DeltaCount));
  Uint32 ct = SDL_GetTicks();
  float dt = min((float)(ct - _ticksCount) / 1000, 0.05f);
  _ticksCount = ct;

  // Update actors
  _updatingActors = true;
  for (auto actor : _actors) {
	actor.Update(dt);
  }
  _updatingActors = false;

  // Resolve pending
  for (auto &actor : _pendingActors) {
	_actors.emplace_back(actor);
  }
  _pendingActors.clear();

  vector<Actor *> deadActors;
  for (auto actor: _actors) {
	if (actor.GetState() == Actor::Dead)
	  deadActors.emplace_back(actor);
  }

  for (auto actor : deadActors) {
	delete actor;
  }
}

void Game::GenerateOutput() {
  for (auto sprite : _sprites)
	sprite->Draw(_renderer);
}

void Game::AddActor(Actor *actor) {
  if (_updatingActors)
	_pendingActors.emplace_back(actor);
  else
	_actors.emplace_back(actor);
}

void Game::RemoveActor(Actor *actor) {

}

void Game::AddSprite(SpriteComponent *sprite) {
  auto myDrawOrder = sprite->GetDrawOrder();
  auto iter = _sprites.begin();
  while (iter != _sprites.end()) {
	if (myDrawOrder < (*iter)->GetDrawOrder())
	  break;
	iter++;
  }

  _sprites.insert(iter, sprite);
}

} // namespace gpcpp::c02