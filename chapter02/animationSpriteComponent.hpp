#ifndef GPCPP_CHAPTER02_ANIMATIONSPRITECOMPONENT_HPP
#define GPCPP_CHAPTER02_ANIMATIONSPRITECOMPONENT_HPP

#include <vector>
#include "spriteComponent.hpp"

namespace gpcpp::c02 {

class AnimationSpriteComponent : public SpriteComponent {
public:
  AnimationSpriteComponent(class Actor *owner, int drawOrder = 100);

  void Update(float deltaTime) override;
  void SetAnimationTextures(const std::vector<SDL_Texture *> &textures);
  float GetAnimationFps() const { return _animationFps; }

private:
  std::vector<SDL_Texture *> _animationTextures;
  float _currentFrame;
  float _animationFps;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_ANIMATIONSPRITECOMPONENT_HPP
