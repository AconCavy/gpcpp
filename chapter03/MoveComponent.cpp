#include "MoveComponent.hpp"

#include "Actor.hpp"
#include "Math.hpp"

using namespace gpcpp::c03;

const double EPS = 1e-6;

MoveComponent::MoveComponent(class Actor *Owner, int UpdateOrder)
    : Component(Owner, UpdateOrder), AngularSpeed(0), ForwardSpeed(0) {}

void MoveComponent::update(float DeltaTime) {
  if (!IsEnabled)
    return;

  if (!isNearZero(AngularSpeed, EPS)) {
    auto R = Owner->getRotation();
    R += AngularSpeed * DeltaTime;
    Owner->setRotation(R);
  }

  if (!isNearZero(ForwardSpeed, EPS)) {
    auto P = Owner->getPosition();
    P += Owner->getForward() * ForwardSpeed * DeltaTime;
    Owner->setPosition(P);
  }
}
