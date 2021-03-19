#include "animationSpriteComponent.hpp"
#include <cmath>

namespace gpcpp::c02 {

void AnimationSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);

  int size = _animationTextures.size();
  if (size > 0) {
	_currentFrame = std::fmod(_currentFrame + _animationFps * deltaTime, size);
	SetTexture(_animationTextures[static_cast<int>(_currentFrame)]);
  }
}
} // namespace gpcpp::c02
