#ifndef GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP
#define GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP

#include "spriteComponent.hpp"
#include <vector>
#include "vector2.hpp"

namespace gpcpp::c02 {

class BackgroundSpriteComponent : public SpriteComponent {
public:
  explicit BackgroundSpriteComponent(class Actor *Owner, int DrawOrder = 10);

  void update(float DeltaTime) override;
  void draw(SDL_Renderer *R) override;
  void setBackgroundTextures(std::vector<SDL_Texture *> &Textures);
  void setScreenSize(const Vector2 &Size) { ScreenSize = Size; }
  void setScrollSpeed(float Speed) { ScrollSpeed = Speed; }
  [[nodiscard]] float getScrollSpeed() const { return ScrollSpeed; }

private:
  struct BackgroundTexture {
	SDL_Texture *Texture;
	Vector2 Offset;
  };

  std::vector<BackgroundTexture> BackgroundTextures;
  Vector2 ScreenSize;
  float ScrollSpeed;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP
