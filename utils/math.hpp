#ifndef GPCPP_UTILS_MATH_HPP
#define GPCPP_UTILS_MATH_HPP

namespace gpcpp {

const double PI = 3.14159;
const double EPS = 1e-6;

static inline float toDegree(float Radian) {
  return static_cast<float>(Radian * 180.0f / PI);
}

static inline float isNearZero(float Value) {
  return abs(Value) < EPS;
}

} // namespace gpcpp

#endif //GPCPP_UTILS_MATH_HPP
