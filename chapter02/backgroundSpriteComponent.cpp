#include "backgroundSpriteComponent.hpp"
#include "actor.hpp"

namespace gpcpp::c02 {

BackgroundSpriteComponent::BackgroundSpriteComponent(class Actor *owner, int drawOrder)
	: SpriteComponent(owner, drawOrder),
	  _scrollSpeed(0) {
}

void BackgroundSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);
  for (auto &background : _textures) {
	background._offset.x += _scrollSpeed * deltaTime;
	if (background._offset.x < -_screenSize.x)
	  background._offset.x = (_textures.size() - 1) * _screenSize.x - 1;
  }
}

void BackgroundSpriteComponent::Draw(SDL_Renderer *renderer) {
  SpriteComponent::Draw(renderer);
  for (auto &background : _textures) {
	SDL_Rect r;
	r.w = static_cast<int>(_screenSize.x);
	r.h = static_cast<int>(_screenSize.y);
	r.x = static_cast<int>(_owner->GetPosition().x - r.w / 2 + background._offset.x);
	r.x = static_cast<int>(_owner->GetPosition().y - r.h / 2 + background._offset.y);

	SDL_RenderCopy(renderer, background._texture, nullptr, &r);
  }
}

void BackgroundSpriteComponent::SetBackgroundTextures(std::vector<SDL_Texture *> &textures) {
  int count = 0;
  for (auto texture : textures) {
	BackgroundTexture tmp{texture, {count * _screenSize.x, 0}};
	_textures.emplace_back(tmp);
	count++;
  }
}

} // namespace gpcpp::c02