#include "game.hpp"

#include <SDL_image.h>

using namespace gpcpp::c03;

Game::Game()
	: Window(nullptr),
	  Renderer(nullptr),
	  IsRunning(true),
	  UpdatingActors(false) {
}

bool Game::initialize() {
  int SDLResult = SDL_Init(SDL_INIT_VIDEO);
  if (SDLResult != 0) {
	SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
	return false;
  }

  Window = SDL_CreateWindow("Game Programming in C++ (Chapter 03)", 100, 100, Width, Height, 0);
  if (!Window) {
	SDL_Log("Failed to create window: %s", SDL_GetError());
	return false;
  }

  Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!Renderer) {
	SDL_Log("Failed to create renderer: %s", SDL_GetError());
	return false;
  }

  int IMGResult = IMG_Init(IMG_INIT_PNG);
  if (IMGResult == 0) {
	SDL_Log("Failed to initialize SDL_Image: %s", IMG_GetError());
	return false;
  }

  loadData();
  TicksCount = SDL_GetTicks();

  return true;
}

void Game::runLoop() {
  while (IsRunning) {
	processInput();
	updateGame();
	generateOutput();
  }
}
void Game::shutdown() {
  unloadData();
  IMG_Quit();
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

void Game::addActor(Actor *A) {
  if (UpdatingActors)
	PendingActors.emplace_back(A);
  else
	Actors.emplace_back(A);
}

void Game::removeActor(Actor *A) {
  auto E = PendingActors.end();
  auto I = std::find(PendingActors.begin(), E, A);
  if (I != E) {
	std::iter_swap(I, E - 1);
	PendingActors.pop_back();
  }

  E = Actors.end();
  I = std::find(Actors.begin(), E, A);
  if (I != E) {
	std::iter_swap(I, E - 1);
	Actors.pop_back();
  }
}

void Game::addSprite(SpriteComponent *SC) {
  auto Order = SC->getDrawOrder();
  auto I = Sprites.begin();
  for (; I != Sprites.end(); ++I) {
	if (Order < (*I)->getDrawOrder()) {
	  break;
	}
  }
  Sprites.insert(I, SC);
}

void Game::removeSprite(SpriteComponent *SC) {
  auto I = std::find(Sprites.begin(), Sprites.end(), SC);
  Sprites.erase(I);
}

SDL_Texture *Game::getTexture(const std::string &FileName) {
  SDL_Texture *Texture = nullptr;
  auto I = Textures.find(FileName);
  if (I != Textures.end()) {
	Texture = I->second;
	return Texture;
  }

  SDL_Surface *Surface = IMG_Load(FileName.c_str());
  if (!Surface) {
	SDL_Log("Failed to load Texture file %s", FileName.c_str());
	return nullptr;
  }

  Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
  SDL_FreeSurface(Surface);
  if (!Texture) {
	SDL_Log("Failed to convert Surface to Texture for %s", FileName.c_str());
	return nullptr;
  }

  Textures.emplace(FileName.c_str(), Texture);
  return Texture;
}

void Game::processInput() {
  SDL_Event Event;
  while (SDL_PollEvent(&Event)) {
	switch (Event.type) {
	case SDL_QUIT: IsRunning = false;
	  break;
	}
  }

  const Uint8 *State = SDL_GetKeyboardState(nullptr);
  if (State[SDL_SCANCODE_ESCAPE])
	IsRunning = false;
}
void Game::updateGame() {
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + DeltaCount));
  Uint32 CurrentTicks = SDL_GetTicks();
  float DeltaTime = std::min(static_cast<float>(CurrentTicks - TicksCount) / 1000, 0.05f);
  TicksCount = CurrentTicks;

  UpdatingActors = true;
  for (auto Actor : Actors) {
	Actor->update(DeltaTime);
  }
  UpdatingActors = false;

  for (auto Actor : PendingActors) {
	Actors.emplace_back(Actor);
  }
  PendingActors.clear();

  std::vector<Actor *> DeadActors;
  for (auto Actor: Actors) {
	if (Actor->getState() == Actor::Dead)
	  DeadActors.emplace_back(Actor);
  }

  for (auto Actor : DeadActors) {
	delete Actor;
  }
}
void Game::generateOutput() {
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
  SDL_RenderClear(Renderer);

  for (auto Sprite : Sprites)
	Sprite->draw(Renderer);

  SDL_RenderPresent(Renderer);
}
void Game::loadData() {

}
void Game::unloadData() {
  while (!Actors.empty())
	delete Actors.back();

  for (const auto &Texture : Textures)
	SDL_DestroyTexture(Texture.second);
  Textures.clear();
}
