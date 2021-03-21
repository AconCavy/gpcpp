#ifndef GPCPP_CHAPTER03_ASTEROID_HPP
#define GPCPP_CHAPTER03_ASTEROID_HPP

#include "actor.hpp"

namespace gpcpp::c03 {

class Asteroid : public Actor {
public:
  explicit Asteroid(class Game *Game);
};

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER03_ASTEROID_HPP
