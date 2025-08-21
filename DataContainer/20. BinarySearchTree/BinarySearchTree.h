/*
* 이진 탐색 트리 클래스
*/

#pragma once

#include <iostream>
#include "Node.h"

template<typename T>
class BinarySearchTree
{
public: // RAII
	BinarySearchTree() = default;
	~BinarySearchTree()
	{
	}

public: // MESSAGE

	// 검색
	bool Find(const T& data, Node<T>*& outNode) const
	{
		return FindRecursive(data, root, outNode);
	}

	// 삽입
	// - 중복된 값을 허용하지 않음
	// - 루트가 nullptr 일 경우 새 노드를 루트로 지정한다.
	// - 루트 부터 비교 시작
	// - 재귀
	//   - 새로 추가하는 값이 비교 노드보다 작으면 왼쪽 하위 노드로 이동
	//   - 새로 추가하는 값이 비교 노드보다 크면 오른쪽 하위 노드로 이동
	bool Insert(const T& data)
	{
		// 1. 중복 값 검사
		Node<T>* outNode = nullptr;
		if (Find(data, outNode))
		{
			std::cout << "ERROR: 중복된 값이 있어 노드 추가 불가\n";
			return false;
		}

		// 2. 루트가 비어 있는 경우
		if (!root)
		{
			root = new Node<T>(data);
			return true;
		}

		// 3. 삽입 처리
		root = InsertRecursive(data, root, nullptr);

		return true;
	}

	// 최솟값 검색

	// 최댓값 검색

	// 삭제

	// 중위 순회(정렬된 수서대로 출력)

private: // METHOD

	// 재귀 검색
	bool FindRecursive(const T& data, Node<T>* node, Node<T>* outNode) const
	{
		// 1. 종료 조건
		// base case 1) 검색 실패
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		// base case 2) 검색 성공
		if (node->GetData() == data)
		{
			outNode == node;
			return true;
		}

		// 2. 재귀
		// 1) 찾는 데이터가 비교하는 노드 보다 작은 경우
		if (node->GetData() > data)
		{
			return FindRecursive(data, node->GetLeft(), outNode);
		}
		// 2) 찾는 데이터가 비교하는 노드 보다 큰 경우
		return FindRecursive(data, node->GetRight(), outNode);
	}

	// 재귀 삽입
	// 현재 노드기 nullptr 일때까지 추가 하려는 데이터가 작으면 왼쪽, 크면 오른쪽으로 내려감
	Node<T>* InsertRecursive(const T& data, Node<T>* node, Node<T>* parent)
	{
		// 1. 종료 조건
		if (!node)
		{
			// 삽입
			return new Node<T>(data, parent);
		}

		// 2. 재귀 탐색
		// 1) 왼쪽: 보다 작은 경우 
		if (node->GetData() > data)
		{
			node->SetLeft(InsertRecursive(data, node->GetLeft(), node));
		}
		// 2) 오른쪽: 보다 큰 경우 
		node->SetLeft(InsertRecursive(data, node->GetRight(), node));

		return node;
	}
	

private: // DATA
	// 최상위 노드
	Node<T>* root = nullptr;
};
