#ifndef GPCPP_CHAPTER03_CIRCLECOMPONENT_HPP
#define GPCPP_CHAPTER03_CIRCLECOMPONENT_HPP

#include <glm/glm.hpp>

#include "component.hpp"

namespace gpcpp::c03 {

class CircleComponent : public Component {
public:
  explicit CircleComponent(Actor *Owner);

  [[nodiscard]] const glm::vec2 &getCenter() const;

  [[nodiscard]] float getRadius() const;

  void setRadius(float R) { Radius = R; }

private:
  float Radius;
  glm::vec2 Center;
};

bool intersect(const CircleComponent &a, const CircleComponent &b);

} // namespace gpcpp::c03

#endif //GPCPP_CHAPTER03_CIRCLECOMPONENT_HPP
