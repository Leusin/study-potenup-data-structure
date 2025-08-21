/*
* RBT
* - 모든 노드에 빨간색 또는 검은 색을 부여하고 다섯가지 규칙을 가짐
* - 이 규칙을 통해 트리의 가장 긴 경로가 가장 짧은 경로의 두배를 넘지 않도록 함
* 1. 모든 노드는 빨간색 또는 검은색
* 2. 루트 노드는 검은색
* 3. 모든 리프 노드(NIL) 은 검은색
* 4. 빨간색 노드의 자식은 모두 검은색(자식이 빨간색이면 안됨. 처리 까다로움)***
* 5. 자기 자신을제외한 어떤 노드 부터 리프(NIL)까지 경로에 있는 검은색 노드 수는 같다
*/
#pragma once

#include <iostream>

#include "Color.h"

class RedBlackTree
{
public: // RAII

	RedBlackTree();
	~RedBlackTree();

public: // MESSAGE

	// 검색
	bool Find(int data, class Node*& outNode);

	// 추가
	bool Insert(int data);

private: // METHOD

	// 노드 생성 팩토리
	class Node* CreatNode(int data, Color color);

	// 검색 재귀
	bool FindRecursive(int data, class Node* node, class Node*& outNode);

	// 삽입 재귀
	void InsertRecursive(class Node* node, class Node* newNode);

	// 노드 삽입 후 재정렬 처리
	void RestructureAfterInsert(class Node* newNode);

	// 좌회전
	void RotateToLeft(Node* node);

	// 우회전
	void RotateToRight(Node* node);


private: // DATA

	class Node* root;

	static class Node* nil;
};