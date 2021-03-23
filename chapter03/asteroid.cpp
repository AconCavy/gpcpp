#include "asteroid.hpp"

#include <random>

#include "circleComponent.hpp"
#include "game.hpp"
#include "math.hpp"
#include "moveComponent.hpp"
#include "positionWrapComponent.hpp"
#include "spriteComponent.hpp"

using namespace gpcpp::c03;

Asteroid::Asteroid(class Game *Game) : Actor(Game) {
  setPosition({gpcpp::getRandomRealRange(0, Game->Width),
				  gpcpp::getRandomRealRange(0, Game->Height)});

  setRotation(static_cast<float>(gpcpp::getRandomRealRange(0, gpcpp::PI * 2)));

  auto SC = new SpriteComponent(this);
  SC->setTexture(Game->getTexture("assets/Asteroid.png"));

  auto MC = new MoveComponent(this);
  MC->setForwardSpeed(150);

  auto PWC = new PositionWrapComponent(this);
  PWC->setWidth(static_cast<float>(Game->Width));
  PWC->setHeight(static_cast<float>(Game->Height));
  PWC->setMargin(static_cast<float>(25));

  Circle = new CircleComponent(this);
  Circle->setRadius(40);

  Game->addAsteroid(this);
}
Asteroid::~Asteroid() {
  getGame()->removeAsteroid(this);
}

