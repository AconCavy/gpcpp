#include "Component.hpp"

#include "Actor.hpp"

using namespace gpcpp::c05;

Component::Component(class Actor *Owner, int UpdateOrder)
    : Owner(Owner), UpdateOrder(UpdateOrder), IsEnabled(true) {
  Owner->addComponent(this);
}

Component::~Component() { Owner->removeComponent(this); }
