#ifndef GPCPP_CHAPTER05_LASER_HPP
#define GPCPP_CHAPTER05_LASER_HPP

#include "Actor.hpp"

namespace gpcpp::c05 {

class Laser : public Actor {
public:
  explicit Laser(class Game *Game);

  void updateActor(float DeltaTime) override;

private:
  class CollisionComponent *Collision;
  float DeathTimer;
};

} // namespace gpcpp::c05

#endif // GPCPP_CHAPTER05_LASER_HPP
