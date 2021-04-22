#include "SpriteComponent.hpp"

#include <Math.hpp>

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
  if (!Texture)
    return;

  auto Scale = createScale(static_cast<float>(TextureWidth),
                           static_cast<float>(TextureHeight), 1);
  auto World = Scale * Owner->getWorldTransform();
  S->setMatrixUniform("uWorldTransform", World);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::setTexture(SDL_Texture *T) {
  Texture = T;
  TextureWidth = TextureHeight = 100;
}
