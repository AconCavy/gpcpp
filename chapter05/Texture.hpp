#ifndef GPCPP_CHAPTER05_TEXTURE_HPP
#define GPCPP_CHAPTER05_TEXTURE_HPP

#include <string>

namespace gpcpp::c05 {

class Texture {
public:
  Texture();

  bool load(const std::string &FileName);
  void unload();

  [[nodiscard]] int getWidth() const { return Width; }
  [[nodiscard]] int getHeight() const { return Height; }

  void setActive();

private:
  unsigned int TextureID;
  int Width;
  int Height;
};

} // namespace gpcpp::c05

#endif // GPCPP_CHAPTER05_TEXTURE_HPP
