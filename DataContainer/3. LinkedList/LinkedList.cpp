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

	while (current != nullptr)
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

void LinkedList::SelectSortLess()
{
	// 시간복잡도: O(n^2)
	// 공간복잡도: O(1)
	// 안정성: false
	// 교환 횟수가 적은 편. 성능이 좋지 않음

	Node* current = head;
	Node* trail = nullptr;

	// 리스트가 비어 있거나 노드가 하나인 경우
	if (current == nullptr || current->next == nullptr)
	{
		return;
	}

	for (int i = 0; i < count - 1 /* && current != nullptr */; i++)
	{
		Node* minNode = current;
		Node* minTrail = trail;

		Node* compareTrail = current;
		Node* compare = compareTrail->next;

		for (int j = i + 1; j < count /* && compare != nullptr */; j++)
		{
			if (compare->data < minNode->data)
			{
				minTrail = compareTrail;
				minNode = minTrail->next;
			}
			compareTrail = compare;
			compare = compareTrail->next;
		}

		if (minNode != current)
		{
			// 1. b 위치에 a 덮어쓰기
			// 1-1. b trail의 next 업데이트
			// 1-1-1. 현재 노드가 맨 앞에 있는 경우
			if (trail == nullptr)
			{
				head = minNode;
			}
			// 1-1-2. 현재 노드가 맨 앞에 있지 않은 경우
			else
			{
				trail->next = minNode; // 현재 노드를 가리키는 노드의 다음을 a로 변경
			}

			// 1-2. a의 next 업데이트
			Node* minNext = minNode->next;
			// 1-2-1. a가 b 노드의 다음 노드인 경우
			if (minNode == current->next)
			{
				// before: [3] -> [2] -> ?
				// after : [2] -> [3] -> ?
				minNode->next = current;
			}
			else // 1-2-2. a 가 b 노드의 다음 노드가 아닌 경우
			{
				minNode->next = current->next;
			}

			// 2. a 의 자리를 b 위치로 쓰기
			minTrail->next = current; // 2-1. a trail의 next 업데이트
			current->next = minNext; // 2-2. b next 업데이트

		}

		// 다음 노드로 이동 
		trail = (minNode != current) ? minNode : current;
		current = trail->next;
	}
}

void LinkedList::BubbleSortLess()
{
	// 시간복잡도: O(n^2)
	// 공간복잡도: O(1)
	// 안정성: true
	// 근처 노드끼리 자리를 배구끼 때문에 간단. 하지만 성능이 좋지 않음

	// 리스트가 비어 있거나 노드가 하나인 경우
	if (head == nullptr || head->next == nullptr)
	{
		return;
	}

	bool swapped = true;

	while (swapped)
	{
		swapped = false;

		Node* current = head;
		Node* trail = nullptr;

		for (int i = 0; i < count - 1 /*&& current != nullptr && current->next != nullptr*/; ++i)
		{
			if (current->data > current->next->data)
			{
				swapped = true;

				Node* nextNode = current->next;
				Node* nextNext = nextNode->next; // ??? 네이밍

				// 1. 현재 위치에 nextNode 덮어쓰기
				// 1-1. trail의 next 업데이트
				if(trail == nullptr)
				{
					head = nextNode; // head를 nextNode로 변경
				}
				else
				{
					trail->next = nextNode;
				}
				// 1-2. next 업데이트
				nextNode->next = current;

				// 2. nextNode의 자리를 현재 위치로 쓰기
				// 2-1. current 의 trail은 nextNode가 됨
				// 2-2. 현재 노드의 다음을 nextNode의 다음으로 업데이트
				current->next = nextNext; 
				trail = nextNode;
			}
			else
			{
				// 다음 노드로 이동
				trail = current;
				current = trail->next;
			}
		}
	}
}

void LinkedList::InsertSortLess()
{
	// 시간복잡도: O(n^2)
	// 공간복잡도: O(1)
	// 안정성: true
	// 요소가 거의 정렬되어 있는 경우 성능이 좋음

	// 리스트가 비어 있거나 노드가 하나인 경우
	if (head == nullptr || head->next == nullptr)
	{
		return;
	}

	Node* current = head; // 정렬된 리스트의 끝 노드
	Node* min = head->next; // 정렬되지 않은 리스트의 시작 노드
	current->next = nullptr; // 정렬된 리스트의 끝을 명시

	for (int i = 0; i < count - 1 /* && current != nullptr */; i++) //while (currentNext != nullptr)
	{
		Node* nextNode = min->next; // 다음 삽입할 노드를 미리 저장
		Node* trail = nullptr; // 정렬된 리스트를 순회할 때 이전 노드

		// 1. current 노드가 들어갈 위치 찾기
		Node* temp = current;

		while (temp != nullptr && temp->data < min->data)
		{
			trail = temp;
			temp = temp->next;
		}

		// 2. current 노드를 정렬된 리스트에 삽입
		// 2-1. current 노드가 sorted 리스트의 맨 앞에 삽입될 경우
		if (trail == nullptr)
		{
			min->next = current;
			head = min; // head 업데이트
			current = min;
		}
		// 2-2. current 노드가 중간 또는 끝에 삽입될 경우
		else
		{
			min->next = trail->next;
			trail->next = min;
		}

		// 3. 다음 노드로 이동
		min = nextNode;
	}
}