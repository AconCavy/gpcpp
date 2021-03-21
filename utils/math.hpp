#ifndef GPCPP_UTILS_MATH_HPP
#define GPCPP_UTILS_MATH_HPP

namespace gpcpp {

const double PI = 3.14159;

static inline float toDegree(float Radian) {
  return static_cast<float>(Radian * 180.0f / PI);
}

} // namespace gpcpp

#endif //GPCPP_UTILS_MATH_HPP
