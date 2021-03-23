#include "ship.hpp"

#include "game.hpp"
#include "inputComponent.hpp"
#include "math.hpp"
#include "positionWrapComponent.hpp"
#include "spriteComponent.hpp"

using namespace gpcpp::c03;

Ship::Ship(class Game *Game)
	: Actor(Game) {
  auto SC = new SpriteComponent(this, 150);
  SC->setTexture(Game->getTexture("assets/Ship.png"));

  auto IC = new InputComponent(this);
  IC->setForwardKey(SDL_SCANCODE_W);
  IC->setBackKey(SDL_SCANCODE_S);
  IC->setClockwiseKey(SDL_SCANCODE_A);
  IC->setCounterClockwiseKey(SDL_SCANCODE_D);
  IC->setMaxAngularSpeed(static_cast<float>(gpcpp::PI * 2));
  IC->setMaxForwardSpeed(300);

  auto PWC = new PositionWrapComponent(this);
  PWC->setWidth(static_cast<float>(Game->Width));
  PWC->setHeight(static_cast<float>(Game->Height));
  PWC->setMargin(static_cast<float>(25));
}

void Ship::updateActor(float DeltaTime) {
}

void Ship::ActorInput(const uint8_t *KeyState) {
}
