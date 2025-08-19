#pragma once

#include "List.h"
#include "Node.h"

template<typename T>
class Tree
{
public:
	Tree(const T& data)
		: root(new Node<T>(data))
	{

	}

	~Tree()
	{
		// TODO: 모든 노드를 순회해서 삭제
	}

	void AddChild(const T& parentData, const T& childData)
	{
		// 1. 검색
		Node<T>* outParent = nullptr;
		bool result = Find(parentData, outParent);

		// 2. 부모 노드 검색 성공 시 자손 노드 추가
		if (result)
		{
			outParent->AddChild(childData);
			return;
		}

		// 부모 노드 검색 실패.
		std::cout << "해당 값을 갖는 부모 노드 검색에 실패했습니다.\n";
	}

	/// <summary>
	/// 데이터로 특정 노드를 검색하는 일반 함수
	/// </summary>
	/// <param name="data">검색할 데이터</param>
	/// <param name="outNode">해당 데이터를 가진 노드(출력용)</param>
	/// <returns></returns>
	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		// base case
		if (node == nullptr)
		{
			outNode = nullptr;
			return false;
		}

		// 검색 성공
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// 자손을 재귀적으로 검색
		List<Node<T>*>& children = node->GetChildren();
		int count = children.Size();

		for (int i = 0; i < count; ++i)
		{
			Node<T>* child = children[i];
			bool result = FindRecursive(data, child, outNode);

			if (result)
			{
				return true;
			}
		}

		// 검색 실패
		outNode = nullptr;
		return false;
	}

private:
	Node<T>* root = nullptr;
};