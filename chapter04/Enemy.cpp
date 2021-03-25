#include "Enemy.hpp"

#include "CollisionComponent.hpp"
#include "Game.hpp"
#include "Grid.hpp"
#include "Math.hpp"
#include "NavComponent.hpp"
#include "SpriteComponent.hpp"
#include "Tile.hpp"

using namespace gpcpp::c04;

Enemy::Enemy(class Game *Game) : Actor(Game) {
  Game->getEnemies().emplace_back(this);
  auto Start = Game->getGrid()->getStartTile();
  auto SC = new SpriteComponent(this);
  SC->setTexture(Game->getTexture("assets/Airplane.png"));
  setPosition(Start->getPosition());

  auto NC = new NavComponent(this);
  NC->setForwardSpeed(150);
  NC->setStart(Start);

  Collision = new CollisionComponent(this);
  Collision->setRadius(25);
}

Enemy::~Enemy() {
  auto &Enemies = getGame()->getEnemies();
  auto I = std::find(Enemies.begin(), Enemies.end(), this);
  Enemies.erase(I);
}

void Enemy::updateActor(float DeltaTime) {
  Actor::updateActor(DeltaTime);
  auto D = glm::distance(getPosition(),
                         getGame()->getGrid()->getGoalTile()->getPosition());
  const float EPS = 10;
  if (isNearZero(D, EPS))
    setState(Dead);
}
