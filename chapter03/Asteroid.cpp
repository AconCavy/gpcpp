#include "Asteroid.hpp"

#include <random>

#include "CollisionComponent.hpp"
#include "Game.hpp"
#include "Math.hpp"
#include "MoveComponent.hpp"
#include "PositionWrapComponent.hpp"
#include "SpriteComponent.hpp"

using namespace gpcpp::c03;

Asteroid::Asteroid(class Game *Game) : Actor(Game) {
  setPosition({gpcpp::getRandomRealRange(0, Game->Width),
               gpcpp::getRandomRealRange(0, Game->Height)});

  setRotation(
      static_cast<float>(gpcpp::getRandomRealRange(0, glm::pi<float>() * 2)));

  auto SC = new SpriteComponent(this);
  SC->setTexture(Game->getTexture("assets/Asteroid.png"));

  auto MC = new MoveComponent(this);
  MC->setForwardSpeed(150);

  auto PWC = new PositionWrapComponent(this);
  PWC->setWidth(static_cast<float>(Game->Width));
  PWC->setHeight(static_cast<float>(Game->Height));
  PWC->setMargin(static_cast<float>(25));

  Collision = new CollisionComponent(this);
  Collision->setRadius(40);

  Game->addAsteroid(this);
}
Asteroid::~Asteroid() { getGame()->removeAsteroid(this); }
