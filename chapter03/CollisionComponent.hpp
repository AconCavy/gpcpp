#ifndef GPCPP_CHAPTER03_COLLISIONCOMPONENT_HPP
#define GPCPP_CHAPTER03_COLLISIONCOMPONENT_HPP

#include <glm/glm.hpp>

#include "Component.hpp"

namespace gpcpp::c03 {

class CollisionComponent : public Component {
public:
  explicit CollisionComponent(Actor *Owner);

  [[nodiscard]] bool isColliding(const CollisionComponent &other) const;

  [[nodiscard]] const glm::vec2 &getCenter() const;
  [[nodiscard]] float getRadius() const;

  void setRadius(float R) { Radius = R; }

private:
  float Radius;
  glm::vec2 Center;
};

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER03_COLLISIONCOMPONENT_HPP
