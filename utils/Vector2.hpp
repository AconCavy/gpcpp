struct Vector2
{
	float x;
	float y;

	Vector2& operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2& operator*=(const float& rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2 operator+(const Vector2& rhs) const
	{
		Vector2 ret{ x + rhs.x, y + rhs.y };
		return ret;
	}

	Vector2 operator*(const float& rhs) const
	{
		Vector2 ret{ x * rhs, y * rhs };
		return ret;
	}
};