#include "ship.hpp"

#include "asteroid.hpp"
#include "collisionComponent.hpp"
#include "game.hpp"
#include "inputComponent.hpp"
#include "laser.hpp"
#include "math.hpp"
#include "positionWrapComponent.hpp"
#include "spriteComponent.hpp"

using namespace gpcpp::c03;

Ship::Ship(class Game *Game)
	: Actor(Game),
	  DefaultPosition(Game->Width / 2, Game->Height / 2),
	  DefaultRotation(0),
	  LaserCoolDown(0) {
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

  Collision = new CollisionComponent(this);
  Collision->setRadius(40);
}

void Ship::updateActor(float DeltaTime) {
  LaserCoolDown = std::max(0.0f, LaserCoolDown - DeltaTime);

  auto Asteroids = getGame()->getAsteroids();
  for (auto A : Asteroids) {
	if (intersect(*Collision, *(A->getCollision()))) {
	  setPosition(DefaultPosition);
	  setRotation(DefaultRotation);
	  break;
	}
  }
}

void Ship::ActorInput(const uint8_t *KeyState) {
  if (KeyState[SDL_SCANCODE_SPACE] && LaserCoolDown == 0) {
	auto L = new Laser(getGame());
	L->setPosition(getPosition());
	L->setRotation(getRotation());
	LaserCoolDown = 0.5f;
  }
}
