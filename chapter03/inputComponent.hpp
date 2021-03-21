#ifndef GPCPP_CHAPTER03_INPUTCOMPONENT_HPP
#define GPCPP_CHAPTER03_INPUTCOMPONENT_HPP

#include "moveComponent.hpp"

namespace gpcpp::c03 {

class InputComponent : public MoveComponent {
public:
  explicit InputComponent(class Actor *Owner);

  void processInput(const uint8_t *KeyState) override;

  [[nodiscard]] float getMaxAngularSpeed() const { return MaxAngularSpeed; }
  [[nodiscard]] float getMaxForward() const { return MaxForwardSpeed; }
  [[nodiscard]] int getForwardKey() const { return ForwardKey; }
  [[nodiscard]] int getBackKey() const { return BackKey; }
  [[nodiscard]] int getClockwiseKey() const { return ClockwiseKey; }
  [[nodiscard]] int getCounterClockwiseKey() const { return CounterClockwiseKey; }

  void setMaxAngularSpeed(float Speed) { MaxAngularSpeed = Speed; }
  void setMaxForwardSpeed(float Speed) { MaxForwardSpeed = Speed; }
  void setForwardKey(int Key) { ForwardKey = Key; }
  void setBackKey(int Key) { ForwardKey = Key; }
  void setClockwiseKey(int Key) { ClockwiseKey = Key; }
  void setCounterClockwiseKey(int Key) { CounterClockwiseKey = Key; }

private:
  float MaxAngularSpeed;
  float MaxForwardSpeed;
  int ForwardKey;
  int BackKey;
  int ClockwiseKey;
  int CounterClockwiseKey;
};

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER03_INPUTCOMPONENT_HPP
