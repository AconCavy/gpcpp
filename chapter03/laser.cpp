#include "laser.hpp"

#include "asteroid.hpp"
#include "circleComponent.hpp"
#include "game.hpp"
#include "moveComponent.hpp"
#include "spriteComponent.hpp"

using namespace gpcpp::c03;

Laser::Laser(class Game *Game)
	: Actor(Game),
	  DeathTimer(1) {
  auto SC = new SpriteComponent(this);
  SC->setTexture(Game->getTexture("assets/Laser.png"));

  auto MC = new MoveComponent(this);
  MC->setForwardSpeed(800);

  auto CC = new CircleComponent(this);
  CC->setRadius(11);
}

void Laser::updateActor(float DeltaTime) {
  DeathTimer -= DeltaTime;
  if (DeathTimer <= 0) {
	setState(Dead);
	return;
  }

  auto Asteroids = getGame()->getAsteroids();
  for (auto A : Asteroids) {
	if (intersect(*Circle, *(A->getCircle()))) {
	  setState(Dead);
	  A->setState(Dead);
	  break;
	}
  }
}
