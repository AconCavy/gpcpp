#ifndef GPCPP_CHAPTER02_SPRITECOMPONENT_HPP
#define GPCPP_CHAPTER02_SPRITECOMPONENT_HPP

#include <SDL.h>
#include "component.hpp"

namespace gpcpp::c02 {

class SpriteComponent : public Component {
public:
  SpriteComponent(class Actor *owner, int drawOrder = 100);
  ~SpriteComponent();
  virtual void Draw(SDL_Renderer *renderer);
  virtual void SetTexture(SDL_Texture *texture);
  int GetDrawOrder() const { return _drawOrder; }
  int GetTextureWidth() const { return _textureWidth; }
  int GetTextureHeight() const { return _textureHeight; }

protected:
  SDL_Texture *_texture;
  int _drawOrder;
  int _textureWidth;
  int _textureHeight;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_SPRITECOMPONENT_HPP
