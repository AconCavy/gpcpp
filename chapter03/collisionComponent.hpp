#ifndef GPCPP_CHAPTER03_COLLISIONCOMPONENT_HPP
#define GPCPP_CHAPTER03_COLLISIONCOMPONENT_HPP

#include <glm/glm.hpp>

#include "component.hpp"

namespace gpcpp::c03 {

class CollisionComponent : public Component {
public:
  explicit CollisionComponent(Actor *Owner);

  [[nodiscard]] const glm::vec2 &getCenter() const;

  [[nodiscard]] float getRadius() const;

  void setRadius(float R) { Radius = R; }

private:
  float Radius;
  glm::vec2 Center;
};

bool intersect(const CollisionComponent &a, const CollisionComponent &b);

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER03_COLLISIONCOMPONENT_HPP
