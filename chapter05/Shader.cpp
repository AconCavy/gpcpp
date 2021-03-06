#include "Shader.hpp"

#include <SDL.h>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

using namespace gpcpp::c05;

Shader::Shader() : ShaderProgram(0), VertexShader(0), FragmentShader(0) {}

bool Shader::load(const std::string &VertexFileName,
                  const std::string &FragmentFileName) {

  if (!compileShader(VertexFileName, GL_VERTEX_SHADER, VertexShader) ||
      !compileShader(FragmentFileName, GL_FRAGMENT_SHADER, FragmentShader))
    return false;

  ShaderProgram = glCreateProgram();
  glAttachShader(ShaderProgram, VertexShader);
  glAttachShader(ShaderProgram, FragmentShader);
  glLinkProgram(ShaderProgram);

  return isValidProgram();
}

void Shader::unload() {
  glDeleteProgram(ShaderProgram);
  glDeleteShader(VertexShader);
  glDeleteShader(FragmentShader);
}

void Shader::setActive() const { glUseProgram(ShaderProgram); }

void Shader::setMatrixUniform(const char *Name, const glm::mat4 &Matrix) {
  GLuint Location = glGetUniformLocation(ShaderProgram, Name);
  glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix));
}

bool Shader::compileShader(const std::string &FileName, GLenum ShaderType,
                           GLuint &OutShader) {

  std::ifstream ShaderFile(FileName);

  if (!ShaderFile.is_open()) {
    SDL_Log("Shader file not found: %s", FileName.c_str());
    return false;
  }

  std::stringstream SStream;
  SStream << ShaderFile.rdbuf();
  auto Contents = SStream.str();
  const char *ContentsChar = Contents.c_str();

  OutShader = glCreateShader(ShaderType);

  glShaderSource(OutShader, 1, &ContentsChar, nullptr);
  glCompileShader(OutShader);

  if (!isCompiled(OutShader)) {
    SDL_Log("Failed to compile shader %s", FileName.c_str());
    return false;
  }

  return true;
}

bool Shader::isCompiled(GLuint Shader) {
  GLint Status;
  glGetShaderiv(Shader, GL_COMPILE_STATUS, &Status);

  if (Status == GL_TRUE)
    return true;

  char Buffer[512];
  memset(Buffer, 0, 512);
  glGetShaderInfoLog(Shader, 511, nullptr, Buffer);
  SDL_Log("GLSL compile failed: \n%s", Buffer);
  return false;
}

bool Shader::isValidProgram() const {
  GLint Status;
  glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Status);

  if (Status == GL_TRUE)
    return true;

  char Buffer[512];
  memset(Buffer, 0, 512);
  glGetProgramInfoLog(ShaderProgram, 511, nullptr, Buffer);
  SDL_Log("GLSL link status: \n%s", Buffer);
  return false;
}
