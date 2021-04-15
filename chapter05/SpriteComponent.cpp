#include "SpriteComponent.hpp"

#include "Actor.hpp"
#include "Game.hpp"
#include "Shader.hpp"

using namespace gpcpp::c05;

SpriteComponent::SpriteComponent(class Actor *Owner, int DrawOrder)
    : Component(Owner), Texture(nullptr), DrawOrder(DrawOrder), TextureWidth(0),
      TextureHeight(0) {
  Owner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent() { Owner->getGame()->removeSprite(this); }

void SpriteComponent::draw(Shader *S) {
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::setTexture(SDL_Texture *T) {
  Texture = T;
}
