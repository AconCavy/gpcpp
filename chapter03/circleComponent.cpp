#include "circleComponent.hpp"

#include "actor.hpp"

using namespace gpcpp::c03;

CircleComponent::CircleComponent(class Actor *Owner)
	: Component(Owner),
	  Radius(0),
	  Center({}) {
}

const glm::vec2 &CircleComponent::getCenter() const {
  return Owner->getPosition();
}
float CircleComponent::getRadius() const {
  return Owner->getScale() * Radius;
}

bool gpcpp::c03::intersect(const CircleComponent &a, const CircleComponent &b) {
  auto Diff = a.getCenter() - b.getCenter();
  auto D2 = Diff.x * Diff.x + Diff.y * Diff.y;
  auto R = a.getRadius() + b.getRadius();

  return D2 <= R * R;
}