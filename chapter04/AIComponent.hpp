#ifndef GPCPP_CHAPTER04_AICOMPONENT_HPP
#define GPCPP_CHAPTER04_AICOMPONENT_HPP

#include <string>
#include <unordered_map>

#include "Component.hpp"

namespace gpcpp::c04 {

class AIComponent : public Component {
public:
  explicit AIComponent(class Actor *Owner);

  void update(float DeltaTime) override;
  void changeState(const std::string &StateName);
  void registerState(class AIState *State);

private:
  std::unordered_map<std::string, class AIState *> StateMap;
  class AIState *CurrentState;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_AICOMPONENT_HPP
