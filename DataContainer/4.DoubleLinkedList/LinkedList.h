#pragma once

#include <iostream>
#include"Node.h"

template<typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

template<typename T>
class LinkedList
{
public:
	LinkedList()
		:first{ new Node<T>() }, last{ new Node<T>() }, count{}
	{
		// 시작 노드 서로 연결
		first->next = last;
		last->previous = first;
	}

	~LinkedList()
	{
		// 전체 삭제
		Clear();

		// 기본 노드 삭제.
		SafeDelete(first);
		SafeDelete(last);
	}

	// 노드 전체 삭제 함수
	void Clear()
	{
		// 시작 노드 저장
		Node<T>* current = first->next;

		// 순회하면서 삭제
		while (current != nullptr && current != last)
		{
			Node<T>* next = current->next; // 다음 노드 임시 저장

			SafeDelete(current); // 현재 노드 제거

			--count;
			current = next; // 다음 노드로 이동
		}

		// 정리
		count = 0;
		first->next = last;
		last->next = first;
	}

	// 마지막 위치에 노드 추가하는 함수
	void PushBack(const T& newData)
	{
		// 새 노드 생성
		Node<T>* newNode = new Node<T>();
		newNode->data = newData;

		// 이전 노드 관련 포인터 정리
		Node<T>* previous = last->previous; // 원래의 마지막 노드 임시 저장
		previous->next = newNode;
		newNode->previous = previous;

		// 새노드 관련 포인터 
		newNode->next = last;
		last->previous = newNode;

		++count;
	}

	void Print()
	{
		Node<T>* current = first->next;

		while (current && current != last)
		{
			std::cout << "데이터: " << current->data << "\n";
			current = current->next;
		}
	}

private:
	// 처음과 마지막을 가리키는 노드
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;

	// 리스트에 저장된 요소 수
	int count = 0;
};
