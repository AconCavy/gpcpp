#include "ship.hpp"

#include "animationSpriteComponent.hpp"
#include "game.hpp"

using namespace gpcpp::c02;

const float MinX = 25;
const float MinY = 25;
const float MaxX = 500;
const float MaxY = 768 - MinY;
const float RightVelocity = 250.0f;
const float DownVelocity = 300.0f;

Ship::Ship(class Game *Game) : Actor(Game), RightSpeed(0), DownSpeed(0) {
  auto Animation = new AnimationSpriteComponent(this);
  std::vector<SDL_Texture *> Textures = {
	  Game->getTexture("assets/Ship01.png"),
	  Game->getTexture("assets/Ship02.png"),
	  Game->getTexture("assets/Ship03.png"),
	  Game->getTexture("assets/Ship04.png")
  };

  Animation->setAnimationTextures(Textures);
}

void Ship::updateActor(float DeltaTime) {
  Actor::updateActor(DeltaTime);
  auto Position = getPosition();
  Position.x = std::min(MaxX, std::max(Position.x + RightSpeed * DeltaTime, MinX));
  Position.y = std::min(MaxY, std::max(Position.y + DownSpeed * DeltaTime, MinY));
  setPosition(Position);
}

void Ship::processKeyboard(const uint8_t *State) {
  RightSpeed = 0;
  DownSpeed = 0;

  if (State[SDL_SCANCODE_D])
	RightSpeed += RightVelocity;
  if (State[SDL_SCANCODE_A])
	RightSpeed -= RightVelocity;
  if (State[SDL_SCANCODE_S])
	DownSpeed += DownVelocity;
  if (State[SDL_SCANCODE_W])
	DownSpeed -= DownVelocity;
}
