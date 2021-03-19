#ifndef GPCPP_UTILS_MATH_HPP
#define GPCPP_UTILS_MATH_HPP

#include "numbers"

namespace gpcpp::utils {

inline float ToDegree(float radian) {
  return radian * 180.0f / std::numbers::pi;
}

} // namespace gpcpp::utils

#endif //GPCPP_UTILS_MATH_HPP
