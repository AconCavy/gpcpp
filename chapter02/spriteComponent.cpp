#include "spriteComponent.hpp"
#include "actor.hpp"
#include "math.hpp"
#include "game.hpp"

using namespace gpcpp::c02;

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
  if (!Texture)
	return;
  SDL_Rect r;
  r.w = static_cast<int>(static_cast<float>(TextureWidth) * Owner->getScale());
  r.h = static_cast<int>(static_cast<float>(TextureHeight) * Owner->getScale());
  r.x = static_cast<int>(Owner->getPosition().X - static_cast<float>(r.w) / 2);
  r.y = static_cast<int>(Owner->getPosition().Y - static_cast<float>(r.h) / 2);

  float Degree = -ToDegree(Owner->getRotation());
  SDL_RenderCopyEx(R, Texture, nullptr, &r, Degree, nullptr, SDL_FLIP_NONE);
}

void SpriteComponent::setTexture(SDL_Texture *T) {
  Texture = T;
  SDL_QueryTexture(T, nullptr, nullptr, &TextureWidth, &TextureHeight);
}
