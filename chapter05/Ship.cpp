#include "Ship.hpp"

#include "Asteroid.hpp"
#include "CollisionComponent.hpp"
#include "Game.hpp"
#include "InputComponent.hpp"
#include "Laser.hpp"
#include "Math.hpp"
#include "PositionWrapComponent.hpp"
#include "SpriteComponent.hpp"

using namespace gpcpp::c05;

const float DefaultSafeTime = 1;

Ship::Ship(class Game *Game)
    : Actor(Game), DefaultPosition(0, 0), DefaultRotation(0), LaserCoolDown(0),
      SafeTimeCurrent(DefaultSafeTime), IsActive(true), IsSafeTime(true) {
  Sprite = new SpriteComponent(this, 150);
  Sprite->setTexture(Game->getTexture("assets/Ship.png"));

  Input = new InputComponent(this);
  Input->setForwardKey(SDL_SCANCODE_W);
  Input->setBackKey(SDL_SCANCODE_S);
  Input->setClockwiseKey(SDL_SCANCODE_A);
  Input->setCounterClockwiseKey(SDL_SCANCODE_D);
  Input->setMaxAngularSpeed(glm::pi<float>() * 2);
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

  if (!IsActive)
    return;

  if (IsSafeTime) {
    SafeTimeCurrent = std::max(0.0f, SafeTimeCurrent - DeltaTime);
    if (SafeTimeCurrent > 0)
      return;

    SafeTimeCurrent = DefaultSafeTime;
    IsSafeTime = false;
  }

  auto Asteroids = getGame()->getAsteroids();
  for (auto A : Asteroids) {
    if (Collision->isColliding(*(A->getCollision()))) {
      setPosition(DefaultPosition);
      setRotation(DefaultRotation);
      IsSafeTime = true;

      return;
    }
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
