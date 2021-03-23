#include "SpriteComponent.hpp"

#include "Actor.hpp"
#include "Game.hpp"
#include "Math.hpp"

using namespace gpcpp::c04;

SpriteComponent::SpriteComponent(class Actor *Owner, int DrawOrder)
	: Component(Owner),
	  Texture(nullptr),
	  DrawOrder(DrawOrder),
	  TextureWidth(0),
	  TextureHeight(0) {
  Owner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent() {
  Owner->getGame()->removeSprite(this);
}

void SpriteComponent::draw(SDL_Renderer *R) {
  if (!IsEnabled || !Texture)
	return;

  SDL_Rect Rect;
  Rect.w = static_cast<int>(static_cast<float>(TextureWidth) * Owner->getScale());
  Rect.h = static_cast<int>(static_cast<float>(TextureHeight) * Owner->getScale());
  Rect.x = static_cast<int>(Owner->getPosition().x - static_cast<float>(Rect.w) / 2);
  Rect.y = static_cast<int>(Owner->getPosition().y - static_cast<float>(Rect.h) / 2);

  float Degree = -toDegree(Owner->getRotation());
  SDL_RenderCopyEx(R, Texture, nullptr, &Rect, Degree, nullptr, SDL_FLIP_NONE);
}

void SpriteComponent::setTexture(SDL_Texture *T) {
  Texture = T;
  SDL_QueryTexture(T, nullptr, nullptr, &TextureWidth, &TextureHeight);
}
