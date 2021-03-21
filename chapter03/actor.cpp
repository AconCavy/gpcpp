#include "actor.hpp"

#include "game.hpp"

using namespace gpcpp::c03;

Actor::Actor(struct Game *Game)
	: State(Active),
	  Scale(1),
	  Position({}),
	  Rotation(0),
	  Game(Game) {
  Game->addActor(this);
}
Actor::~Actor() {
  Game->removeActor(this);
  while (!Component.empty()) {
	delete Component.back();
  }
}

void Actor::update(float DeltaTime) {
  if (State == Active) {
	updateComponents(DeltaTime);
	updateActor(DeltaTime);
  }
}

void Actor::updateComponents(float DeltaTime) {
  for (auto component : Component) {
	component->update(DeltaTime);
  }
}

void Actor::updateActor(float DeltaTime) {
}

void Actor::addComponent(struct Component *C) {
  auto Order = C->getUpdateOrder();
  auto I = Component.begin();
  auto E = Component.end();
  for (; I != E; ++I) {
	if (Order < (*I)->getUpdateOrder())
	  break;
  }
  Component.insert(I, C);
}
void Actor::removeComponent(struct Component *C) {
  auto E = Component.end();
  auto I = std::find(Component.begin(), E, C);
  if (I != E)
	Component.erase(I);
}