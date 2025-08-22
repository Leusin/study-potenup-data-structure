#pragma once

#include "Position.h"

class Node
{
public: // RAII
	Node(int x = 0, int y = 0, Node* parent = nullptr)
		: position{ x, y }
		, gCost{ 0 }
		, hCost{ 0 }
		, fCost{ 0 }
		, parent{ parent }
	{

	}

public: // OPERATOR
	Position operator-(const Node& other) const
	{
		return Position{ position.x - other.position.x, position.y - other.position.y };
	}

	bool operator==(const Node& other) const
	{
		return position == other.position;
	}

//private: // DATA

	// 위치
	Position position;
	float gCost;
	float hCost;
	float fCost;
	Node* parent;
};