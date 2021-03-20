#include <algorithm>
#include <random>

#include "game.hpp"

using namespace gpcpp::c01;

const int Height = 768;
const int Width = 1024;

const int Thickness = 15;
const int PaddleHeight = 100;
const int SpeedLimit = 3;
const int BallCount = 5;
const int VelocityLimit = 300;

Game::Game() : Window(nullptr), Renderer(nullptr), IsRunning(true) {
  Players.push_back({{0, Height / 2}, 0});
  Players.push_back({{Width - Thickness, Height / 2}, 0});

  std::random_device Rnd;
  std::mt19937 MT32(Rnd());
  std::uniform_int_distribution<int> RndRange(-VelocityLimit, VelocityLimit);
  for (int i = 0; i < BallCount; ++i) {
	float Vx = RndRange(MT32);
	float Vy = RndRange(MT32);
	Balls.push_back({{Width / 2, Height / 2}, {Vx, Vy}});
  }
}

bool Game::initialize() {
  int SDLResult = SDL_Init(SDL_INIT_VIDEO);
  if (SDLResult != 0) {
	SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
	return false;
  }

  Window = SDL_CreateWindow("Game Programming in C++ (Chapter 01)", 100, 100, Width, Height, 0);
  if (!Window) {
	SDL_Log("Failed to create window: %s", SDL_GetError());
	return false;
  }

  Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!Renderer) {
	SDL_Log("Failed to create renderer: %s", SDL_GetError());
	return false;
  }

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
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
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

  if (State[SDL_SCANCODE_W])
	Players[0].Direction--;
  if (State[SDL_SCANCODE_S])
	Players[0].Direction++;

  if (State[SDL_SCANCODE_I])
	Players[1].Direction--;
  if (State[SDL_SCANCODE_K])
	Players[1].Direction++;

  Players[0].Direction = std::max(-SpeedLimit, std::min(SpeedLimit, Players[0].Direction));
  Players[1].Direction = std::max(-SpeedLimit, std::min(SpeedLimit, Players[1].Direction));
}

void Game::updateGame() {
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + 16));

  Uint32 CurrentTicks = SDL_GetTicks();
  float DeltaTime = (float)(CurrentTicks - TicksCount) / 1000;
  TicksCount = CurrentTicks;

  DeltaTime = std::min(DeltaTime, 0.05f);

  for (auto &Player : Players) {
	if (Player.Direction == 0)
	  continue;
	float Y = Player.Position.Y + static_cast<float>(Player.Direction) * 300.0f * DeltaTime;
	float H = static_cast<float>(PaddleHeight) / 2 + Thickness;
	Y = std::max((float)H, Y);
	Y = std::min((float)Height - H, Y);
	Player.Position.Y = Y;
  }

  for (auto &Ball : Balls) {
	Ball.Position += Ball.Velocity * DeltaTime;

	if (Ball.Position.X >= Width - Thickness && Ball.Velocity.X > 0)
	  Ball.Velocity.X *= -1;

	if (Ball.Position.Y <= Thickness && Ball.Velocity.Y < 0 ||
		Ball.Position.Y >= Height - Thickness && Ball.Velocity.Y > 0)
	  Ball.Velocity.Y *= -1;

	for (Paddle player : Players) {
	  float Dx = abs(player.Position.X - Ball.Position.X);
	  float Dy = abs(player.Position.Y - Ball.Position.Y);
	  if (Dx <= Thickness && Dy <= static_cast<float>(PaddleHeight) / 2)
		Ball.Velocity.X *= -1;
	}

	if (Ball.Position.X <= 0 || Width <= Ball.Position.X) {
	  Ball.Position.X = static_cast<float>(Width) / 2;
	  Ball.Position.Y = static_cast<float>(Height) / 2;
	}
  }
}

void Game::generateOutput() {
  // background
  SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
  SDL_RenderClear(Renderer);

  // walls
  // top
  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
  SDL_Rect Wall{0, 0, Width, Thickness};
  SDL_RenderFillRect(Renderer, &Wall);
  // bottom
  Wall.y = Height - Thickness;
  SDL_RenderFillRect(Renderer, &Wall);

  // players
  for (auto Player : Players) {
	SDL_Rect Rect{
		static_cast<int>(Player.Position.X - static_cast<float>(Thickness) / 2),
		static_cast<int>(Player.Position.Y - static_cast<float>(PaddleHeight) / 2),
		Thickness,
		PaddleHeight};
	SDL_RenderFillRect(Renderer, &Rect);
  }

  // balls
  for (auto Ball : Balls) {
	float Tmp = static_cast<float>(Thickness) / 2;
	SDL_Rect Rect{
		(int)(Ball.Position.X - Tmp),
		(int)(Ball.Position.Y - Tmp),
		Thickness,
		Thickness};
	SDL_RenderFillRect(Renderer, &Rect);
  }

  SDL_RenderPresent(Renderer);
}
