#include "RedBlackTree.h"

#include "Node.h"
#include "SafeDelete.h"

Node* RedBlackTree::nil = nullptr;

RedBlackTree::RedBlackTree()
{
	if (!nil)
	{
		nil = new Node(0, Color::Black);
	}

	root = nil;
}

RedBlackTree::~RedBlackTree()
{
	// TODO: 재귀적으로 모든 노드를 삭제하는 함수 작성 후 호출

	SafeDelete(nil);
}

bool RedBlackTree::Find(int data, Node*& outNode)
{
	// 트리가 비어있는지 확인
	if (root == nil)
	{
		return false;
	}

	// 재귀적으로 검색 진행
	return FindRecursive(data, root, outNode);
}

bool RedBlackTree::Insert(int data)
{
	// 삽입규칙
	/*
	* - 새로운 노드는 항생 레드
	* - 삽입 후 부모가 블랙이면 그대로 유지
	* - 부모가 레드인 경우(규칙 4번 위배) 재조정
	*	- 부모의 형제(삼촌)색에 따라 세가지 해결 유형(Case 1~3)으로 나뉨
	*/

	// 1. 중복 값 탐색
	Node* node = nullptr;
	if (Find(data, node))
	{
		std::cout << "ERROR: 이미 같은 값이 있음\n";
		return false;
	}

	// 2. 삽입 처리

	// 1) 트리가 비어있는 경우
	if (root == nullptr)
	{
		// 2번 규칙. 루트는 검은색
		root = CreatNode(data, Color::Black);
		return true;
	}

	// 2) 트리가 비어있지 않는 경우

	// 재귀적으로 삽입 위치 검색 및 삽입
	Node* newNode = CreatNode(data, Color::Red);
	InsertRecursive(root, newNode);

	// 3. 삽입 후 Recoloring
	RestructureAfterInsert(newNode);

	return true;
}

Node* RedBlackTree::CreatNode(int data, Color color)
{
	Node* newNode = new Node(data, color);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	return newNode;
}

bool RedBlackTree::FindRecursive(int data, Node* node, Node*& outNode)
{
	// 1. 탈출 조건
	// 1) 값이 존재하지 않음
	if (node == nil)
	{
		outNode = nullptr;
		return false;
	}
	// 2) 찾음
	if (node->GetData() == data)
	{
		outNode = node;
		return true;
	}

	// 2. 재귀 탐색 진행
	// 1) 값이 현재 노드값 보다 작은 경우
	if (node->GetData() > data)
	{
		return FindRecursive(data, node->GetLeft(), outNode);
	}
	// 2) 큰 경우
	return FindRecursive(data, node->GetRight(), outNode);
}

void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
	// 작으면 왼쪽 하위 트리로
	if (node->GetData() > newNode->GetData())
	{
		// 1) 하위 자손이 없는 경우
		if (node->GetLeft() == nil)
		{
			node->SetLeft(newNode); // 노드의 왼쪽 자손으로 새노드 설정
			newNode->SetParent(node); // 새노드의 부모를 현재 노드로
			return;
		}
		// 2) 하위 자손이 있는경우 재귀적으로 더 진행
		InsertRecursive(node->GetLeft(), newNode);
	}
	// 크면 오른쪽 하위 트리로
	else // if (node->GetData() < newNode->GetData())
	{
		// 1) 하위 자손이 없는 경우
		if (node->GetRight() == nil)
		{
			node->SetRight(newNode); // 노드의 오른쪽쪽 자손으로 새노드 설정
			newNode->SetParent(node); // 새노드의 부모를 현재 노드로
			return;
		}
		// 2) 하위 자손이 있는경우 재귀적으로 더 진행
		InsertRecursive(node->GetRight(), newNode);
	}
}

void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
	// Recoloring 규칙
	/*
	* - 트리 구조가 규칙 4(빨간색의 자손이 검은색이 되도록)을 지키도록 정렬
	* - 자식 노드와 부모 노드가 RED인 경우(Red-Red Conflict), 부모의 형제(삼촌) 노드에 따라 3가지 경우로 나눠 처리
	*
	*	Case 1.
	*	- 상황: 부모와 삼촌이 RED
	*	- 해결:
	*		[1] 부모와 삼촌을 BLACK
	*		[2] 조부모를 RED로 변경
	*		[3] 조부모를 기준으로 재검사
	*
	*	Case 2.
	*	- 상황: 부모는 RED 삼촌이 BLACK(또는 NIL), 조부모까지 경로가 지그재그 형태
	*	- 해결:
	*		[1] 부모를 기준으로 좌/우 회전(일직선으로 만듦)
	*		[2] Case3 으로 진행
	*
	*	Case 3.
	*	- 상황: 부모는 RED 삼촌은 BLACK(또는 NIL), 조부모까지 경로가 일직선 형태
	*	- 해결:
	*		[1] 부모를 BLACK
	*		[2] 조부모를 RED로 변경
	*		[3] 조부모를 기준으로 회전
	*/

	// 부모 노드가 빨간색인 경우(Red-Red Conflict)
	while (newNode != root && newNode->GetParent()->GetColor() == Color::Red)
	{
		Node* parent = newNode->GetParent();
		Node* grandParent = newNode->GetParent()->GetParent();
		Node* uncle = (parent == grandParent->GetLeft()) ? grandParent->GetRight() : grandParent->GetLeft();

		// Case1.
		// 부모가 RED, 삼촌도 RED
		if (uncle->GetColor() == Color::Red)
		{
			// [1] 부모와 삼촌을 BLACK
			parent->SetColor(Color::Black);
			uncle->SetColor(Color::Black);

			// [2] 조부모를 RED로 변경
			grandParent->SetColor(Color::Red);

			// [3] 조부모를 기준으로 재검사
			newNode = grandParent;

			continue;
		}

		// Case2.
		// 부모는 RED 삼촌이 BLACK(또는 NIL), 조부모까지 경로가 지그재그 형태

		// [1] 부모를 기준으로 좌/우 회전(일직선으로 만듦)
		if (true/* TODO: 어떻케든 검사*/)
		{
			// TODO : 회전
		}
		
		// Case3.
		// 부모는 RED 삼촌은 BLACK(또는 NIL), 조부모까지 경로가 일직선 형태
		
		// [1] 부모를 BLACK
		parent->SetColor(Color::Black);

		// [2] 조부모를 RED로 변경
		grandParent->SetColor(Color::Red);

		// [3] 조부모를 기준으로 회전
		// TODO: 조부모 기준 회전
	}
}

void RedBlackTree::RotateToLeft(Node* node)
{
	// 1. (부모가 될) 자손 노드
	Node* right = node->GetRight();

	//2. 현재 node 와 자식의 관계 변경
	// 오른쪽 자손의 왼쪽 자손 노드를 부모의 오른쪽 자손으로 등록
	// 이진 탐색 트리의 특징으로 오른쪽 자손의 모든 자손은 부모보다 큼
	node->SetRight(right->GetLeft());

	// 부모 정리
	if (right->GetLeft() != nil)
	{
		right->GetLeft()->SetParent(node);
	}

	// 3. 최상위 부모 노드 연결
	// 1) root 인 경우
	if (right->GetParent() == root)
	{
		// root 변경
		root = right;
		right->SetParent(nullptr);
	}
	// 2) root 아님
	else
	{
		if (node == node->GetParent()->GetLeft())
		{
			node->GetParent()->SetLeft(right);
		}
		else
		{
			node->GetParent()->SetRight(right);
		}
	}

	// 오른쪽 자손의 왼쪽 자손으로 부모 노드 등록
	right->SetLeft(node);

	// 조부모를 오른쪽 자손으로
	right->SetParent(node->GetParent());

	// 조부모 오른쪽 자손으로
	node->SetParent(right);
}

void RedBlackTree::RotateToRight(Node* node)
{
}
