#pragma once

#include <iostream>

#include "Node.h"

template<typename T>
class BinaryTree
{
public: // RAII
	BinaryTree() : root{ nullptr }
	{
	}

	BinaryTree(const T& data) : root{ new Node<T>(data) }
	{

	}

	~BinaryTree()
	{
		if (root)
		{
			root->Destroy();
			root = nullptr;
		}
	}

public: // MESSAGE
	void AddLeftChild(const T& parentData, const T& childData)
	{
		// 1. 부모 검색
		Node<T>* parent = nullptr;
		bool result = Find(parentData, parent);

		// 1) 검색 성공
		if (result)
		{
			parent->AddLeftChild(childData);
			return;
		}

		// 2) 검색 실패
		std::cout << "추가 실패: 부모 노드를 찾지 못했습니다.\n";
	}

	void AddRightChild(const T& parentData, const T& childData)
	{
		// 1. 부모 검색
		Node<T>* parent = nullptr;
		bool result = Find(parentData, parent);

		// 1) 검색 성공
		if (result)
		{
			parent->AddRightChild(childData);
			return;
		}

		// 2) 검색 실패
		std::cout << "추가 실패: 부모 노드를 찾지 못했습니다.\n";
	}

	// 검색
	// 재귀로 동작
	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

	// 전위 순회
	// 재귀로 동작
	void PreorderTraverse()
	{
		PreorderTraverseRecursive(root);
	}

	// 삭제
	bool DeleteNode(const T& data)
	{
		// 1. 검색
		Node<T>* deleteNode = nullptr;
		bool result = Find(data, deleteNode);

		// 1) 찾은 경우 - 삭제
		if (result)
		{
			deleteNode->Destroy();
			return true;
		}

		// 2) 찾지 못한 경우
		std::cout << "삭제 실패: 노드를 찾지 못했습니다.\n";
		return false;
	}

public: // Getter Setter
	Node<T>* GetLeft() const { return root-> GetLeftChild(); }
	Node<T>* GetRight() const { return root-> GetRightChild(); }

private: // METHOD
	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		// base case 1) 끝내 목표 노드를 찾지 못함
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		// base case 2) 목표 노드를 찾음
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// 왼쪽 자손으로 재귀
		bool resultLeft = FindRecursive(data, node->GetLeftChild(), outNode);
		if (resultLeft)
		{
			return true;
		}

		// 오른쪽 자손으로 재귀
		bool resultRight = FindRecursive(data, node->GetRightChild(), outNode);
		if (resultRight)
		{
			return true;
		}

		outNode = nullptr;
		return false;
	}

	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// base case
		if (!node)
		{
			return;
		}

		// 뎊스 출력
		for (int i = 0; i < depth; ++i)
		{
			std::cout << "    ";
		}

		// 부모 방문
		std::cout << node->GetData() << "\n";

		// 왼쪽 자손 방문
		PreorderTraverseRecursive(node->GetLeftChild(), depth + 1);

		// 오른쪽 자손 방문
		PreorderTraverseRecursive(node->GetRightChild(), depth + 1);
	}

private:
	// 최상위 노드 
	Node<T>* root;
};