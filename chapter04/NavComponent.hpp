#ifndef GPCPP_CHAPTER04_NAVCOMPONENT_HPP
#define GPCPP_CHAPTER04_NAVCOMPONENT_HPP

#include "MoveComponent.hpp"

#include <glm/glm.hpp>

namespace gpcpp::c04 {

class NavComponent : public MoveComponent {
public:
  explicit NavComponent(class Actor *Owner, int UpdateOrder = 10);

  void update(float DeltaTime) override;

  void setStart(const class Tile *Start);
  void turnTo(const glm::vec2 &Position);

private:
  const class Tile *NextNode;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_NAVCOMPONENT_HPP
