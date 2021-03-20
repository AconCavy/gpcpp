#ifndef GPCPP_UTILS_MATH_HPP
#define GPCPP_UTILS_MATH_HPP

#include "numbers"

namespace gpcpp {

static inline float toDegree(float Radian) {
  return static_cast<float>(Radian * 180.0f / std::numbers::pi);
}

} // namespace gpcpp

#endif //GPCPP_UTILS_MATH_HPP
