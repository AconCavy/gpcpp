#include "game.hpp"

using namespace gpcpp::c02;

int main(int Argc, char *Argv[]) {
  Game Game;
  bool Success = Game.initialize();
  if (Success) {
	Game.runLoop();
  }

  Game.shutdown();

  return 0;
}
