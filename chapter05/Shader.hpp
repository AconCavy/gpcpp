#ifndef GPCPP_CHAPTER05_SHADER_HPP
#define GPCPP_CHAPTER05_SHADER_HPP

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace gpcpp::c05 {

class Shader {
public:
  Shader();

  bool load(const std::string &VertexFileName,
            const std::string &FragmentFileName);
  void unload();

  void setActive() const;
  void setMatrixUniform(const char *Name, const glm::mat4 &Matrix);

private:
  bool compileShader(const std::string &FileName, GLenum ShaderType,
                     GLuint &OutShader);

  [[nodiscard]] static bool isCompiled(GLuint Shader);
  [[nodiscard]] bool isValidProgram() const;

  GLuint VertexShader;
  GLuint FragmentShader;
  GLuint ShaderProgram;
};

} // namespace gpcpp::c05

#endif // GPCPP_CHAPTER05_SHADER_HPP
