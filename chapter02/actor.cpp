#include "actor.hpp"
#include "game.hpp"

namespace gpcpp::c02 {

Actor::Actor(struct Game *game) : _state(Active), _scale(1), _rotation(0), _game(game) {
  _game->AddActor(this);
}
Actor::~Actor() {
  _game->RemoveActor(this);
  while (!_components.empty())
	delete _components.back();
}

void Actor::Update(float deltaTime) {
  if (_state == Active) {
	UpdateComponents(deltaTime);
	UpdateActor(deltaTime);
  }
}

void Actor::UpdateComponents(float deltaTime) {
  for (auto component : _components) {
	component->Update(deltaTime);
  }
}

void Actor::UpdateActor(float deltaTime) {

}

void Actor::AddComponent(struct Component *component) {
  auto order = component->GetUpdateOrder();
  auto iter = _components.begin();
  for (; iter != _components.end(); iter++) {
	if (order < (*iter)->GetUpdateOrder())
	  break;
  }
  _components.insert(iter, component);
}
void Actor::RemoveComponent(struct Component *component) {
  auto iter = std::find(_components.begin(), _components.end(), component);
  if (iter != _components.end())
	_components.erase(iter);
}

} // namespace gpcpp::c02