#include "moveComponent.hpp"

#include "actor.hpp"
#include "math.hpp"

using namespace gpcpp::c03;

MoveComponent::MoveComponent(class Actor *Owner, int UpdateOrder)
	: Component(Owner, UpdateOrder),
	  AngularSpeed(0),
	  ForwardSpeed(0) {
}

void MoveComponent::update(float DeltaTime) {
  if (!isNearZero(AngularSpeed)) {
	auto R = Owner->getRotation();
	R += AngularSpeed * DeltaTime;
	Owner->setRotation(R);
  }

  if (!isNearZero(ForwardSpeed)) {
	auto P = Owner->getPosition();
	P += ForwardSpeed * DeltaTime;
	Owner->setPosition(P);
  }
}
