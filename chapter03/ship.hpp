#ifndef GPCPP_CHAPTER02_SHIP_HPP
#define GPCPP_CHAPTER02_SHIP_HPP

#include "actor.hpp"

namespace gpcpp::c03 {

class Ship : public Actor {
public:
  explicit Ship(class Game *Game);
  void updateActor(float DeltaTime) override;
  void ActorInput(const uint8_t *KeyState) override;

private:
  float LaserCoolDown;
};

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER02_SHIP_HPP
