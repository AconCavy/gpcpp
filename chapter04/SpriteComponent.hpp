#ifndef GPCPP_CHAPTER04_SPRITECOMPONENT_HPP
#define GPCPP_CHAPTER04_SPRITECOMPONENT_HPP

#include <SDL.h>

#include "Component.hpp"

namespace gpcpp::c04 {

class SpriteComponent : public Component {
public:
  explicit SpriteComponent(class Actor *Owner, int DrawOrder = 100);
  ~SpriteComponent() override;

  virtual void draw(SDL_Renderer *R);
  virtual void setTexture(SDL_Texture *T);

  [[nodiscard]] int getDrawOrder() const { return DrawOrder; }
  [[nodiscard]] int getTextureWidth() const { return TextureWidth; }
  [[nodiscard]] int getTextureHeight() const { return TextureHeight; }

protected:
  SDL_Texture *Texture;
  int DrawOrder;
  int TextureWidth;
  int TextureHeight;
};

} // namespace gpcpp::c04

#endif // GPCPP_CHAPTER04_SPRITECOMPONENT_HPP
