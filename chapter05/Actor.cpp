#include "Actor.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Component.hpp"
#include "Game.hpp"
#include "Math.hpp"

using namespace gpcpp::c05;

Actor::Actor(struct Game *Game)
    : State(Active), Scale(1), Position({}), Rotation(0), Game(Game),
      RecomputeWorldTransform(true) {
  Game->addActor(this);
}
Actor::~Actor() {
  Game->removeActor(this);
  while (!Components.empty()) {
    delete Components.back();
  }
}

void Actor::update(float DeltaTime) {
  if (State == Active) {
    computeWorldTransform();
    updateComponents(DeltaTime);
    updateActor(DeltaTime);
    computeWorldTransform();
  }
}

void Actor::updateComponents(float DeltaTime) {
  for (auto C : Components) {
    C->update(DeltaTime);
  }
}

void Actor::updateActor(float DeltaTime) {}

void Actor::addComponent(struct Component *C) {
  auto Order = C->getUpdateOrder();
  auto I = Components.begin();
  auto E = Components.end();
  for (; I != E; ++I) {
    if (Order < (*I)->getUpdateOrder())
      break;
  }
  Components.insert(I, C);
}
void Actor::removeComponent(struct Component *C) {
  auto E = Components.end();
  auto I = std::find(Components.begin(), E, C);
  if (I != E)
    Components.erase(I);
}

void Actor::processInput(const uint8_t *KeyState) {
  if (State != Active)
    return;

  for (auto C : Components) {
    C->processInput(KeyState);
  }

  ActorInput(KeyState);
}

void Actor::ActorInput(const uint8_t *KeyState) {}

void Actor::computeWorldTransform() {
  if (!RecomputeWorldTransform)
    return;

  RecomputeWorldTransform = false;
  WorldTransform = createScale(Scale);
  WorldTransform *= createRotationZ(Rotation);
  WorldTransform *= createTranslation({Position.x, Position.y, 0});

  for (auto C : Components) {
    C->onUpdateWorldTransform();
  }
}
