#include "Vector2.h"

std::ostream& operator<<(std::ostream& os, const Vector2& vector2)
{
	return os << "(" << vector2.x << ", " << vector2.y << ")";
}

Vector2::Vector2()
	:x(0), y(0)
{
}

Vector2::Vector2(int x, int y)
	:x(x), y(y)
{
}

Vector2::~Vector2()
{
}