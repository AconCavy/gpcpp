#include "Bullet.hpp"

#include "CollisionComponent.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "MoveComponent.hpp"
#include "SpriteComponent.hpp"

using namespace gpcpp::c04;

Bullet::Bullet(class Game *Game) : Actor(Game) {
  auto SC = new SpriteComponent(this);
  SC->setTexture(Game->getTexture("assets/Projectile.png"));

  auto MC = new MoveComponent(this);
  MC->setForwardSpeed(400);

  Collision = new CollisionComponent(this);
  Collision->setRadius(5);

  LiveTime = 1;
}
void Bullet::updateActor(float DeltaTime) {
  Actor::updateActor(DeltaTime);
  for (auto Enemy : getGame()->getEnemies()) {
    if (Collision->isColliding(*Enemy->getCollision())) {
      Enemy->setState(Dead);
      setState(Dead);
      return;
    }
  }

  LiveTime -= DeltaTime;
  if (LiveTime <= 0) {
    setState(Dead);
  }
}
