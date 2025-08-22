#include "RedBlackTree.h"

#include "Node.h"
#include "SafeDelete.h"

RedBlackTree::RedBlackTree()
	: nil{ new Node(0, Color::Black) }
	//, root{ nullptr }
{
	root = nil;
}

RedBlackTree::~RedBlackTree()
{
	DestroyRecursive(root);

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
	* - 새로운 노드는 항상 RED
	* - 삽입 후 부모가 BLACK일 경우: 그대로 유지
	* - 부모가 RED인 경우(규칙 4번 위배): 재조정
	*- 부모의 형제(삼촌)색에 따라 세가지 해결 유형(Case 1~3)으로 나뉨
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
	if (root == nil)
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

void RedBlackTree::Print(int depth, int blackCount)
{
	PrintRecursive(root, depth, blackCount);
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
	*	1) 상황: 부모와 삼촌이 RED
	*	2) 해결:
	*		[1] 부모와 삼촌을 BLACK
	*		[2] 조부모를 RED로 변경
	*		[3] 조부모를 기준으로 재검사
	*+		parent	0x0000000000000000 <NULL>	Node *

	*	Case 2.
	*	1) 상황: 부모는 RED 삼촌이 BLACK(또는 NIL), 조부모까지 경로가 지그재그 형태
	*	2) 해결:
	*		[1] 부모를 기준으로 좌/우 회전(일직선으로 만듦)
	*		[2] Case3 으로 진행
	*
	*	Case 3.
	*	1) 상황: 부모는 RED 삼촌은 BLACK(또는 NIL), 조부모까지 경로가 일직선 형태
	*	2) 해결:
	*		[1] 부모를 BLACK
	*		[2] 조부모를 RED로 변경
	*		[3] 조부모를 기준으로 회전
	*/

	// 부모 노드가 빨간색인 경우(Red-Red Conflict)
	while (newNode != root && newNode->GetParent()->GetColor() == Color::Red)
	{
		Node* parent = newNode->GetParent();
		Node* grandParent = newNode->GetParent()->GetParent();

		bool isParentRight = (parent == grandParent->GetRight());
		Node* uncle = (isParentRight) ? grandParent->GetLeft() : grandParent->GetRight();

		//
		// Case1.
		// 부모가 RED, 삼촌도 RED
		/*
		* befor)
		*		 B
		*		/ \
		*	   R   R
		*	  /
		*	 R(new)
		*
		* after)
		*		 R
		*		/ \
		*	   B   B
		*	  /
		*	 R(new)
		*/
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

		//
		// Case2.
		// 삼촌이 BLACK(또는 NIL), 조부모까지 경로가 지그재그 형태
		/*
		* ex) 부모를 기준으로 왼쪽 회전
		*		 B					 B
		*		/ \					/ \
		*	   R   B	 ->	  (new)R   B
		*		\				  /
		*		 R(new)			 R
		*
		*/
		bool isNodeRight = (newNode == parent->GetRight());
		if (isNodeRight != isParentRight) // 지그제그인 경우
		{
			// [1] 부모를 기준으로 좌/우 회전(일직선으로 만듦)

			// 가족 관계 재설정
			if (isParentRight)
			{
				// 부모 기준 우회전
				RotateToRight(parent);
			}
			else
			{
				// 부모 기준 우회전
				RotateToLeft(parent);
			}

			newNode = parent;
			parent = newNode->GetParent();
		}

		//
		// Case3.
		// 부모는 RED 삼촌은 BLACK(또는 NIL), 조부모까지 경로가 일직선 형태
		/*
		* 1)
		*		 B
		*		/ \
		*	   R   B
		*	  /
		*	 R
		*
		* 2)
		*		 B
		*		/ \
		*	   B   B
		*			\
		*			 R
		*/
		// [1] 부모를 BLACK
		parent->SetColor(Color::Black);

		// [2] 조부모를 RED로 변경
		grandParent->SetColor(Color::Red);

		// [3] 조부모를 기준으로 회전
		// 트리의 균형을 맞추는 동작
		if (isParentRight)
		{
			// 조부모 기준 우회전
			RotateToLeft(grandParent);
		}
		else
		{
			// 조부모 기준 좌회전
			RotateToRight(grandParent);
		}

	} // while END

	root->SetColor(Color::Black);
}

void RedBlackTree::RotateToLeft(Node* node)
{
	/*
	* befor)
	*	X
	*	 \
	*	  Y
	*	 / \
	*	A   B
	*
	* after)
	*	  Y
	*	 / \
	*	X   B
	*	 \
	*	  A
	*/

	// 1. (부모가 될) 자손 노드의 자식 노드 정리
	/*
	*	  Y	    X
	*	 /	->	 \
	*	A		  A
	*/
	
	// Y (오른쪽 자식)
	Node* right = node->GetRight();

	// 1. Y의 왼쪽 자식(A)을 X(부모)의 오른쪽 자식으로 연결
	node->SetRight(right->GetLeft());
	if (right->GetLeft() != nil)
	{
		right->GetLeft()->SetParent(node);
	}

	// 2. Y의 부모를 X의 부모(조부모)로
	Node* grandParent = node->GetParent();
	right->SetParent(grandParent);

	// 1) 조부모가 없음 (원래 부모가 root 인 경우)
	if (grandParent == nullptr)
	{
		// root 변경
		root = right;
	}
	// 2) 조부모가 있음
	else
	{
		// X가 부모의 왼쪽 자식이었으면, Y를 부모의 왼쪽 자식으로
		if (node == node->GetParent()->GetLeft())
		{
			node->GetParent()->SetLeft(right);
		}
		// X가 부모의 오른쪽 자식이었으면, Y를 부모의 오른쪽 자식으로
		else
		{
			node->GetParent()->SetRight(right);
		}
	}

	// 3. Y를 X의 부모로, X를 Y의 왼쪽 자식으로 연결

	// 원래 부모를 왼쪽 자손으로
	right->SetLeft(node);

	// 원래 부모의 부모 재설정
	node->SetParent(right);
}

void RedBlackTree::RotateToRight(Node* node)
{
	/*
	* befor)
	*		X
	*	   /
	*	  Y
	*	 / \
	*	A   B
	*
	* after)
	*	  Y
	*	 / \
	*	A   X
	*	   /
	*	  B
	*/

	// 1. (부모가 될) 자손 노드의 자식 노드 정리
	/*
	*  Y			X
	*   \	->	   /
	*	 B		  B
	*/

	// Y (왼쪽 자식)
	Node* left = node->GetLeft();

	// 1. Y의 오른쪽 자식(B)을 X(부모)의 왼쪽 자식으로 연결
	node->SetLeft(left->GetRight());
	if (left->GetRight() != nil)
	{
		left->GetRight()->SetParent(node);
	}

	// 2. Y의 부모를 X의 부모와 연결
	Node* grandParent = node->GetParent();
	left->SetParent(grandParent);

	// 1) 조부모가 없음 (원래 부모가 root 인 경우)
	if (grandParent == nullptr)
	{
		// root 변경
		root = left;
	}
	// 2) 조부모가 있음
	else
	{
		// X가 부모의 왼쪽 자식이었으면, Y를 부모의 왼쪽 자식으로
		if (node == node->GetParent()->GetLeft())
		{
			node->GetParent()->SetLeft(left);
		}
		// X가 부모의 오른쪽 자식이었으면, Y를 부모의 오른쪽 자식으로
		else
		{
			node->GetParent()->SetRight(left);
		}
	}

	// 3. Y를 X의 부모로, X를 Y의 오른쪽 자식으로 연결

	// 원래 부모를 오른쪽 자손으로
	left->SetRight(node);

	// 원래 부모의 부모 재설정
	node->SetParent(left);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// 탈출 조건.
	if (node == nil)
	{
		return;
	}

	// 노드 색상이 검정이면 blackCount 증가.
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// 부모 표기 문자열 설정.
	int parentData = 0;
	const char* position = "Root";

	// 부모 노드가 있는지 확인.
	if (node->GetParent())
	{
		// 부모 노드의 데이터 저장.
		parentData = node->GetParent()->GetData();

		// 부모 노드로부터 현재 노드의 위치 설정.
		if (node == node->GetParent()->GetLeft())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// 검은색 수 출력을 위한 문자열.
	char blackCountString[50] = { };

	// 자손이 없으면 현재까지의 검은색 노드 수 설정.
	if (node->GetLeft() == nil && node->GetRight() == nil)
	{
		sprintf_s(blackCountString, "------ %d", blackCount);
	}

	// Depth 출력.
	for (int ix = 0; ix < depth; ++ix)
	{
		std::cout << "  ";
	}

	// 노드 색상에 따른 콘솔 설정.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// 현재 노드 값 출력.
	std::cout
		<< node->GetData() << " "
		<< node->GetColorString() << " ["
		<< position << ", "
		<< parentData << "] "
		<< blackCountString << "\n";

	// 노드를 출력한 뒤에는 콘솔 원래대로.
	SetTextColor(TextColor::White);

	// 하위 노드 출력.
	PrintRecursive(node->GetLeft(), depth + 1, blackCount);
	PrintRecursive(node->GetRight(), depth + 1, blackCount);
}

void RedBlackTree::DestroyRecursive(Node* node)
{
	// 재귀 탈출 조건.
	if (node == nil)
	{
		return;
	}

	// 자식이 있는 경우.
	DestroyRecursive(node->GetLeft());
	DestroyRecursive(node->GetRight());

	// 노드 삭제.
	SafeDelete(node);
}

void SetTextColor(TextColor color)
{
	// 콘솔 색상 설정.
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}