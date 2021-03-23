#include "Component.hpp"

#include "Actor.hpp"

using namespace gpcpp::c02;

Component::Component(class Actor *Owner, int UpdateOrder) : Owner(Owner), UpdateOrder(UpdateOrder) {
  Owner->addComponent(this);
}

Component::~Component() {
  Owner->removeComponent(this);
}

void Component::update(float DeltaTime) {

}
