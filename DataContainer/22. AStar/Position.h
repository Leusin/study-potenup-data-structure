#pragma once

struct Position
{
	Position(int x = 0, int y = 0)
		:x(x), y(y)
	{
	}

	bool operator==(const Position& other) const
	{
		return x == other.x && y == other.y;
	}

	int x = 0;
	int y = 0;
};
