#include "NavComponent.hpp"

#include "Actor.hpp"
#include "Tile.hpp"

using namespace gpcpp::c04;

NavComponent::NavComponent(class Actor *Owner, int UpdateOrder)
    : MoveComponent(Owner, UpdateOrder), NextNode(nullptr) {}

void NavComponent::update(float DeltaTime) {
  if (glm::distance(Owner->getPosition(), NextNode->getPosition()) <= 2.0f) {
    NextNode = NextNode->getParent();
    turnTo(NextNode->getPosition());
  }
  MoveComponent::update(DeltaTime);
}

void NavComponent::setStart(const struct Tile *Start) {
  NextNode = Start->getParent();
  turnTo(NextNode->getPosition());
}

void NavComponent::turnTo(const glm::vec2 &Position) {
  auto Direction = Position - Owner->getPosition();
  float Angle = std::atan2(-Direction.y, Direction.x);
  Owner->setRotation(Angle);
}
