#include "spriteComponent.hpp"
#include "actor.hpp"
#include "math.hpp"
#include "game.hpp"

namespace gpcpp::c02 {

SpriteComponent::SpriteComponent(class Actor *owner, int drawOrder)
	: Component(owner),
	  _texture(nullptr),
	  _drawOrder(drawOrder),
	  _textureWidth(0),
	  _textureHeight(0) {
  _owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
  _owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer *renderer) {
  if (!_texture)
	return;
  SDL_Rect r;
  r.w = static_cast<int>(_textureWidth * _owner->GetScale());
  r.h = static_cast<int>(_textureHeight * _owner->GetScale());
  r.x = static_cast<int>(_owner->GetPosition().x - r.w / 2);
  r.y = static_cast<int>(_owner->GetPosition().y - r.h / 2);

  float degree = -utils::ToDegree(_owner->GetRotation());
  SDL_RenderCopyEx(renderer, _texture, nullptr, &r, degree, nullptr, SDL_FLIP_NONE);
}

void SpriteComponent::SetTexture(SDL_Texture *texture) {
  _texture = texture;
  SDL_QueryTexture(texture, nullptr, nullptr, &_textureWidth, &_textureHeight);
}

} // namespace gpcpp::c02