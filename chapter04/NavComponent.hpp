#ifndef GPCPP_CHAPTER04_NAVCOMPONENT_HPP
#define GPCPP_CHAPTER04_NAVCOMPONENT_HPP

#include "MoveComponent.hpp"

#include <glm/glm.hpp>

namespace gpcpp::c04 {

class NavComponent : public MoveComponent {
public:
  NavComponent(class Actor *Owner, int UpdateOrder);

  void update(float DeltaTime) override;
  void TurnTo(const glm::vec2 &Position);

  void setNextPoint(const glm::vec2 &Position) { NextPosition = Position; }

private:
  glm::vec2 NextPosition;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_NAVCOMPONENT_HPP
