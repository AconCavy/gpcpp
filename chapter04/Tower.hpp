#ifndef GPCPP_CHAPTER04_TOWER_HPP
#define GPCPP_CHAPTER04_TOWER_HPP

#include "Actor.hpp"

namespace gpcpp::c04 {

class Tower : public Actor {
public:
  explicit Tower(class Game *Game);
  void updateActor(float DeltaTime) override;

private:
  class MoveComponent *Move;
  float NextAttack;
  const float AttackTime = 2.5f;
  const float AttackRange = 100;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_TOWER_HPP
