#include <SDL2/SDL_image.h>

#include "game.hpp"

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

  LoadData();
  _ticksCount = SDL_GetTicks();

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
  UnloadData();
  IMG_Quit();
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

void Game::AddActor(Actor *actor) {
  if (_updatingActors)
	_pendingActors.emplace_back(actor);
  else
	_actors.emplace_back(actor);
}

void Game::RemoveActor(Actor *actor) {
  auto iter = std::find(_pendingActors.begin(), _pendingActors.end(), actor);
  _pendingActors.erase(iter);

  iter = std::find(_actors.begin(), _actors.end(), actor);
  _actors.erase(iter);
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

void Game::RemoveSprite(SpriteComponent *sprite) {
  auto iter = std::find(_sprites.begin(), _sprites.end(), sprite);
  _sprites.erase(iter);
}

SDL_Texture *Game::GetTexture(const std::string &fileName) {
  SDL_Texture *texture = nullptr;
  auto iter = _textures.find(fileName);
  if (iter != _textures.end()) {
	texture = iter->second;
	return texture;
  }

  SDL_Surface *surface = IMG_Load(fileName.c_str());
  if (!surface) {
	SDL_Log("Failed to load texture file %s", fileName.c_str());
	return nullptr;
  }

  texture = SDL_CreateTextureFromSurface(_renderer, surface);
  SDL_FreeSurface(surface);
  if (!texture) {
	SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
	return nullptr;
  }

  _textures.emplace(fileName.c_str(), texture);
  return texture;
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
  float dt = std::min((float)(ct - _ticksCount) / 1000, 0.05f);
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

  std::vector<Actor *> deadActors;
  for (auto actor: _actors) {
	if (actor->GetState() == Actor::Dead)
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

void Game::LoadData() {

}

void Game::UnloadData() {
  while (!_actors.empty())
	delete _actors.back();

  for (const auto &x : _textures)
	SDL_DestroyTexture(x.second);
  _textures.clear();
}

} // namespace gpcpp::c02