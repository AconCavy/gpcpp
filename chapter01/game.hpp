#ifndef GPCPP_CHAPTER01_GAME_HPP_
#define GPCPP_CHAPTER01_GAME_HPP_

#include <SDL2/SDL.h>
#include "vector.hpp"

class Game
{
 public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

 private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _isRunning;

	Vector2 _paddlePosition;
	Vector2 _ballPosition;
	Vector2 _ballVelocity;

	Uint32 _ticksCount;
	int _paddleDirection;

};

#endif //GPCPP_CHAPTER01_GAME_HPP_
