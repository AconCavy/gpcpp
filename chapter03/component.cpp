#include "component.hpp"

#include "actor.hpp"

using namespace gpcpp::c03;

Component::Component(class Actor *Owner, int UpdateOrder)
	: Owner(Owner),
	  UpdateOrder(UpdateOrder),
	  IsEnabled(true) {
  Owner->addComponent(this);
}

Component::~Component() {
  Owner->removeComponent(this);
}

void Component::update(float DeltaTime) {

}

void Component::processInput(const uint8_t *KeyState) {

}
