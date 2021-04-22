#ifndef GPCPP_CHAPTER05_SPRITECOMPONENT_HPP
#define GPCPP_CHAPTER05_SPRITECOMPONENT_HPP

#include <SDL.h>

#include "Component.hpp"

namespace gpcpp::c05 {

class SpriteComponent : public Component {
public:
  explicit SpriteComponent(class Actor *Owner, int DrawOrder = 100);
  ~SpriteComponent() override;

  virtual void draw(class Shader *S);
  virtual void setTexture(class Texture *T);

  [[nodiscard]] int getDrawOrder() const { return DrawOrder; }
  [[nodiscard]] int getTextureWidth() const { return TextureWidth; }
  [[nodiscard]] int getTextureHeight() const { return TextureHeight; }

protected:
  class Texture *Texture;
  int DrawOrder;
  int TextureWidth;
  int TextureHeight;
};

} // namespace gpcpp::c05

#endif // GPCPP_CHAPTER05_SPRITECOMPONENT_HPP
