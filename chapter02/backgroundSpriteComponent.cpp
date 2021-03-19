#include "backgroundSpriteComponent.hpp"

namespace gpcpp::c02 {

void BackgroundSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);
  for (auto &background : _textures) {
	background._offset.x += _scrollSpeed * deltaTime;
	if (background._offset.x < -_screenSize.x)
	  background._offset.x = (_textures.size() - 1) * _screenSize.x - 1;
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