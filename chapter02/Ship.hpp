#ifndef GPCPP_CHAPTER02_SHIP_HPP
#define GPCPP_CHAPTER02_SHIP_HPP

#include "Actor.hpp"

namespace gpcpp::c02 {

class Ship : public Actor {
public:
  explicit Ship(class Game *Game);

  void updateActor(float DeltaTime) override;
  void processKeyboard(const uint8_t *State);

  [[nodiscard]] float getRightSpeed() const { return RightSpeed; }
  [[nodiscard]] float getDownSpeed() const { return DownSpeed; }

private:
  float RightSpeed;
  float DownSpeed;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_SHIP_HPP
