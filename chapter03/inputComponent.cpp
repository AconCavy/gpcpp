#include "inputComponent.hpp"

using namespace gpcpp::c03;

InputComponent::InputComponent(class Actor *Owner)
	: MoveComponent(Owner),
	  MaxAngularSpeed(0),
	  MaxForwardSpeed(0),
	  ForwardKey(0),
	  BackKey(0),
	  ClockwiseKey(0),
	  CounterClockwiseKey(0) {
}
void InputComponent::processInput(const uint8_t *KeyState) {
  auto ForwardSpeed = 0.0f;
  if (KeyState[ForwardKey])
	ForwardSpeed += MaxForwardSpeed;
  if (KeyState[BackKey])
	ForwardSpeed -= MaxForwardSpeed;
  setForwardSpeed(ForwardSpeed);

  auto AngularSpeed = 0.0;
  if (KeyState[ClockwiseKey])
	AngularSpeed += MaxAngularSpeed;
  if (KeyState[CounterClockwiseKey])
	AngularSpeed -= MaxAngularSpeed;
  setAngularSpeed(AngularSpeed);
}


