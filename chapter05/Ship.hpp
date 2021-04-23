#ifndef GPCPP_CHAPTER05_SHIP_HPP
#define GPCPP_CHAPTER05_SHIP_HPP

#include "Actor.hpp"

namespace gpcpp::c05 {

class Ship : public Actor {
public:
  explicit Ship(class Game *Game);

  void updateActor(float DeltaTime) override;
  void ActorInput(const uint8_t *KeyState) override;

  [[nodiscard]] glm::vec2 getDefaultPosition() const { return DefaultPosition; }
  [[nodiscard]] float getDefaultRotation() const { return DefaultRotation; }

  void setDefaultPosition(const glm::vec2 &P) { DefaultPosition = P; }
  void setDefaultRotation(float R) { DefaultRotation = R; }
  void setActive(bool Flag);

private:
  float LaserCoolDown;
  float SafeTimeCurrent;
  glm::vec2 DefaultPosition;
  float DefaultRotation;
  bool IsActive;
  bool IsSafeTime;

  class SpriteComponent *Sprite;
  class InputComponent *Input;
  class CollisionComponent *Collision;
};

} // namespace gpcpp::c05

#endif // GPCPP_CHAPTER05_SHIP_HPP
