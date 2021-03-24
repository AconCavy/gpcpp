#include "AIState.hpp"

#include <SDL_log.h>

#include "AIComponent.hpp"

using namespace gpcpp::c04;

void AIPatrol::update(float DeltaTime) {
  SDL_Log("Updating %s state", getName());
  bool Dead = true;
  if (Dead) {
    Owner->changeState("Death");
  }
}

void AIPatrol::onEnter() { SDL_Log("Entering %s state", getName()); }

void AIPatrol::onExit() { SDL_Log("Exiting %s state", getName()); }

void AIDeath::update(float DeltaTime) {
  SDL_Log("Updating %s state", getName());
}

void AIDeath::onEnter() { SDL_Log("Entering %s state", getName()); }

void AIDeath::onExit() { SDL_Log("Exiting %s state", getName()); }

void AIAttack::update(float DeltaTime) {
  SDL_Log("Updating %s state", getName());
}

void AIAttack::onEnter() { SDL_Log("Entering %s state", getName()); }

void AIAttack::onExit() { SDL_Log("Exiting %s state", getName()); }
