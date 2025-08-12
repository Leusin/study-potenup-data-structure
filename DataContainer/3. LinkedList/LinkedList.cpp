#include "LinkedList.h"

LinkedList::LinkedList()
	: count(0)
	, head(nullptr)
{
}

LinkedList::~LinkedList()
{
	Node* current = head;
	Node* trail = nullptr;

	while(current != nullptr)
	{
		// 임시 저장
		trail = current;

		// 다음 노드로 이동
		current = current->next;

		// 할당 해제
		delete trail;
		trail = nullptr;

		// 디버깅용
		--count;
	}
}

void LinkedList::AddToHead(int newData)
{
	// 새 노드 생성
	Node* newNode = new Node(newData);

	// 1. Head 가 비어 있는 경우
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// 2. Head가 비어 있지 않은 경우
	newNode->next = head;
	head = newNode;
	++count;
}

// 맨 뒤에 데이터 추가 
void LinkedList::Insert(int newData)
{
	// 새 노드 생성
	Node* newNode = new Node(newData);

	// 1. 리스트가 비어 있는 경우
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// 2. Head가 비어 있지 않은 경우
	// 2-1. 마지막 노드 검색, 
	// 실습에서는 while 을 썼지만 count 값이 있으니 안전하게 루프문을 돌아 봄
	Node* current = head;
	for (int i = 0; i < count - 1; i++) // 크기가 n 이라면 n-1 번 이동
	{
		current = current->next;
	}

	// 일어나선 안되는 조건
	if (current == nullptr || current->next != nullptr) 
	{
		__debugbreak();
		return;
	}

	// 2-2. 마지막 노드 검색 완료. 
	// 새로운 노드 할당 
	current->next = newNode;
	++count;
}

void LinkedList::Delete(int data)
{
	if (head == nullptr)
	{
		std::cout << "리스트가 비어 있어서 삭제 불가\n";
	}

	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		// 찾으려는 데이터를 가진 노드 검색에 성공한 경우
		if (current->data == data)
		{
			break;
		}

		// 못 찾은 경우 다음 노드
		trail = current;
		current = current->next;
	}

	// 경우의 수 확인
	// #1 리스트에 삭제하려는 데이터가 없음
	if (current == nullptr)
	{
		std::cout << "값: " << data << "를 찾지 못했습니다.\n";
		return;
	}

	// #2 검색에 성공한 경우
	// #2-1 삭제하려는 노드가 head 인 경우
	if (current == head)
	{
		head = head->next;
	}
	// #2-2 삭제하려는 노드가 head 가 아닌 경우
	else
	{
		trail->next = current->next;
	}

	// 삭제
	delete current;
	current = nullptr;
	--count;
}

void LinkedList::Print()
{
	// head 노드부터 순회하면서 출력.
	Node* current = head;

	// 현재 노드가 null일 때까지 반복 (모든 노드 방문).
	//while (current != nullptr)
	//{
	//	// 현재 노드 데이터 출력.
	//	std::cout << *current << "\n";

	//	// 다음 노드로 이동.
	//	current = current->next;
	//}

	// 내버전
	for (int i = 0; i < count; i++)
	{
		// 현재 노드 데이터 출력.
		std::cout << *current << "\n";

		// 다음 노드로 이동.
		current = current->next;
	}
}
