#include "collisionComponent.hpp"

#include "actor.hpp"

using namespace gpcpp::c03;

CollisionComponent::CollisionComponent(class Actor *Owner)
	: Component(Owner),
	  Radius(0),
	  Center({}) {
}

const glm::vec2 &CollisionComponent::getCenter() const {
  return Owner->getPosition();
}
float CollisionComponent::getRadius() const {
  return Owner->getScale() * Radius;
}

bool gpcpp::c03::intersect(const CollisionComponent &a, const CollisionComponent &b) {
  auto Diff = a.getCenter() - b.getCenter();
  auto D2 = Diff.x * Diff.x + Diff.y * Diff.y;
  auto R = a.getRadius() + b.getRadius();

  return D2 <= R * R;
}