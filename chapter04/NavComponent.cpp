#include "NavComponent.hpp"

#include "Actor.hpp"

using namespace gpcpp::c04;

NavComponent::NavComponent(class Actor *Owner, int UpdateOrder)
    : MoveComponent(Owner, UpdateOrder), NextPosition({}) {}

void NavComponent::update(float DeltaTime) {
  auto D = glm::distance(Owner->getPosition(), NextPosition);
  if (D <= 2.0f) {
    //    NextPosition = getNextPosition();
    TurnTo(NextPosition);
  }
  MoveComponent::update(DeltaTime);
}

void NavComponent::TurnTo(const glm::vec2 &Position) {
  auto Direction = Position - Owner->getPosition();
  float Angle = std::atan2(-Direction.y, Direction.x);
  Owner->setRotation(Angle);
}
