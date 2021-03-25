#include "Tower.hpp"

#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "MoveComponent.hpp"
#include "SpriteComponent.hpp"

using namespace gpcpp::c04;
Tower::Tower(class Game *Game) : Actor(Game) {
  auto SC = new SpriteComponent(this);
  SC->setTexture(Game->getTexture("assets/Tower.png"));

  Move = new MoveComponent(this);

  NextAttack = AttackTime;
}

void Tower::updateActor(float DeltaTime) {
  Actor::updateActor(DeltaTime);
  NextAttack -= DeltaTime;
  if (NextAttack > 0)
    return;

  auto Enemy = getGame()->getNearestEnemy(getPosition());
  if (Enemy != nullptr) {
    const auto P = getPosition();
    const auto EP = Enemy->getPosition();
    const auto Direction = EP - P;
    if (glm::distance(EP, P) < AttackRange) {
      setRotation(std::atan2(-Direction.y, Direction.x));
      auto *B = new Bullet(getGame());
      B->setPosition(P);
      B->setRotation(getRotation());
    }
  }

  NextAttack += AttackTime;
}
