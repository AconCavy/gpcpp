#ifndef GPCPP_CHAPTER02_COMPONENT_HPP
#define GPCPP_CHAPTER02_COMPONENT_HPP

#include "SDL.h"

namespace gpcpp::c03 {

class Component {
public:
  explicit Component(class Actor *Owner, int UpdateOrder = 100);
  virtual ~Component();
  virtual void update(float DeltaTime);
  virtual void processInput(const uint8_t *KeyState);
  [[nodiscard]] int getUpdateOrder() const { return UpdateOrder; }

protected:
  class Actor *Owner;
  int UpdateOrder;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_COMPONENT_HPP
