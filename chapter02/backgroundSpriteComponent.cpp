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
	Background.Offset.X += ScrollSpeed * DeltaTime;
	if (Background.Offset.X < -ScreenSize.X)
	  Background.Offset.X = static_cast<float>(BackgroundTextures.size() - 1) * ScreenSize.X - 1;
  }
}

void BackgroundSpriteComponent::draw(SDL_Renderer *R) {
  SpriteComponent::draw(R);
  for (auto &Background : BackgroundTextures) {
	SDL_Rect R;
	R.w = static_cast<int>(ScreenSize.X);
	R.h = static_cast<int>(ScreenSize.Y);
	R.x = static_cast<int>(Owner->getPosition().X - static_cast<float>(R.w) / 2 + Background.Offset.X);
	R.x = static_cast<int>(Owner->getPosition().Y - static_cast<float>(R.h) / 2 + Background.Offset.Y);

	SDL_RenderCopy(R, Background.Texture, nullptr, &R);
  }
}

void BackgroundSpriteComponent::setBackgroundTextures(std::vector<SDL_Texture *> &Textures) {
  int count = 0;
  for (auto Texture : Textures) {
	BackgroundTexture BackgroundTexture{Texture, {static_cast<float>(count) * ScreenSize.X, 0}};
	BackgroundTextures.emplace_back(BackgroundTexture);
	count++;
  }
}