#ifndef GPCPP_CHAPTER03_ASTEROID_HPP
#define GPCPP_CHAPTER03_ASTEROID_HPP

#include "Actor.hpp"

namespace gpcpp::c03 {

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

} // namespace gpcpp::c03

#endif // GPCPP_CHAPTER03_ASTEROID_HPP
