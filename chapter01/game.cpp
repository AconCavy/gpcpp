#include <algorithm>
#include "game.hpp"
using namespace std;

#define HEIGHT 768
#define WIDTH 1024

const int thickness = 15;
const int paddleHeight = 100;
const int speedLimit = 3;

Game::Game() : _window(nullptr), _renderer(nullptr), _isRunning(true)
{
	_paddlePosition.x = 0;
	_paddlePosition.y = HEIGHT / 2;
	_paddleDirection = 0;

	_ballPosition.x = WIDTH / 2;
	_ballPosition.y = HEIGHT / 2;
	_ballVelocity.x = -200;
	_ballVelocity.y = -235;
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	_window = SDL_CreateWindow("Game Programming in C++ (Chapter 01)", 100, 100, WIDTH, HEIGHT, 0);
	if (!_window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::RunLoop()
{
	while (_isRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(_renderer);
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_isRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE]) _isRunning = false;

	if (state[SDL_SCANCODE_W]) _paddleDirection--;
	if (state[SDL_SCANCODE_S]) _paddleDirection++;

	_paddleDirection = max(-speedLimit, min(speedLimit, _paddleDirection));
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + 16));

	Uint32 ct = SDL_GetTicks();
	float dt = (float)(ct - _ticksCount) / 1000;
	_ticksCount = ct;

	dt = std::min(dt, 0.05f);

	if (_paddleDirection != 0)
	{
		float y = _paddlePosition.y + _paddleDirection * 300.0f * dt;
		float h = paddleHeight / 2 + thickness;
		y = max((float)h, y);
		y = min((float)HEIGHT - h, y);
		_paddlePosition.y = y;
	}

	_ballPosition += _ballVelocity * dt;

	if (_ballPosition.x >= WIDTH - thickness && _ballVelocity.x > 0)
		_ballVelocity.x *= -1;

	if (_ballPosition.y <= thickness && _ballVelocity.y < 0 ||
		_ballPosition.y >= HEIGHT - thickness && _ballVelocity.y > 0)
		_ballVelocity.y *= -1;

	float diff = abs(_paddlePosition.y - _ballPosition.y);
	if (diff <= paddleHeight / 2 &&
		_ballPosition.x <= 25 && _ballPosition.x >= 20 &&
		_ballVelocity.x < 0)
		_ballVelocity.x *= -1;

}

void Game::GenerateOutput()
{
	// background
	SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
	SDL_RenderClear(_renderer);

	// walls
	// top
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_Rect wall{ 0, 0, WIDTH, thickness };
	SDL_RenderFillRect(_renderer, &wall);
	// bottom
	wall.y = 768 - thickness;
	SDL_RenderFillRect(_renderer, &wall);
	// right
	wall.x = WIDTH - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = HEIGHT;
	SDL_RenderFillRect(_renderer, &wall);

	// paddle
	SDL_Rect paddle{
		static_cast<int>(_paddlePosition.x - thickness / 2),
		static_cast<int>(_paddlePosition.y - paddleHeight / 2),
		thickness,
		paddleHeight };
	SDL_RenderFillRect(_renderer, &paddle);

	// ball
	SDL_Rect ball{
		(int)(_ballPosition.x - thickness / 2),
		(int)(_ballPosition.y - thickness / 2),
		thickness,
		thickness };
	SDL_RenderFillRect(_renderer, &ball);

	SDL_RenderPresent(_renderer);
}
