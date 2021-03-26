#ifndef GPCPP_CHAPTER05_ASTEROID_HPP
#define GPCPP_CHAPTER05_ASTEROID_HPP

#include "Actor.hpp"

namespace gpcpp::c05 {

class Asteroid : public Actor {
public:
  explicit Asteroid(class Game *Game);
  ~Asteroid() override;

  class CollisionComponent *getCollision() {
    return Collision;
  }

private:
  class CollisionComponent *Collision;
};

} // namespace gpcpp::c05

#endif // GPCPP_CHAPTER05_ASTEROID_HPP
