#include "component.hpp"
#include "actor.hpp"

namespace gpcpp::c02 {

Component::Component(class Actor *owner, int updateOrder) : _owner(owner), _updateOrder(updateOrder) {
  owner->AddComponent(this);
}

Component::~Component() {
  _owner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {

}

} // namespace gpcpp::c02
