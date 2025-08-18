#pragma once

template<typename T>
class Node
{
	template<typename T>
	friend class LinkedList;

private:
	Node()
		: data{}, next{ nullptr }, previous{ nullptr }
	{

	}

public:
	T data;/* = default(T); // ?? 초기화 */
	Node<T>* next = nullptr;
	Node<T>* previous = nullptr;
};