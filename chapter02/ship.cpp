#include "ship.hpp"
#include "animationSpriteComponent.hpp"
#include "game.hpp"
#include "vector2.hpp"

using namespace gpcpp::utils;

namespace gpcpp::c02 {

const float minX = 25;
const float minY = 25;
const float maxX = 500;
const float maxY = 768 - minY;
const float rightVelocity = 250.0f;
const float downVelocity = 300.0f;

Ship::Ship(class Game *game) : Actor(game), _rightSpeed(0), _downSpeed(0) {
  auto animation = new AnimationSpriteComponent(this);
  std::vector<SDL_Texture *> textures = {
	  game->GetTexture("assets/Ship01.png"),
	  game->GetTexture("assets/Ship02.png"),
	  game->GetTexture("assets/Ship03.png"),
	  game->GetTexture("assets/Ship04.png")
  };

  animation->SetAnimationTextures(textures);
}

void Ship::UpdateActor(float deltaTime) {
  Actor::UpdateActor(deltaTime);
  auto position = GetPosition();
  Vector2 v{_rightSpeed, _downSpeed};
  position += v * deltaTime;
  position.x = std::min(maxX, std::max(position.x, minX));
  position.y = std::min(maxY, std::max(position.y, minY));
  SetPosition(position);
}

void Ship::ProcessKeyboard(const uint8_t *state) {
  _rightSpeed = 0;
  _downSpeed = 0;

  if (state[SDL_SCANCODE_D])
	_rightSpeed += rightVelocity;
  if (state[SDL_SCANCODE_A])
	_rightSpeed -= rightVelocity;
  if (state[SDL_SCANCODE_S])
	_downSpeed += downVelocity;
  if (state[SDL_SCANCODE_W])
	_downSpeed -= downVelocity;
}

} // namespace gpcpp::c02