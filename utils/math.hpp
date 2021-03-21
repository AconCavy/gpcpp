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

} // namespace gpcpp

#endif //GPCPP_UTILS_MATH_HPP
