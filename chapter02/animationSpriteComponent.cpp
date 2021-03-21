#include "animationSpriteComponent.hpp"

#include <cmath>

using namespace gpcpp::c02;

AnimationSpriteComponent::AnimationSpriteComponent(class Actor *Owner, int DrawOrder)
	: SpriteComponent(Owner, DrawOrder),
	  CurrentFrame(0),
	  AnimationFPS(24) {
}

void AnimationSpriteComponent::update(float DeltaTime) {
  SpriteComponent::update(DeltaTime);

  int Size = AnimationTextures.size();
  if (Size > 0) {
	CurrentFrame = std::fmod(CurrentFrame + AnimationFPS * DeltaTime, Size);
	setTexture(AnimationTextures[static_cast<int>(CurrentFrame)]);
  }
}

void AnimationSpriteComponent::setAnimationTextures(const std::vector<SDL_Texture *> &Textures) {
  AnimationTextures = Textures;
  if (!AnimationTextures.empty()) {
	CurrentFrame = 0;
	setTexture(AnimationTextures[0]);
  }
}
