#ifndef GPCPP_UTILS_MATH_HPP
#define GPCPP_UTILS_MATH_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>

namespace gpcpp {

static inline float toDegree(float Radian) {
  return static_cast<float>(Radian * 180.0f / glm::pi<float>());
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

static inline glm::mat4 createScale(const glm::vec3 &Scale) {
  return glm::scale(glm::mat4(1), Scale);
}

static inline glm::mat4 createScale(float Scale) { return glm::mat4(Scale); }

static inline glm::mat4 createRotationX(float Theta) {
  return glm::rotate(glm::mat4(1), Theta, {1, 0, 0});
}

static inline glm::mat4 createRotationY(float Theta) {
  return glm::rotate(glm::mat4(1), Theta, {0, 1, 0});
}

static inline glm::mat4 createRotationZ(float Theta) {
  return glm::rotate(glm::mat4(1), Theta, {0, 0, 1});
}

static inline glm::mat4 createTranslation(const glm::vec3 &Translation) {
  auto Matrix = glm::mat4(1);
  Matrix[0][3] = Translation.x;
  Matrix[1][3] = Translation.y;
  Matrix[2][3] = Translation.z;
  return Matrix;
}

static glm::mat4 createSimpleViewProjection(float Width, float Height) {
  auto Matrix = glm::mat4(1);
  Matrix[0][0] = 2 / Width;
  Matrix[1][1] = 2 / Height;
  Matrix[2][3] = 1;
  return Matrix;
}

} // namespace gpcpp

#endif // GPCPP_UTILS_MATH_HPP
