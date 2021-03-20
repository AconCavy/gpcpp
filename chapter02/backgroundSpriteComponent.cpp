#include "backgroundSpriteComponent.hpp"
#include "actor.hpp"

using namespace gpcpp::c02;

BackgroundSpriteComponent::BackgroundSpriteComponent(class Actor *Owner, int DrawOrder)
	: SpriteComponent(Owner, DrawOrder),
	  ScrollSpeed(0),
	  ScreenSize({}) {
}

void BackgroundSpriteComponent::update(float DeltaTime) {
  SpriteComponent::update(DeltaTime);
  for (auto &Background : BackgroundTextures) {
	Background.Offset.x += ScrollSpeed * DeltaTime;
	if (Background.Offset.x < -ScreenSize.x)
	  Background.Offset.x = static_cast<float>(BackgroundTextures.size() - 1) * ScreenSize.x - 1;
  }
}

void BackgroundSpriteComponent::draw(SDL_Renderer *R) {
  SpriteComponent::draw(R);
  for (auto &Background : BackgroundTextures) {
	SDL_Rect Rect;
	Rect.w = static_cast<int>(ScreenSize.x);
	Rect.h = static_cast<int>(ScreenSize.y);
	Rect.x = static_cast<int>(Owner->getPosition().x - static_cast<float>(Rect.w) / 2 + Background.Offset.x);
	Rect.x = static_cast<int>(Owner->getPosition().y - static_cast<float>(Rect.h) / 2 + Background.Offset.y);

	SDL_RenderCopy(R, Background.Texture, nullptr, &Rect);
  }
}

void BackgroundSpriteComponent::setBackgroundTextures(std::vector<SDL_Texture *> &Textures) {
  int count = 0;
  for (auto Texture : Textures) {
	BackgroundTexture BackgroundTexture{Texture, {static_cast<float>(count) * ScreenSize.x, 0}};
	BackgroundTextures.emplace_back(BackgroundTexture);
	count++;
  }
}