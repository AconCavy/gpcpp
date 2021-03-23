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

const float ResurrectionTime = 1;

Ship::Ship(class Game *Game)
	: Actor(Game),
	  DefaultPosition(Game->Width / 2, Game->Height / 2),
	  DefaultRotation(0),
	  LaserCoolDown(0),
	  ResurrectionCoolDown(ResurrectionTime) {
  Sprite = new SpriteComponent(this, 150);
  Sprite->setTexture(Game->getTexture("assets/Ship.png"));

  Input = new InputComponent(this);
  Input->setForwardKey(SDL_SCANCODE_W);
  Input->setBackKey(SDL_SCANCODE_S);
  Input->setClockwiseKey(SDL_SCANCODE_A);
  Input->setCounterClockwiseKey(SDL_SCANCODE_D);
  Input->setMaxAngularSpeed(static_cast<float>(gpcpp::PI * 2));
  Input->setMaxForwardSpeed(300);

  auto PWC = new PositionWrapComponent(this);
  PWC->setWidth(static_cast<float>(Game->Width));
  PWC->setHeight(static_cast<float>(Game->Height));
  PWC->setMargin(static_cast<float>(25));

  Collision = new CollisionComponent(this);
  Collision->setRadius(40);
}

void Ship::updateActor(float DeltaTime) {
  LaserCoolDown = std::max(0.0f, LaserCoolDown - DeltaTime);
  ResurrectionCoolDown = std::max(0.0f, ResurrectionCoolDown - DeltaTime);

  if (IsActive) {
	auto Asteroids = getGame()->getAsteroids();
	for (auto A : Asteroids) {
	  if (Collision->IsColliding(*(A->getCollision()))) {
		setPosition(DefaultPosition);
		setRotation(DefaultRotation);
		setActive(false);

		return;
	  }
	}
  }

  if (ResurrectionCoolDown == 0) {
	setActive(true);
	ResurrectionCoolDown = ResurrectionTime;
  }
}

void Ship::ActorInput(const uint8_t *KeyState) {
  if (!IsActive)
	return;

  if (KeyState[SDL_SCANCODE_SPACE] && LaserCoolDown == 0) {
	auto L = new Laser(getGame());
	L->setPosition(getPosition());
	L->setRotation(getRotation());
	LaserCoolDown = 0.5f;
  }
}

void Ship::setActive(bool Flag) {
  IsActive = Flag;
  Sprite->setActive(Flag);
  Input->setActive(Flag);
  Collision->setActive(Flag);
}
