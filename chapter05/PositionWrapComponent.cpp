#include "PositionWrapComponent.hpp"

#include "Actor.hpp"

using namespace gpcpp::c05;

PositionWrapComponent::PositionWrapComponent(class Actor *Owner,
                                             int UpdateOrder)
    : Component(Owner, UpdateOrder), Width(0), Height(0), Margin(0) {}

void PositionWrapComponent::update(float DeltaTime) {
  auto P = Owner->getPosition();
  if (P.x < -Margin)
    P.x = Width + Margin;
  else if (P.x > Width + Margin)
    P.x = -Margin;

  if (P.y < -Margin)
    P.y = Height + Margin;
  else if (P.y > Height + Margin)
    P.y = -Margin;

  Owner->setPosition(P);
}
