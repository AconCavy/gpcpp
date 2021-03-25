#ifndef GPCPP_CHAPTER04_ENEMY_HPP
#define GPCPP_CHAPTER04_ENEMY_HPP

#include "Actor.hpp"

namespace gpcpp::c04 {

class Enemy : public Actor {
public:
  explicit Enemy(class Game *Game);
  ~Enemy();

  void updateActor(float DeltaTime) override;

  class CollisionComponent *getCollision() {
    return Collision;
  }

private:
  class CollisionComponent *Collision;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_ENEMY_HPP
