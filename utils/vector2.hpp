#ifndef GPCPP_UTILS_VECTOR2_HPP
#define GPCPP_UTILS_VECTOR2_HPP

namespace gpcpp {

struct Vector2 {
  float X;
  float Y;

  Vector2 &operator+=(const Vector2 &RHS) {
	X += RHS.X;
	Y += RHS.Y;
	return *this;
  }

  Vector2 &operator*=(const float &RHS) {
	X *= RHS;
	Y *= RHS;
	return *this;
  }

  Vector2 operator+(const Vector2 &RHS) const {
	Vector2 Ret{X + RHS.X, Y + RHS.Y};
	return Ret;
  }

  Vector2 operator*(const float &RHS) const {
	Vector2 Ret{X * RHS, Y * RHS};
	return Ret;
  }
};

} // namespace gpcpp

#endif //GPCPP_UTILS_VECTOR2_HPP