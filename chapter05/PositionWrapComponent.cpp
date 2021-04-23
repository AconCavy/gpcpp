#include "PositionWrapComponent.hpp"

#include "Actor.hpp"

using namespace gpcpp::c05;

PositionWrapComponent::PositionWrapComponent(class Actor *Owner,
                                             int UpdateOrder)
    : Component(Owner, UpdateOrder), Width(0), Height(0), Margin(0) {}

void PositionWrapComponent::update(float DeltaTime) {
  auto P = Owner->getPosition();
  auto Width2 = Width / 2;
  auto Height2 = Height / 2;

  if (P.x < -Width2 - Margin)
    P.x = Width2 + Margin;
  else if (P.x > Width2 + Margin)
    P.x = -Width2 - Margin;

  if (P.y < -Height2 - Margin)
    P.y = Height2 + Margin;
  else if (P.y > Height2 + Margin)
    P.y = -Height2 - Margin;

  Owner->setPosition(P);
}
