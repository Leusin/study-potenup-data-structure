#pragma once

#include <vector>
#include "Bounds.h"

/*
* 쿼드 트리 클래스
*/
class QuardTree
{
public:
	QuardTree(const Bounds& bounds);
	~QuardTree();

	// 노드 추가하는 함수
	void Insert(class Node* node);

	// 전달한 노드와 겹치는 노드를 반환 하는 질의 함수
	std::vector<class Node*> Query(class Node* queryNode);

public:

	static int maxDepth;

private:
	class Node* root = nullptr;
};