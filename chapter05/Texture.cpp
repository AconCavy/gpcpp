#include "Texture.hpp"

#include <SDL.h>
#include <SOIL2/SOIL2.h>
#include <gl/glew.h>

using namespace gpcpp::c05;

Texture::Texture() : TextureID(0), Width(0), Height(0) {}

bool Texture::load(const std::string &FileName) {
  int Channels = 0;
  auto Image = SOIL_load_image(FileName.c_str(), &Width, &Height, &Channels,
                               SOIL_LOAD_AUTO);

  if (Image == nullptr) {
    SDL_Log("SOIL failed to load image %s: %s", FileName.c_str(),
            SOIL_last_result());
    return false;
  }

  int Format = Channels == 4 ? GL_RGBA : GL_RGB;

  glGenTextures(1, &TextureID);
  glBindTexture(GL_TEXTURE_2D, TextureID);
  glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format,
               GL_UNSIGNED_BYTE, Image);

  SOIL_free_image_data(Image);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return true;
}

void Texture::unload() { glDeleteTextures(1, &TextureID); }

void Texture::setActive() { glBindTexture(GL_TEXTURE_2D, TextureID); }
