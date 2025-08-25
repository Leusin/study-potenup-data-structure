#pragma once

#include "Bounds.h"
#include <vector>

enum class NodeIndex
{
	// 완전히 포함하는 경우
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,

	Straddling, // 두 영역에 겹친 경우
	OutOfArea	// 영역에 벗어난 경우
};

class Node
{
public: // RAII
	Node(const Bounds& bounds, int depth = 0);
	~Node();

public: // GET SET

	// 삽입
	void Insert(Node* node);

	// 질의
	void Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes);

	// 정리
	void Clear();

public: // GET SET

	Bounds GetBounds() const { return bounds; }
	const std::vector<Node*>& GetPointers() const { return points; }

	Node* GetTopLeft() const { return topLeft; }
	Node* GetTopRight() const { return topRight; }
	Node* GetBottomLeft() const { return bottomLeft; }
	Node* GetBottomRight() const { return bottomRight; }

private: // MESSAGE

	// 겹치는지 또는 포함되는지 확인
	NodeIndex TestRegion(const Bounds& bounds);

	// 요청한 Bounds와 겹치는 4분면 목록 반환 함수
	std::vector<NodeIndex>GetQuads(const Bounds& bounds);

	// 4분면 분할 함수
	bool Subdivide();

	// 분할됐는지 확인하는 함수
	bool IsDivided();

private: // FILD

	// 깊이.
	int depth = 0;

	// 영역.
	Bounds bounds;

	// 현재 노드에 포함된 노드 (배열).
	std::vector<Node*> points;

	// 자식 노드
	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;
};