#include "animationSpriteComponent.hpp"
#include <cmath>

namespace gpcpp::c02 {

AnimationSpriteComponent::AnimationSpriteComponent(class Actor *owner, int drawOrder)
	: SpriteComponent(owner, drawOrder),
	  _currentFrame(0),
	  _animationFps(24) {
}

void AnimationSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);

  int size = _animationTextures.size();
  if (size > 0) {
	_currentFrame = std::fmod(_currentFrame + _animationFps * deltaTime, size);
	SetTexture(_animationTextures[static_cast<int>(_currentFrame)]);
  }
}

void AnimationSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture *> &textures) {
  _animationTextures = textures;
  if (!_animationTextures.empty()) {
	_currentFrame = 0;
	SetTexture(_animationTextures[0]);
  }
}

} // namespace gpcpp::c02
