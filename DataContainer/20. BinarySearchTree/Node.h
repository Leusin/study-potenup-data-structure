#pragma once


/*
* 
*/
template<typename T>
class Node
{
public: // RAII
	Node(const T& data /* = T() */, Node<T>* parent = nullptr)
		:data{data}, parent{ parent }, left{ nullptr }, right{ nullptr }
	{
	}

public: // GET SET
	T GetData() const { return data; }
	void SetData(const T& newdata) { data = newdata; }

	Node<T>* GetParent() const { return parent; }
	void SetParent(Node<T>* newParent) { parent = newParent; }

	Node<T>* GetLeft() const { return left; }
	void SetLeft(Node<T>* newLeft) { left = newLeft; }

	Node<T>* GetRight() const { return right; }
	void SetRight(Node<T>* newRight) { right = newRight; }

private: // DATA
	T data;

	// 부모 
	Node<T>* parent;

	// 왼쪽 자손
	Node<T>* left;

	// 오른쪽 자손
	Node<T>* right;
};
