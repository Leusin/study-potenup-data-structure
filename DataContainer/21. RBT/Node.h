#include "Node.h"
#pragma once

#include "Color.h"

class Node
{
public: // RAII
	Node(int data, Color color = Color::Red);
	~Node() = default;

	inline void Node::Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes)
	{
	}

public: // GET SET
	int GetData() const { return data; }
	void SetData(const int& newData) { data = newData; }

	Color GetColor() const { return color; }
	void SetColor(const Color& newColor) { color = newColor; }
	const char* GetColorString() const;

	Node* GetParent() const { return parent; }
	void SetParent(Node* newParent) { parent = newParent; }

	Node* GetLeft() const { return left; }
	void SetLeft(Node* newLeft) { left = newLeft; }

	Node* GetRight() const { return right; }
	void SetRight(Node* newRight) { right = newRight; }

private: //DATA

	int data = 0;
	Color color;

	//
	// 계층 구조
	//

	// 부모 
	Node* parent = nullptr;

	// 자손
	// 왼쪽: 보다 작은 값
	Node* left = nullptr;

	// 오른쪽: 보다 큰 값
	Node* right = nullptr;
};