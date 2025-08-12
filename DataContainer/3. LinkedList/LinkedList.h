#pragma once

#include "Node.h"

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	// 첫 노드에 데이터 추가
	// 노드가 비여있으면 Head 생성
	// 노드가 있으면 Head 교체
	void AddToHead(int newData);

	// 맨 뒤에 노드 추가
	void Insert(int newData);

	// 노드 삭제
	void Delete(int newData);

	// 출력
	void Print();

	// 오름차순 정렬 함수
	void SelectionSortGreater();
	void BubbleSortGreater();

	int Count() const { return count; };

	// 선택 정렬
	void SelectSortLess();
	void BubbleSortLess();
	void InsertSortLess();

private:

	// Head 노드
	Node* head = nullptr;

	// 연결 리스트에 저장된 요소 수
	int  count = 0;
};