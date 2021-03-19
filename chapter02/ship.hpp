#ifndef GPCPP_CHAPTER02_SHIP_HPP
#define GPCPP_CHAPTER02_SHIP_HPP

#include "actor.hpp"

namespace gpcpp::c02 {

class Ship : public Actor {
public:
  Ship(class Game *game);
  void UpdateActor(float deltaTime) override;
  void ProcessKeyboard(const uint8_t *state);

  float GetRightSpeed() const { return _rightSpeed; }
  float GetDownSpeed() const { return _downSpeed; }

private:
  float _rightSpeed;
  float _downSpeed;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_SHIP_HPP
