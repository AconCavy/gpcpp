#ifndef GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP
#define GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP

#include "spriteComponent.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace gpcpp::c02 {

class BackgroundSpriteComponent : public SpriteComponent {
public:
  explicit BackgroundSpriteComponent(class Actor *Owner, int DrawOrder = 10);

  void update(float DeltaTime) override;
  void draw(SDL_Renderer *R) override;

  [[nodiscard]] float getScrollSpeed() const { return ScrollSpeed; }

  void setBackgroundTextures(std::vector<SDL_Texture *> &Textures);
  void setScreenSize(const glm::vec2 &Size) { ScreenSize = Size; }
  void setScrollSpeed(float Speed) { ScrollSpeed = Speed; }

private:
  struct BackgroundTexture {
	SDL_Texture *Texture;
	glm::vec2 Offset;
  };

  std::vector<BackgroundTexture> BackgroundTextures;
  glm::vec2 ScreenSize;
  float ScrollSpeed;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP
