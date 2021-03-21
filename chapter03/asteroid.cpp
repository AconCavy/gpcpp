#include "asteroid.hpp"

#include <random>

#include "game.hpp"
#include "moveComponent.hpp"
#include "math.hpp"

using namespace gpcpp::c03;

Asteroid::Asteroid(class Game *Game) : Actor(Game) {
  setPosition({gpcpp::getRandomRealRange(0, Game->Width),
				  gpcpp::getRandomRealRange(0, Game->Height)});

  setRotation(static_cast<float>(gpcpp::getRandomRealRange(0, gpcpp::PI * 2)));

  auto *SC = new SpriteComponent(this);
  SC->setTexture(Game->getTexture("assets/Asteroid.png"));

  auto MC = new MoveComponent(this);
  MC->setForwardSpeed(150);
}

