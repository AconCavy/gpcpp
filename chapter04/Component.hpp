#ifndef GPCPP_CHAPTER04_COMPONENT_HPP
#define GPCPP_CHAPTER04_COMPONENT_HPP

#include "SDL.h"

namespace gpcpp::c04 {

class Component {
public:
  explicit Component(class Actor *Owner, int UpdateOrder = 100);
  virtual ~Component();

  virtual void update(float DeltaTime);
  virtual void processInput(const uint8_t *KeyState);

  [[nodiscard]] int getUpdateOrder() const { return UpdateOrder; }
  [[nodiscard]] bool IsActive() const { return IsEnabled; }

  void setActive(bool Flag) { IsEnabled = Flag; }

protected:
  class Actor *Owner;
  int UpdateOrder;
  bool IsEnabled;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_COMPONENT_HPP
