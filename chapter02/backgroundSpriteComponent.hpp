#ifndef GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP
#define GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP

#include "spriteComponent.hpp"
#include <vector>
#include "vector2.hpp"

namespace gpcpp::c02 {

class BackgroundSpriteComponent : public SpriteComponent {
public:
  BackgroundSpriteComponent(class Actor *owner, int drawOrder = 10);

  void Update(float deltaTime) override;
  void Draw(SDL_Renderer *renderer) override;
  void SetBackgroundTextures(std::vector<SDL_Texture *> &textures);
  void SetScreenSize(const utils::Vector2 &screenSize) { _screenSize = screenSize; }
  void SetScrollSpeed(float scrollSpeed) { _scrollSpeed = scrollSpeed; }
  float GetScrollSpeed() const { return _scrollSpeed; }

private:
  struct BackgroundTexture {
	SDL_Texture *_texture;
	utils::Vector2 _offset;
  };

  std::vector<BackgroundTexture> _textures;
  utils::Vector2 _screenSize;
  float _scrollSpeed;
};

} // namespace gpcpp::c02

#endif //GPCPP_CHAPTER02_BACKGROUNDSPRITECOMPONENT_HPP
