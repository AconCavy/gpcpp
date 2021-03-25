#ifndef GPCPP_CHAPTER04_BULLET_HPP
#define GPCPP_CHAPTER04_BULLET_HPP

#include "Actor.hpp"

namespace gpcpp::c04 {

class Bullet : public Actor {
public:
  explicit Bullet(class Game *Game);

  void updateActor(float DeltaTime) override;

private:
  class CollisionComponent *Collision;
  float LiveTime;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_BULLET_HPP
