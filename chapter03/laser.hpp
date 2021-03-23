#ifndef GPCPP_CHAPTER03_LASER_HPP
#define GPCPP_CHAPTER03_LASER_HPP

#include "actor.hpp"

namespace gpcpp::c03 {

class Laser : public Actor {
public:
  explicit Laser(class Game *Game);

  void updateActor(float DeltaTime) override;

private:
  class CircleComponent *Circle;
  float DeathTimer;
};

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER03_LASER_HPP
