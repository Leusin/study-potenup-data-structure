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
		DestroyRecursive(root);
	}

public: // MESSAGE

	// 검색
	bool Find(const T& data, Node<T>*& outNode) const
	{
		return FindRecursive(data, root, outNode);
	}

	// 삽입
	/*
	* - 중복된 값을 허용하지 않음
	* - 루트가 nullptr 일 경우 새 노드를 루트로 지정한다.
	* - 루트 부터 비교 시작
	* - 재귀
	*   - 새로 추가하는 값이 비교 노드보다 작으면 왼쪽 하위 노드로 이동
	*   - 새로 추가하는 값이 비교 노드보다 크면 오른쪽 하위 노드로 이동
	*/
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
		/* root = */InsertRecursive(data, root, nullptr);

		return true;
	}

	// 삭제
	bool Delete(const T& data)
	{
		Node<T>* deleteNode = nullptr;
		if (!Find(data, deleteNode))
		{
			std::cout << "ERROR:  삭제할 노드를 찾지 못했습니다.\n";
			return false;
		}

		// TODO: 재귀적으로 삭제하는 함수 작성 후 호출
		DeleteRecursive(data, root);
		return true;
	}

	// 최솟값 검색
	Node<T>* FindMin(Node<T>* node)
	{
		// 가장 왼쪽 끝의 노드 검색
		while (node->GetLeft())
		{
			node = node->GetLeft();
		}

		return node;
	}

	// 최댓값 검색
	Node<T>* FindMax(Node<T>* node)
	{
		// 가장 오른쪽 끝의 노드 검색
		while (node->GetRight())
		{
			node = node->GetRight();
		}

		return node;
	}

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
		else
		{
			node->SetRight(InsertRecursive(data, node->GetRight(), node));
		}

		return node;
	}

	// 재귀 삭제
	Node<T>* DeleteRecursive(const T& data, Node<T>* node)
	{
		// 1. 종료 조건
		// 1) 현재 노드가 nullptr 인 경우 - ??? 발생하면 안 되는 조건
		if (!node)
		{
			return nullptr;
		}

		// 2. 재귀 탐색
		// 1) 현재 노드보다 값이 작음
		if (node->GetData() > data)
		{
			node->SetLeft(DeleteRecursive(data, node->GetLeft()));
		}
		// 2) 현재 노드보다 값이 큰 
		else if (node->GetData() < data)
		{
			node->SetRight(DeleteRecursive(data, node->GetRight()));
		}
		// 3) 삭제할 값을 찾음

		// 3. 삭제 노드 탐색
		else //if (node->GetData() == data)
		{
			// 1) 자식이 없는 경우
			if (!node->GetLeft() && !node->GetRight())
			{
				delete node;
				return nullptr;
			}

			// 2) 자식이 모두 있는 경우
			if (node->GetLeft() && node->GetRight())
			{
				/*
				* 두가지 선택지가 있다.
				* -> 현재 위치를 자식 노드 중 큰 값으로 대체
				* -> 현재 위치를 자식 노드 중dms 작 값으로 대체 (이쪽 방법 선택)
				*/

				// [1] 삭제할 위치의 노드 값을 대체 값으로 할당
				Node<T>* minChild = FindMin(node->GetRight());
				node->SetData(minChild->GetData());

				// [2] 대체되는 노드 삭제
				node->SetRight(DeleteRecursive(node->GetData(), node->GetRight()));
			}

			// 3) 자식이 하나만 있는 경우
			else // if ((node->GetLeft() || node->GetRight()) && !(node->GetLeft() && node->GetRight())) // XOR
			{
				// 3-1) 왼쪽만 있는 경우
				if (node->GetLeft())
				{
					Node<T>* left = node->GetLeft();
					left->SetParent(node->GetParent());

					delete node;

					return left;

				}
				// 3-2) 오른쪽만 있는 경우
				else if (node->GetRight())
				{
					Node<T>* right = node->GetRight();
					right->SetParent(node->GetParent());

					delete node;

					return right;
				}
			}
		}

		return node;
	}

	// 재귀 메모리 해제
	void DestroyRecursive(Node<T>* node)
	{
		// 종료 조건.
		if (!node)
		{
			return;
		}

		Node<T>* left = node->GetLeft();
		Node<T>* right = node->GetRight();

		if (!left && !right)
		{
			delete node;
			node = nullptr;
			return;
		}

		// 자손이 있으면 재귀적으로 한번 더 진행.
		DestroyRecursive(left);
		DestroyRecursive(right);

		// 자손 모두 제거 후 노드 제거.
		delete node;
		node = nullptr;
	}

private: // DATA

	// 최상위 노드
	Node<T>* root = nullptr;
};
