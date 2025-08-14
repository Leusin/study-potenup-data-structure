#pragma once

#include <ostream>

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector2);

//private:
	int x = 0;
	int y = 0;
};