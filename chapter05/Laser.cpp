#include "Laser.hpp"

#include "Asteroid.hpp"
#include "CollisionComponent.hpp"
#include "Game.hpp"
#include "MoveComponent.hpp"
#include "SpriteComponent.hpp"

using namespace gpcpp::c05;

Laser::Laser(class Game *Game) : Actor(Game), DeathTimer(1) {
  auto SC = new SpriteComponent(this);
  SC->setTexture(Game->getTexture("assets/Laser.png"));

  auto MC = new MoveComponent(this);
  MC->setForwardSpeed(800);

  Collision = new CollisionComponent(this);
  Collision->setRadius(11);
}

void Laser::updateActor(float DeltaTime) {
  DeathTimer -= DeltaTime;
  if (DeathTimer <= 0) {
    setState(Dead);
    return;
  }

  auto Asteroids = getGame()->getAsteroids();
  for (auto A : Asteroids) {
    if (Collision->isColliding(*(A->getCollision()))) {
      setState(Dead);
      A->setState(Dead);
      break;
    }
  }
}
