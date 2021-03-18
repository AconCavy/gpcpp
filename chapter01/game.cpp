#include <algorithm>
#include <random>

#include "game.hpp"

using namespace std;

#define HEIGHT 768
#define WIDTH 1024

const int thickness = 15;
const int paddleHeight = 100;
const int speedLimit = 3;
const int ballCount = 5;
const int velocityLimit = 300;

Game::Game() : _window(nullptr), _renderer(nullptr), _isRunning(true)
{
	_players.push_back({{ 0, HEIGHT / 2 }, 0 });
	_players.push_back({{ WIDTH - thickness, HEIGHT / 2 }, 0 });

	std::random_device rnd;
	std::mt19937 mt32(rnd());
	std::uniform_int_distribution<int> rnd_range(-velocityLimit, velocityLimit);
	for (int i = 0; i < ballCount; ++i)
	{
		float vx = rnd_range(mt32);
		float vy = rnd_range(mt32);
		_balls.push_back({{ WIDTH / 2, HEIGHT / 2 }, { vx, vy }});
	}
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

	if (state[SDL_SCANCODE_W]) _players[0].direction--;
	if (state[SDL_SCANCODE_S]) _players[0].direction++;

	if (state[SDL_SCANCODE_I]) _players[1].direction--;
	if (state[SDL_SCANCODE_K]) _players[1].direction++;

	_players[0].direction = max(-speedLimit, min(speedLimit, _players[0].direction));
	_players[1].direction = max(-speedLimit, min(speedLimit, _players[1].direction));
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + 16));

	Uint32 ct = SDL_GetTicks();
	float dt = (float)(ct - _ticksCount) / 1000;
	_ticksCount = ct;

	dt = std::min(dt, 0.05f);

	for (Paddle& player : _players)
	{
		if (player.direction == 0) continue;
		float y = player.position.y + player.direction * 300.0f * dt;
		float h = paddleHeight / 2 + thickness;
		y = max((float)h, y);
		y = min((float)HEIGHT - h, y);
		player.position.y = y;
	}

	for (Ball& ball : _balls)
	{
		ball.position += ball.velocity * dt;

		if (ball.position.x >= WIDTH - thickness && ball.velocity.x > 0)
			ball.velocity.x *= -1;

		if (ball.position.y <= thickness && ball.velocity.y < 0 ||
			ball.position.y >= HEIGHT - thickness && ball.velocity.y > 0)
			ball.velocity.y *= -1;

		for (Paddle player : _players)
		{
			float dx = abs(player.position.x - ball.position.x);
			float dy = abs(player.position.y - ball.position.y);
			if (dx <= thickness && dy <= paddleHeight / 2) ball.velocity.x *= -1;
		}

		if (ball.position.x <= 0 || WIDTH <= ball.position.x)
		{
			ball.position.x = WIDTH / 2;
			ball.position.y = HEIGHT / 2;
		}
	}
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
	wall.y = HEIGHT - thickness;
	SDL_RenderFillRect(_renderer, &wall);

	// players
	for (Paddle player : _players)
	{
		SDL_Rect rect{
			static_cast<int>(player.position.x - thickness / 2),
			static_cast<int>(player.position.y - paddleHeight / 2),
			thickness,
			paddleHeight };
		SDL_RenderFillRect(_renderer, &rect);
	}

	// balls
	for (Ball ball : _balls)
	{
		SDL_Rect rect{
			(int)(ball.position.x - thickness / 2),
			(int)(ball.position.y - thickness / 2),
			thickness,
			thickness };
		SDL_RenderFillRect(_renderer, &rect);
	}

	SDL_RenderPresent(_renderer);
}
