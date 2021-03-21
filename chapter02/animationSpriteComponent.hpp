#ifndef GPCPP_CHAPTER02_ANIMATIONSPRITECOMPONENT_HPP
#define GPCPP_CHAPTER02_ANIMATIONSPRITECOMPONENT_HPP

#include <vector>

#include "spriteComponent.hpp"

namespace gpcpp::c02 {

class AnimationSpriteComponent : public SpriteComponent {
public:
  explicit AnimationSpriteComponent(class Actor *Owner, int DrawOrder = 100);

  void update(float DeltaTime) override;

  [[nodiscard]] float getAnimationFPS() const { return AnimationFPS; }

  void setAnimationTextures(const std::vector<SDL_Texture *> &Textures);

private:
  std::vector<SDL_Texture *> AnimationTextures;
  float CurrentFrame;
  float AnimationFPS;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_ANIMATIONSPRITECOMPONENT_HPP
