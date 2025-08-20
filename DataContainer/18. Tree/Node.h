#pragma once

#include "List.h"

template<typename T>
class Node
{
public:
	Node(const T& data)
		:data(data), parent(nullptr)
	{
	}

	// 복사 생성자 제거
	Node(const Node& other) = delete;

	~Node()
	{
		parent = nullptr;
	}

	void AddChild(const T& data)
	{
		AddChild(new Node<T>(data));
	}

	void AddChild(Node<T>* child)
	{
		child->parent = this;

		children.PushBack(child);
	}

	void RemoveChild(Node<T>* child)
	{
		RemoveChildRecursive(child);
	}

	void RemoveChildRecursive(Node<T>* child)
	{
		if (!child)
		{
			return;
		}

		List<Node<T>*>& children = child->GetChildren();

		// 1) 자손 이 없는 경우
		if (children.Size() == 0)
		{
			child->GetParent()->GetChildren().Remove(child);

			delete child;
			child = nullptr;

			return;
		}

		// 자손이 있는 경우
		while (children.Size() > 0)
		{
			RemoveChildRecursive(children[0]);
		}

		child->GetParent()->GetChildren().Remove(child);

		delete child;
		child = nullptr;
	}


	T GetData() const
	{
		return data;
	}

	const List<Node<T>*>& GetChildren() const
	{
		return children;
	}

	List<Node<T>*>& GetChildren()
	{
		return children;
	}

	Node<T>* GetParent() const
	{
		return parent;
	}

	void SetParent(const Node<T>* const parent)
	{
		this->parent = parent;
	}

private:
	// 노드에 저장할 데이터
	T data;

	// 부모 참조 변수
	Node<T>* parent = nullptr;

	List<Node<T>*> children;
};
