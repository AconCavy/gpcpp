#include "AIComponent.hpp"

#include "AIState.hpp"

using namespace gpcpp::c04;

AIComponent::AIComponent(class Actor *Owner)
    : Component(Owner), CurrentState(nullptr) {}
void AIComponent::update(float DeltaTime) {
  if (CurrentState)
    CurrentState->update(DeltaTime);
}

void AIComponent::changeState(const std::string &StateName) {
  if (CurrentState)
    CurrentState->onExit();

  auto I = StateMap.find(StateName);
  if (I != StateMap.end()) {
    CurrentState = I->second;
    CurrentState->onEnter();
    return;
  }

  SDL_Log("Could not find AIState %s", StateName.c_str());
  CurrentState = nullptr;
}

void AIComponent::registerState(class AIState *State) {
  StateMap.emplace(State->getName(), State);
}
