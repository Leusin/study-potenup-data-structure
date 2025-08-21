#pragma once

/// <summary>
/// 이진 트리에 사용될 노드
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
class Node
{
	// friend 선언
	template<typename T> 
	friend class BinaryTree;

public: // 생성자 소멸자
	Node() : data{}, parent{ nullptr }, left{ nullptr }, right{ nullptr }
	{
	}

	Node(const T& data) : data{ data }, parent{ nullptr }, left{ nullptr }, right{ nullptr }
	{
	}

	~Node() = default;

public: // 메시지 Message (인터페이스 Interface)
	void AddLeftChild(const T& data)
	{
		AddLeftChild(new Node<T>(data));
	}

	void AddLeftChild(Node<T>* child)
	{
		// 1. child 부모 설정
		child->SetParent(this);

		// 2. 왼쪽 자손으로 설정
		left = child;
	}

	void AddRightChild(const T& data)
	{
		AddRightChild(new Node<T>(data));
	}

	void AddRightChild(Node<T>* child)
	{
		// 1. child 부모 설정
		child->SetParent(this);

		// 2. 오른쪽 자손으로 설정
		right = child;
	}

	void Destroy()
	{
		// 1. 부모 노드의 포인터 정리
		if (parent)
		{
			// 1) 부모 노드의 왼쪽인 경우
			if (parent->GetLeftChild() == this)
			{
				parent->left = nullptr;
			}

			// 2) 부모 노드의 오른쪽인 경우
			else if (parent->GetRightChild() == this)
			{
				parent->right = nullptr;
			}
		}

		// 2. 이 노드 포함 자손까지 방문해서 정리
		DestroyRecursive(this);
	}

public: // Getter Setter
	T GetData() const { return data; }

	Node<T>* GetParent() const { return parent; }
	void SetParent(Node<T>* newParent) { parent = newParent; }

	Node<T>* GetLeftChild() const { return left; }
	Node<T>* GetRightChild() const { return right; }

private: // 메소드 Method
	void DestroyRecursive(Node<T>* node)
	{
		// base case
		if (!node)
		{
			return;
		}

		// 자손 노드의 존재 확인
		Node<T>* leftChild = node->GetLeftChild();
		Node<T>* rightChild = node->GetRightChild();

		// 1) 자손이 없는 경우.
		if (leftChild == nullptr && rightChild == nullptr)
		{
			// 자신 삭제 후 종료
			delete node;
			node = nullptr;

			return;
		}

		// 2) 자손이 있는 경우.
		DestroyRecursive(leftChild);
		DestroyRecursive(rightChild);

		delete node;
		node = nullptr;
	}

private:
	T data;

	// 부모 
	Node<T>* parent = nullptr;

	// 자손
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;

};
