#ifndef GPCPP_CHAPTER04_MOVECOMPONENT_HPP
#define GPCPP_CHAPTER04_MOVECOMPONENT_HPP

#include "Component.hpp"

namespace gpcpp::c04 {

class MoveComponent : public Component {
public:
  explicit MoveComponent(class Actor *Owner, int UpdateOrder = 10);

  void update(float DeltaTime) override;

  [[nodiscard]] float getAngularSpeed() const { return AngularSpeed; }
  [[nodiscard]] float getForwardSpeed() const { return ForwardSpeed; }

  void setAngularSpeed(float Speed) { AngularSpeed = Speed; }
  void setForwardSpeed(float Speed) { ForwardSpeed = Speed; }

private:
  float AngularSpeed;
  float ForwardSpeed;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_MOVECOMPONENT_HPP
