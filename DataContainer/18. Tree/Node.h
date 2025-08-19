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
