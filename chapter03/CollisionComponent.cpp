#include "CollisionComponent.hpp"

#include "Actor.hpp"

using namespace gpcpp::c03;

CollisionComponent::CollisionComponent(class Actor *Owner)
    : Component(Owner), Radius(0), Center({}) {}

const glm::vec2 &CollisionComponent::getCenter() const {
  return Owner->getPosition();
}
float CollisionComponent::getRadius() const {
  return Owner->getScale() * Radius;
}

bool CollisionComponent::isColliding(const CollisionComponent &other) const {
  if (!IsEnabled)
    return false;

  auto Diff = getCenter() - other.getCenter();
  auto D2 = Diff.x * Diff.x + Diff.y * Diff.y;
  auto R = getRadius() + other.getRadius();

  return D2 <= R * R;
}