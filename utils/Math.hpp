#ifndef GPCPP_UTILS_MATH_HPP
#define GPCPP_UTILS_MATH_HPP

#include <glm/glm.hpp>
#include <random>

namespace gpcpp {

const double PI = 3.14159;

static inline float toDegree(float Radian) {
  return static_cast<float>(Radian * 180.0f / PI);
}

static inline bool isNearZero(double Value, double EPS) {
  return abs(Value) < EPS;
}

static inline long getRandomIntRange(long Min, long Max) {
  std::random_device Rnd;
  std::mt19937 MT32(Rnd());
  std::uniform_int_distribution<long> Range(Min, Max);
  return Range(MT32);
}

static inline double getRandomRealRange(double Min, double Max) {
  std::random_device Rnd;
  std::mt19937 MT32(Rnd());
  std::uniform_real_distribution<double> Range(Min, Max);
  return Range(MT32);
}

static glm::mat4x4 createScale(float X, float Y, float Z) {
  glm::mat4x4 Matrix;
  Matrix[0][0] = X;
  Matrix[1][1] = Y;
  Matrix[2][2] = Z;
  Matrix[3][3] = 1;
  return Matrix;
}

static glm::mat4x4 createScale(float Scale) {
  return createScale(Scale, Scale, Scale);
}

static glm::mat4x4 createScale(const glm::vec3 &Scale) {
  return createScale(Scale.x, Scale.y, Scale.z);
}

static glm::mat4x4 createRotationX(float Theta) {
  glm::mat4x4 Matrix;
  Matrix[0][0] = 1;
  Matrix[1][1] = glm::cos(Theta);
  Matrix[1][2] = glm::sin(Theta);
  Matrix[2][1] = -glm::sin(Theta);
  Matrix[2][2] = glm::cos(Theta);
  Matrix[3][3] = 1;
  return Matrix;
}

static glm::mat4x4 createRotationY(float Theta) {
  glm::mat4x4 Matrix;
  Matrix[1][1] = 1;
  Matrix[0][0] = glm::cos(Theta);
  Matrix[0][2] = -glm::sin(Theta);
  Matrix[2][0] = glm::sin(Theta);
  Matrix[2][2] = glm::cos(Theta);
  Matrix[3][3] = 1;
  return Matrix;
}

static glm::mat4x4 createRotationZ(float Theta) {
  glm::mat4x4 Matrix;
  Matrix[2][2] = 1;
  Matrix[0][0] = glm::cos(Theta);
  Matrix[0][1] = glm::sin(Theta);
  Matrix[1][0] = -glm::sin(Theta);
  Matrix[1][1] = glm::cos(Theta);
  Matrix[3][3] = 1;
  return Matrix;
}

static glm::mat4x4 createTranslation(float X, float Y, float Z) {
  glm::mat4x4 Matrix;
  Matrix[0][0] = Matrix[1][1] = Matrix[2][2] = Matrix[3][3] = 1;
  Matrix[3][0] = X;
  Matrix[3][1] = Y;
  Matrix[3][2] = Z;
  return Matrix;
}

static glm::mat4x4 createSimpleViewProjection(float Width, float Height) {
  glm::mat4x4 Matrix;
  Matrix[0][0] = 2 / Width;
  Matrix[1][1] = 2 / Height;
  Matrix[2][2] = 1;
  Matrix[3][2] = Matrix[3][3] = 1;
  return Matrix;
}

static glm::mat4x4 createTranslation(const glm::vec3 &Translation) {
  return createTranslation(Translation.x, Translation.y, Translation.z);
}

} // namespace gpcpp

#endif // GPCPP_UTILS_MATH_HPP
